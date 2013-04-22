/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 10
    Aufgabennr.   	: 30
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
#include <string.h>

#define MAX 100

struct Aufnahme {
  char titel[256];
  char regie[128];
  unsigned short band;
  unsigned char nummer;
};

void ausgeben(struct Aufnahme video);
int suchen(struct Aufnahme video, char key[]);
struct Aufnahme einlesen(struct Aufnahme video);

int main(void)
{
  int i, wahl;
  char ciao;
  char key[256];

  struct Aufnahme video[MAX] = { {"", "", 0, 0} };
  struct Aufnahme gefunden = { "", "", 0, 0 };

  do
  {
    printf("\nWas wollen Sie tun :     Neuen Film eingeben                1");
    printf("\n                         Nach Film suchen                   2");
    printf("\n                         Zuletzt gefundenen Film ausgeben   3");
    printf("\n\nIhre Wahl : ");
    fflush(stdin);
    scanf("%d",&wahl);

    switch(wahl)
    {
      case 1: for (i=0; i<MAX; i++)
              {
	        if (video[i].titel[0] == '\0')
	        {
	      	  video[i] = einlesen(video[i]);
	          break;
	        }
              }
	      if (i==MAX)
                printf("\n\nEs ist nicht mehr genügend Speicherplatz für den Film vorhanden !");

              break;

      case 2: printf("\nNach welchem Schlüssel wollen Sie suchen : ");
              fflush(stdin);
	      gets(key);

	      for (i=0; i<MAX; i++)
              {
		if (video[i].titel == '\0')
                {
		  i=MAX;
		  break;
		}

		if (suchen(video[i], key) == 1)
		{
		  printf("\n\nFilmtitel wurde gefunden !\n");
		  gefunden = video[i];
                  ausgeben(gefunden);
                  break;
                }
	      }

	      if (i==MAX)
		printf("\n\nFilmtitel wurde nicht gefunden !\n");
              
	      break;

      case 3: ausgeben(gefunden);

      default: ;

    }

    printf("\n\nWollen Sie abbrechen (j/n) : ");
    fflush(stdin);
    scanf("%c",&ciao);

    printf("\n\n\n\n\n");

  } while (ciao != 'j');

  return 0;
}

struct Aufnahme einlesen(struct Aufnahme video)
{
  printf("\nBitte geben Sie den Filmtitel ein : ");
  fflush(stdin);
  gets(video.titel);
  printf("Bitte geben Sie den Namen des Regisseurs ein : ");
  fflush(stdin);
  gets(video.regie);
  printf("Bitte geben Sie den Stand des Bandzählers ein : ");
  fflush(stdin);
  scanf("%hu",&video.band);
  printf("Bitte geben Sie die Filmnummer ein : ");
  fflush(stdin);
  scanf("%u",&video.nummer);

  return video;
}


int suchen(struct Aufnahme video, char key[])
{
  int i;
  char *ptr;

  ptr = strstr(strlwr(video.titel), strlwr(key));

  if (ptr != NULL)
    return 1;
  else
    return 0;

}


void ausgeben(struct Aufnahme video)
{
  printf("\nFilmtitel : \t\t%s",video.titel);
  printf("\nRegisseur: \t\t%s",video.regie);
  printf("\nStand Bandzähler: \t%hu",video.band);
  printf("\nNummer des Films: \t%u",video.nummer);
}



