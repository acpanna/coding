/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 07
    Aufgabennr.   	: 20
    Teilaufgabe   	: --

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

int main(void)
{
  int i;
  int jahr, anzahl;
  int hasealt2 = 0, hasealt1 = 1, haseneu = 1;

  printf("\nBitte geben Sie die Anzahl der Jahre ein: ");
  scanf("%d",&jahr);
  printf("Bitte geben Sie die Anzahl der Hasen ein: ");
  scanf("%d",&anzahl);

  for (i=1 ; i<=jahr ; i++)
  {
    haseneu = hasealt1 + 2 * hasealt2;
    hasealt2 = hasealt1;
    hasealt1 = haseneu;
  }
 
  printf("\n\nNach %d Jahren ist/sind %d Hase(n) vorhanden !",jahr,haseneu);

  haseneu = 1;
  hasealt1 = 1;
  hasealt2 = 0;
  jahr = 0;

  while (anzahl > haseneu)
  {
    haseneu = hasealt1 + 2 * hasealt2;
    hasealt2 = hasealt1;
    hasealt1 = haseneu;
    jahr = jahr + 1;
  }

  printf("\n\nEr muß minimal %d Jahr(e) züchten um mindestens %d Hase(n) zu besitzen !",jahr,anzahl);

  if (haseneu > anzahl)
    jahr = jahr - 1;
                    
  printf("\n\nEr darf maximal %d Jahr(e) züchten um höchstens %d Hase(n) zu besitzen !",jahr,anzahl);
  
  return 0;
}
