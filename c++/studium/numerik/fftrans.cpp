#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int FFT (int mu, double re[], double im[]);
int HornerX (int mu, double re[], double im[], double x);

int main(void)
{
	int i, eingabe;

	double stelle;

	double *real;
	double *imag;

	printf("\nFast - Fourier - Transform (Algorithmus von Cooley und Tukey)");
	printf("\nfftfftfftfftfftfffftfftfftfftfftfftfftfftfftfftfftfftfftfftff");
	printf("\n\n\nBitte geben Sie den Wert fuer mu ein");
	printf("\n(Programm erwartet 2 hoch mu Eingabedaten) : ");
	scanf("%d",&eingabe);

    real = (double *) calloc((int) pow(2,eingabe),sizeof(double));
	imag = (double *) calloc((int) pow(2,eingabe),sizeof(double));

	if (real == 0 || imag == 0)
	{
		printf("\n\nSpeicher - Reservierung fehlgeschlagen, Programmabbruch !!!");
		exit(1);
	}

    printf("\n\nEingabe der Daten in aufsteigender Reihenfolge (f0, f1, ...) :");
	printf("\n\n");
	
	for (i=0; i<pow(2,abs(eingabe)); i++)
	{
		printf("RealTeil des %d.-ten Eingabedatums : ",i+1);
		scanf("%lf",&real[i]);
		printf("ImaginaerTeil des %d.-ten Eingabedatums : ",i+1);
		scanf("%lf",&imag[i]);
	}

	if (FFT(eingabe, real, imag) == 0)
	{
		printf("\n\nWaehrend der Berechnung trat ein Fehler auf, Programmabbruch !!!");
		exit(1);
	}

	printf("\n\nAusgabe der Fourierkoeffizienten in aufsteigender Reihenfolge (a0, a1, ...) :");
	printf("\n\n");
	
	printf("%lg + (%lgi)", real[0],imag[0]);

	for (i=1; i<pow(2,eingabe); i++)
		printf(", %lg + (%lgi)", real[i],imag[i]);

	printf("\n\n");

	printf("\nBitte geben Sie eine Zwischenstelle x ein,");
	printf("\nan der das Fourierpolynom p ausgewertet werden soll : ");

    scanf("%lf",&stelle);
	
	if (HornerX(eingabe, real, imag, stelle) == 0)
	{
		printf("\n\nWaehrend der Berechnung trat ein Fehler auf, Programmabbruch !!!");
		exit(1);
	}

	printf("\np(x) = %lg + (%lgi)",real[0],imag[0]);

	printf("\n\n");

	free(real);
	free(imag);

	return 0;
}

int FFT (int mu, double re[], double im[])
{
	double PI = asin(1) * 2.0;

    double *re2, *im2;
                          
	re2 = (double *) calloc((int) pow(2,mu),sizeof(double));
	im2 = (double *) calloc((int) pow(2,mu),sizeof(double));

	if (re2 == 0 || im2 == 0)
	{
		printf("\n\nSpeicher - Reservierung fehlgeschlagen, Programmabbruch !!!");
		exit(1);
	}

	for (int s=1; s<= mu; s++)
	{
		int M, R;

		M = (int) pow(2,s-1);
		R = (int) pow(2,mu-s);

		for (int k=0; k<= R-1; k++)
			for (int j=0; j<= M-1; j++)
			{
				re2[(int)pow(2,s)*k+j] = 1.0/2.0 * (re[(int)pow(2,s-1)*k+j] + re[(int)pow(2,s-1)*(R+k)+j] * cos(-j*2*PI/pow(2,s)) - im[(int)pow(2,s-1)*(R+k)+j] * sin(-j*2*PI/pow(2,s)));
				im2[(int)pow(2,s)*k+j] = 1.0/2.0 * (im[(int)pow(2,s-1)*k+j] + re[(int)pow(2,s-1)*(R+k)+j] * sin(-j*2*PI/pow(2,s)) + im[(int)pow(2,s-1)*(R+k)+j] * cos(-j*2*PI/pow(2,s)));

				re2[(int)pow(2,s)*k+M+j] = 1.0/2.0 * (re[(int)pow(2,s-1)*k+j] - re[(int)pow(2,s-1)*(R+k)+j] * cos(-j*2*PI/pow(2,s)) + im[(int)pow(2,s-1)*(R+k)+j] * sin(-j*2*PI/pow(2,s)));
				im2[(int)pow(2,s)*k+M+j] = 1.0/2.0 * (im[(int)pow(2,s-1)*k+j] - re[(int)pow(2,s-1)*(R+k)+j] * sin(-j*2*PI/pow(2,s)) - im[(int)pow(2,s-1)*(R+k)+j] * cos(-j*2*PI/pow(2,s)));
			}

		for (int i=0; i<(int)pow(2,mu); i++)
		{
			re[i] = re2[i];
		    im[i] = im2[i];
		}
	}
	
	free(re2);
	free(im2);
	
	return 1;
}

int HornerX (int mu, double re[], double im[], double x)
{
    if (mu == 0) 
		return 1;

	for (int i=(int)pow(2,mu)-2; i>= 0; i--)
	{
		re[i] = re[i+1]*cos(x) - im[i+1]*sin(x) + re[i];
		im[i] = re[i+1]*sin(x) + im[i+1]*cos(x) + im[i];
	}

	// Ergebnis steht in re[0] und im[0]

    return 1;
}