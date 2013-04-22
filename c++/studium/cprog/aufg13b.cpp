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
#include <string.h>

int i, weiter = 0;

char filename[256];
char name[20], vorname1[20], vorname2[20] = {'\0'}, benutzer[20];

char *datum="          ";

int main(void)
{
  FILE *fp;

  printf("Bitte geben Sie den Pfad des Eingabefiles ein : ");
  gets(filename);

  fp = fopen(filename, "r");

  if (fp)
    {

      while(!feof(fp))
        {
	  weiter = fscanf(fp,"%s",name);

	  if (weiter != 1)
            break;

          fscanf(fp,"%s",vorname1);
          fscanf(fp,"%s",benutzer);
      
          if (benutzer[0] != 'c')
            {  
	       strcpy(vorname2, benutzer);
               fscanf(fp,"%s",benutzer);
            }

	  i = 0;
	       
          while (benutzer[i] != '\0')
            i = i + 1;
      
          if (benutzer[i-1] != ';')
            {
              i = 0;

              while(benutzer[i] != ';')
                i = i + 1;

              benutzer[i] = '\0';
              datum = &benutzer[i+1];
            }  

          else
            {
              benutzer[i-1] = '\0';
              fscanf(fp,"%s",datum);
            }
 
          i = 0;     

          while(name[i] != ',')
            i = i + 1;  
      
          name[i] = '\0';

          printf("\n%15s   %15s   %15s   %s  %s",vorname1,vorname2,name,benutzer,datum);
    
          vorname2[0] = '\0';

        }
    }

  else
    {
      printf("Eingabefile wurde nicht gefunden !");
    }

  return 0;

}


/*
--------------------------------------------------------------------------------


Warum wird u.U. ein Datensatz zu oft eingelesen ?

Dies kann am Ende des Files geschehen, z.B. nachdem mit fscanf die
letzte Zeile eingelesen wurde, kann es passieren das das Ende der Datei
mit feof noch nicht erkannt wird, weil vielleicht am Ende der letzen Zeile
noch vor dem Fileende ein paar Leerstellen dranhängen.
Folglich wird die while-Schleife nochmals durchlaufen, jedoch ist diesesmal
keine Eingabe für fscanf vorhanden, somit wird aktzeile auch nicht geändert
und sozusagen die Zeile des vorherigen Durchlaufs wieder verwendet.

Deshalb habe ich in meinen Programmcode eine Abfrage eingebaut, die den Wert
eines Zeigers testet, der den Rückgabewert der fgets - Funktion erhält.
Ist dieser Wert NULL ( = Adresse NULL) wurde kein String eingelesen und
es wird abgebrochen.

--------------------------------------------------------------------------------
*/ 