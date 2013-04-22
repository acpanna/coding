#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

int main(void)
{
 double **matrixA;
  double **matrixB;
  double **matrixC;

  int zeilenA = 0, zeilenB = 0, zeilenC = 0;
  int spaltenA = 0, spaltenB = 0, spaltenC = 0;
  char ciao = 'n';
    
  double det;
 
  int i, j, zeil, spalt, wahl, check;
 
  while (ciao != 'j')
  {
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t           M A T R I X  v1.1   (by Heiko Vogel in 1999)");
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

	      printf("\nBitte geben Sie die Zeilenanzahl der einzugebenden Matrix an : ");
              scanf("%d",&zeil);
              printf("Bitte geben Sie die Spaltenanzahl der einzugebenden Matrix an : ");
	      scanf("%d",&spalt);

	      if (wahl == 1)
	      {
		freemem(&matrixA, zeilenA);
                check = initmat(&matrixA, zeil, spalt);

	        if (check == 1)
		  goto end;

		printf("\n");

		for(i=0; i<zeil; i++)
                {
                  for(j=0; j<spalt; j++)
                  {
                    printf("Eintrag der %2d. Zeile und %2d. Spalte : ",i+1,j+1);
                    scanf("%lf",&matrixA[i][j]);
                  }
		}

		zeilenA = zeil;
		spaltenA = spalt;
              }

              else 
	      { 
		freemem(&matrixB, zeilenB);
                check = initmat(&matrixB, zeil, spalt);

	        if(check == 1)
		  goto end;

		for(i=0; i<zeil; i++)
                {
                  for(j=0; j<spalt; j++)
                  {
                    printf("Eintrag der %2d. Zeile und %2d. Spalte : ",i+1,j+1);
                    scanf("%lf",&matrixB[i][j]);
                  }
		}

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

	      if ((wahl != 1) && (wahl != 2))
                break;

	      printf("\nMit welchem Skalar soll multipliziert werden : ");
	      scanf("%lg",&det);

	      if (wahl == 1)
                skmult(matrixA, zeilenA, spaltenA, det);
	      else
	        skmult(matrixB, zeilenB, spaltenB, det);

	      break;


      case 4: printf("\nWollen Sie die Determinante der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
                break;

	      if (wahl == 1)
              {
		if (zeilenA != spaltenA)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
		}

		det = detmat(matrixA, zeilenA);
              }
	      else
	      {
		if (zeilenB != spaltenB)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
		}

		det = detmat(matrixB, zeilenB);
	      }
	                  	     
	      printf("\nDie Determinante der Matrix ist : %lg",det);
              enter();

              break;


      case 5: printf("\nWollen Sie die Adjungierte der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
		break;
             
	      freemem(&matrixC, zeilenC);

	      if (wahl == 1)
              {
		if (zeilenA != spaltenA)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
		}
		else if (zeilenA <= 1)
	        {
		  printf("\nDie Adjungierte einer Zahl ist immer gleich 1 !");
                  enter();
                  break;
		}
                
		check = initmat(&matrixC, zeilenA, zeilenA);

	        if(check == 1)
                  goto end;

	        zeilenC = zeilenA;
                spaltenC = spaltenA;

		matadj(matrixA, matrixC, zeil);

              }
	      else
	      {
		if (zeilenB != spaltenB)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
		}
		else if (zeilenB <= 1)
	        {
		  printf("\nDie Adjungierte einer Zahl ist immer gleich 1 !");
                  enter();
                  break;
	        }

		check = initmat(&matrixC, zeilenB, zeilenB);

	        if(check == 1)
                  goto end;

	        zeilenC = zeilenB;
                spaltenC = spaltenB;

		matadj(matrixB, matrixC, zeil);
	      }

	      break;


      case 6: printf("\nWollen Sie die Inverse der ersten oder der zweiten Matrix");
              printf("\nberechnen (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
		break;

              freemem(&matrixC, zeilenC);

	      if (wahl == 1)
              {
		if (zeilenA != spaltenA)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
	        }

	        else
	        {
		  det = detmat(matrixA, zeilenA);

		  if (det == 0)
		  {
                    printf("\nDie Matrix kann nicht invertiert werden (det = 0) !");
		    enter();
                    break;
	      	  }

		  zeilenC = zeilenA;
                  spaltenC = spaltenA;

		  check = initmat(&matrixC, zeilenC, zeilenC);

		  if(check == 1)
                    goto end;
	
		  if (zeil > 1)
                  {
		    matadj(matrixA, matrixC, zeilenA);
		    skmult(matrixC, zeilenC, spaltenC, 1.0/det);
		  }
		  else
                    matrixC[0][0] = 1.0/matrixA[0][0];
	        }
              }
	      else 
              {
		if (zeilenB != spaltenB)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
	        }

	        else
	        {
		  det = detmat(matrixB, zeilenB);

		  if (det == 0)
		  {
                    printf("\nDie Matrix kann nicht invertiert werden (det = 0) !");
		    enter();
                    break;
	      	  }

		  zeilenC = zeilenB;
                  spaltenC = spaltenB;

		  check = initmat(&matrixC, zeilenC, zeilenC);

		  if(check == 1)
                    goto end;
	
		  if (zeil > 1)
                  {
		    matadj(matrixB, matrixC, zeilenB);
		    skmult(matrixC, zeilenC, spaltenC, 1.0/det);
		  }
		  else
                    matrixC[0][0] = 1.0/matrixB[0][0];
		}
              }
	     
              break;


      case 7: freemem(&matrixC, zeilenC);
              check = initmat(&matrixC, zeilenA, spaltenA);

	      if(check == 1)
                goto end;

              matadd(matrixA, matrixB, matrixC, zeilenA, zeilenB, zeilenC, spaltenA, spaltenB, spaltenC);

              break;


      case 8: printf("\nWollen Sie (1)  mat1 * mat2           ");
              printf("\n                   oder               ");
              printf("\n	   (2)  mat2 * mat1 rechnen : ");

	      scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
		break;
              	      
	      freemem(&matrixC, zeilenC);

	      if (wahl == 1)
              {
		check = initmat(&matrixC, zeilenA, spaltenB);

		if(check == 1)
		  goto end;

	       	matmult(matrixA, matrixB, matrixC, zeilenA, zeilenB, zeilenC, spaltenA, spaltenB, spaltenC);
              }
	      else
	      {
		check = initmat(&matrixC, zeilenB, spaltenA);

		if(check == 1)
		  goto end;

		matmult(matrixB, matrixA, matrixC, zeilenB, zeilenA, zeilenC, spaltenB, spaltenA, spaltenC);
              }

	      break;
                      

      case 9: printf("\nWollen Sie die die erste oder die zweite Matrix ");
	      printf("\npotenzieren (1 oder 2) : ");
       	      scanf("%d",&wahl);

	      if ((wahl != 1) && (wahl != 2))
		break;

	      freemem(&matrixC, zeilenC);

	      if (wahl == 1)
              {
		if (zeilenA != spaltenA)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
	        }

	        check = initmat(&matrixC, zeilenA, zeilenA);

	        if(check == 1)
                  goto end;
	                   
                printf("\nBitte geben Sie die gewünschte Potenz ein : ");
                scanf("%d",&wahl);

	        zeilenC = zeilenA;
	        spaltenC = spaltenA;

		potmat(matrixA, matrixC, zeilenA, wahl);

              }
	      else
	      {
		if (zeilenB != spaltenB)
                {
	          printf("\n\nSpalten- und Zeilenzahl der Matrix stimmen nicht überein !");
                  enter();
                  break;
	        }

	        check = initmat(&matrixC, zeilenB, zeilenB);

	        if(check == 1)
                  goto end;
	                   
                printf("\nBitte geben Sie die gewünschte Potenz ein : ");
                scanf("%d",&wahl);

	        zeilenC = zeilenB;
	        spaltenC = spaltenB;

		potmat(matrixB, matrixC, zeilenB, wahl);
              }
            	    
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


      case 11: printf("\nWelche Matrix soll ersetzt werden (1 oder 2) : ");
	       scanf("%d",&wahl);

	       if ((wahl != 1) && (wahl != 2))
		break;

	       fflush(stdin);

	       if (wahl == 1)
	       {
		 freemem(&matrixA, zeilenA);
                 loadmat(&matrixA, zeilenA, spaltenA);
	       }
	       else 
	       {
		 freemem(&matrixB, zeilenB);
                 loadmat(&matrixB, zeilenB, spaltenB);
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

  end: ;
  }	    

  freemem(&matrixA, zeilenA);
  freemem(&matrixB, zeilenB);
  freemem(&matrixC, zeilenC);

  return 0;
}


