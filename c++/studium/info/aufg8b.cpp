#include <stdio.h>
#include <stdlib.h>

struct linkedlist {
  int data;
  int link;
} *x;


void invert(struct linkedlist *x);
void ausgabe(struct linkedlist *x);


int main(void)

{
  
   int n,i;

   printf("\nBitte geben Sie die Anzahl der Folgenglieder von X ein : ");
   scanf("%d",&n);
 
   x = (struct linkedlist *) malloc ( (n+1) * sizeof(struct linkedlist));

   printf("\n");

   for(i=1; i<=n ; i++)
     {
       x[0].link = 1;
       printf("Bitte geben Sie das  %2d.-te Folgenglied von X ein : ",i);
       scanf("%d",&x[i].data);
       x[i].link = i+1;
       if (i==n)
         x[i].link=0;
     }
  
   if(n==0)
     x[0].link=0;

   invert(x);
   ausgabe(x);

   return 0;
}


void invert(struct linkedlist x[])
{

  int n, m, i, j, temp;

  m=0;

  for (i=0 ;; i++)
    {
      if (x[m].link==0)
        break;
      else
	m = x[m].link;
    }

  /* In i steht Anzahl der Elemente der Folge */

  m=0;
        
  for (j=1 ; j<=i-1; j++)       /* Gehe bis zum 'vorletzten' Element */
    {
      m = x[m].link;
    }

  temp = x[m].link;             /*  und speichere dessen Link-Feld */
            

  for (n=1 ;; n++)
    {
      m=0;

      for (j=1 ; j<=i-2; j++)   /* Gehe bis zum 'vorvorletzten' Element */
        {
          m = x[m].link;
	}


      x[x[x[m].link].link].link = x[m].link;   /* und speichere dessen Link im Link des letzten Elements */         
      i = i - 1;                               /* Erniedrige i um 1, d.h. beim nächsten Durchlauf wird   */
					       /*         nicht bis zum 'vorvorletzten' sondern          */
      if (i<=1)                                /*       nur bis zum 'vorvorvorletzten' gesprungen.       */
	{                                      /* Falls i = 1, d.h. das 1. Element, so wird dessen Link  */
          x[1].link = 0;                      /* mit 0 und der Link des Listenkopfzeigers mit temp belegt */
          x[0].link = temp;
	  break;
        }
    }
}

void ausgabe(struct linkedlist x[])
{
  int i, j, k=0;

  j = x[0].link;

  printf("\nErgebnis:\n\n");

  if (j != 0)
    {
      for (i=1 ;; i++) 
        {
	  k=k+1;
	  if (k==30)
            printf("\n     ");
	  printf(" %d",x[j].data);
	  j = x[j].link;
	  if (j==0)
	     break;
	}
    }
}
