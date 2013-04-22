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
    Teilaufgabe   	: a)

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

char string[111];
char such[21];

char url1[]="http://www.fireball.de/query-fireball.fcg?action=query&pg=express&q=";
char url2[]="&what=";
char url3[]="&fmt=d";

char *ort="german_web";

char test;

int main(void)
{
  printf("Bitte geben Sie den Suchbegriff ein : ");
  scanf("%s",&such);

  printf("\nDeutschlandweite oder Weltweite Suche (d oder w) : ");
  scanf(" %c",&test);

  if (test=='w')
    ort="web";

  strcat(string,url1);
  strcat(string,such);
  strcat(string,url2);
  strcat(string,ort);
  strcat(string,url3);

  printf("\n\n%s",string);

  return 0;
}
     