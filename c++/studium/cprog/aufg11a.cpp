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
#include <string.h>

char test[20];

/* Funktionskopf für print_rueckwaerts() */
void print_rueckwaerts(const char *string);

/* Funktionskopf für inKleinSchreibweise() */
void inKleinSchreibweise(char *string);

int main(void)
{
   printf("Bitte geben Sie einen String ein (max. 20 Zeichen) : ");
   gets(test);

   printf("\n");

   print_rueckwaerts(test);

   printf("\n");

   inKleinSchreibweise(test);

   return 0;
}

/* Funktion print_rueckwaerts() */
void print_rueckwaerts(const char *string)
{
  int i = 0;

  while (string[i] != '\0')
    i = i + 1;
    
  for (i = i - 1; i>=0 ; i = i - 1)
    printf("%c",string[i]);

  printf("\n");
}

/* Funktion inKleinSchreibweise */
void inKleinSchreibweise(char *string)
{
  int i = 0, j;

  while (string[i] != '\0')
    {
      for (j=65; j<=90 ; j++)
	{
	  if (string[i] == j)
	    string[i] = j + 32;
	}

      printf("%c",string[i]);		     

      i = i + 1;
    }

  printf("\n");
}


/*
------------------------------------------------------------------------
*/
/*

 Beantwortung der Fragen:

 Die Funktion tolower() ist eine Charaktermanipulierungsfunktion,
 stellt sie einen Großbuchstaben fest, so wird dieser in einen
 Kleinbuchstaben umgewandelt. Ansonsten läßt sie den Charakter
 unverändert.

 Der Funktionskopf der 1. Funktion sollte einen Pointer auf konstante
 Charakterwerte als Argument nehmen, da ja der String nicht verändert wird.
 Der Funktionskopf der 2. Funktion sollte einen Pointer auf nicht-konstante
 Charakterwerte als Argument nehmen, weil der String ja verändert wird.

*/
/*
------------------------------------------------------------------------
*/