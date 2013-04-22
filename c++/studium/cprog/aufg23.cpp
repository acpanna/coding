/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 08
    Aufgabennr.   	: 23
    Teilaufgabe   	: --

    verwendeter
    Compiler
    m. Version    	: Borland Turbo C++ for Windows V3.1 (c) 1991,92
                        
    verwendetes
    Betriebssystem	: Windows98

*/

/*
------------------------------------------------------------------------
*/
                            
#include <stdio.h>
#include <stdlib.h>

#define NMAX 10

void ident(int n, double x[][NMAX]);
void zeros(int n, double x[][NMAX]);
void randsym(int n, double x[][NMAX]);
void tridiag(int n, double x[][NMAX], double y[]);

int main(void)
{
  int i, j, n, wahl;
  double vektor[NMAX];
  double matrix[NMAX][NMAX];
  
  printf("\n Bitte geben Sie die Spaltenzahl der zu erzeugenden Matrix ein : ");
  scanf("%d",&n);

  if (n > NMAX)
  {
    printf("\n\nArraygrenze überschritten - NMAX muß größer gewählt werden !");
    exit(1);
  }

  else
  {
    printf("\n Welchen Typ von Matrix wollen Sie erzeugen : \n");
    printf("\n                Einheitsmatrix          1");
    printf("\n                Nullmatrix              2");
    printf("\n                Symmetr. Zufallsmatrix  3");
    printf("\n                Trigonalmatrix          4");
    printf("\n\nBitte treffen Sie eine Wahl : ");
    scanf("%d",&wahl);

    switch(wahl)
    {
      case 1:  ident(n,matrix);
               break;

      case 2:  zeros(n,matrix);
               break;

      case 3:  randsym(n,matrix);
               break;

      case 4:  printf("\nBitte geben Sie den zu übergebenden Diagonalvektor ein :\n\n");

               for (i=0; i<n; i++)
               {
                 printf("%2d.-te Komponente des Vektors : ",i+1);
                 scanf("%lg",&vektor[i]);
               }

               tridiag(n,matrix,vektor);
               break;           

      default: exit(1);
    }

    printf("\n\n\t");   

    for (i=0; i<n; i++)
    {
      for (j=0; j<n; j++)
      	printf(" %2lg",matrix[i][j]);

      printf("\n\t");
    }
  
    printf("\n\n");

  }

  return 0;
}


void ident(int n, double x[][NMAX])
{
  int i;

  zeros(n,x);
    
  for (i=0; i<n; i++)
  {
    x[i][i] = 1;
  }
}


void zeros(int n, double x[][NMAX])
{
  int i, j;

  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
      x[i][j] = 0;
  }
}


void randsym(int n, double x[][NMAX])
{
  int i,j;

  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
    {
      x[i][j] = rand() % 100;
      x[j][i] = x[i][j];
    }
  }
}


void tridiag(int n, double x[][NMAX], double y[])
{
  int i;

  zeros(n,x);
  
  for (i=0; i<n-1; i++)
  {
    x[i][i]=y[i];
    x[i][i+1]=1;
    x[i+1][i]=-2;    
  }

  x[n-1][n-1] = y[n-1];
}
