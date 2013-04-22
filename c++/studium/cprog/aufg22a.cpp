/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 08
    Aufgabennr.   	: 22
    Teilaufgabe   	: i) und ii)

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
#include <math.h>
#include <stdlib.h> 

#define NMAX  50

double norm_1(int n, double x[]);
double max_elem(int n, double x[]);

int main(void)
{
  int i,n;
  double vektor[NMAX];
   
  printf("\nAus wievielen Komponenten besteht der einzugebende Vektor : ");
  scanf("%d",&n);

  if (n>NMAX)
  {
    printf("\n\nArraygrenze wird überschritten - NMAX muß größer gewählt werden !");
    exit(1);
  }

  else
  { 
    printf("\n\n");

    for (i = 0; i < n; i++)
    {
      printf("Bitte geben Sie die %2d.-te Komponente des Vektors ein : ",i+1);
      scanf("%lg",&vektor[i]);
    }
  }
    
  printf("\n\nDie Summennorm des Vektors ist : %lg",norm_1(n,vektor));
  printf("\n\nDas maximale Element des Vektors ist : %lg",max_elem(n,vektor));


  return 0;
}

double norm_1(int n, double x[])
{
  int i;
  double wert = 0;

  for (i=0; i<n; i++)
  {
    wert += fabs(x[i]);
  }

  return wert;
}

double max_elem(int n, double x[])
{
  int i;
  double wert;

  wert = x[0];

  for (i=1; i<n; i++)
  {
    if (wert < x[i])
      wert = x[i];
  }

  return wert;
}  