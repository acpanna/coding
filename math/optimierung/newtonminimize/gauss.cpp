#include "gauss.h"
#include <iostream>

using namespace std;

int gauss(const int &zeilen, 
		double ** const matrix, 
		double * const vektor, 
		int * const zeilentausch)
{
  int i, j, k, rang = zeilen, zeile = -1;
  double big, temp;

  for (i=0; i<zeilen; i++)
    zeilentausch[i] = i;

  for (j=0; j<zeilen; j++)
  {
    big = 0.0;
    for (i=j; i<zeilen; i++)
    {
      /* Spalten - Pivotsuche */
      if (fabs(matrix[i][j]) > fabs(big)) 
      {
	big = matrix[i][j];
	zeile = i;
      }
    }

    if (big == 0)
    {
      rang--;
      continue;
    }
  
    /*  Vertauschung von Zeilen */
    /*   Pivot Eintrag wird an  */
    /* richtige Stelle gebracht */
    for (i=0; i<zeilen; i++) 
    {                        
      temp = matrix[j][i];   
      matrix[j][i] = matrix[zeile][i];
      matrix[zeile][i] = temp;
    }

    /* Ebenfalls Vertauschung im */
    /*       Ergebnisvektor      */
    temp = vektor[j];          
    vektor[j] = vektor[zeile];
    vektor[zeile] = temp;
	
    /*        Vermerken der        */
    /* Zeilenvertauschung im Array */
    temp = (double) zeilentausch[j];	   
    zeilentausch[j] = zeilentausch[zeile]; 
    zeilentausch[zeile] = (int) temp;
    
    for (k=j+1; k<zeilen; k++)
    {
      /*   Speichern von 'l' an freiwerdendem Platz     */
      matrix[k][j] = matrix[k][j]/big;     
      
      /*     Abziehen des Produkts aus 'l' und dem      */
      /* Pivoteintrag des Vektors vom aktuellen Eintrag */
      vektor[k] = vektor[k] - (matrix[k][j] * vektor[j]);
          
      /* Abziehen von 'l' * Pivotzeile von aktueller Zeile */
      for (i=j+1; i<zeilen; i++)
	matrix[k][i] = matrix[k][i] - (matrix[k][j] * matrix[j][i]); 
    }
  }
  // Matrix ist nun LR zerlegt
  return rang;
}

bool solveLR(const int &zeilen, 
		const double ** const matrix, 
		double * const vektor,
		const int * const zeilentausch)
{
  int i, j;
  bool returncode = true;
  double *tempvektor;
  
  tempvektor = (double *) calloc(zeilen, sizeof(double));
  ASSERT(tempvektor);

  for (i=0; i<zeilen; i++) // Fuehre Zeilenpermutation mit Vektor durch
    tempvektor[i] = vektor[zeilentausch[i]];
  for (i=0; i<zeilen; i++) 
    vektor[i] = tempvektor[i];

  for (i=0; i<zeilen; i++) // Loese das System L*c = b
  {                        // (wobei b der permutierte Vektor ist) 
    double sub = 0.0;

    for (j=0; j<i; j++)
      sub +=vektor[j] * matrix[i][j];

    vektor[i] = vektor[i] - sub;
  }

  for (int l=zeilen-1; l>=0; l--) // Loese das System R*y = c
  {                               // --> y loest das System A*x=b
    double sub = 0.0;

    for (j=l+1; j<zeilen; j++)                   
      sub += matrix[l][j] * vektor[j];
     
    if (!matrix[l][l]) // System besitzt unendlich viele/keine Loesung
    { returncode = false; break; } 
    
    vektor[l] = (vektor[l] - sub)/matrix[l][l];
  } 
	
  free(tempvektor);
  return returncode;
}
