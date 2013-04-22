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

#include <iostream.h>
#include <math.h>

int main (void)
{

  int i;

  cout << "Dieses Programm gibt alle Quadratzahlen zu den Basen 1 bis 20 aus!";
  cout << "\n\n";

  for ( i = 20 ; i > 0 ; i=i-1 )              /* Veränderte for-Schleife */
  {
  /* for-Schleife Anfang */

    cout << "Basis: " << i;
    cout << "\t";                             /* Tabulator */
    cout << "Ergebnis: " << i*i;              /* Berechnung der Quadratzahl
					      in der printf()-Funktion! */
    cout << "\tASCII: " << (char) ('A'+i);
    cout << "\tpow: " << pow(i, 2);
    cout << "\n";
  }
  /* for-Schleife Ende */

  return 0;
}

/*
------------------------------------------------------------------------

        Beantwortung der Fragen:

Fragen: Erkennt der Compiler die Vorgaben des C++ - Standards an oder beharrt
	er noch auf veralten Konventionen zum Einbinden von Headerfiles?
	Wie muß man das Programm ändern, damit es zuerst die Quadratzahl von 20,
	dann die von 19,... und dann die 1 ausgibt?

Antworten: Leider beharrt der Borland C++ Compiler noch auf veralten Konventionen,
	   d.h. z.B. nicht <iostream> sondern <iostream.h>.

	   Es muß lediglich der Zählvariablen i zu anfangs der Wert 20 zugewiesen
	   werden und von diesem dann bis zur 1 heruntergezählt werden, dies geschieht
	   durch die Anweisung i=i-1. Das schließlich nur bis zur 1 heruntergezählt wird,
	   ist bedingt durch i>0, d.h. für i=1 wird die Schleife noch durchlaufen,
           jedoch nicht mehr für i=0.

========================================================================
*/
