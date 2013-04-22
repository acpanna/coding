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
	double *vektor3;
	
	double eigenwert, big, temp, norm;

	unsigned int *zeilentausch;

	unsigned int zeilen, iterationen;
	unsigned int i, j, k, zeile;
 
	printf("Inverse Iteration von Wielandt\n");
	printf("==============================\n\n");
	printf("\nBitte geben Sie die Dimension der quadrat. Matrix an : ");

	scanf("%u",&zeilen);
 
	if (zeilen == 0)
		exit(1);

	/* Speicherreservierung für Matrix, vektor1, vektor12 und zeilentausch */

	matrix = (double **) calloc(zeilen, sizeof(double));
	vektor1 = (double *) calloc(zeilen, sizeof(double));
	vektor2 = (double *) calloc(zeilen, sizeof(double));
	vektor3 = (double *) calloc(zeilen, sizeof(double));
    zeilentausch = (unsigned int *) calloc(zeilen, sizeof(unsigned int));

	if (matrix == NULL || vektor1 == NULL || zeilentausch == NULL || vektor2 == NULL || vektor3 == NULL )
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

			zeilentausch[i] = i;   /* Besetzung des Zeilen - Permutations - Array */
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

	printf("\nBitte geben Sie die Naehrung des Eigenwerts ein :  ");
	cin >> eigenwert;
	
	printf("\nBitte geben Sie die maximale Iterationszahl ein :  ");
	scanf("%u",&iterationen);

	for (i=0; i<zeilen; i++)
	{
		matrix[i][i] -= eigenwert;        // Bildung von (A - lambda * E)
		vektor2[i] = vektor1[i];          // Erstellen Sicherungskopie Startvektor
	}

	/* //////////////////// Anwendung des Gauß'schen Algorithmus //////////////////// */

	for (j=0; j<zeilen-1; j++)
	{
		big = matrix[j][j];
		zeile = j;
                     
		for (i=1; i<zeilen; i++)
		{                                          
			if (fabs(matrix[i][j]) > fabs(big))		/* Suche nach größtem Pivot - Eintrag in der Spalte */
			{
				big = matrix[i][j];
				zeile = i;
			}
		}

		if (big == 0)
			break;

		for (i=0; i<zeilen; i++)					/*  Vertauschung von Zeilen */
		{											/*   Pivot Eintrag wird an  */
			temp = matrix[j][i];					/* richtige Stelle gebracht */
			matrix[j][i] = matrix[zeile][i];
			matrix[zeile][i] = temp;
		}

		temp = vektor1[j];							/* Ebenfalls Vertauschung im */
		vektor1[j] = vektor1[zeile];				/*      Ergebnisvektor1      */
		vektor1[zeile] = temp;

		temp = (double) zeilentausch[j];			/*        Vermerken der        */
		zeilentausch[j] = zeilentausch[zeile];		/* Zeilenvertauschung im Array */
		zeilentausch[zeile] = (unsigned int) temp;
                          
		for (k=j+1; k<zeilen; k++)
		{
			matrix[k][j] = matrix[k][j]/big;						/* Speichern von 'l' an freiwerdendem Platz */

			vektor1[k] = vektor1[k] - (matrix[k][j] * vektor1[j]);  /* Abziehen von 'l' * Pivoteintrag des vektor1s von aktuellem Eintrag */
     
			for (i=j+1; i<zeilen; i++)                              /* Abziehen von 'l' * Pivotzeile von aktueller Zeile */
				matrix[k][i] = matrix[k][i] - (matrix[k][j] * matrix[j][i]); 
		} 
	}

	///////////////////////// Ende des Gauß'schen Algorithmus //////////////////////////

    // Matrix (A - lambda*E) ist nun LR zerlegt, L im unteren und R im oberen Dreieck //

    /* /////////// Beginn der Iteration /////////// */

	for (k=0; k<iterationen; k++)
	{
		norm = 0.0;

		for (i=0; i<zeilen; i++)
			norm += pow(vektor2[i],2);

		norm = sqrt(norm);

		for (i=0; i<zeilen; i++)                  // Normiere (Start-) Vektor 
		{
			vektor2[i] /= norm;
			vektor1[i] = vektor2[i];              // Kopiere Vektor und rechne mit Kopie  
		}
	
     	for (i=0; i<zeilen; i++)                  // Fuehre Zeilenpermutation mit Vektor durch
			vektor3[i] = vektor1[zeilentausch[i]];
		for (i=0; i<zeilen; i++) 
			vektor1[i] = vektor3[i];
		
		for (i=0; i<zeilen; i++)                   // Loese das System L*c = b  (wobei b der permutierte Vektor ist)
		{
			double sub = 0.0;

			for (j=0; j<i; j++)
				sub +=vektor1[j] * matrix[i][j];

			vektor1[i] = vektor1[i] - sub;
		}
		
		for (int l=zeilen-1; l>=0; l--)            // Loese das System R*y = c    
		{                                          // --> y loest das System (A - lambda*E) * y(i+1) = x(i)
			double sub = 0.0;                             

			for (j=l+1; j<zeilen; j++)                   
				sub += matrix[l][j] * vektor1[j];
     
			vektor1[l] = (vektor1[l] - sub)/matrix[l][l];
		} 	
 		
		// Es gilt: vektor1 == y(i+1) und vektor2 == x(i)
 
  		/* // Ausgabeanfang // */
		
		printf("\n\nEigenvektor :  ( %lg", vektor2[0]);
	
		for (i=1; i<zeilen; i++)
			printf(", %lg",vektor2[i]);
		
		printf(" )");
		
		printf("\nKomponentenweiser Eigenwert : ");
    	
		for (i=0; i<zeilen; i++)
			printf(" %lg",1.0/(vektor1[i]/vektor2[i])+eigenwert);

		/* // Ausgabeende // */
	
        for (i=0; i<zeilen; i++)        // Kopiere gewonne Iterierte in vektor2
			vektor2[i] = vektor1[i];    // und fahre mit Iteration fort
	}  

	/* ///////////  Ende der Iteration  /////////// */

	printf("\n\n");

	for (i=0; i<zeilen; i++) 
		delete matrix[i];

	delete matrix;
	delete vektor1;
	delete vektor2;
	delete vektor3;
	delete zeilentausch;

	return 0;
}


