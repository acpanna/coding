#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cfloat>
#include <cmath>

#define VERBOSE
#define MAXITERS 10000

bool simplex(int zeilen, int spalten, double **A, double *b, double *cost, double *ergebnis);
bool simplex_with_equations(int zeilen, int spalten, double **A, double *b, double *cost, double *ergebnis);
void phase2(int m, int n, double **A, double *b, double *c, double *p1);

unsigned int * gauss(int zeilen, int spalten, double **matrix, double *vektor);
void solveLR(int zeilen, double **matrix, double *vektor, unsigned int *zeilentausch);

int main(void)
{
  int m, n, i, j;

  double **A;
  double *b;
  double *c;
  double *result;

  printf("\nSimplex - Verfahren");
  printf("\n===================");
  printf("\n\nDieses Verfahren loest lineare Problemstellungen der Art:");
  printf("\n   Minimiere c'x unter den Nebenbedingungen A*x<=b und x>=0");
  printf("\n\nBitte geben Sie die Dimension der mxn - Matrix A ein (z.B. 4,6) : ");
  scanf("%d,%d", &m, &n);

  A = (double **) calloc(m, sizeof(double));
  b = (double *) calloc(m, sizeof(double));
  c = (double *) calloc(n, sizeof(double));
  result = (double *) calloc(n, sizeof(double));
	
  assert(A);
  assert(b);
  assert(c);
  assert(result);

  for (i=0; i<m; i++)
  {
    A[i] = (double *) calloc(n, sizeof(double));
    assert(A[i]);
  }

  cout << "\nBitte geben Sie die Matrix eintragsweise ein :\n";
  for (i=0; i<m; i++)
    for (int j=0; j<n; j++)
    {
      cout << "Eintrag (" <<i+1<<", "<<j+1<<") :  ";
      cin >> A[i][j];
    }

  cout << "\nBitte geben Sie den Vektor b eintragsweise ein :\n";
  for (i=0; i<m; i++)
  {
    cout << "Eintrag ("<<i+1<<") :  ";
    cin >> b[i];
  }
 
  cout << "\nBitte geben Sie den Vektor c eintragsweise ein :\n";
  for (i=0; i<n; i++)
  {
    cout << "Eintrag ("<<i+1<<") :  ";
    cin >> c[i];
  }

  simplex(m, n, A, b, c, result);

  for (i=0; i<m; i++)
    free(A[i]);

  free(A);
  free(b);
  free(c);

  return 0;
}

// Dient dazu, die Ungleichungen der Form A*x<=b in Gleichungen zu verwandeln,
// durch Einfuehrung von Schlupfvariablen -- erst danach wird der eigentliche
// Simplex-Algoithmus aufgerufen, der mit Gleichungen arbeitet
bool simplex(int zeilen, int spalten, double **A, double *b, double *cost, double *ergebnis)
{
  bool returncode;
  int i, j;
  
  double **tempA;
  double *tempc, *temperg;

  tempA    = (double **) calloc(    zeilen, sizeof(double));
  tempc    = (double *)  calloc( spalten+zeilen, sizeof(double));
  temperg  = (double *)  calloc( spalten+zeilen, sizeof(double));
  
  for (i=0; i<zeilen; i++) // Fuege Schlupfvariablen ein
  {
    tempA[i] = (double *) calloc( spalten+zeilen, sizeof(double));
    assert(tempA[i]);
    
    tempA[i][i+spalten] = 1.0;
    
    for (j=0; j<spalten; j++)
      tempA[i][j] = A[i][j];
  }

  for (j=0; j<spalten; j++)
    tempc[j] = cost[j]; 
  for (j=spalten; j<spalten+zeilen; j++)
    tempc[j] = 0.0; // Schlupfvariablen sollen Kosten nicht beeinflussen
    
  returncode = simplex_with_equations(zeilen, spalten+zeilen, tempA, b, tempc, temperg);

  for (i=0; i<spalten; i++)
    ergebnis[i] = temperg[i];
 
  for (i=0; i<zeilen; i++)
    free(tempA[i]);

  free(tempA);
  free(tempc);
  free(temperg);

  return returncode;
}
    
