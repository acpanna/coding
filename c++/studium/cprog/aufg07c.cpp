/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 03
    Aufgabennr.   	: 07
    Teilaufgabe   	: c)

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

void draw(float fzahl, double dzahl);

int main(void)
{
  float x_float;
  double x_double;

  printf("\n             Float-Ausgabe               Double-Ausgabe\n");
  
  x_float = 1.0f/8.0f;
  x_double = 1.0/8.0;

  draw(x_float, x_double);

  x_float = 1.0f/10.0f;
  x_double = 1.0/10.0;
 
  draw(x_float, x_double);

  x_float = 1.0f/3.0f;
  x_double = 1.0/3.0;

  draw(x_float, x_double);

  x_float = 1/3;
  x_double = 1/3;

  draw(x_float, x_double);

  x_float = 1.0f/3;
  x_double = 1.0/3;

  draw(x_float, x_double);

  x_float = 1.0/3.0;
  x_double = 1.0f/3.0f;

  draw(x_float, x_double);

  x_float = exp(1.0);
  x_double = exp(1.0);

  draw(x_float, x_double);
 
  printf("\n");

  return 0;
}

void draw(float fzahl, double dzahl)
{
  printf("\n     %.20e    %.20e  \n",fzahl,dzahl);
}

/*
------------------------------------------------------------------------
        
Feststellung:

Ausgabe zeigt das bei double - Variablen die Genauigkeit
höher ist, als bei float - Variablen.

Außerdem:

 Der Ausdruck 1.0f/3 ergibt eine float - Zahl mit float - Genauigkeit
 Der Ausdruck 1.0/3 ergibt eine double - Zahl mit double - Genauigkeit.

 Der Ausdruck 1.0/3.0 ergibt eine double - Zahl mit double - Genauigkeit,
 da dieser Ausdruck jedoch einer float - Variablen zugewiesen wird, wird
 er wieder in einen float - Ausdruck, also in eine Zahl mit float -
 Genauigkeit umgewandelt.
  
 Der Ausdruck 1.0f/3.0f ergibt eine float - Zahl mit float - Genauigkeit,
 da dieser Ausdruck jedoch einer double - Variablen zugewiesen wird, wird
 er wieder in einen double - Ausdruck, also in eine Zahl mit double -
 Genauigkeit umgewandelt.

 Die restlichen Ausgaben entsprachen meinen Erwartungen.

========================================================================
*/

