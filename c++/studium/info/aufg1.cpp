#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int term, terma, termb, termc;

int *pola, *polb, *polc;

int main(void)
{
  printf("\nProgramm zur Berechnung des Produkts zweier Polynome A und B\n");
  printf("------------------------------------------------------------\n");

  printf("\nBitte geben Sie ein aus wievielen Termen Polynom A besteht : ");
  scanf("%d",&terma);
  printf("Bitte geben Sie ein aus wievielen Termen Polynom B besteht : ");
  scanf("%d",&termb);


  /* Allocate Anweisung für pola, polb, polc (Speicherplatzreservierung) */


  pola=(int *)malloc(sizeof(int)*(terma*2+1));
  polb=(int *)malloc(sizeof(int)*(termb*2+1));
  polc=(int *)malloc(sizeof(int)*(terma*termc*2+1));


  pola[0]=terma;     /*    Belege jeweils die erste Position der    */
  polb[0]=termb;     /*  Felder pola und polb mit Anzahl der Terme  */

  /* Eingabe der einzelnen Terme für A */     

  termc=0;
  for (term=1; term<2*pola[0]; term++)
    {
      termc = termc+1;
      printf("\nBitte geben Sie den Exponenten des %d.-ten Termes von A ein    : ",termc);
      scanf("%d",&pola[term]);
      term = term +1;
      printf("Bitte geben Sie den Koeffizienten des %d.-ten Termes von A ein : ",termc);
      scanf("%d",&pola[term]);
    }

  printf("\n\n");

  /* Eingabe der einzelnen Terme für B */

  termc=0;
  for (term=1; term<2*polb[0]; term++)
    {
      termc = termc+1;
      printf("\nBitte geben Sie den Exponenten des %d.-ten Termes von B ein    : ",termc);
      scanf("%d",&polb[term]);
      term = term +1;
      printf("Bitte geben Sie den Koeffizienten des %d.-ten Termes von B ein : ",termc);
      scanf("%d",&polb[term]);
    }


  /* Hier beginnt die Multiplikation von A und B */


  termc=1;
  for (terma=1; terma<2*pola[0]; terma=terma+2)
    {
       for (termb=1; termb<2*polb[0]; termb++)
        {
	  polc[termc]=pola[terma]+polb[termb];     /*  Addition der Exponenten  */						       
						    
	  termb = termb+1;                               
          termc = termc+1;					     

          polc[termc]=pola[terma+1]*polb[termb];   /* Multiplikation der Koeffizienten */

          termc = termc+1;                              
        }
    }

  polc[0]=pola[0]*polb[0];

 
  /* Verkürzung des Polynoms C */ 


  for (terma=1; terma<2*polc[0]; terma=terma+2)
    {
      for (termb=terma+2; termb<2*polc[0]; termb=termb+2)
        {
	  if (polc[terma]==polc[termb])
	    {
  	      polc[terma+1]=polc[terma+1]+polc[termb+1];    /*  Kommen zwei Terme mit gleichem  */
 	      polc[termb]=polc[2*polc[0]-1];                /*     Exponenten vor, so werden    */
 	      polc[termb+1]=polc[2*polc[0]];                /*  diese zusammengefaßt, die Ko-   */  
 	      polc[2*polc[0]]=0;                            /*        effizienten addiert und   */
 	      polc[2*polc[0]-1]=0;                          /* schließlich wird der Array noch  */
	      polc[0]=polc[0]-1;                            /*     um ein Element verkürzt.     */
              termb = termb-2;
	    }
        }
    } 
        

  /* Ausgabe von Polynom C */


  printf("\n\n\nDas durch Multiplikation von Polynom A mit Polynom B entstehende\n");
  printf("Polynom C ist von folgender Gestalt :  \n\n");
  printf("C(x) = ");

  for (term=1; term<2*polc[0]; term=term+2)
    {
      printf("+(%d",polc[term+1]);
      printf("x^%d) ",polc[term]);
    }

  free(pola);
  free(polb);
  free(polc);

  return 0;
}