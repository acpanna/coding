/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 10
    Aufgabennr.   	: 28
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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void falsch(void);

int main(void)
{
  int i;

  char nummer[12];
  char code[]="0123456789";
  char buchstaben[]="adgklnsuyz";

  int nummer2[11];
  int nummer3[11];
  int PI[11][10] = { {1,5,7,6,2,8,3,0,9,4}, {5,8,0,3,7,9,6,1,4,2}, {8,9,1,6,0,4,3,5,2,7},
            	     {9,4,5,3,1,2,6,8,7,0}, {4,2,8,6,5,7,3,9,0,1}, {2,7,9,3,8,0,6,4,1,5},
		     {7,0,4,6,9,1,3,2,5,8}, {0,1,2,3,4,5,6,7,8,9}, {1,5,7,6,2,8,3,0,9,4},
		     {5,8,0,3,7,9,6,1,4,2}, {0,1,2,3,4,5,6,7,8,9} };
  int MULT[10][10] = { {0,1,2,3,4,5,6,7,8,9}, {1,2,3,4,0,6,7,8,9,5}, {2,3,4,0,1,7,8,9,5,6}, 
                       {3,4,0,1,2,8,9,5,6,7}, {4,0,1,2,3,9,5,6,7,8}, {5,9,8,7,6,0,4,3,2,1}, 
                       {6,5,9,8,7,1,0,4,3,2}, {7,6,5,9,8,2,1,0,4,3}, {8,7,6,5,9,3,2,1,0,4}, 
		       {9,8,7,6,5,4,3,2,1,0} };
  int erg[10];

  printf("\nBitte geben Sie die 11 - stellige Seriennummer des Geldscheins ein : \n\n\t");
  scanf("%11s",&nummer);
   
  if (strlen(nummer) != 11)                                   /* Test ob Nummer den formalen */
    falsch();
  if (((int) nummer[0] > 47) && ((int) nummer[0] < 58))       /*     Kriterien entspricht    */
    falsch();
  if (((int) nummer[1] > 47) && ((int) nummer[1] < 58))
    falsch();
  if (((int) nummer[9] > 47) && ((int) nummer[9] < 58))
    falsch();

  for (i=2; i<9; i++)
  {
    if (((int) nummer[i] < 48) && ((int) nummer[i] > 57))
      falsch();
  }

  if (((int) nummer[10] < 48) && ((int) nummer[10] > 57))
    falsch();

  for (i=0; i<10; i++)                                    /* Umwandlung der Buchstaben */
  {
    if (tolower(nummer[0]) == buchstaben[i])              /*         in Zahlen         */
      nummer[0] = code[i];
    if (tolower(nummer[1]) == buchstaben[i])
      nummer[1] = code[i];
    if (tolower(nummer[9]) == buchstaben[i])
      nummer[9] = code[i];
  }

  printf("\nAusgabe der codierten Zahl: \t\t");
                                         /*          Umwandlung Zeichen in Zahlen           */
  for (i=0; i<11; i++)
  {
    nummer2[i] = ((int) nummer[i]) - 48; /* Zeichen mit ASCII-Wert 48 entspricht der Zahl 0 */
    printf("%d",nummer2[i]);
  }

  printf("\nAusgabe der permutierten Zahl: \t\t");

  for (i=0; i<11; i++)
  {
    nummer3[i] = PI[i][nummer2[i]];      /* Permutation */
    printf("%d",nummer3[i]);
  }

  erg[0] = MULT[nummer3[0]][nummer3[1]]; /* Schrittweise Multiplikation */
  
  for (i=1; i<10; i++)
    erg[i] = MULT[erg[i-1]][nummer3[i+1]];

  printf("\nMultiplikation nach Tabelle ergibt: \t%d", erg[9]);
  
  if (erg[9] == 0)
    printf("\n\nDer Schein scheint echt zu sein !");

  else
    printf("\n\nTja, das war wohl ´ne Blüte !");

  return 0;
}

void falsch(void)
{
  printf("\nBei diesem Schein handelt es sich wohl um eine recht plumpe Fälschung !");
  exit(1);
}
