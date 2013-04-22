#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>

int main(void)
{
  char enter, datei[256];

  double big, temp;

  double **matrix;
  double *vektor;

  unsigned int *zeilentausch;

  unsigned int zeilen;
  unsigned int i, j, k, zeile;

  printf("Dieses Programm dient zum Lösen linearer Gleichungssysteme\n");
  printf("(für quadratische nxn - Matrizen) unter Verwendung des\n");
  printf("Gauß'schen Algorithmus\n");
  printf("\nBitte geben Sie den Wert für n an : ");

  scanf("%u",&zeilen);
 
  if (zeilen == 0)
    exit(1);

  /* Speicherreservierung für Matrix und Vektor */

  matrix = (double **) calloc(zeilen, sizeof(double));
  vektor = (double *) calloc(zeilen, sizeof(double));
  zeilentausch = (unsigned int *) calloc(zeilen, sizeof(unsigned int));

  if (matrix == NULL || vektor == NULL  || zeilentausch == NULL)
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
    printf("Bitte geben Sie nun die Matrixeinträge ein :\n");

    for (i=0; i<zeilen; i++)
      for (j=0; j<zeilen; j++)
      {
        printf("Eintrag (%u,%u) : ",i+1,j+1);
        scanf("%ld",&(matrix[i][j]));
      }
  }

  printf("\nWollen Sie den Ergebnisvektor aus einer Datei einlesen (j/n) : ");
  scanf(" %c",&enter);

  if (enter == 'j' || enter == 'J')
  {
    printf("Dateiname : ");
    scanf("%s",&datei);

    ifstream fin(datei);     /* Einlesen des Vektors */

    for (i=0; i<zeilen; i++)
    {
      if (fin.eof())
      {
	printf("\nEinlesefehler !!! Programmabbruch !!!");
        exit(1);
      }

      fin >> vektor[i];
    }

    fin.close();
  }

  else                       /* Eingabe des Vektors */
  {
    printf("Bitte geben Sie nun den Ergebnisvektor ein :\n");
                                                          
    for (i=0; i<zeilen; i++)
    {
      printf("Eintrag (%u) : ",i+1);
      scanf("%lg",&(vektor[i]));
    }
  }


  /* //////////////////// Anwendung des Gauß'schen Algorithmus //////////////////// */

  for (j=0; j<zeilen-1; j++)
  {
    big = matrix[j][j];
    zeile = j;
                     
    for (i=1; i<zeilen; i++)
    {                                          
      if (fabs(matrix[i][j]) > fabs(big)) /* Suche nach größtem Pivot - Eintrag in der Spalte */
      {
	big = matrix[i][j];
	zeile = i;
      }
    }

    if (big == 0)
      break;

    for (i=0; i<zeilen; i++)               /*  Vertauschung von Zeilen */
    {                                      /*   Pivot Eintrag wird an  */
      temp = matrix[j][i];                 /* richtige Stelle gebracht */
      matrix[j][i] = matrix[zeile][i];
      matrix[zeile][i] = temp;
    }

    temp = vektor[j];                      /* Ebenfalls Vertauschung im */
    vektor[j] = vektor[zeile];             /*       Ergebnisvektor      */
    vektor[zeile] = temp;

    temp = (double) zeilentausch[j];                /*        Vermerken der        */
    zeilentausch[j] = zeilentausch[zeile];          /* Zeilenvertauschung im Array */
    zeilentausch[zeile] = (unsigned int) temp;
                          
    for (k=j+1; k<zeilen; k++)
    {
      matrix[k][j] = matrix[k][j]/big;                               /* Speichern von 'l' an freiwerdendem Platz */

      vektor[k] = vektor[k] - (matrix[k][j] * vektor[j]);            /* Abziehen von 'l' * Pivoteintrag des Vektors von aktuellem Eintrag */
     
      for (i=j+1; i<zeilen; i++)                                     /* Abziehen von 'l' * Pivotzeile von aktueller Zeile */
	matrix[k][i] = matrix[k][i] - (matrix[k][j] * matrix[j][i]); 
    } 
  }

  /* ////////////////////// Ende des Gauß'schen Algorithmus ////////////////////// */


  printf("\n");                        /* Ausgabe der erweiterten Koeffizientenmatrix */

  for (i=0; i<zeilen; i++)             /*         nach Abbruch des Verfahrens         */
  {
    for (j=0; j<zeilen; j++)
      printf("%5.4lf\t",matrix[i][j]);

    printf("|  %5.4lf",vektor[i]);
    printf("\n");
  }

  /* Berechnung der Lösung */

  if (big == 0)                        /*        Entscheidung, ob System lösbar       */
  {
    for (i=zeile; i<zeilen; i++)
    {
      if (vektor[i] != 0)
      {
	printf("\nDas System besitzt keine Lösung !");
	break;
      }
    }

    if (i == zeilen)
      printf("\nDas System besitzt unendlich viele Lösungen !");
  }

  else if (matrix[zeilen-1][zeilen-1] == 0 && vektor[zeilen-1] != 0)
    printf("\nDas System besitzt keine Lösung !");

  else if (matrix[zeilen-1][zeilen-1] == 0 && vektor[zeilen-1] == 0)
    printf("\nDas System besitzt unendlich viele Lösungen !");

  else                                             
  {
    for (int l=zeilen-1; l>=0; l--)                /*   Falls genau eine Lösung existiert   */
    {
      double sub = 0;                              /*      erfolgt hier die Berechnung      */

      for (j=l+1; j<zeilen; j++)                   /*  durch Lösen des gestaffelten Systems */
         sub += matrix[l][j] * vektor[j];
     
      vektor[l] = (vektor[l]-sub)/matrix[l][l];
    }

    printf("\nDie Lösung des Systems ist : (");    /*       Ausgabe des Lösungsvektors      */

    printf(" %lg",vektor[0]);

    for(l=1; l<zeilen;l++)
      printf(", %lg",vektor[l]);

    printf(" )");
  }

  /* Ausgabe der Zeilen - Permutations - Matrix */

  printf("\n\nAusgabe der Matrix P (Bitte RETURN betätigen) :\n");  

  fflush(stdin);

  scanf("%c",&enter);

  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen; j++)
    {
      if (zeilentausch[i] == j)
	printf("1 ");
      else
	printf("0 ");
    }
    printf("\n");
  }

  /* Ausgabe der oberen Dreiecksmatrix R */

  printf("\nAusgabe der Matrix R (Bitte RETURN betätigen) :\n");

  fflush(stdin);

  scanf("%c",&enter);

  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen; j++)
    {
      if (i > j)
      {
        temp = 0.0;
	printf("%5.4lf\t",temp);
      }
      else
        printf("%5.4lf\t",matrix[i][j]);
    }
    printf("\n");
  }

  /* Ausgabe der unteren Dreiecksmatrix L */

  printf("\nAusgabe der Matrix L (Bitte RETURN betätigen) :\n");

  fflush(stdin);

  scanf("%c",&enter);

  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen; j++)
    {
      if (i == j)
      {
        temp = 1.0;
	printf("%5.4lf\t",temp);
      }
      else if (i > j)
	printf("%5.4lf\t",matrix[i][j]);
      else
      {
	temp = 0.0;
	printf("%5.4lf\t",temp);
      }
    }
    printf("\n");
  }
  
  return 0;
}


