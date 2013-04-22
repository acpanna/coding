/*
========================================================================


    Vorname       : Heiko
    Name          : Vogel
    Matrikelnummer: 0854794
    Uebungsgruppe : mittwochs

    Benutzernummer: c06
    e-mail-Adresse: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     : 02
    Aufgabennr.   : 04
    Teilaufgabe   : --

    verwendeter
      Compiler
      m. Version  : Borland Turbo C++ for Windows V3.1 (c) 1991,92
                        
    verwendetes
      Betriebs-
      sytem       : Windows98

*/

/*
------------------------------------------------------------------------
*/

#include <stdio.h>

int main(void)
{
  float fahr, faktor, celsius;
  int unten=0, oben=300, schritt=20;
    
  for (fahr = 0; fahr <= oben; fahr = fahr + schritt)
  {
    // Fahrenheit in Celsius umrechnen
    faktor = 0.5555;
    celsius = faktor * (fahr-32);
    printf("%3.0f %6.1f\n", fahr, celsius);
  }

  return 0;
}

/*
------------------------------------------------------------------------

    Beantwortung der Fragen:

Frage: Welche Fehler enth�lt das Programm?

Antwort: 1. Zeile: fehlerhafte include - Anweisung [fehlendes Kreuz (#),
		   Header-Datei mu� in spitzen Klammern stehen, Strichpunkt
		   mu� weg]
	 3. Zeile: Funktionskopf f�r main() enth�lt keine Information �ber
		   einen eventuellen R�ckgabewert bzw. �ber die Anzahl der
		   Argumente.
	 6. Zeile: Die zu deklarierenden Integer - Variablen m�ssen mit Kommas
		   voneinander getrennt werden.
	12. Zeile: (for - Schleife) "step" mu� "schritt" hei�en, au�erdem mu� der
		   Strichpunkt weg.
	15. Zeile: 5/9 ist unendlicher Dezimalbruch und kann nicht in dieser Form
		   in einer endlichen float - Variable abgespeichert werden, deshalb
		   Speicherung von 5/9 als endliche N�herungszahl (z.B. 0.5555).

		   (Zeilenangaben beziehen sich auf die Urfassung des Programms !)

	       Schlie�lich fehlt noch die "return 0;" - Anweisung, vor dem Blockende
	                  	   der main() - Funktion !


Verbesserungsvorschl�ge:   Die Deklaration und Initialisierung der INT - Variablen
			              sollte in einer Zeile erfolgen.
                                                                          
========================================================================
*/
