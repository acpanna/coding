/*
========================================================================


    Vorname       : Heiko
    Name          : Vogel
    Matrikelnummer: 0854794
    Uebungsgruppe : mittwochs

    Benutzernummer: c06
    e-mail-Adresse: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     : 
    Aufgabennr.   : 
    Teilaufgabe   : 

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
#include <math.h>

char *frage[3]={ "die gefahrenen Kilometer",
		 "den durchschnittlichen Benzinverbrauch",
		 "den Benzinpreis in DM" };

float antwort[3];

float kosten, benzinverbrauch;

int i;

int main(void)
{
  printf("\nProgramm zur Berechnung:\n");
  printf("\na) des durchschnittlichen Benzinverbrauchs auf 100 km und");
  printf("\nb) der Kosten pro gefahrenen Kilometer\n");

  for(i=0 ; i<3; i++)
  {
    printf("\nBitte geben Sie ");
    puts(frage[i]);
    printf("ein : ");
    scanf("%f",&antwort[i]);
  }

  benzinverbrauch = antwort[1] / (antwort[0] / 100);
  kosten = (benzinverbrauch / 100) * antwort[2];

  printf("\n  zu a) %f Liter auf 100km",benzinverbrauch);
  printf("\n  zu b) %f DM pro km",kosten);
  
  return 0;
}

/*
------------------------------------------------------------------------

        Beantwortung der Fragen:

Fragen: a)Was meldet der Compiler, wenn Sie sich beim Funktionsaufruf "printf()"
	oder beim Namen des Ausgabeobjekts "cout" vertippen?

	b)Was meldet der Compiler, wenn Sie die Variablen versehentlich vom Daten-
	typ "real" anstatt des Datentyps "float" anlegen?

	c)Erhalten Sie zusätzliche Informationen durch eine Fehlernummer oder eine
	Zeilennummer?

Antworten: a) z.B. print statt printf
	      Fehlermeldung:  Call to function 'print' with no prototype
		      (Aufruf der Funktion print ohne vorherige Deklaration)

	   b) Fehlermeldung: Declaration Syntax Error
                   (Borland Compiler kennt keinen real - Datentyp)

	   c) Es wird lediglich eine Zeilennummer ausgeben

========================================================================
*/