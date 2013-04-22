#include <stdio.h>
#include <stdlib.h>


struct linkedlist {
  int data;
  int link;
}*x, *y, *z;


void haeng(struct linkedlist *x, struct linkedlist *y, struct linkedlist *z);
void ausgabe(struct linkedlist *z);


int main(void)
{
  
  int n,m,i;

  printf("\nBitte geben Sie die Anzahl der Folgenglieder von X ein : ");
  scanf("%d",&n);
  printf("Bitte geben Sie die Anzahl der Folgenglieder von Y ein : ");
  scanf("%d",&m);

  x = (struct linkedlist * ) malloc( (n+1)   * sizeof(struct linkedlist));
  y = (struct linkedlist * ) malloc( (m+1)   * sizeof(struct linkedlist));
  z = (struct linkedlist * ) malloc( (m+n+1) * sizeof(struct linkedlist));

  printf("\n");
    
  for(i=1; i<=n ; i++)
    {                                                                     /* Startzeiger der Folge X */
      x[0].link = 1;                                                      /* (zeigt aufs 1. Element) */
      printf("Bitte geben Sie das  %2d.-te Folgenglied von X ein : ",i);
      scanf("%d",&x[i].data);
      x[i].link = i+1;
      if (i==n)
	x[i].link=0;
    }

  printf("\n");

  for(i=1; i<=m ; i++)
    {                                                                     /* Startzeiger der Folge Y */
      y[0].link = 1;
      printf("Bitte geben Sie das  %2d.-te Folgenglied von Y ein : ",i);
      scanf("%d",&y[i].data);
      y[i].link = i+1;
      if (i==m)
	y[i].link=0;
    }                                                                     /*        Falls X oder Y leer,       */
                                                                          /* Startzeiger zeigt auf sich selbst */
  if(n==0)
    x[0].link=0;

  if(m==0)
    y[0].link=0;  
                

   haeng(x,y,z);
   ausgabe(z);

   return 0;
}
  

void haeng(struct linkedlist *x, struct linkedlist *y, struct linkedlist *z)
{
  int m,n,i,j;
					      /* In n,m wird jeweils die Position des */
  m = y[0].link;                              /*    1.Elements von X,Y gespeichert    */
  n = x[0].link;

  if (x[0].link==0 && y[0].link==0)
    {
      z[0].link = 0;
    }

  else
    {
      z[0].link = 1;
            
      for (i=1 ;; i++)
        {                                     /* z[i].data wird solange gleich x[n].data gesetzt */
	  if (x[0].link != 0)
            {
              z[i].data = x[n].data;              /*        bis x[n].link=0, also X durch ist        */
              z[i].link = i+1;
	    }
	  else
	    i = i - 1;

	  if (x[n].link==0)
	    {
	      for (j=i+1 ;; j++)
	        {
		  if (y[0].link != 0)
                    z[j].data=y[m].data;        /* z[i].data wird solange gleich y[m].data gesetzt */
		  else
                    j = j - 1;
                                              /*        bis y[m].link=0, also Y durch ist        */
	          if (y[m].link==0)
	            {
	              z[j].link=0;
	              break;
		    }

                  m = y[m].link;

	          z[j].link = j+1;
	        }	
	      break;

	    }
		        
	  n = x[n].link;
        }
    } 
}


void ausgabe(struct linkedlist *z)
{
  int i, j, k=0;

  j = z[0].link;

  printf("\nErgebnis:\n\n");

  if (j != 0)
    {
      for (i=1 ;; i++) 
        {
	  k=k+1;

	  if (k==30)
            printf("\n     ");

	  printf(" %d",z[j].data);

	  j = z[j].link;

	  if (j==0)
	     break;
	}
    }
}
