#include <stdio.h>
#include <time.h>
#include <alloc.h>
#include <stdlib.h>

#define M  4           /* Hier müssen die Werte m bzw. n der m x n Matrizen vor */
#define N  4           /*   der Compilierung des Programms festgelegt werden    */

int bitfeldA[M][N];
int bitfeldB[M][N];
int bitfeldC[M][N];

int i,j;

int tA=0;
int tB=0;
int tC=0;
int positionA=0;
int positionB=0;
int positionC=0;

int *werteA;
int *werteB;
int *werteC;

int main(void)
{

  printf("\nProgramm zur Addition zweier dünnbesetzter m x n Matrizen\n");
  printf("---------------------------------------------------------\n\n");

  /* Erzeuge zufaelliges Bitfeld für Matrix A */
    
  for(i=0; i<M; i++)
    {
      for(j=0; j<N; j++)
	{
          bitfeldA[i][j] = rand() % 2;         /* Zufallszahlen 0 oder 1 */
	  if (bitfeldA[i][j]==1)
	    tA = tA +1;
	}
    }
    
  werteA = (int *)malloc(sizeof(int)*tA);      /* Speicherreservierung für Werte von A */

  /* Erzeuge zufaelliges Wertefeld fuer A */

  randomize();
  for(i=0; i<tA; i++)
    {
      werteA[i] = (1 + rand()  % 100)-(1 + rand() % 100);  /* Zufallszahlen zw.-99 und 99 ohne Null */
      if (werteA[i] == 0)
	werteA[i] == 1;
    }

  /* Matrix A ist nun fertiggestellt */


  /* Erzeuge zufaelliges Bitfeld für Matrix B */

  for(i=0; i<M; i++)
     {
       for(j=0; j<N; j++)
     	 {
           bitfeldB[i][j] = rand() % 2;         /* Zufallszahlen 0 oder 1 */
	   if (bitfeldB[i][j]==1)
	     tB = tB +1;
       	 }
     }
    
  werteB = (int *)malloc(sizeof(int)*tB);      /* Speicherreservierung für Werte von B */

  /* Erzeuge zufaelliges Wertefeld fuer B */

  randomize();
  for(i=0; i<tB; i++)
    {
      werteB[i] = (1 + rand()  % 100)-(1 + rand() % 100);  /* Zufallszahlen zw.-99 und 99 ohne Null */
      if (werteB[i] == 0)
	werteB[i] == 1;
    }

  /* Matrix B ist nun fertiggestellt */


  /* Ausgabe der Matrizen A,B am Screen */
    
  for (i=0; i<M; i++)
    {
      for(j=0; j<N; j++)
	{
	  if (bitfeldA[i][j]==0)
	    printf("\t0");
	  if (bitfeldA[i][j]==1)
	    {
	      printf("\t%d",werteA[positionA]);
	      positionA = positionA +1;
	    }
	}
      printf("\n");
      }
  
  printf("\n                             +\n");

  printf("\n");
         
  for (i=0; i<M; i++)
    {
      for(j=0; j<N; j++)
        {
          if (bitfeldB[i][j]==0)
            printf("\t0");
          if (bitfeldB[i][j]==1)
            {
              printf("\t%d",werteB[positionB]);
              positionB = positionB +1;
            }
        }
     printf("\n");
     }

  printf("\n");

  positionA=0;
  positionB=0;


  werteC = (int *)malloc(sizeof(int)*(tA+tB)); /* Speicherreservierung für Werte von B */


  /* Addition der Matrizen */

  for(i=0; i<M; i++)
    {
      for(j=0; j<N; j++)
        {
           if(bitfeldA[i][j] == 0 & bitfeldB[i][j] == bitfeldA[i][j])
	     bitfeldC[i][j]=0;

	   if(bitfeldA[i][j] == 1 & bitfeldB[i][j] == 0)
             {
               bitfeldC[i][j]=1;
	       werteC[positionC] = werteA[positionA];
	       positionC = positionC+1;
	       positionA = positionA+1;
	     }

	   if(bitfeldA[i][j] == 0 & bitfeldB[i][j] == 1)
             {
               bitfeldC[i][j]=1;
	       werteC[positionC] = werteB[positionB];
	       positionC = positionC+1;
	       positionB = positionB+1;
	     }
                      
	   if(bitfeldA[i][j] ==1 & bitfeldB[i][j] == 1)
	     {
	       if(werteA[positionA] == -1 * werteB[positionB])
		 bitfeldC[i][j]=0;
	       else
		 {
		   bitfeldC[i][j]=1;
		   werteC[positionC]= werteA[positionA] + werteB[positionB];
                   positionA = positionA+1;
		   positionB = positionB+1;
		   positionC = positionC+1;
		 }
             }
        }
    }

  /* Addition von A und B ist abgeschlossen, Ergebnis steht in Matrix C */
                                                 
  /* Ausgabe der Matrix C am Screen */
  
  positionC=0;

  printf("                             =\n\n");

  for (i=0; i<M; i++)
    {
      for(j=0; j<N; j++)
	{
	  if (bitfeldC[i][j]==0)
	    printf("\t0");
	  if (bitfeldC[i][j]==1)
	    {
	      printf("\t%d",werteC[positionC]);
	      positionC = positionC +1;
	    }
	}
      printf("\n");
      }
  
  free(bitfeldA);                                      
  free(bitfeldB);                                        /*  Speicherplatz   */
  free(bitfeldC);
  free(werteA);                                          /* wird freigegeben */
  free(werteB);
  free(werteC);

  return 0;
  }                               