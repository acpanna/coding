/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 06
    Aufgabennr.   	: 17
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
#include <math.h>

int check(char *eingabe);
                                  
int main(void)
{
  
  int ergebnis;
  char einlesen[9];

  printf("\nBitte geben Sie eine 8-stellige Dualzahl ein : ");
  scanf("%8s",einlesen);

  printf("\n");

  ergebnis = check(einlesen);

  printf("\n\nDie entsprechende Dezimalzahl ist : %d",ergebnis);

  return 0;
}                   


int check(char *eingabe)
{
  int i, zaehler = 0;
  
  for (i=0; i <=7 ; i++)
    {
      if (eingabe[i] == '\0')
	break;

      if (eingabe[i] == '1')
        zaehler = zaehler + pow(2, 7 - i);
    }

  return zaehler;

}