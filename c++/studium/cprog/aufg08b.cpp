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

int main(void)
{
  int i;
  long anztage, anzueber, betrag;

  float faktor = 1.95583;
  double schulden = 100000.0 / faktor;

  float feuro;
  double deuro;
  double differenz, getilgt, prozent;

  printf("\nGesamtschulden :  100000 DM");
  printf("\n===========================");
  printf("\n\nBitte geben Sie die Höchstlaufzeit der Überweisungsaufträge in Tagen ein : ");
  scanf("%ld",&anztage);
  printf("Bitte geben Sie die Anzahl der täglichen Überweisungsaufträge ein : ");
  scanf("%ld",&anzueber);
  printf("Bitte geben Sie die den Überweisungsbetrag in DM ein : ");
  scanf("%ld",&betrag);

  feuro = (float) betrag / (float) faktor;
  deuro = (double) betrag / (double) faktor;

  differenz = ((double) feuro) - deuro;

  if (differenz<0)
    differenz = differenz * (-1.0);

  differenz = differenz * ((double) anzueber);

  for (i=1; i<=anztage; i++)
    {
      getilgt = differenz * ((double) i);

      if (getilgt >= schulden)
	{
	  printf("\nDie Schulden wären nach %d Tag(en) getilgt !",i);
	  break;
	}
    }

  if (getilgt < schulden)
    {
      prozent = (getilgt / schulden) * 100.0;
      printf("\nNach %ld Tagen, wären gerademal %.2f Prozent der Schulden getilgt !",anztage,prozent);
    }

  return 0;
  }