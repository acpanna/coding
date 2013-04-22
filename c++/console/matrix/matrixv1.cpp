#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *mat;
double *matrixA;
double *matrixB;
double *matrixC;

int zeilenA = 0, zeilenB = 0, zeilenC = 0;
int spaltenA = 0, spaltenB = 0, spaltenC = 0;

void eingabe(int &zeilen, int &spalten);
void mattrans(double *matrix, int &zeilen, int &spalten);
void skmult(double *matrix, int zeilen, int spalten, double skalar);
void potmat(double *matrix1, double *matrix2, int zeilen, int potenz);
void matadd(double *matrix1, double *matrix2, double *matrix3,
            int zeilen1, int zeilen2, int &zeilen3,
	    int spalten1, int spalten2, int &spalten3);
void matmult(double *matrix1, double *matrix2, double *matrix3,
             int zeilen1, int zeilen2, int &zeilen3,
	     int spalten1, int spalten2, int &spalten3);
void matadj(double *matrix1, double *matrix2, int zeilen);
void ausgabe(double *matrix, int zeilen, int spalten);
void savemat(double *matrix, int zeilen, int spalten);
double detmat(double *matrix1, int zeilen);


int main(void)
{
  FILE *fp;

  char datei[256];
  char enter;
  char ciao = 'n';

  double det;

  int i, j, wahl;
  int zeil = 0, spalt = 0;
  
  while (ciao != 'j')
  {
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t           M A T R I X  v1.0   (by Heiko Vogel in 1999)");
    printf("\n\t\t           =-=-=-=-=-=-=-=-=");
    printf("\n\n");
    printf("\n\t\tAuswahlmenü:\n");
    printf("\n\t\tEingabe der Matrizen                  1");
    printf("\n\t\tTransposition einer Matrix            2");
    printf("\n\t\tSkalare Multiplikation einer Matrix   3");
    printf("\n\t\tDeterminante einer Matrix             4");
    printf("\n\t\tAdjungierte einer Matrix              5");
    printf("\n\t\tInverse einer Matrix                  6");
    printf("\n\t\tAddition der Matrizen 1 und 2         7");
    printf("\n\t\tMultiplikation der Matrizen 1 und 2   8");
    printf("\n\t\tPotenz einer Matrix                   9");
    printf("\n\t\tAusgabe der Matrizen                 10");
    printf("\n\t\tLaden einer Matrix                   11");
    printf("\n\t\tSpeichern einer Matrix               12");
    printf("\n\t\tund tschüß                           13");
    printf("\n\n\t\tWie lautet Ihre Wahl : ");
    scanf("%d",&wahl);

    switch(wahl)
    {
      case 1: printf("\nWollen Sie die erste oder die zweite Matrix eingeben (1 oder 2) : ");
              scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
		break;
	      else if (wahl == 1)
		mat = matrixA;
              else if (wahl == 2)
                mat = matrixB;

	      eingabe(zeil, spalt);
              	     
	      mat = (double *) realloc(mat, zeil * spalt * sizeof(double));

              if (mat == NULL)
              {
		printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                fflush(stdin);

                printf("\n\nBitte RETURN drücken");
                scanf("%c",&enter);

		break;
	      }
 
              printf("\n");

              for(i=0; i<zeil; i++)
              {
                for(j=0; j<spalt; j++)
                {
                  printf("Eintrag der %2d. Zeile und %2d. Spalte : ",i+1,j+1);
                  scanf("%lf",&mat[i*spalt + j]);
                }
              }

	      if (wahl == 1)
	      {
	        matrixA = mat;
		zeilenA = zeil;
		spaltenA = spalt;
              }
	      else
	      {
	      	matrixB = mat;
		zeilenB = zeil;
		spaltenB = spalt;
	      }
	      
  	      break;


      case 2: printf("\nWollen Sie die erste oder die zweite Matrix transponieren (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
		mattrans(matrixA, zeilenA, spaltenA);
	      else if (wahl == 2)
	        mattrans(matrixB, zeilenB, spaltenB);
	      
	      break;


      case 3: printf("\nWollen Sie die die erste oder die zweite Matrix mit einem");
              printf("\nSkalar multiplizieren (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
		mat = matrixA;
		zeil = zeilenA;
		spalt = spaltenA;
              }
	      else if (wahl == 2)
              {
		mat = matrixB;
		zeil = zeilenB;
		spalt = spaltenB;
              }
              else
		break;

	      printf("\nMit welchem Skalar soll multipliziert werden : ");
              scanf("%lg",&det);
               
	      skmult(mat, zeil, spalt, det);

	      break;


      case 4: printf("\nWollen Sie die Determinante der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
		mat = matrixA;
		zeil = zeilenA;
		spalt = spaltenA;
              }
	      else if (wahl == 2)
              {
		mat = matrixB;
		zeil = zeilenB;
		spalt = spaltenB;
              }
              else
		break;

	      if (zeil != spalt)
              {
	         printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");

		 fflush(stdin);

                 printf("\n\nBitte RETURN drücken");
                 scanf("%c",&enter);

		 break;
	      }

              det = detmat(mat, zeil);

	      printf("\nDie Determinante der Matrix ist : %lg",det);

	      fflush(stdin);

              printf("\n\nBitte RETURN drücken");
              scanf("%c",&enter);

              break;


      case 5: printf("\nWollen Sie die Adjungierte der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
		mat = matrixA;
		zeil = zeilenA;
		spalt = spaltenA;
              }
	      else if (wahl == 2)
              {
		mat = matrixB;
		zeil = zeilenB;
		spalt = spaltenB;
              }
              else
		break;

	      if (zeil != spalt)
              {
	         printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");

		 fflush(stdin);

                 printf("\n\nBitte RETURN drücken");
                 scanf("%c",&enter);

		 break;
	      }

	      else if (zeil <= 1)
	      {
		printf("\nDie Adjungierte einer Zahl ist immer gleich 1 !");

	        fflush(stdin);

                printf("\n\nBitte RETURN drücken");
                scanf("%c",&enter);

	        break;
	      }

	      matrixC = (double *) realloc(matrixC, zeil * zeil * sizeof(double));

	      if (matrixC == NULL)
              {
		printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                fflush(stdin);

                printf("\n\nBitte RETURN drücken");
                scanf("%c",&enter);

		break;
	      }

	      zeilenC = zeil;
              spaltenC = spalt;

	      matadj(mat, matrixC, zeil);

              break;


      case 6: printf("\nWollen Sie die Inverse der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
		mat = matrixA;
		zeil = zeilenA;
		spalt = spaltenA;
              }
	      else if (wahl == 2)
              {
		mat = matrixB;
		zeil = zeilenB;
		spalt = spaltenB;
              }
              else
		break;
             	     
	      if (zeil != spalt)
              {
	         printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");

		 fflush(stdin);

                 printf("\n\nBitte RETURN drücken");
                 scanf("%c",&enter);

		 break;
	      }

	      else
	      {
		det = detmat(mat, zeil);

		if (det == 0)
		{
                  printf("\nDie Matrix kann nicht invertiert werden (det = 0) !");
		  
		  fflush(stdin);

                  printf("\n\nBitte RETURN drücken");
                  scanf("%c",&enter);

		  break;
		}

		zeilenC = zeil;
                spaltenC = spalt;

		matrixC = (double *) realloc(matrixC, zeil * zeil * sizeof(double));

	        if (matrixC == NULL)
                {
		  printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
		  printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                  fflush(stdin);

                  printf("\n\nBitte RETURN drücken");
                  scanf("%c",&enter);

	          break;
		}

		if (zeil > 1)
                {
		  matadj(mat, matrixC, zeil);
		  skmult(matrixC, zeilenC, spaltenC, 1.0/det);
		}
		else
                  matrixC[0] = 1.0/mat[0];
	      }
              
              break;


      case 7: matrixC = (double *) realloc(matrixC, spaltenA * zeilenA * sizeof(double));

	      if (matrixC == NULL)
              {
		printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                fflush(stdin);

                printf("\n\nBitte RETURN drücken");
                scanf("%c",&enter);

		break;
	      }

              matadd(matrixA, matrixB, matrixC, zeilenA, zeilenB, zeilenC, spaltenA, spaltenB, spaltenC);

              break;


      case 8: printf("\nWollen Sie (1)  mat1 * mat2           ");
              printf("\n                   oder               ");
              printf("\n	   (2)  mat2 * mat1 rechnen : ");

	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
                matrixC = (double *) realloc(matrixC, zeilenA * spaltenB * sizeof(double));

		if (matrixC == NULL)
                {
		  printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                  printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                  fflush(stdin);

                  printf("\n\nBitte RETURN drücken");
                  scanf("%c",&enter);

		  break;
	        }

		matmult(matrixA, matrixB, matrixC, zeilenA, zeilenB, zeilenC, spaltenA, spaltenB, spaltenC);
              }
	      else if (wahl == 2)
	      {
		matrixC = (double *) realloc(matrixC, zeilenB * spaltenA * sizeof(double));

		if (matrixC == NULL)
                {
		  printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                  printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                  fflush(stdin);

                  printf("\n\nBitte RETURN drücken");
                  scanf("%c",&enter);

		  break;
	        }

		matmult(matrixB, matrixA, matrixC, zeilenB, zeilenA, zeilenC, spaltenB, spaltenA, spaltenC);
              }

	      break;


     

      case 9: printf("\nWollen Sie die die erste oder die zweite Matrix ");
	      printf("\npotenzieren (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if (wahl == 1)
              {
		mat = matrixA;
		zeil = zeilenA;
		spalt = spaltenA;
              }
	      else if (wahl == 2)
              {
		mat = matrixB;
		zeil = zeilenB;
		spalt = spaltenB;
              }
              else
		break;

	      if (zeil != spalt)
              {
	         printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");

		 fflush(stdin);

                 printf("\n\nBitte RETURN drücken");
                 scanf("%c",&enter);

		 break;
	      }

	      matrixC = (double *) realloc(matrixC, zeil * zeil * sizeof(double));

	      if (matrixC == NULL)
              {
	        printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
	        printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                fflush(stdin);

                printf("\n\nBitte RETURN drücken");
                scanf("%c",&enter);

	        break;
	      }
              
              printf("\nBitte geben Sie die gewünschte Potenz ein : ");
              scanf("%d",&wahl);

	      zeilenC = zeil;
	      spaltenC = spalt;

	      potmat(mat, matrixC, zeil, wahl);

	      break;


      case 10: printf("\nWollen Sie die erste, die zweite Matrix oder das Ergebnis der");
	       printf("\nletzten Matrizenaddition, -multiplikation, -inversion,");
	       printf("\nAdjungiertenbestimmung bzw. Potenzierung ausgeben (1,2 oder 3) : ");
               scanf("%d",&wahl);

	       if (wahl == 1)
	         ausgabe(matrixA, zeilenA, spaltenA);
	       else if (wahl == 2)
	         ausgabe(matrixB, zeilenB, spaltenB);
	       else if (wahl == 3)
	         ausgabe(matrixC, zeilenC, spaltenC);
              
	       break;


      case 11: printf("\nWelche Matrix soll ersetzt werden (1,2 oder 3) : ");
	       scanf("%d",&wahl);

	       if (wahl == 1)
	       {
	         mat = matrixA;
		 zeil = zeilenA;
		 spalt = spaltenA;
               }
	       else if (wahl == 2)
	       {
	      	 mat = matrixB;
	         zeil = zeilenB;
		 spalt = spaltenB;
               }
	       else if (wahl == 3)
	       {
	      	 mat = matrixC;
		 zeil = zeilenC;
		 spalt = spaltenC;
               }
	       else
                 break;
	      
               fflush(stdin);

               printf("\nBitte geben Sie den Dateinamen der Matrix ein : ");
               gets(datei);

	       if ((fp = fopen(datei,"r")))
               {
                 fscanf(fp,"%d",&zeil);
                 fscanf(fp,"%d",&spalt);

                 mat = (double *) realloc (mat, spalt * zeil * sizeof(double));

                 if (mat == NULL)
                 {
		   printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
                   printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

                   fflush(stdin);

                   printf("\n\nBitte RETURN drücken");
                   scanf("%c",&enter);

                   fclose(fp);

		   break;
		 }

                 for (i=0; i<zeil; i++)
                 {
                   for (j=0; j<spalt; j++)
                   {
	             fscanf(fp,"%lf",&mat[i*spalt + j]);
                   }
                 }
               }
               else
               {
                 printf("\nDatei wurde nicht gefunden !");

                 fflush(stdin);

                 printf("\n\nBitte RETURN drücken");
                 scanf("%c",&enter);
               }

               fclose(fp);

	       if (wahl == 1)
	       {
	         matrixA = mat;
		 zeilenA = zeil;
		 spaltenA = spalt;
               }
	       else if (wahl == 2)
	       {
	         matrixB = mat;
		 zeilenB = zeil;
		 spaltenB = spalt;
	       }
	       else
	       {
	         matrixC = mat;
		 zeilenC = zeil;
		 spaltenC = spalt;
               }
	                    
	       break;


      case 12: printf("\nWelche Matrix soll gespeichert werden (1,2 oder 3) : ");
	       scanf("%d",&wahl);

	       if (wahl == 1)
	         savemat(matrixA, zeilenA, spaltenA);
	       else if (wahl == 2)
	         savemat(matrixB, zeilenB, spaltenB);
	       else if (wahl == 3)
                 savemat(matrixC, zeilenC, spaltenC);

	       break;


      case 13: fflush(stdin);
               printf("\nWollen Sie wirklich aussteigen (j oder n) : ");
	       ciao = getchar();


      default: ;
    }

   
  }	    

  return 0;
}


void eingabe(int &zeilen, int &spalten)
{
  printf("\nBitte geben Sie die Zeilenanzahl der einzugebenden Matrix an : ");
  scanf("%d",&zeilen);
  printf("Bitte geben Sie die Spaltenanzahl der einzugebenden Matrix an : ");
  scanf("%d",&spalten);
}


void mattrans(double *matrix, int &zeilen, int &spalten)
{
  int tem, i, j;
  double temp;

  for (i=0; i<zeilen; i++)
  {
    for (j=i; j<spalten; j++)
    {
      temp = matrix[i*spalten + j];
      matrix[i*spalten + j] = matrix[j*spalten + i];
      matrix[j*spalten + i] = temp;
    }
  }

  tem = zeilen;
  zeilen = spalten;
  spalten = tem;
                      
}


void matadd(double *matrix1, double *matrix2, double *matrix3,
            int zeilen1, int zeilen2, int &zeilen3,
	    int spalten1, int spalten2, int &spalten3)
{

  char enter;
  int i,j;

  if ((zeilen1 != zeilen2) || (spalten1 != spalten2))
  {
    printf("\n\nDie Matrizen 1 und 2 können nicht miteinander addiert werden,");
    printf("\nda sie unterschiedlich dimensioniert sind !");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);

    return;
  }
  else
  {
    for(i=0; i<zeilen1; i++)
    {
      for(j=0; j<spalten1; j++)
      {
	matrix3[i*spalten1+j] = matrix1[i*spalten1+j] + matrix2[i*spalten1+j];
      }
    }

    zeilen3 = zeilen1;
    spalten3 = spalten1;
  }

}


