/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 09
    Aufgabennr.   	: 25
    Teilaufgabe   	: --

    verwendeter
    Compiler
    m. Version    	: Borland Turbo C++ for Windows V3.1 (c) 1991,92
                        
    verwendetes
    Betriebssystem	: Windows98

/*
------------------------------------------------------------------------
*/

#include <stdio.h>

#define ZEILEN  5
#define SPALTEN 5

void matrix_mult(int m, int n, int p,
		 double A[ZEILEN][SPALTEN],
		 double B[ZEILEN][SPALTEN],
		 double Erg[ZEILEN][SPALTEN]);
void matrix_mult_vektor(int zeilen, int spalten,
		        double A[ZEILEN][SPALTEN],
			double x[SPALTEN], double erg[ZEILEN]);
void matrix_add(int zeilen, int spalten, 
		double A[ZEILEN][SPALTEN],
		double B[ZEILEN][SPALTEN],
		double Erg[ZEILEN][SPALTEN]);
void vektor_ausgabe(int spalten, double x[]);
void matrix_ausgabe(int zeilen, int spalten,
		    double A[ZEILEN][SPALTEN]);
void vektor_eingabe(int spalten, double x[]);
void matrix_eingabe(int zeilen, int spalten,
		    double A[ZEILEN][SPALTEN]);

int main(void)
{
  char enter, ciao = 'n';
  int wahl;

  int zeilen, spalten, zeilen1, spalten1, zeilen2, spalten2, zeilen3, spalten3;
  double matrix1[ZEILEN][SPALTEN], matrix2[ZEILEN][SPALTEN], matrix3[ZEILEN][SPALTEN];

  int spaltenv1;
  int spaltenv2;
  double vektor1[SPALTEN];
  double vektor2[ZEILEN];

  while (ciao != 'j')
  {
    printf("\n\n\n\n");
    printf("\nEingabe einer Matrix          1");
    printf("\nEingabe eines Vektors         2");
    printf("\nMatrizenaddition              3");
    printf("\nVektor/Matrix Multiplikation  4");
    printf("\nMatrix/Matrix Multiplikation  5");
    printf("\nAusgabe der Matrizen/Vektoren 6");
    printf("\nund tschüß                    7");
    printf("\n\nBitte treffen Sie eine Auswahl : ");
    scanf("%d",&wahl);

    switch(wahl)
    {
      case 1:  printf("\nBitte geben Sie die Zeilenanzahl der Matrix ein : ");
	       scanf("%d",&zeilen);
	       printf("Bitte geben Sie die Spaltenanzahl der Matrix ein : ");
	       scanf("%d",&spalten);

	       if ((zeilen > ZEILEN) || (spalten > SPALTEN))
	       {
		 printf("\nZeilen- bzw. Spaltenzahl ist zu groß gewählt !");
		 break;
	       }
               	        
               printf("\nWelche Matrix wollen Sie eingeben (1 oder 2) : ");
	       scanf("%d",&wahl);
               
	       if (wahl == 1)
	       {
	       	 zeilen1 = zeilen;
                 spalten1 = spalten;
		 matrix_eingabe(zeilen1,spalten1,matrix1);
	       }

	       else if (wahl == 2)
               {
		 zeilen2 = zeilen;
                 spalten2 = spalten;
		 matrix_eingabe(zeilen2,spalten2,matrix2);
               }

	       break;

      case 2:  printf("\nAus wievielen Komponenten soll der Vektor bestehen : ");
	       scanf("%d",&spaltenv1);

	       if (spaltenv1 > SPALTEN)
	       {
		 printf("\nSpaltenzahl ist zu groß gewählt !");
		 break;
	       }

	       vektor_eingabe(spaltenv1,vektor1);

               break;

      case 3:  printf("Es wird die Addition Matrix1 + Matrix2 ausgeführt ...");

               if ((spalten1 != spalten2) || (zeilen1 != zeilen2))
	       {
		 printf("\nMatrizenaddition aus Dimensionsgründen nicht möglich !");
		 break;
	       }

	       zeilen3 = zeilen1;
               spalten3 = spalten1;
                                        
               matrix_add(zeilen3,spalten3,matrix1,matrix2,matrix3);
               printf("\nErgebnis steht in Matrix3");

               break;

      case 4:  printf("Es wird die Multiplikation Matrix1 * Vektor ausgeführt ...");

	       if (spalten1 != spaltenv1)
	       {
		 printf("Multiplikation aus Dimensionsgründen nicht möglich !");
		 break;
	       }

               spaltenv2 = zeilen1;

               matrix_mult_vektor(zeilen1,spalten1,matrix1,vektor1,vektor2);
               printf("\nErgebnis steht in Vektor2");

	       break;
	      

      case 5:  printf("Es wird die Multiplikation Matrix1 * Matrix2 ausgeführt ...");

               if (spalten1 != zeilen2)
	       {
		 printf("\nMatrizenmultiplikation aus Dimensionsgründen nicht möglich !");
		 break;
	       }

	       zeilen3 = zeilen1;
	       spalten3 = spalten2;

	       matrix_mult(zeilen3,spalten3,spalten1,matrix1,matrix2,matrix3);
               printf("\nErgebnis steht in Matrix3");

               break;

      case 6:  printf("\n Matrix1   1");
	       printf("\n Matrix2   2");
	       printf("\n Matrix3   3");
	       printf("\n Vektor1   4");
               printf("\n Vektor2   5");
	       printf("\n\nWas wollen Sie ausgeben : ");
               scanf("%d",&wahl);

	       printf("\n");

	       if (wahl == 1)
	         matrix_ausgabe(zeilen1,spalten1,matrix1);
	       if (wahl == 2)
	         matrix_ausgabe(zeilen2,spalten2,matrix2);
	       if (wahl == 3)		 
		 matrix_ausgabe(zeilen3,spalten3,matrix3);
	       if (wahl == 4)
		 vektor_ausgabe(spaltenv1,vektor1);
	       if (wahl == 5)
	         vektor_ausgabe(spaltenv2,vektor2);

	       break;


      case 7:  printf("\nWollen Sie wirklich aussteigen (j/n) : ");
               fflush(stdin);
               scanf("%c",&ciao);

      default: ;
    }

    printf("\nBitte RETURN drücken !");
    fflush(stdin);
    scanf("%c",&enter);

  }

  return 0;
}


