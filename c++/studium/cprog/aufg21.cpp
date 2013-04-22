/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 07
    Aufgabennr.   	: 21
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
#include <math.h>
 
const int MAXITER = 30;             /* maximal durchzufuehrende Iterationen */
const double ITEREPS = 1.0e-8;      /* Iterationsgenauigkeit                */
 
int main(void) 
{
  char    weiter;
  double  x, test;
  int     iter, start_wahl;
       
  do
  {
    printf("  (1) vordefinierte Startpunkte\n");
    printf("  (2) selbst einzugebender Startpunkt\n");
    printf("\nWahl (1/2)? ");
    scanf("%d", &start_wahl);

    if (start_wahl != 2)
    {
      printf("vordefinierte Startpunkte:\n");
      printf("  (1) x0 = -10.0\n");
      printf("  (2) x0 = 0.0\n");
      printf("  (3) x0 = 0.5\n");
      printf("  (4) x0 = 0.55\n");
      printf("  (5) x0 = 1.0\n");
      printf("  (6) x0 = 100.0\n");
      printf("\nWahl (1/2)? ");
      scanf("%d", &start_wahl);

      switch (start_wahl)
      {
        case 1: x = -10.0;
                break;
        case 2: x = 0.0;
                break;
        case 3: x = 0.5;
                break;
        case 4: x = 0.55;
                break;
        case 5: x = 1.0;
                break;
        case 6: x = 100.0;
                break;
        default: printf("Falsche Eingabe!\n");
                 x = 0.0;
      }     
  
    }
    else
    {
      printf("Startwert:");
      scanf("%lf",&x);
      fflush(stdin);
    }
         
      iter=0;
      printf("\niter=%3d   x=%1.9f\n",iter,x);

      do  
      {
        iter++;
        x = exp(-x);
        test = fabs(x-exp(-x));
            
        printf("iter=%3d   x=%1.9f\n",iter,x);
      } while (test > ITEREPS && iter < MAXITER);
      
     
      printf("\n%d Iterationen\n\n", iter);
      printf("Fixpunkt x=%1.9f\n", x);
      printf("Fehler   r=%e\n", test);

      printf("\nWeiter (j/n)? ");
      weiter = getchar();

      if (weiter == '\n')
      {
        fflush(stdin);
        weiter = getchar();
      }

      printf("\n");

  } while (weiter != 'n');
           
  return 0;
}
