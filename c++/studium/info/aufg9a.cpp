#include <stdio.h>
#include <stdlib.h>

int vstart, v2start, mstart;

struct matrix {
  int zeile;
  int spalte;
  int wert;
  int rechts;
  int runter;
};

struct vektor {
  int wert;
  int runter;
};

struct vektor *vektor;
struct vektor *vektor2;
struct matrix *matrix;
        
void mult(struct matrix *matrix, struct vektor *vektor, struct vektor *vektor2, int mstart, int vstart, int v2start);
void ausgabe(struct vektor *vektor2, int v2start);
void efehler(void);

int main(void)
{

  int m, n, t;
  int i, max, temp;

  eingabe1:

  printf("\nBitte geben Sie die Zeilenanzahl der Matrix ein           : ");
  scanf("%d",&m);
  printf("Bitte geben Sie die Spaltenanzahl der Matrix ein          : ");
  scanf("%d",&n);

  if(n==0 || m==0)
    {
      printf("\nNaja, das ist wohl zu einfach, ich schätz´ mal das \n            war ein Eingabefehler !\n");
      goto eingabe1;
    }

  printf("Bitte geben Sie die Anzahl der von 0 versch. Einträge ein : ");
  scanf("%d",&t);

  if (t == 0)
    {
      printf("\nNaja, das ist wohl zu einfach, ich schätz´ mal das \n            war ein Eingabefehler !\n");
      goto eingabe1;
    }
       
  if (t > m*n)
    {
      printf("\n Die Anzahl der Einträge ist größer als das Produkt\n     aus der Spalten- und Zeilenzahl !\n");
      goto eingabe1;
    }

  if(m > n)
    max = m;

  if(m <= n)
    max = n;

  matrix  = (struct matrix *) malloc( (t+1+max) * sizeof(struct matrix));
  vektor  = (struct vektor *) malloc(   max    *  sizeof(struct vektor));
  vektor2 = (struct vektor *) malloc(    m    *   sizeof(struct vektor));
  
  
  matrix[0].zeile = m;                     /* Initialiserung des Masterkopfes */
  matrix[0].spalte = n;
  matrix[0].wert = 1;
  matrix[0].rechts = 0;
  matrix[0].runter = 0;

  for(i=1; i<= max; i++)

    {
      matrix[i-1].wert = i;                /* Initialisierung der Zeilen-/Spaltenköpfe */
      matrix[i].wert = 0;
      matrix[i].rechts = i;
      matrix[i].runter = i;
      matrix[i].zeile = 0;
      matrix[i].spalte = 0;
    }

  printf("\nEingabe muß zeilenweise erfolgen, d.h. erst von links nach rechts,\n");
  printf("                                       dann von oben nach unten !\n\n");
    
  for (i=max+1 ; i<=max+t ; i++)
    {

      eingabe2:
     
      printf("\nBitte geben Sie den %2d.-ten Zeilenindex ein  : ",i-max);
      scanf("%d",&matrix[i].zeile);
      printf("Bitte geben Sie den %2d.-ten Spaltenindex ein : ",i-max);
      scanf("%d",&matrix[i].spalte);
      printf("Bitte geben Sie den %2d.-ten Eintrag ein      : ",i-max);
      scanf("%d",&matrix[i].wert);

      if ((matrix[i].zeile == matrix[i-1].zeile) && (matrix[i].spalte == matrix[i-1].spalte))
	{
	  efehler();
	  goto eingabe2;
	}

      if ((matrix[i].spalte < matrix[i-1].spalte) && (matrix[i].zeile == matrix[i-1].zeile))
	{
	  efehler();
          goto eingabe2;
        }
                                             
      if (matrix[i].zeile < matrix[i-1].zeile)
	{
	  efehler();
	  goto eingabe2;
        }

      if ((matrix[i].zeile > m) || (matrix[i].spalte > n))
	{
	  efehler();
	  goto eingabe2;
        }  	           


      temp = matrix[i].zeile;                              /* Verknüpfung der Einträge derselben */
                                                           /*    Zeile mit entsprechendem Kopf   */
      while (matrix[temp].rechts != matrix[i].zeile)
	{
	  temp = matrix[temp].rechts;
        }

      matrix[temp].rechts = i;
           

      temp = matrix[i].spalte;                             /* Verknüpfung der Einträge derselben */
                                                           /*   Spalte mit entsprechendem Kopf   */
      while (matrix[temp].runter != matrix[i].spalte)
        {
	  temp = matrix[temp].runter;
        }

      matrix[temp].runter = i;

      matrix[i].rechts = matrix[i].zeile;                  /* Letzten Einträge einer Zeile/Spalte */
      matrix[i].runter = matrix[i].spalte;                 /*         zeigen wieder auf Kopf      */
                       
    }
    
  printf("\n\nEingabe des Vektors:\n\n");
        
  for (i=0 ; i<n; i++)
    {
      printf("Bitte geben Sie den %2d.-ten Vektoreintrag ein : ",1+i);
      scanf("%d",&vektor[i].wert);

      vektor[i].runter = i + 1;
    }

  vektor[n-1].runter = 0;
  

  for (i=0; i<m; i++)                                   /* Formattierung des Ergebnisvektors */
    {
      vektor2[i].wert=0;
      vektor2[i].runter=i+1;
    }

  vektor2[m-1].runter = 0;

  vstart  = 0;
  v2start = 0;
  mstart  = 0;
    
  mult(matrix, vektor, vektor2, mstart, vstart, v2start);
  ausgabe(vektor2, v2start);
    
  return 0;
}


