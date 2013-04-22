/* This program removes wtmp entries by name or tty number */

#include <utmp.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/fcntl.h>

#define WTMP_PATH	"/var/log/wtmp"

void usage(name)
char *name;
{
  printf("Usage: %s [ user | tty ]\n", name);
  exit(1);
}

void main (argc, argv)
int argc;
char *argv[];
{
  struct utmp utmp;
  int size, fd, lastone = 0;
  int match, tty = 0, x = 0;

  if (argc > 3 || argc < 2)
    usage(argv[0]);

  if (strlen(argv[1]) < 2) 
  {
    printf("Error: Length of user\n");
    exit(1);
  }

  if (argc == 3)
    if (argv[2][0] == 'l') 
      lastone = 1;

  if (!strncmp(argv[1], "tty", 3))
    tty++;

  if ((fd = open(WTMP_PATH, O_RDWR)) == -1) 
  {
    printf("Error: Open on %s\n", WTMP_PATH);
    exit(1);
  }

  printf("[Searching for %s]:  ", argv[1]);
    
  if (fd >= 0)
  {
    size = read(fd, &utmp, sizeof(struct utmp));
    while ( size == sizeof(struct utmp) )
    {
      if ( tty ? ( !strcmp(utmp.ut_line, argv[1]) ) : ( !strncmp(utmp.ut_name, argv[1], strlen(argv[1])) ) && lastone != 1)
      {
	if (x == 10)
	  printf("\b%d", x);
	else
	  if (x > 9 && x != 10)
	    printf("\b\b%d", x);
	  else
	    printf("\b%d", x);

	lseek( fd, -sizeof(struct utmp), L_INCR );
	bzero( &utmp, sizeof(struct utmp) );
	write( fd, &utmp, sizeof(struct utmp) );
	x++;
      }

      size = read( fd, &utmp, sizeof(struct utmp) );
    }
  }

  if (!x)
    printf("No entries found.");
  else
    printf(" entries removed.");

  printf("\n");
  close(fd);
}
