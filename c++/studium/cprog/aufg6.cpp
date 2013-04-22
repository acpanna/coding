/*
========================================================================


    Vorname       : Heiko
    Name          : Vogel
    Matrikelnummer: 0854794
    Uebungsgruppe : mittwochs

    Benutzernummer: c06
    e-mail-Adresse: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     : 02
    Aufgabennr.   : 06
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
#include <math.h>

int main(void)
{
  int n;

  int a[3] = {1, 1, 1};

  for (n=0; n<11; n++)
  {
    if (n!=0 & n!=1)
      {
        a[2] = a[1] + a[0];
	a[0] = a[1];
	a[1] = a[2];
      }
    printf("Fibonacci - Zahl für n = %2d  : %3d\n", n, a[2]);
    
  }

  return 0;
}

/*
------------------------------------------------------------------------

    Beantwortung der Fragen:

Fragen: 1. Wieviele Variablen brauchen Sie mindestens?
	2. Hängt die Zahl von der maximalen Iterationszahl n ab?

Antworten: 1. Es werden mind. 4 Variablen benötigt (eine Zählvariable für die
	      for - Schleife und 3 Variablen zur Speicherung der Fibonacci -
	      Zahlen a[n], a[n-1] und a[n-2]).
	   2. Die Zahl hängt nicht von der maximalen Iterationszahl n
	      ab (vgl. Programmcode) !
              
========================================================================
*/

  