/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 04
    Aufgabennr.   	: 12
    Teilaufgabe   	: b)

    verwendeter
    Compiler
    m. Version    	: Borland Turbo C++ for Windows V3.1 (c) 1991,92
                        
    verwendetes
    Betriebssystem	: Windows98

*/

/*
------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>

char string[200];

char *protokollname;
char *servername;
char *dokuadresse;

char *paraname[5];
char *parawert[5];

int main(void)
{
  int i;
  char *ptr;

  printf("Bitte geben Sie die URL - Zeile ein : ");
  scanf("%s",&string);
    
  protokollname = string;
  ptr = strchr(string,':');

  if (ptr != 0)
    {
      *ptr='\0';
       ptr = ptr+3;

       servername = ptr;
       ptr = strchr(servername,'/');

       if (ptr != 0)
         {
	   *ptr='\0';
           ptr++;

           dokuadresse = ptr;
           ptr = strchr(dokuadresse,'?');

	   for (i=0; i<5; i++)
	     {
	       if (ptr != 0)
	         {
                   *ptr='\0';
                   ptr++;

                   paraname[i] = ptr;
	           ptr = strchr(paraname[i],'=');

	           if (ptr != 0)
                     {
                       *ptr='\0';
                       ptr++;

                       parawert[i] = ptr;
                  
                       ptr = strchr(parawert[i],'&');
		     }
		 }
             }
	 }	   
    }
 
  printf("\n\nProtokollname:\t\t\t%s\nServername:\t\t\t%s\nWWW-Dokumentadresse:\t\t%s"
						  ,protokollname,servername,dokuadresse);
  for (i=0; i<5; i++)
    printf("\n%d.Parametername:\t\t%s\n%d.Parameterwert:\t\t%s",i+1,paraname[i],i+1,parawert[i]);
    
  return 0;
}
     