bool simplex_with_equations(int zeilen, int spalten, double **A, double *b, double *cost, double *ergebnis)
{
  int i, j;

  double **tempA;
  double *tempb, *tempc, *temperg;
  	
  /////// Beginn Phase 1 ///////

  tempA    = (double **) calloc(    zeilen, sizeof(double));
  tempb    = (double *)  calloc(    zeilen, sizeof(double));
  tempc    = (double *)  calloc( spalten+zeilen, sizeof(double));
  temperg  = (double *)  calloc( spalten+zeilen, sizeof(double));

  assert(tempA);
  assert(tempb);
  assert(tempc);
  assert(temperg);
	
  for (i=0; i<zeilen; i++)
  {
    tempA[i] = (double *) calloc( spalten+zeilen, sizeof(double));
    assert(tempA[i]);
  }
  
  for (i=0; i<zeilen; i++) // Mache alle b[i] >= 0	
    for(j=0; j<spalten; j++)
    {
      if (b[i] < 0)
      {
	tempb[i] = -b[i];
	tempA[i][j] = -A[i][j];
      }
      else
      {
	tempb[i] = b[i];
	tempA[i][j] = A[i][j];
      }
    }

  for (i=0; i<zeilen; i++) // Erweiterung der Ausgangsmatrix mit m-ter Einheitsmatrix
    for (j=spalten; j<spalten+zeilen; j++)
    {
      if ((j-spalten) == i)
	tempA[i][j] = 1;
      else
	tempA[i][j] = 0;
    }

  for (i=0; i<spalten+zeilen; i++) // Bilde tempc fuer Phase I und belege temperg mit gueltiger Basisloesung
  {
    if (i<spalten)
    {
      tempc[i] = 0;
      temperg[i] = 0;
    }
    else
    {
      tempc[i] = 1;
      temperg[i] = tempb[i-spalten];
    }
  }
#ifdef VERBOSE
  printf("\n\nAusgabe Phase I :");
#endif
  phase2(zeilen, spalten+zeilen, tempA, tempb, tempc, temperg);

  for (i=spalten; i<spalten+zeilen; i++)
    if(temperg[i] != 0)
    {
#ifdef VERBOSE
      printf("\nDas Problem ist unzulaessig -- es gibt entartete Basisloesungen !");
#endif
      return false;
    }

  ////// Ende Phase 1  //////

#ifdef VERBOSE
  printf("\nAusgabe Phase II :");
#endif
  phase2(zeilen, spalten, A, b, cost, temperg);

  for (i=0; i<spalten; i++)
    ergebnis[i] = temperg[i];
		
  for (i=0; i<zeilen; i++)
    free(tempA[i]);

  free(tempA);
  free(tempb);
  free(tempc);
  free(temperg);

  return true;
}

void phase2(int m, int n, double **A, double *b, double *c, double *p1)
{
  int *J, *Jc;

  double *p2;
  double **x1, **x2;

  unsigned int *tausch;
	
  int i, j, k, l, countJ, countJc, counter;
	
  double sum, min;

  x1 = (double **) calloc(n, sizeof(double));
  x2 = (double **) calloc(n, sizeof(double));
  J  = (int *) calloc(m, sizeof(double));
  Jc = (int *) calloc(n-m, sizeof(double));
  p2 = (double *) calloc(n, sizeof(double));
	
  assert(x1);
  assert(x2);
  assert(J);
  assert(Jc);
  assert(p2);

  for (i=0; i<n; i++)
  {
    x1[i] = (double *) calloc( n, sizeof(double));
    x2[i] = (double *) calloc( n, sizeof(double));

    assert(x1[i]);
    assert(x2[i]);
  }

  countJ = 0;
  countJc = 0;

  for (i=0; i<n; i++)
  {
    if (p1[i] == 0) // Erzeugung der Indexmengen
    {
      Jc[countJc] = i;
      countJc++;
    }

    else
    {
      J[countJ] = i;
      countJ++;
    }
  }

  for (j=0; j<n-m; j++) // Berechnung der Startwerte fuer x[i][j] 
    for (i=0; i<m; i++)
      x1[i][Jc[j]] = A[i][Jc[j]];

  for (i=0; i<m; i++)
    for (j=0; j<m; j++)
      A[i][j] = A[i][J[j]] ;
		
  tausch = gauss(m, m, A, b);
	
  for (j=0; j<n-m; j++)
  {
    for (i=0; i<m; i++)
      b[i] = x1[i][Jc[j]];

    solveLR(m, A, b, tausch);

    for (i=0; i<m; i++)
      x1[J[i]][Jc[j]] = b[i];
  }

  free(tausch);
  counter = 0;

  while (counter < MAXITERS) // Schleife bis max. Iterationszahl erreicht
  {
    for (i=0; i<n-m; i++) // Bildung der negativen red. Kosten
    {
      sum = 0;

      for (j=0; j<m; j++)
	sum += c[J[j]] * x1[J[j]][Jc[i]];

      sum -= c[Jc[i]];

      if (sum > 0)
      {
	k = Jc[i]; // k gefunden
	break;
      }
    }
  		
    if (sum > 0)
    {
      min = DBL_MAX;
      for (i=0; i<m; i++)
      {
	if (x1[J[i]][k] > 0)
	  if ((p1[J[i]] / x1[J[i]][k]) < min)
	  {
	    min = p1[J[i]] / x1[J[i]][k];
	    l = J[i]; // l gefunden
	  }
      }

      for (i=0; i<m; i++)
	if (J[i] == l)
	  J[i] = k; // Update der Indexmengen
			
      for (i=0; i<n-m; i++)
	if (Jc[i] == k)
	  Jc[i] = l;
				
      // Anwendung der Rekursionsformeln
      for (i=0; i<m; i++)
      {
	if (J[i] == k)
	  p2[k] = p1[l]/x1[l][k];
	else
	  p2[J[i]] = p1[J[i]] - (p1[l] * x1[J[i]][k])/x1[l][k];
      }
		
      for (i=0; i<m; i++)
	for (j=0; j<n-m; j++)
	{
	  if (J[i] == k && Jc[j] == l)
	    x2[k][l] = 1/x1[l][k];
	  else if (J[i] == k)
	    x2[k][Jc[j]] = x1[l][Jc[j]]/x1[l][k];
	  else if (Jc[j] == l)
	    x2[J[i]][l] = - (x1[J[i]][k]/x1[l][k]);
	  else
	    x2[J[i]][Jc[j]] = x1[J[i]][Jc[j]] - (x1[l][Jc[j]]*x1[J[i]][k])/x1[l][k];
				}
      // Umkopieren fuer Neubeginn der Rekursion
      for (i=0; i<m; i++)
	p1[J[i]] = p2[J[i]];
      for (i=0; i<n; i++)
	for (j=0; j<n; j++)
	  x1[i][j] = x2[i][j];

      counter++;
    }
    else
      break;
  }

  for (i=0; i<n-m; i++)
    p1[Jc[i]] = 0.0;
   
#ifdef VERBOSE
  // Ausgabe minimaler Funktionswert, Anzahl der Iterationen, p
  sum  = 0;
  for (i=0; i<m; i++)
    sum += c[J[i]]*p1[J[i]];

  printf("\nMinimaler Funktionswert :  %lg",sum);
  printf("\nZugehoeriges p : ( %lg",p1[0]);

  for (i=1; i<n; i++)
    printf(", %lg",p1[i]);

  printf(" )");
  printf("\nAnzahl der Iterationen :  %d\n\n",counter+1);
#endif
  
  for (i=0; i<n; i++)
  {
    free(x1[i]);
    free(x2[i]);
  }

  free(x1);
  free(x2);
  free(J);
  free(Jc);
  free(p2);
}

