/*
========================================================================


    Vorname       : Heiko 
    Name          : Vogel
    Matrikelnummer: 0854794
    Uebungsgruppe : mittwochs

    Benutzernummer: c06
    e-mail-Adresse: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     : 01
    Aufgabennr.   : 01
    Teilaufgabe   : --

    verwendeter
      Compiler
      m. Version  : Borland C++ for Windows V3.1 (c)1991,92

    verwendetes
      Betriebs-
      sytem       : Windows98

*/

/*
------------------------------------------------------------------------
    C-Programm oder C-Headerfile als Textfile nach Kommentar einfuegen:
*/

#include <stdio.h>
#include <math.h>

int main (void)
{

  int i;

  printf("Dieses Programm gibt alle Quadratzahlen zu den Basen 1 bis 20 aus!");
  printf("\n\n");

  for ( i = 1 ; i < 21 ; i=i+1 )
  {
  /* for-Schleife Anfang */

    printf("Basis: %d", i);
    printf("\t");                      /* Tabulator */
    printf("Ergebnis: %d",i*i);        /* Berechnung der Quadratzahl
					  in der printf()-Funktion! */
    printf("\tASCII: %c", (char) ('A'+i));
    printf("\tpow: %f", pow(i, 2));
    printf("\n");
  }
  /* for-Schleife Ende */

  return 0;
}

/*
------------------------------------------------------------------------

        Beantwortung der Fragen:

Fragen: Was gibt das Programm in den Spalten "ASCII" bzw. "pow" aus?
        Was bewirkt das Zeichen '\t' bei der Ausgabe?

Antworten: In der Spalte "ASCII" werden die ASCII - Werte ausgegeben, die
	   entsprechenden Dezimalwerten zugeordnet sind,
	   so z.B 65   entspricht A (wird nicht ausgegeben) 
	        65+1 entspricht B
		65+2 entspricht C
		65+3 entspricht D
                usw.

	   In der Spalte "pow" wird jeweils die Qadratzahl von
	   1, 2, 3, ... und 20 in Form einer float - Zahl (Gleitkomma) ausgegeben.

	   Das '\t' ist ein Tabulator - Zeichen und hat eine
	   formatierte Ausgabe zur Folge. D.h. trifft die
	   printf() bzw. cout - Funktion auf solch ein Zeichen,
	   wird das nächstfolgende Zeichen am nächsten TABSTOP
	   ausgegeben.
        
========================================================================
*/