void matrix_eingabe(int zeilen, int spalten,
		    double A[ZEILEN][SPALTEN])
{
  int i, j;

  for (i = 0; i < zeilen; i++)
  {
    printf("\n%d.te Zeile:\n", i+1);
    for (j = 0; j < spalten; j++)
    {
      printf("  A(%d,%d) = ", i+1, j+1);
      scanf("%lf", &A[i][j]);
    }
  }
}

void vektor_eingabe(int spalten, double x[])
{
  int i;

  for (i = 0; i < spalten; i++)
  {
    printf("  x(%d) = ", i+1);
    scanf("%lf", &x[i]);
  }
}

void matrix_ausgabe(int zeilen, int spalten,
		    double A[ZEILEN][SPALTEN])
{
  int i, j;

  for (i = 0; i < zeilen; i++)
  {
    for (j = 0; j < spalten; j++)
      printf("  %f", A[i][j]);
    printf("\n");
  }
  printf("\n");
}

void vektor_ausgabe(int spalten, double x[])
{
  int i;

  for (i = 0; i < spalten; i++)
    printf("  %f", x[i]);
  printf("\n");
}

void matrix_add(int zeilen, int spalten, 
		double A[ZEILEN][SPALTEN],
		double B[ZEILEN][SPALTEN],
		double Erg[ZEILEN][SPALTEN])
{
  int i, j;

  for (i = 0; i < zeilen; i++)
    for (j = 0; j < spalten; j++)
      Erg[i][j] = A[i][j] + B[i][j];
}

void matrix_mult_vektor(int zeilen, int spalten,
		        double A[ZEILEN][SPALTEN],
			double x[SPALTEN], double erg[ZEILEN])
{
  int i, j;

  for (i = 0; i < zeilen; i++)
  {
    erg[i] = 0.0;
    for (j = 0; j < spalten; j++)
      erg[i] += A[i][j] * x[j];
  }
}

void matrix_mult(int m, int n, int p,
		 double A[ZEILEN][SPALTEN],
		 double B[ZEILEN][SPALTEN],
		 double Erg[ZEILEN][SPALTEN])
{
  int i, j, k;

  for (i = 0; i < m; i++)
    for (j = 0; j < p; j++)
    {
      Erg[i][j] = 0.0;
      for (k = 0; k < n; k++)
	Erg[i][j] += A[i][k] * B[k][j];
    }
}


/*
---------------------------------------------------------------------------------------

       Leider ist es mir nicht möglich eine Programmausgabe mit abzugeben,
      da aus welchen windows- bzw. compilerspezifischen Gründen auch immer,
	      die Eingabeumlenkung bei mir nicht funktioniert !

---------------------------------------------------------------------------------------
/*