void mattrans(double **matrix, int &zeilen, int &spalten)
{
  int i, j;
  double temp;

  for (i=0; i<zeilen; i++)
  {
    for (j=i; j<spalten; j++)
    {
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }

  i = zeilen;
  zeilen = spalten;
  spalten = i;
                      
}


void matadd(double **matrix1, double **matrix2, double **matrix3,
            int zeilen1, int zeilen2, int &zeilen3,
	    int spalten1, int spalten2, int &spalten3)
{
  int i, j;

  if ((zeilen1 != zeilen2) || (spalten1 != spalten2))
  {
    printf("\n\nDie Matrizen 1 und 2 können nicht miteinander addiert werden,");
    printf("\nda sie unterschiedlich dimensioniert sind !");
    enter();
    return;
  }
  else
  {
    for(i=0; i<zeilen1; i++)
      for(j=0; j<spalten1; j++)
        matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
    
    zeilen3 = zeilen1;
    spalten3 = spalten1;
  }

}


void matmult(double **matrix1, double **matrix2, double **matrix3,
             int zeilen1, int zeilen2, int &zeilen3,
	     int spalten1, int spalten2, int &spalten3)
{
  int i, j, k;

  if (spalten1 != zeilen2)
  {
    printf("\n\nDie Matrizen 1 und 2 bzw. 2 und 1 können nicht miteinander multipliziert");
    printf("\n werden, da sie unterschiedlich dimensioniert sind !");
    enter();
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
	  matrix3[i][k] = 0.0;

          for (j=0; j<spalten1; j++)
	    matrix3[i][k] += matrix1[i][j] * matrix2[j][k];
        } 
    } 
  }
}


