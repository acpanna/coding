/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 06
    Aufgabennr.   	: 16
    Teilaufgabe   	: a) - d)

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

  unsigned short einlesen, linksresultat, rechtsresultat;
  unsigned char zuweisen, links, rechts;

  char zuweisen2, links2, rechts2;


  printf("\nBitte geben Sie eine vorzeichenlose Short - Zahl ein : ");
  scanf("%hu",&einlesen);

  zuweisen = (unsigned char) einlesen;

  links  = zuweisen << 1;
  rechts = zuweisen >> 1;

  linksresultat  = (unsigned short) links;
  rechtsresultat = (unsigned short) rechts;

  printf("\n\nErgebnis (für unsigned char):\n\nLinksshift = %hu, Rechtsshift = %hu",linksresultat, rechtsresultat);

  zuweisen2 = (char) einlesen;

  links2  = zuweisen2 << 1;
  rechts2 = zuweisen2 >> 1;

  linksresultat  = (unsigned short) links2;
  rechtsresultat = (unsigned short) rechts2;

  printf("\n\n\nErgebnis (für signed char):\n\nLinksshift = %hu, Rechtsshift = %hu",linksresultat, rechtsresultat);

  return 0;
}

/*
------------------------------------------------------------------------

    Beantwortung der Fragen:

zu a) Ja, bei vorzeichenbehafteten Werten liefert der Linksshift 65408,
	  bei vorzeichenlosen Werten liefert der Linksshift 128.

      Begründung:                   01000000 entspricht 64
		   Linksshift  -->  10000000 entspricht 128 als vorzeichenlose
					     bzw. -128 als vorzeichenbehaftete Zahl.

		   Bei der Umwandlung in unsigned short geschieht bei 128 nichts
		   weltbewegendes, wohl aber bei -128.
		   Denn -128 entspricht als unsigned short - Zahl, gerade der Zahl 0 - 128.
		   "Vor" der Null kommt aber bei unsigned short 65535, also erhält man als
		   Ergebnis der Zuweisung: 65408 ( = 65535 - 127 )

zu b) Als vorzeichenbehafteter Wert erhält man 65472 beim Rechtshift und als
	  vorzeichenloser Wert 64.

      Begründung:                  10000000 entspricht 128 als vorzeichenlose Zahl
		   Rechtsshift --> 01000000 entspricht 64 als vorzeichenlose Zahl

				   10000000 entspricht -128 als vorz.beh. Zahl
		   Rechtsshift --> 11000000 entspricht -64 als vorz.beh. Zahl
                                  (bei vorzeichenbeh. Zahlen wird 1 nachgeschoben)

                   Bei der Umwandlung in unsigned short geschieht bei 64 wiederum
		   nichts großartiges, wohl aber bei -64.
		   Denn -64 entspricht als unsigned short - Zahl, gerade der Zahl 0 - 64.
		   "Vor" der Null kommt aber bei unsigned short 65535, also erhält man als
		   Ergebnis der Zuweisung: 65472 ( = 65535 - 63 )

zu c) Shift nach links ist vergleichbar mit einer Verdopplung der Zahl,
      während Shift nach rechts einer Halbierung entspricht, wobei evt.
      sich ergebende Nachkommastellen abgeschnitten werden.

zu d) Die beiden Ausgaben liefern unterschiedliches Ergebnis, weil:

      Im 1. Fall wird 64 << 1 ( = 10000000) einer vorzeichenbehafteten Variable
      zugewiesen, deshalb entspricht das Resultat des Linksshifts -128.

      Im 2.Fall wird 64 << 1 direkt ausgegeben, hierbei wird der aus 64 << 1
      resultierende Wert als vorzeichenlos behandelt und somit erfolgt als
      Ausgabe 128.  
                   
========================================================================
*/
