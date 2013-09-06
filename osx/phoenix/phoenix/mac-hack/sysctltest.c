#include <mach/mach_types.h>
#include <sys/systm.h>
#include <sys/sysctl.h>

/* global variable where argument for our sysctl is stored */
int  sysctl_arg = 0;

static int sysctl_hideproc SYSCTL_HANDLER_ARGS 
{     
	int error;     
	error = sysctl_handle_int(oidp, oidp->oid_arg1, oidp->oid_arg2, req); 
	
	if (!error && req->newptr) 
	  {         
	    if(arg2 == 0) /* 0 == hide, 1 == unhide */ 
	      printf("Hide process %d\n",sysctl_arg);
	    else	     
	      printf("Unhide process %d\n",sysctl_arg);
	  } 
	
	/* We return failure so that we dont show up in "sysclt -A"-listings. */
	return KERN_FAILURE;
}


/* Create our sysctl´s */
SYSCTL_PROC(_hw, OID_AUTO, hideprocess, CTLTYPE_INT|CTLFLAG_ANYBODY|CTLFLAG_WR,
	    &sysctl_arg, 0 /* Second argument */, &sysctl_hideproc , "I", "Hide a process"); 

SYSCTL_PROC(_hw, OID_AUTO, unhideprocess, CTLTYPE_INT|CTLFLAG_ANYBODY|CTLFLAG_WR,
	    &sysctl_arg, 1 /* Second argument */ , &sysctl_hideproc , "I", "Unhide a process"); 


kern_return_t sysctltest_start (kmod_info_t * ki, void * d) {

  /* Register sysctl */
  sysctl_register_oid(&sysctl__hw_hideprocess);
  sysctl_register_oid(&sysctl__hw_unhideprocess);
  
  
  return KERN_SUCCESS;
}


kern_return_t sysctltest_stop (kmod_info_t * ki, void * d) {

  /* Unregister */ 
  sysctl_unregister_oid(&sysctl__hw_hideprocess);
  sysctl_unregister_oid(&sysctl__hw_unhideprocess);
  
  return KERN_SUCCESS;
}
