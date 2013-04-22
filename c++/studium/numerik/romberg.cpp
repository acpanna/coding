#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void romberg(double a, double b, int anzahl);
double func(double x);

int main(void)
{
    printf("Beispielausgabe: f(x) = x^2, a = 0, b = 1, anzahl = 5\n");

	romberg(0, 1, 5);
	return 0;
}

void romberg(double a, double b, int anzahl)
{
	int i, k, q, n;
    double h, s;

	double *T;
		
	T = (double *) malloc(anzahl * sizeof(double));
   
	if (T == NULL)
	{
		printf("\nZu wenig Speicher -- Programmabbruch !!!");
		exit(1);
	}

/// Beginn des Romberg - Algorithmus ///	

	n = 1;
	h = b - a;
	
	T[0] = 0.5 * h * (func(a) + func(b));

	printf("\n %lf",T[0]);
	
	for (k=1; k<=anzahl; k++)
	{
	    s = 0;
		h = 0.5 * h;
		n = 2 * n;
		q = 1;

		for (i=1; i <= n-1; i=i+2)
			s = s + func(a + i*h);
		
		T[k] = 0.5 * T[k-1] + s*h;
		printf("\n %lf",T[k]);

		for (i=k-1; i>=0; i--)
		{
			q = q*4;
			T[i] = T[i+1] + (T[i+1] - T[i]) / (q-1);
			printf(" %lf",T[i]);
		}
	}

///  Ende des Romberg - Algorithmus  ///

	free(T);

	printf("\n\n");
}

double func(double x)
{
	return (pow(x,2));  // x - Quadrat - Funktion
}