void matmult(double *matrix1, double *matrix2, double *matrix3,
             int zeilen1, int zeilen2, int &zeilen3,
	     int spalten1, int spalten2, int &spalten3)
{
  char enter;
  int i, j, k;

  if (spalten1 != zeilen2)
  {
    printf("\n\nDie Matrizen 1 und 2 bzw. 2 und 1 können nicht miteinander multipliziert");
    printf("\n werden, da sie unterschiedlich dimensioniert sind !");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);

    return;
  }

  else
  {
    zeilen3 = zeilen1;
    spalten3 = spalten2;

    for (k=0; k<spalten3; k++)
    { 
      for (i=0; i<zeilen1; i++)
	{
	  matrix3[i*spalten3 + k] = 0.0;

          for (j=0; j<spalten1; j++)
	    matrix3[i*spalten3 + k] += matrix1[i*spalten1 + j] * matrix2[j*spalten2 + k];
        } 
    } 
 
  }

}


void ausgabe(double *matrix, int zeilen, int spalten)
{
  int i, j, enter;

  printf("\n\n");

  for(i=0; i<zeilen; i++)
  {
    for (j=0; j<spalten; j++)
    {
      printf(" %3lg",matrix[i*spalten + j]);
    }

    printf("\n");

  }

  fflush(stdin);

  printf("\n\nBitte RETURN drücken");
  scanf("%c",&enter);
}


