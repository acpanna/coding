/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 08
    Aufgabennr.   	: 22
    Teilaufgabe   	: iv)

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
#include <ctype.h>

int test;

char* ersetze(char *dest, const char *source);
int lex_vergleich_uml(char wort_1[], char wort_2[]);

char stringold1[41], stringold2[41];
char stringnew1[81], stringnew2[81];

int main(void)
{
  printf("\nBitte geben Sie den  ersten String ein \n(nicht länger als 40 Zeichen): ");
  fgets(stringold1,40,stdin);
  printf("\nBitte geben Sie den zweiten String ein \n(nicht länger als 40 Zeichen): ");
  fgets(stringold2,40,stdin);

  test = lex_vergleich_uml(ersetze(stringnew1, stringold1), ersetze(stringnew2, stringold2));
           
  printf("\n\nDer lexikographische Vergleich liefert: %d",test);

  return 0;
}


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


int lex_vergleich_uml(char wort_1[], char wort_2[])
{
  int i = 0;

  while((wort_1[i] != 0) && (wort_2[i] != 0))
  {
    if( tolower(wort_1[i]) < tolower(wort_2[i]))
      return -1;

    else if ( tolower(wort_1[i]) > tolower(wort_2[i]) )
      return 1;

    i++;
  }

  if( ( wort_1[i] == '\0') && ( wort_2[i] == '\0'))
    return 0;

  else if (wort_1[i] != '\0')
    return 1;

  else
    return -1;
}
