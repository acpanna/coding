/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 03
    Aufgabennr.   	: 09
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
#include <math.h>

int main(void)
{
  int i;
  double h;
  double ergebnis, differenz;

  printf("\nWert von i   exp(1 + h) - exp(1)) / h       Fehler:");
  printf("\n===================================================\n");

  for (i=1; i<=22; i++)
    {
      h = pow(10,-i);   

      ergebnis = (exp(1 + h) - exp(1)) / h;

      differenz = ergebnis - exp(1);

      if (differenz<0)
        differenz = differenz * (-1.0);

      printf(" i = %d\t:  \t%.15f  ",i,ergebnis);
      printf(" \t%.15f\n",differenz);

    }
  return 0;
}