void mult(struct matrix *matrix, struct vektor *vektor, struct vektor *vektor2, int mstart, int vstart, int v2start)
{
  int i, j;
  int positionm, positionv, positionv2;
  

  positionm = matrix[mstart].wert;
   
  while(matrix[positionm].rechts == positionm)            /*  Suchen nach Kopf mit Einträgen  */
    {
      positionm = matrix[positionm].wert;
    }  

  positionm = matrix[positionm].rechts;                   /* Springen auf ersten Eintrag */

  for (i=1 ;; i++)
    {
      positionv = vstart;
      positionv2 = v2start;
                                                              
      for (j=1; j < matrix[positionm].spalte; j++)        /*        Suche entsprechend dem Spaltenindex        */
	{                                                 /* des Matrixeintrags die jeweilige Vektorkoordinate */
          positionv = vektor[positionv].runter;   
        }
                                                                                                         
      for (j=1; j < matrix[positionm].zeile; j++)         /*        Suche entsprechend dem Zeilenindex       */
	{                                                 /* des Matrixeintrags die Ergebnisvektorkoordinate */
	  positionv2 = vektor2[positionv2].runter;
	}

      matrix[positionm].wert = matrix[positionm].wert * vektor[positionv].wert;     /* Multipliziere Matrixeintrag mit Vektoreintrag */

      vektor2[positionv2].wert = matrix[positionm].wert + vektor2[positionv2].wert; /* Addiere Ergebnis der Multiplikation zum Ergebnisvektor */

      positionm = matrix[positionm].rechts;                                         /* Springe zum nächsten Eintrag der Matrix */
      
      if ((matrix[positionm].zeile == 0) && (matrix[positionm].spalte == 0))        /* Falls Kopf => Zeile durch, weiter zum nächsten Kopf */
        {
	  positionm = matrix[positionm].wert;
         
	  if ((matrix[positionm].zeile != 0) || (matrix[positionm].spalte != 0))   /* Falls Masterkopf => Matrix durch => fertig */           
	    goto fertig;
          	  
	  while(matrix[positionm].rechts == positionm)                             /* Suche nach Kopf mit Einträgen */ 
                {
		  positionm = matrix[positionm].wert;
		  
		  if ((matrix[positionm].zeile != 0) || (matrix[positionm].spalte != 0)) /* Falls Masterkopf => Matrix durch => fertig */
		    goto fertig;
		}

	  positionm = matrix[positionm].rechts;

        }
    }

  fertig:
}


void efehler(void)
{
  printf("\n\n\aEingabefehler !!\n\nDie Einträge müssen von links nach rechts zeilenweise eingeben werden !\n");
}

      
void ausgabe(struct vektor *vektor2, int v2start)
{
  int positionv2, i;
  printf("\n\nErgebnis:\n");

  positionv2 = v2start;

  for(i=1 ;; i++)
    {
      printf("\t\t%4d\n",vektor2[positionv2].wert);
      if (vektor2[positionv2].runter == 0)
	break;
      else
	positionv2 = vektor2[positionv2].runter;
    }
}