void savemat(double *matrix, int zeilen, int spalten)
{
  int i, j;

  char datei[256], enter;

  FILE *fp;

  fflush(stdin);

  printf("\nBitte geben Sie den Dateinamen der Matrix ein : ");
  gets(datei);

  if ((fp = fopen(datei,"w")))
  {
    fprintf(fp," %d",zeilen);
    fprintf(fp," %d",spalten);

    for (i=0; i<zeilen; i++)
    {
      for (j=0; j<spalten; j++)
      {
	fprintf(fp," %lg",matrix[i*spalten + j]);
      }
    }
  }
  else
  {
    printf("\nDatei konnte nicht erstellt werden !");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);
  }

  fclose(fp);
}


double detmat(double *matrix1, int zeilen)
{
  char enter;
  int i, j, j2, k;

  double erg = 0.0;
  double *matrix;

  if (zeilen == 1)
    return matrix1[0];
	      
  matrix = (double *) malloc((zeilen-1)*(zeilen-1)*sizeof(double));

  if (matrix == NULL)
  {
    printf("\n\nEs konnte nicht genügend freier Speicherplatz zur Berechnung  ");
    printf("\nder Determinante bereitgestellt werden !");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);

    return 0;
  }

  for (k=0; k<zeilen; k++)
  {
    for (i=1; i<zeilen; i++)
    {
      j2 = 0;

      for (j=0; j<zeilen; j++)
      {
	if ((j==k) && (k != zeilen - 1))
	  j++;

	else if ((j==k) && (k == zeilen - 1))
          break;

	matrix[(i-1)*(zeilen - 1) + j2] = matrix1[i*zeilen + j];
	j2++;
      }
    }

    erg += pow(-1, k+2) * matrix1[k] * detmat(matrix, zeilen-1);

  }

  free(matrix);
   
  return erg;
}


