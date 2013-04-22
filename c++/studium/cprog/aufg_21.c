#include <stdio.h>
#include <math.h>
 
const int MAXITER = 30;             /* maximal durchzufuehrende Iterationen */
const double ITEREPS = 1.0e-8;      /* Iterationsgenauigkeit                */
 
int main(void) 
{
  char    weiter;
  double  x, test;
  int     iter, start_wahl;
       
  loop:
    printf("  (1) vordefinierte Startpunkte\n");
  printf("  (2) selbst einzugender Startpunkt\n");
  printf("\nWahl (1/2)? ");
  scanf("%d", &start_wahl);

  if (start_wahl == 2)
    goto eingabe;

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
  goto iter;

  eingabe:
    printf("Startwert:");
  scanf("%lf",&x);
  fflush(stdin);

  iter: 
    iter=0;
  printf("\niter=%3d   x=%1.9f\n",iter,x);

  next_iter: 
    iter++;
  x = exp(-x);
  test = fabs(x-exp(-x));
            
  printf("iter=%3d   x=%1.9f\n",iter,x);
  if (test > ITEREPS && iter < MAXITER)
    goto next_iter;
     
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
  if (weiter == 'n')
    goto ende;

  printf("\n");
  goto loop;

  ende:
    ;

  return 0;
}
