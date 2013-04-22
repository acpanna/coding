#include <stdio.h>

#define ANZAHL 100        /*     Die Höchstanzahl der möglichen Einträge der Matrix    */
                          /* muß hier vor Compilierung des Programms festgelegt werden */  

int zeilen, spalten, eintraege;
int tmpmem;

int i,j,n,aij=0;

int matrix[ANZAHL][3];

void draw(void); /*  Prototyp der draw - Unterfunktion zur  */
		 /*  Darstellung der Matrix auf dem Screen  */
int main (void)
{
  
  printf("\nProgramm um eine Matrix zu transponieren\n");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");


  /* Eingabe der Daten m,n,t der Matrix */ 

  printf("\nBitte geben Sie ein wieviele Zeilen die Matrix besitzt (=m)   : ");
  scanf("%d",&zeilen);
  printf("Bitte geben Sie ein wieviele Spalten die Matrix besitzt (=n)  : ");
  scanf("%d",&spalten);
  printf("Bitte geben Sie die Anzahl der von Null verschiedenen \n");
  printf("                               Einträge der Matrix ein (=t)   : ");
  scanf("%d",&eintraege);

  
  matrix[0][0]=zeilen;
  matrix[0][1]=spalten;
  matrix[0][2]=eintraege;
  
  printf("\n\n");


  /* Abfragen der Einträge der Matrix und der zugehörigen Spalten-/Zeilenindizes */

  for (i=1; i<=eintraege; i++)
    {
      printf("\nBitte geben Sie den Zeilenindex des %d.-ten Eintrags ein  : ",i);
      scanf("%d",&matrix[i][0]);
      printf("Bitte geben Sie den Spaltenindex des %d.-ten Eintrags ein : ",i);
      scanf("%d",&matrix[i][1]);
      printf("Bitte geben Sie den %d.-ten Eintrag ein : ",i);
      scanf("%d",&matrix[i][2]);
    }

  printf("\n");
  draw();
     

  /*  Transponierung der Matrix unter Nutzung einer temporären Variable  */

  for (i=0; i<=eintraege; i++)
    {
      tmpmem = matrix[i][0];
      matrix[i][0] = matrix[i][1];
      matrix[i][1] = tmpmem;
    }

          
  /*          Sortiere die Matrix nach den Zeilenidizes, d.h. in matrix[1,0]       */
  /* steht der kleinste Zeilenindex, in matrix[eintraege,0] der größte Zeilenindex */

  for (i=1; i<eintraege; i++)
    {
      for (j=i+1; j<=eintraege; j++)
        {
	  if (matrix[i][0]>matrix[j][0])
	    {
	      for (n=0; n<3; n++)
	        {
		  tmpmem = matrix[i][n];
		  matrix[i][n] = matrix[j][n];
		  matrix[j][n] = tmpmem;
	        }
	    }
	}
    }

  draw();
      	    
  return 0;
}


  /* Darstellung der Matrix auf Bildschirm */

  void draw(void)
    {
      for (i=1 ; i<=matrix[0][0]; i++)
        {  
          for (j=1; j<=matrix[0][1]; j++)
            {
              aij=0;

	      for(n=1 ; n<=matrix[0][2]; n++)
                {
	          if(matrix[n][0]==i & matrix[n][1]==j)
	            {
	              aij = matrix[n][2];
                      n = matrix[0][2]+1;
	            }
                }
              printf("  %d",aij);
            }
          printf("\n");
        }
    printf("\n\n");
    }