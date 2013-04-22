/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 03
    Aufgabennr.   	: 08
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

int main(void)
{
  float faktor = 1.95583;
  float schulden;

  float feuro;
  double deuro;
  double differenz;

  printf("\nBitte geben Sie den Schuldenberg in DM ein : ");
  scanf("%f",&schulden);

  feuro = schulden / faktor;
  deuro = (double) schulden / (double) faktor;

  differenz = deuro - ((double) feuro);

  if (differenz<0)
     differenz = differenz * (-1.0); 

  printf("\n%.6f Euros (in float - Darstellung)\n",feuro);
  printf("%.18f Euros (in double - Darstellung)\n",deuro);

  printf("\nUnterschied : %.18f Euros (in double - Darstellung)",differenz);

  return 0;
}
