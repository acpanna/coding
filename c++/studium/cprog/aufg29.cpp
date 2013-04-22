/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 10
    Aufgabennr.   	: 29
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXANZAHL 200


struct komplex {
                 double re, im;
               };

struct komplex add(struct komplex x, struct komplex y);
struct komplex mult(struct komplex x, struct komplex y);
double betrag(struct komplex x);

int main(void)
{
  struct komplex z[MAXANZAHL] = {{ 0.0, 0.0}}, c = { 0.0, 0.0};

  FILE *fp;

  double pmin, pmax, qmin, qmax, dp, dq, p, q, M;
  int K, rx, ry, np, nq, k;

  printf("\nBitte geben Sie die Intervallgrenzen ein :");
  printf("\n\nRealteil (untere Grenze) : \t");
  scanf("%lg",&pmin);
  printf("Realteil (obere Grenze) : \t");
  scanf("%lg",&pmax);
  printf("Imaginärteil (untere Grenze) : \t");
  scanf("%lg",&qmin);
  printf("Imaginärteil (obere Grenze) : \t");
  scanf("%lg",&qmax);

  printf("\nBitte wählen Sie die maximale Iterationszahl ( < %d ) : ",MAXANZAHL);
  scanf("%d",&K);
  printf("Bitte geben Sie die Abbruchschranke ein ( > 0 ): \t");
  scanf("%lg",&M);

  printf("\nBitte geben Sie die Auflösung des resultierenden");
  printf("\nBildes ein (z.B. 300 300) : ");
  scanf("%d %d",&rx,&ry);

  fp = fopen("fraktneu.dat", "w");
  if (fp == NULL)
  {
    printf("Konnte Datei \"fraktneu.dat\" nicht zum Schreiben oeffnen!\n"
           "Abbruch!\n");
    exit(1);
  }

  dp = fabs((pmax-pmin)/(rx-1));
  dq = fabs((qmax-qmin)/(ry-1));

  for (np = 0; np<rx; np++)
  {
    for (nq = 0; nq<ry; nq++)
    {
      p = pmin + np*dp;
      q = qmin + nq*dq;
      c.re = p;
      c.im = q;

      for (k=0; k<K; k++)
      {
        if (betrag(z[k]) > M)
        {
       	  k = k % 16;
	  break;
        }

        z[k+1] = add(mult(z[k],z[k]),c); 
      }

      if (k==K)
        k = 17;
              
      fprintf(fp," %d",k);
    }

    fprintf(fp, "\n");
  }
    
  fclose(fp);   

  printf("Fraktal wurde in \"fraktneu.dat\" gespeichert!\n");

  return 0;
}


struct komplex add(struct komplex x, struct komplex y)
{
  x.re += y.re;
  x.im += y.im;
  return x;
}


struct komplex mult(struct komplex x, struct komplex y)
{
  struct komplex z;

  z.re = x.re*y.re - x.im*y.im;
  z.im = x.re*y.im + x.im*y.re;
  return z;
}


double betrag(struct komplex x)
{
  return sqrt(pow(x.re, 2) + pow(x.im, 2));
}