void matadj(double *matrix1, double *matrix2, int zeilen)
{
  char enter;

  int i, j, k, l, k2, l2;

  double *matrix;

  matrix = (double *) malloc((zeilen-1)*(zeilen-1)*sizeof(double));

  if (matrix == NULL)
  {
    printf("\n\nEs konnte nicht genügend freier Speicherplatz zur Berechnung  ");
    printf("\nder Adjungierten bereitgestellt werden !");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);

    return;
  }
 
  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen; j++)
    {
      k2 = 0;

      for (k=0; k<zeilen; k++)
      {
	if ((k == j) && (k != zeilen - 1))
	  k++;
	else if ((k == j) && (k == zeilen - 1))
          break;

        l2 = 0;

	for (l=0; l<zeilen; l++)
	{
	  if ((l == i) && (l != zeilen - 1))
	    l++;
	  else if ((l == i) && (l == zeilen - 1))
            break;

          matrix[k2*(zeilen-1)+l2] = matrix1[k*zeilen+l];

          l2++;
        }

        k2++;
      }

      matrix2[i*zeilen + j] = pow(-1, i+j+2) * detmat(matrix, zeilen-1);
    }
  }

  free(matrix);

}


void skmult(double *matrix, int zeilen, int spalten, double skalar)
{
  int i, j;

  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<spalten; j++)
    {
      matrix[i*zeilen+j] *= skalar;
    }
  }
}


void potmat(double *matrix1, double *matrix2, int zeilen, int potenz)
{
  int i, j, k;

  char enter;

  double *matrix3;

  matrix3 = (double *) malloc(zeilen * zeilen * sizeof(double));

  if (matrix3 == NULL)
  {
    printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
    printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

    fflush(stdin);

    printf("\n\nBitte RETURN drücken");
    scanf("%c",&enter);
    
    return;
  }  
  
  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen; j++)
    {
      matrix2[i*zeilen + j] = matrix1[i*zeilen + j];
    }
  }
  
  for (k=1; k<potenz; k++)
  {
    matmult(matrix1, matrix2, matrix3, zeilen, zeilen, zeilen, zeilen, zeilen, zeilen);

    for (i=0; i<zeilen; i++)
    {
      for (j=0; j<zeilen; j++)
      {
        matrix2[i*zeilen + j] = matrix3[i*zeilen + j];
      }
    }
  }

  free(matrix3);

}