unsigned int * gauss(int zeilen, int spalten, double **matrix, double *vektor)
{	
  int i, j, k;
 
  unsigned int zeile;
  unsigned int *zeilentausch;

  double big, temp; 
  
  zeilentausch = (unsigned int *) calloc(zeilen, sizeof(unsigned int));
   assert(zeilentausch);

  for (i=0; i<zeilen; i++)
    zeilentausch[i] = i;

  for (j=0; j<zeilen-1; j++)
  {
    big = matrix[j][j];
    zeile = j;
                     
    for (i=1; i<zeilen; i++)
    {                                          
      if (fabs(matrix[i][j]) > fabs(big)) /* Spalten - Pivotsuche */
      {
	big = matrix[i][j];
	zeile = i;
      }
    }

    if (big == 0)
      break;

    for (i=0; i<zeilen; i++) /*  Vertauschung von Zeilen */
    {                        /*   Pivot Eintrag wird an  */
      temp = matrix[j][i];   /* richtige Stelle gebracht */
      matrix[j][i] = matrix[zeile][i];
      matrix[zeile][i] = temp;
    }

    temp = vektor[j];          /* Ebenfalls Vertauschung im */
    vektor[j] = vektor[zeile]; /*       Ergebnisvektor      */
    vektor[zeile] = temp;
	
    temp = (double) zeilentausch[j];	   /*        Vermerken der        */
    zeilentausch[j] = zeilentausch[zeile]; /* Zeilenvertauschung im Array */
    zeilentausch[zeile] = (unsigned int) temp;
    
    for (k=j+1; k<zeilen; k++)
    {
      matrix[k][j] = matrix[k][j]/big;                    /*   Speichern von 'l' an freiwerdendem Platz     */
      vektor[k] = vektor[k] - (matrix[k][j] * vektor[j]); /*     Abziehen des Produkts aus 'l' und dem      */
                                                          /* Pivoteintrag des Vektors vom aktuellen Eintrag */
    
      for (i=j+1; i<zeilen; i++) /* Abziehen von 'l' * Pivotzeile von aktueller Zeile */
	matrix[k][i] = matrix[k][i] - (matrix[k][j] * matrix[j][i]); 
    } 
  }

  // Matrix ist nun LR zerlegt
  return zeilentausch;
}

void solveLR(int zeilen, double **matrix, double *vektor, unsigned int *zeilentausch)
{
  int i, j;

  double *tempvektor;
  
  tempvektor = (double *) calloc(zeilen, sizeof(double));
  assert(tempvektor);
	
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
     
    vektor[l] = (vektor[l] - sub)/matrix[l][l];
  } 
	
  free(tempvektor);
}
