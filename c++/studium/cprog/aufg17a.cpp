/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 06
    Aufgabennr.   	: 17
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

void check(unsigned char eingabe, int wert);
                                  
int main(void)
{

  unsigned char einlesen;

  printf("\nBitte geben Sie einen vorzeichenlosen Bytewert ein : ");
  scanf("%d",&einlesen);

  printf("\n");

  check(einlesen,128);
  check(einlesen,64);
  check(einlesen,32);
  check(einlesen,16);
  check(einlesen,8);
  check(einlesen,4);
  check(einlesen,2);
  check(einlesen,1);

  return 0;
}                   


void check(unsigned char eingabe, int wert)
{
  if((eingabe & wert) == wert)
    printf(" 1");
  else
    printf(" 0");
}

/*
------------------------------------------------------------------------

    Beantwortung der Fragen:

Zum Testen einzelner Bits eignet sich der & Operator verknüpft mit den Potenzen von 2,
denn z.B. 1 entspricht 00000001
          2            00000010
	  4            00000100
	  8            00001000
	  ...


Das heißt der Ausdruck:  5 & 1 liefert mir 1, weil das 1.Bit von 5 gesetzt ist
			 
			 6 & 1 liefert mir 0, weil das 1.Bit von 6 nicht gesetzt ist

			 4 & 2 liefert mir 0, weil das 2.Bit von 4 nicht gesetzt ist

			 usw.


Zum Setzen einzelner Bits eignet sich der | Operator verknüpft mit den Potenzen von 2,
will man z.B. das 1.Bit einer Variable "test" auf 1 setzen so geschieht dies mit dem
Ausdruck: test = test | 1. Oder wenn man das 8.Bit einer Variable "test" auf 1 setzen
will, so geschieht dies mit dem Ausdruck: test = test | 128.

========================================================================
*/
