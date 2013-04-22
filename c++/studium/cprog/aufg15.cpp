/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 05
    Aufgabennr.   	: 15
    Teilaufgabe   	: --

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

enum fehler1 {NFOUND=100, NREAD=101, NWRITE=102, EMPTY=103};
enum notini {INI = 100, NINI1, NINI2};
enum fehler2 {NOERROR = 0, NFOUND2 = 100, NREAD2 = 101, NWRITE2 = 102, EMPTY2 = 103};
enum schalter { AUS = 0 , EIN , OFF = 0, ON};

int main(void)
{
  printf("\n Datei nicht gefunden     : %d",NFOUND);
  printf("\n Datei nicht lesbar       : %d",NREAD);
  printf("\n Datei nicht beschreibbar : %d",NWRITE);
  printf("\n Datei leer               : %d",EMPTY);

  printf("\n");
  printf("\n Erster Wert mit 100 initialisiert, die anderen nicht:");
  printf("\n INI = %d, NINI1 = %d, NINI2 = %d",INI,NINI1,NINI2);

  printf("\n");
  printf("\n Kein Fehler              : %d",NOERROR);
  printf("\n Datei nicht gefunden     : %d",NFOUND2);
  printf("\n Datei nicht lesbar       : %d",NREAD2);
  printf("\n Datei nicht beschreibbar : %d",NWRITE2);
  printf("\n Datei leer               : %d",EMPTY2);

  printf("\n");
  printf("\n Schalter: AUS = %d, EIN = %d, OFF = %d, ON = %d",AUS,EIN,OFF,ON);


  printf("\n");
  printf("\n Für den Datentyp 'enum' werden %d Bytes verwendet.",sizeof(schalter));

  return 0;
}

/*

Leider ist es mir nicht möglich eine Ausgabe mit abzugeben,
da aus welchen windows- bzw. compiler-spezifischen Gründen auch immer
die Dateiausgabe- bzw. eingabeumlenkung bei mir nicht funktioniert !

*/