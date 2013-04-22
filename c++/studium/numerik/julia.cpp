#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXANZAHL 201

struct komplex
{
	double re, im;
};

struct komplex add(struct komplex x, struct komplex y);
struct komplex mult(struct komplex x, struct komplex y);
double betrag(struct komplex x);

int main(void)
{
  struct komplex z[MAXANZAHL] = {{ 0.0, 0.0}}, c = { 0.0, 0.0};

  FILE *fp;

  double xmin, xmax, ymin, ymax, dx, dy, x, y, M;
  int K, rx, ry, nx, ny, k;

  printf("\nBitte geben Sie die Intervallgrenzen ein :");
  printf("\n\nRealteil (untere Grenze) : ");
  scanf("%lg",&xmin);
  printf("Realteil (obere Grenze)  : ");
  scanf("%lg",&xmax);
  printf("Imaginaerteil (untere Grenze) : ");
  scanf("%lg",&ymin);
  printf("Imaginaerteil (obere Grenze)  : ");
  scanf("%lg",&ymax);
  printf("\n\nBitte geben Sie 'c' ein :");
  printf("\n\nRealteil      : ");
  scanf("%lg",&(c.re));
  printf("Imaginaerteil : ");
  scanf("%lg",&(c.im));

  printf("\nBitte waehlen Sie die maximale Iterationszahl ( <= %d ) : ",MAXANZAHL - 1);
  scanf("%d",&K);
  printf("Bitte geben Sie die Abbruchschranke ein ( > 0 ): ");
  scanf("%lg",&M);

  printf("\nBitte geben Sie die Aufloesung des resultierenden");
  printf("\nBildes ein (z.B. 300 300) : ");
  scanf("%d %d",&rx,&ry);
  
  fp = fopen("fraktneu.dat", "w");
  if (fp == NULL)
  {
    printf("Konnte Datei \"fraktneu.dat\" nicht zum Schreiben oeffnen!\n"
           "Abbruch!\n");
    exit(1);
  }

  dx = fabs((xmax-xmin)/(rx-1));
  dy = fabs((ymax-ymin)/(ry-1));


  for (nx = 0; nx<rx; nx++)
  {
    for (ny = 0; ny<ry; ny++)
    {
		x = xmin + nx*dx;
		y = ymin + ny*dy;
	  
		z[0].re = x;
		z[0].im = y;
     
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
