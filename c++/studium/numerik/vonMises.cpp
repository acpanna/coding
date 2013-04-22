#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>

int main(void)
{
	char enter, datei[256];

	double **matrix;
	double *vektor1;
	double *vektor2;

	double norm;

	unsigned int zeilen, iterationen;
	unsigned int i, j, k;
 
	printf("Von - Mises - Eigenwert/Eigenvektor - Iteration\n");
	printf("===============================================\n\n");
	printf("\nBitte geben Sie die Dimension der quadrat. Matrix an : ");

	scanf("%u",&zeilen);
 
	if (zeilen == 0)
		exit(1);

	/* Speicherreservierung für Matrix, vektor1 und vektor2 */

	matrix = (double **) calloc(zeilen, sizeof(double));
	vektor1 = (double *) calloc(zeilen, sizeof(double));
	vektor2 = (double *) calloc(zeilen, sizeof(double));
 
	if (matrix == NULL || vektor1 == NULL || vektor2 == NULL)
	{
		printf("\n\nEs konnte nicht genügend freier Speicherplatz bereitgestellt");
		printf("\nwerden, Sie müssen die Dimensionen kleiner wählen");

		exit(1);
	}

	else
	{     
		for (i=0; i<zeilen; i++)
		{ 
			matrix[i] = (double *) calloc(zeilen, sizeof(double));
	
			if (matrix[i] == NULL)
			{
				printf("\n\nEs konnte nicht genügend freier Speicherplatz bereitgestellt");
				printf("\nwerden, Sie müssen die Dimensionen kleiner wählen");

				exit(1);
			}
		}
	}
  
	printf("\nWollen Sie die Matrix aus einer Datei einlesen (j/n) : ");
	scanf(" %c",&enter);

	if (enter == 'j' || enter == 'J')
	{
		printf("Dateiname : ");
		scanf("%s",&datei);

		ifstream fin(datei);     /* Einlesen der Matrix */

		for (i=0; i<zeilen; i++)
			for (j=0; j<zeilen; j++)
			{
				if (fin.eof())
				{
					printf("\nEinlesefehler !!! Programmabbruch !!!");
					exit(1);
				}

				fin >> matrix[i][j];
			}

		fin.close();
	}

	else                       /* Eingabe der Matrix */
	{
		printf("\nBitte geben Sie nun die Matrixeinträge ein :\n");

		for (i=0; i<zeilen; i++)
			for (j=0; j<zeilen; j++)
			{
				printf("Eintrag (%u,%u) : ",i+1,j+1);
				cin >> matrix[i][j];
			}
	}

	printf("\nWollen Sie den Startvektor aus einer Datei einlesen (j/n) : ");
	scanf(" %c",&enter);

	if (enter == 'j' || enter == 'J')
	{
		printf("Dateiname : ");
		scanf("%s",&datei);

		ifstream fin(datei);     /* Einlesen des Startvektors */

		for (i=0; i<zeilen; i++)
		{
			if (fin.eof())
			{
				printf("\nEinlesefehler !!! Programmabbruch !!!");
				exit(1);
			}

			fin >> vektor1[i];
		}

		fin.close();
	}

	else                       /* Eingabe des Startvektors */
	{
		printf("\nBitte geben Sie nun den Startvektor ein :\n");
                                                          
		for (i=0; i<zeilen; i++)
		{
			printf("Eintrag (%u) : ",i+1);
			cin >> vektor1[i];
		}
	}

	printf("\nBitte geben Sie die maximale Iterationszahl ein :  ");
	scanf("%u",&iterationen);
   
	/* ///// Beginn der Iteration ///// */

	for (k=0; k<iterationen; k++)
	{
		norm = 0.0;

		for (i=0; i<zeilen; i++)
			norm += pow(vektor1[i],2);    // Normierung des (Start-) Vektors
	
		norm = sqrt(norm);

		for (i=0; i<zeilen; i++)
			vektor1[i] /= norm;

		for (i=0; i<zeilen; i++)          // Multiplikation A * x(i)
		{
			vektor2[i] = 0.0;

			for(j=0; j<zeilen;j++)
				vektor2[i] += matrix[i][j] * vektor1[j];
		}
	
		for (i=0; i<zeilen; i++)          // Kopiere gewonne Iterierte in vektor1
		{
			double temp;

			temp = vektor1[i];
			vektor1[i] = vektor2[i];
			vektor2[i] = temp;
		}
	
		/* // Ausgabeanfang // */

		printf("\n\nEigenvektor :  (%lg",vektor2[0]);
		
		for (i=1; i<zeilen; i++)
			printf(", %lg",vektor2[i]);
		
		printf(")");
		
		printf("\nKomponentenweise Eigenwerte :  ");		
		for (i=0; i<zeilen; i++)
			printf("%lg  ",vektor1[i]/vektor2[i]);
	
		/* // Ausgabeende // */
	}

	/* /////  Ende der Iteration  ///// */

	printf("\n\n");	
  
	for (i=0; i<zeilen; i++)
		delete matrix[i];

	delete matrix;
	delete vektor1;
	delete vektor2;

	return 0;
}


