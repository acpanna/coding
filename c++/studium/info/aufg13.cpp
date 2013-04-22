#include <stdio.h>
#include <stdlib.h>

#define ANZAHL 100 /* Hier muß die Maximalgröße des Kellers vor Compilierung festgelegt werden */
                
int start;
int frei;

struct keller {
  char element;
  int link;
} keller[ANZAHL];

struct leer {
  int link;
} leer[ANZAHL];
 
void erzeuge(void);
void pull(int start);
void kopf(int start);
void istleer(int start);
void push(char element, int start);


int main(void)
{
  printf("\nBeispielprogramm um Kellerbenutzung zu veranschaulichen :\n");
  printf("\n\n1. Erzeuge Keller");

  erzeuge();

  printf("\n\n2. Teste ob erzeugter Keller leer ist");

  istleer(start);

  printf("\n\n3. Schiebe Elemente A, B, C auf Keller");

  push('A',start);
  push('B',start);
  push('C',start);

  printf("\n\n4. Gebe Kopfelement des Kellers aus");

  kopf(start);

  printf("\n\n5. Lösche Kopf des Kellers");

  pull(start);

  printf("\n\n6. Ausgabe des neuen Kopfes");
   
  kopf(start);

  printf("\n\n7. Test ob Keller bereits leer");

  istleer(start);

  printf("\n\n8. 2 maliges Anwenden von Pull");

  pull(start);
  pull(start);

  printf("\n\n9. Nochmaliges Anwenden von Pull");

  pull(start);
                            
  return 0;
}


void erzeuge(void)
{
  int i;

  start = 0;
  frei = 0;

  for (i=0; i<ANZAHL; i++)
    {
      leer[i].link = i+1;
    }

  keller[start].link = -1;
  keller[start].element = '\0';
  leer[i-1].link = -1;
}

 
void push(char element, int start)
{
  int position;

  position = start;
  
  if(frei == -1)
    {
      printf("\n\tPush - Keller voll !");
      exit(1);
    }

  while(keller[position].link != -1)
    position = keller[position].link;
  
  keller[frei].element = element;
  keller[frei].link = -1;

  if (frei != position)
    keller[position].link = frei;
   
  frei = leer[frei].link;
}


void pull(int start)
{
  int temp, position, vorgaenger = 0;
  position = start;

  if ((keller[start].element == '\0') && (keller[start].link == -1))
    {
      printf("\n\tPull - Keller leer !");
      exit(1);
    }
   
  while(keller[position].link != -1)
    {
      vorgaenger = position;
      position = keller[position].link;
    }

  temp = frei;

  frei = position;

  leer[frei].link = temp;
  
  keller[position].element = '\0';
  keller[vorgaenger].link = -1;
}

void kopf(int start)
{
  int position;
  position = start;

  if ((keller[start].element == '\0') && (keller[start].link == -1))
    {
      printf("\n\tKopf - Keller leer !");
      exit(1);
    }
   
  while(keller[position].link != -1)
    position = keller[position].link;

  printf("\n\t%c",keller[position].element);
    
}

void istleer(int start)
{
  if ((keller[start].element == '\0') && (keller[start].link == -1))
    printf("\n\tIstleer - Keller leer !");
  else
    printf("\n\tIstleer - Keller ist nicht leer !");

}      
   
  

