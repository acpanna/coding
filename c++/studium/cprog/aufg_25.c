#include <stdio.h>
#define ZEILEN  20
#define SPALTEN 20

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
