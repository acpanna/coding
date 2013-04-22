/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 04
    Aufgabennr.   	: 11
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

char* ersetze(char *dest, const char *source);

char mit_Umlaute[41];
char ohne_Umlaute[81];

int main(void)
{
  printf("\nBitte geben Sie einen String ein \n(nicht länger als 40 Zeichen): ");
  gets(mit_Umlaute);

  printf("\n%s",ersetze(ohne_Umlaute, mit_Umlaute));

  return 0;
}

/* Funktion */

char* ersetze(char *dest, const char *source)
{
  int i = 0, j = 0;

  while (source[i] != '\0')
    {
      switch(source[i])
	{
	  case 'ä':
	    dest[j]='a';
	    j++;
	    dest[j]='e';
	    break;

	  case 'ö':
	    dest[j]='o';
	    j++;
	    dest[j]='e';
	    break;

	  case 'ü':
	    dest[j]='u';
	    j++;
	    dest[j]='e';
	    break;

	  case 'ß':
	    dest[j]='s';
	    j++;
	    dest[j]='s';
	    break;

	  case 'Ä':
	    dest[j]='A';
	    j++;
	    dest[j]='e';
	    break;

	  case 'Ö':
	    dest[j]='O';
	    j++;
	    dest[j]='e';
	    break;

	  case 'Ü':
	    dest[j]='U';
	    j++;
	    dest[j]='e';
	    break;

	  default:
            dest[j]=source[i];
        }
      j++;      
      i++;
    }

  dest[j]='\0';
  
  return dest;
}

/*
------------------------------------------------------------------------
*/
/*

Beantwortung der Frage:

Der String "ohne_Umlaute" muß im Extremfall doppelt solange sein,
wie der String "mit_Umlaute" (\0 nicht mitgerechnet).
Der Extremfall wird jedoch so gut wie nie eintreten, deshalb würde
es genügen den String z.B. nur um 1/4 länger zu machen als den
ursprünglichen String, da in einem durchschnittlichem deutschem Satz
normalerweise weniger als ein Viertel aller Buchstaben Umlaute sind.
*/
/*
------------------------------------------------------------------------
*/
