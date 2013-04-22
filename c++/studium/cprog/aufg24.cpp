/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 08
    Aufgabennr.   	: 24
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
#include <stdlib.h>

#define MAX 100

int position = 0;

int push(int stack[], int neu);
int pop(int stack[]);

int main(void)
{
  int i, neu;
  int stack[MAX];

  char action = 'j';

  char buchautor[][20]={"Kernighan, Ritchie", "Krüger", "Willms", "Geary", "Lippman, Lajoie",
                        "S.u.S.E.", "Flanagan"};
  char buch[][60]={"Progr. in C mit dem Reference Manual in dt. Sprache", "C programmieren",
		   "Das C-Grundlagen-Buch", "Graphic Java. Mastering the JFC I", "C++ Primer",
		   "Linux 6.1 Handbuch", "JavaScript. Das umfassende Referenzwerk"};
  
  while (action != 'n')
  {
    printf("\n\n\n\n\nNr.  Autor               Buchtitel");
    printf("\n----------------------------------\n");

    for (i=0; i<7; i++)
    {
      printf("\n%2d %20s: %s", i+1, buchautor[i], buch[i]);
    }

    printf("\n\nWollen Sie ein Buch vom Stack holen oder auf den Stack schieben (h oder s) ? ");
    action = getchar();

    if (action == 'h')
      pop(stack);
    else
    {
      printf("\nWelches Buch soll auf den Stack geschoben werden : ");
      scanf("%d",&neu);
      push(stack,neu);
    }

    printf("\n\nAusgabe des Stacks:\n");

    for (i=0 ; i<position; i++)
      printf("\n%2d %20s: %s", stack[i], buchautor[stack[i]-1], buch[stack[i]-1]);
    
    fflush(stdin);

    printf("\n\nWeitermachen (j/n) ? ");
    action = getchar();

    fflush(stdin);
  }
  return 0;
}

int push(int stack[], int neu)
{
  int i = 0;

  if (position <= MAX - 1)
  {
    stack[position] = neu;
    position = position + 1;
  }

  else
  {
    printf("\nStack ist voll !");
    exit(1);
  }
}


int pop(int stack[])
{
  if (position != 0)
    position = position - 1;

  else
  {
    printf("\nStack ist leer !");
    exit(1);
  }
}
