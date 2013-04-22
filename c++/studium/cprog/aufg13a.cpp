/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 05
    Aufgabennr.   	: 13
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

int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

char *weiter;

char zaehler;
char aktzeile[256];
char filename[256];

int check(char *kommentar, const char *zeile);


int main(void)
{
  FILE *fp;

  printf("\nBitte geben Sie den Pfad des Eingabefiles ein : ");
  gets(filename);

  fp = fopen(filename,"r");

  if (fp)
    {
  
      while(!feof(fp))
        {
          weiter = fgets(aktzeile, 256, fp);

	  if(weiter != NULL)
            {
              test1 = check("REM",aktzeile);
              test2 = check("rem",aktzeile);
              test3 = check("#",aktzeile);
              test4 = check(";",aktzeile);

              if((test1 == 0) && (test2 == 0) && (test3 == 0) && (test4 == 0))
                {
		  if (zaehler == 20)
		    {
		      printf("\nRETURN drücken zum Anzeigen der nächsten Seite\n");
		      scanf("%c",&zaehler);
                      zaehler = 0;
                    }

	          printf("%s",aktzeile);
		  zaehler = zaehler + 1;
                }

	    }
	  else
	    {
	      break;
	    }   
	}
    }

  else
    {
      printf("\nEingabefile wurde nicht gefunden !");
    }

  fclose(fp);
  return 0;
}


int check(char *kommentar, const char *zeile)
{
  int i = 0, j = 0, test = 0;
  
  while(zeile[i] == ' ' && zeile[i] != '\0')
    i = i + 1;

  while(kommentar[j] != '\0')
    {
            
      if (zeile[i] == kommentar[j])
	test = 1;

      else
        {
          test = 0;
	  break;
	}

      i++;
      j++;
    }

  return test;
}