void ausgabe(double **matrix, int zeilen, int spalten)
{
  int i, j;

  printf("\n\n");

  for(i=0; i<zeilen; i++)
  {
    for (j=0; j<spalten; j++)
      printf(" %3lg",matrix[i][j]);
    
    printf("\n");
  }

  enter();
}


void loadmat(double ***matrix, int &zeilen, int &spalten)
{
  int i, j, check;

  char datei[256];

  FILE *fp;

  fflush(stdin);

  printf("\nBitte geben Sie den Dateinamen der Matrix ein : ");
  gets(datei);
                                                
  if ((fp = fopen(datei,"r")) != NULL)
  {
    fscanf(fp,"%d",&zeilen);
    fscanf(fp,"%d",&spalten);

    check = initmat(matrix, zeilen, spalten);

    if(check == 1)
    {
      fclose(fp);
      return;
    }

    for (i=0; i<zeilen; i++)
      for (j=0; j<spalten; j++)
        fscanf(fp,"%lf",&((*matrix)[i][j]));
  }
  else
  {
    printf("\nDatei wurde nicht gefunden !");
    enter();
  }

  fclose(fp);
}


void savemat(double **matrix, int zeilen, int spalten)
{
  int i, j;

  char datei[256];

  FILE *fp;

  fflush(stdin);

  printf("\nBitte geben Sie den Dateinamen der Matrix ein : ");
  gets(datei);

  if ((fp = fopen(datei,"w")) != NULL)
  {
    fprintf(fp," %d",zeilen);
    fprintf(fp," %d",spalten);

    for (i=0; i<zeilen; i++)
      for (j=0; j<spalten; j++)
        fprintf(fp," %lg",matrix[i][j]);
  }
  else
  {
    printf("\nDatei konnte nicht erstellt werden !");
    enter();
  }

  fclose(fp);
}


