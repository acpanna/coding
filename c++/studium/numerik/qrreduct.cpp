#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
	unsigned int i, j, n, l, zeilen, spalten;
	unsigned int sing = 0;
	
	double **A;
	double **P;
	double **P2;
	double **temp;
	double *b;

	printf("Bitte geben Sie die Zeilenzahl ein  : ");
	scanf("%u",&zeilen);
	printf("Bitte geben Sie die Spaltenzahl ein : ");
	scanf("%u",&spalten);
	
    A    = (double **) calloc(zeilen, sizeof(double));
    P    = (double **) calloc(zeilen, sizeof(double));
    P2   = (double **) calloc(zeilen, sizeof(double));
    temp = (double **) calloc(zeilen, sizeof(double));
	b    = (double *)  calloc(zeilen, sizeof(double));

    if (A == NULL || P == NULL || P2 == NULL || temp == NULL || b == NULL)
	{
		printf("\n\nEs konnte nicht genügend freier Speicherplatz bereitgestellt");
        printf("\nwerden, Sie müssen die Dimensionen kleiner wählen");

        exit(1);
	}

    else
	{
		for (i=0; i<zeilen; i++)
		{
			A[i]    = (double *) calloc(spalten + 1, sizeof(double));
			P[i]    = (double *) calloc(zeilen,      sizeof(double));
	        P2[i]   = (double *) calloc(zeilen,      sizeof(double));
			temp[i] = (double *) calloc(zeilen,      sizeof(double));

            if (A[i] == NULL || P[i] == NULL || P2[i] == NULL || temp[i] == NULL)
			{
				printf("\n\nEs konnte nicht genügend freier Speicherplatz bereitgestellt");
                printf("\nwerden, Sie müssen die Dimensionen kleiner wählen");

	            exit(1);
			}
		}
	}

    for (i=0; i<zeilen; i++)                             // Vorbelegung von P mit Einheitsmatrix 
		for (j=0; j<zeilen; j++)                    
		{
			if (i == j)
				P[i][j] = 1.0;
			else
				P[i][j] = 0.0;
		}

    printf("\n");

	for (i=0; i<zeilen; i++)
		for (j=0; j<spalten; j++)
		{
			printf("Eintrag (%u,%u) : ",i+1,j+1);    
		    scanf("%lf",&(A[i][j]));                     // Eingabe von A
	
		}

	printf("\n\nEingabe der rechten Seite (Vektor) :\n\n");
		
	for (i=0; i<zeilen; i++)
	{
		printf("Komponente (%u) : ",i+1);
		scanf("%lf",&A[i][spalten]);                     // Eingabe des Ergebnisvektors 
	}


	//////////////////////////// Householder Reduktion ////////////////////////////

	for (j = 0; j<spalten; j++)
	{
        double sigma = 0.0, beta = 0.0, k = 0.0; 

		for (i=j; i<zeilen; i++)
			sigma += pow(A[i][j],2);                     // Berechnung von Sigma

		if (sigma == 0)                                  // Singulaerer Fall
		{
			beta = 0.0;
			sing = 1;
		}

		else 
		{
			sigma = sqrt(sigma);

			if (A[j][j] < 0)                             // Berechnung von k
				 k = sigma;
			else 
				 k = -sigma;

		    beta = 1/(sigma*(sigma + fabs(A[j][j])));    // Berechnung von beta
			
			b[j] = A[j][j] - k;                          // Aufstellen des Vektors b

			for (i=j+1; i<zeilen; i++)
				 b[i] = A[i][j];
		}	
		
		for (i=j; i<zeilen; i++)                         // Belegung von P2 im Block rechts unten
			for (n=j; n<zeilen; n++)
			{
				if (n==i)
					P2[i][n] = 1.0 - beta*b[i]*b[n];
				else 
					P2[i][n] = - beta*b[i]*b[n];
			}
		
	    for (l=0; l<zeilen; l++)                         // Matrizenmultiplikation von P2 * P (nur relevante Eintraege)
			for (i=j; i<zeilen; i++)                     // Ergebnis in Matrix temp
			{
				temp[i][l] = 0.0;

                for (n=j; n<zeilen; n++)
					temp[i][l] += P2[i][n] * P[n][l];
			} 

	    for (i=j; i<zeilen; i++)                         // Kopieren von temp in P (nur relevante Eintraege) 
			for (n=0; n<zeilen; n++)
				P[i][n] = temp[i][n];
    
		for (l=j; l<spalten+1; l++)                      // Matrizenmultiplikation von P2 * A (nur relevante Eintraege)
			for (i=j; i<zeilen; i++)                     // Ergebnis in Matrix temp
			{
				temp[i][l] = 0.0;

				if (l == j && i > j)                     // Nullmachen der Eintraeage unter Diagonale in j-ter Spalte 
					continue;

                for (n=j; n<zeilen; n++)
					temp[i][l] += P2[i][n] * A[n][l];
			} 

	    for (i=j; i<zeilen; i++)                         // Kopieren von temp in A (nur relevante Eintraege)
			for (n=j; n<spalten+1; n++)
				A[i][n] = temp[i][n];
 
	
	}

	//////////////////////// Ende der Householder Reduktion ///////////////////////


    // Ausgabe von R

    printf("\nMatrix R:\n"); 

    for (i=0; i<zeilen; i++)
	{
		printf("\n");
	    for (j=0; j<spalten; j++)
		    printf(" %9lg",A[i][j]);
	}

    // Ausgabe von Q (gesterntes bzw. transponiertes P)
    
	printf("\n\nMatrix Q:\n"); 
	
	for (i=0; i<zeilen; i++)
	{
		printf("\n");
    	for (j=0; j<zeilen; j++)
 		    printf(" %9lg",P[j][i]);
	}

    // Ausgabe, ob A singulaer bzw. regulaer war

	printf("\n\n"); 

	if (sing == 1)
		printf("Die eingegebene Matrix war singulaer.\n");
	else
	{
		printf("Die eingegebene Matrix war regulaer.\n");

		for (int z=spalten-1; z>=0; z--)                 // Falls A regulaer war   
		{
			double sub = 0;                              // erfolgt hier die Berechnung der Loesung

            for (j=z+1; j<spalten; j++)                  // durch Loesen des gestaffelten Systems 
				sub += A[z][j] * A[j][spalten];
     
            A[z][spalten] = (A[z][spalten]-sub)/A[z][z];
		}

        printf("\nDie Loesung des Systems ist : (");     // Ausgabe des Loesungsvektors

        printf(" %lg",A[0][spalten]);

        for(l=1; l<spalten;l++)
			printf(", %lg",A[l][spalten]);

        printf(" )\n");
	}
	
	return 0;
}