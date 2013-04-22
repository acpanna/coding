/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 04
    Aufgabennr.   	: 10
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

int main(void)
{
  FILE * fp;

  char bearb_kuerzel;
  char bezeich[81], name[256];

  short kredit;
  unsigned short weiter, letzter_tag, jahr, monat, stunde;

  float kontost;
  unsigned long blz, kontonr, ueber;
       
  printf("Name des Eingabefiles: ");
  scanf("%s", name); 

  fp = fopen(name, "r");

  if (fp == NULL)
  {
    printf("Datei mit Namen \"%s\" konnte nicht geoeffnet werden!\n",name);
    return 1;
  }

  weiter = 1;
  
  while (!feof(fp) && weiter)
  {
    weiter = fscanf(fp, "%s %lu", bezeich, &blz);
    
    weiter = (weiter == 2);

    if (weiter)  
    {
      printf("%s %lu\n", bezeich, blz);

      fscanf(fp, "%s %lu", bezeich, &kontonr);
      printf("%s %lu\n", bezeich, kontonr);
      
      fscanf(fp, "%s %f", bezeich, &kontost);
      printf("%s %.2f\n", bezeich, kontost);

      fscanf(fp, "%s %lu", bezeich, &ueber);
      printf("%s %lu\n", bezeich, ueber);

      fscanf(fp, "%s %hd", bezeich, &kredit);
      printf("%s %d\n", bezeich, kredit);

      fscanf(fp, "%s%*c %c", bezeich, &bearb_kuerzel);
      printf("%s %c\n", bezeich, bearb_kuerzel);      
  
      fscanf(fp, "%s %hu", bezeich, &letzter_tag);
      printf("%s %d\n", bezeich, letzter_tag);    

      fscanf(fp, "%s %hu", bezeich, &monat);
      printf("%s %d\n", bezeich, monat);

      fscanf(fp, "%s %hu", bezeich, &jahr);
      printf("%s %d\n", bezeich, jahr);

      fscanf(fp, "%s %hu", bezeich, &stunde);
      printf("%s %d\n", bezeich, stunde);
    }

    printf("\n");
  }

  printf("\n");
 
  fclose(fp);

  return 0;
}


/* ------------------------------------------------------------------------*/
/*
   Erklärung der Wahl der Datentypen:

   bearb_kuerzel enthält lediglich ein Zeichen --> char
   kontost ist Kommazahl (auf 2 Stellen)  --> float
   blz, kontonr, über sind immer positive Ganzzahlen, die jedoch
               größere Werte abspeichern müssen --> unsigned long
   tag, jahr, monat, stunde enthalten kleine ganzzahlige positive Werte
		                                             --> unsigned short
   kredit enthält kleine ganzzahlige Werte, die auch negativ sein können --> short
*/
/* ------------------------------------------------------------------------*/