double detmat(double **matrix1, int zeilen)
{
  int i, j, j2, k, check;

  double erg = 0.0;
  double **matrix;

  if (zeilen == 1)
    return matrix1[0][0];
	      
  check = initmat(&matrix, zeilen-1, zeilen-1);

  if (check == 1)
    return -11111.11111;

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

	matrix[i-1][j2] = matrix1[i][j];
	j2++;
      }
    }

    erg += pow(-1, k+2) * matrix1[0][k] * detmat(matrix, zeilen-1);

  }

  freemem(&matrix, zeilen-1);
     
  return erg;
}


void matadj(double **matrix1, double **matrix2, int zeilen)
{
  int i, j, k, l, k2, l2, check;

  double **matrix;

  check = initmat(&matrix, zeilen-1, zeilen-1);

  if (check == 1)
    return;
   
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

          matrix[k2][l2] = matrix1[k][l];

          l2++;
        }

        k2++;
      }

      matrix2[i][j] = pow(-1, i+j+2) * detmat(matrix, zeilen-1);
    }
  }
        
  freemem(&matrix, zeilen-1);
}


void skmult(double **matrix, int zeilen, int spalten, double skalar)
{
  int i, j;

  for (i=0; i<zeilen; i++)
    for (j=0; j<spalten; j++)
      matrix[i][j] *= skalar;
}


void potmat(double **matrix1, double **matrix2, int zeilen, int potenz)
{
  int i, j, k, check;

  double **matrix3;

  check = initmat(&matrix3, zeilen, zeilen);

  if (check == 1)
    return;
    
  for (i=0; i<zeilen; i++)
    for (j=0; j<zeilen; j++)
      matrix2[i][j] = matrix1[i][j];
    
  for (k=1; k<potenz; k++)
  {
    matmult(matrix1, matrix2, matrix3, zeilen, zeilen, zeilen, zeilen, zeilen, zeilen);

    for (i=0; i<zeilen; i++)
      for (j=0; j<zeilen; j++)
        matrix2[i][j] = matrix3[i][j];
  }
      
  freemem(&matrix3, zeilen);
}


int initmat(double ***matrix, int zeilen, int spalten)
{
   int i;
       
   *matrix = (double **) calloc(zeilen, sizeof(double));

   if (*matrix == NULL)
   {
     printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
     printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

     enter();

     spalten = 0;
     zeilen  = 0;

     return 1;
   }

   else
   {     
     for (i=0; i<zeilen; i++)
     { 
       (*matrix)[i] = (double *) calloc(spalten, sizeof(double));
	
       if ((*matrix)[i] == NULL)
       {
         printf("\n\nEs konnte nicht genügend freier Speicherplatz für die Matrix ");
         printf("\nbereitgestellt werden, Sie müssen die Dimensionen kleiner wählen");

	 enter();

	 spalten = 0;
	 zeilen  = 0;

         return 1;
       }
     }
   }

   return 0;
}


void freemem(double ***matrix, int zeilen)
{
  int i;
printf("test1");
  if (zeilen > 0)
  {
    for (i=0; i<zeilen; i++)
      free((*matrix)[i]);
  }

  delete *matrix;
}


void enter(void)
{
  char enter;

  fflush(stdin);

  printf("\n\nBitte RETURN drücken");
  scanf("%c",&enter);
}
