#include "simplex.h"
#include <iostream>
#include <iomanip>
#include <cfloat>
#include <cstdlib>
#include "defs.h"

#define OUTPUTWIDTH      12
#define OUTPUTPRECISION  2

//#define VERBOSE // Entkommentieren, falls eine Tableauausgabe erfolgen soll

using namespace std;

bool simplex(const int &zeilen, 
		const int &spalten, 
		const double ** const A, 
		const double * const b,
		const double * const cost, 
		double * const ergebnis)
{
  bool returncode;
  int i, j;  
  
  double **tempA;
  double *tempb, *tempc, *temperg;

  tempA    = (double **) calloc(    zeilen, sizeof(double));
  tempb    = (double *)  calloc(    zeilen, sizeof(double));
  tempc    = (double *)  calloc( spalten+zeilen, sizeof(double));
  temperg  = (double *)  calloc( spalten+zeilen, sizeof(double));
 
  ASSERT(tempA);
  ASSERT(tempb);
  ASSERT(tempc);
  ASSERT(temperg);
  
  // Fuege Schlupfvariablen ein
  for (i=0; i<zeilen; i++) 
  {
    tempA[i] = (double *) calloc( spalten+zeilen, sizeof(double));
    ASSERT(tempA[i]);
    
    tempA[i][i+spalten] = 1.0;
    
    for (j=0; j<spalten; j++)
      tempA[i][j] = A[i][j];

    tempb[i] = b[i];
  }

  for (j=0; j<spalten; j++)
    tempc[j] = cost[j]; 
  for (j=spalten; j<spalten+zeilen; j++)
    tempc[j] = 0.0; // Schlupfvariablen sollen Kosten nicht beeinflussen
    
  // Starte Simplex-Verfahren 
  returncode = simplex_with_equations(zeilen, spalten+zeilen, tempA, 
		  				tempb, tempc, temperg);
  for (i=0; i<spalten; i++)
    ergebnis[i] = temperg[i];
 
  for (i=0; i<zeilen; i++)
    free(tempA[i]);

  free(tempA);
  free(tempb);
  free(tempc);
  free(temperg);

  return returncode;
}
    
bool simplex_with_equations(const int &zeilen, const int &spalten, 
		double ** const A, double * const b,
		const double * const cost, double * const ergebnis)
{
  bool returncode = true;
  int i, j;

  double **tempA;
  double *tempc, *temperg;
  	
  ////////// Beginn Phase 1 //////////

  tempA    = (double **) calloc(    zeilen, sizeof(double));
  tempc    = (double *)  calloc( spalten+zeilen, sizeof(double));
  temperg  = (double *)  calloc( spalten+zeilen, sizeof(double));

  ASSERT(tempA);
  ASSERT(tempc);
  ASSERT(temperg);
	
  for (i=0; i<zeilen; i++)
  {
    tempA[i] = (double *) calloc( spalten+zeilen, sizeof(double));
    ASSERT(tempA[i]);
  }
  
  // Mache alle b[i] >= 0	
  for (i=0; i<zeilen; i++) 
    for(j=0; j<spalten; j++)
    {
      if (b[i] < 0)
	tempA[i][j] = -A[i][j];
      else
	tempA[i][j] = A[i][j];
    }

  // Erweiterung der Ausgangsmatrix mit m-ter Einheitsmatrix
  for (i=0; i<zeilen; i++) 
    for (j=spalten; j<spalten+zeilen; j++)
    {
      if ((j-spalten) == i)
	tempA[i][j] = 1;
      else
	tempA[i][j] = 0;
    }

  // Bilde tempc fuer Phase I und belege temperg mit gueltiger Basisloesung
  for (i=0; i<spalten+zeilen; i++)
  {
    if (i<spalten)
    {
      tempc[i] = 0;
      temperg[i] = 0;
    }
    else
    {
      tempc[i] = 1;
      
      if (b[i-spalten] < 0)
	temperg[i] = -b[i-spalten];
      else
	temperg[i] = b[i-spalten];
    }
  }
  
#ifdef VERBOSE  
  cout << endl << "===================" << endl;
  cout << "| Ausgabe Phase I |" << endl;
  cout << "===================" << endl;
 
  ////////// Ausgabe von A, b, c //////////
  cout << endl << "--" << endl;
  cout << " Matrix A:" << endl;
  cout << "--" << endl;
  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<zeilen+spalten; j++)
      cout << setw(OUTPUTWIDTH) << setprecision(OUTPUTPRECISION) << tempA[i][j];
    cout << endl;
  }
  cout << endl << "--" << endl;
  cout << " Vektor b: ( ";
  if (b[0] < 0)
    cout << -b[0];
  else
    cout << b[0];
  
  for (i=1; i<zeilen; i++)
  {
    cout << setprecision(OUTPUTPRECISION) << ", ";
    if (b[i] < 0)
      cout << -b[i];
    else
      cout << b[i];
  }
  cout << " )";
  cout << endl << " Vektor c: ( " << tempc[0];
  for (j=1; j<zeilen+spalten; j++)
    cout << setprecision(OUTPUTPRECISION) << ", " << tempc[j];
  cout << " )";
  cout << endl << "--";
  ////////// Ausgabe Ende //////////
#endif
  
  if (!(returncode = phase2(zeilen, spalten+zeilen, tempA, tempc, temperg)))
     goto cleanup;

  for (i=spalten; i<spalten+zeilen; i++)
    if(temperg[i] != 0)
    {
      cout << "phase1: Problem ist nicht loesbar, "
	"da keine zulaessigen Punkte existieren --- Funktionsabbruch\n";
      returncode = false;
      goto cleanup;
    }

  ////////// Ende Phase 1 //////////

#ifdef VERBOSE
  cout << endl << "====================" << endl;
  cout << "| Ausgabe Phase II |" << endl;
  cout << "====================" << endl;

  ////////// Ausgabe von A, b, c //////////
  cout << endl << "--" << endl;
  cout << " Matrix A:" << endl;
  cout << "--" << endl;
  for (i=0; i<zeilen; i++)
  {
    for (j=0; j<spalten; j++)
      cout << setw(OUTPUTWIDTH) << setprecision(OUTPUTPRECISION) << A[i][j];
    cout << endl;
  }
  cout << endl << "--" << endl;
  cout << " Vektor b: ( " << b[0];
  for (i=1; i<zeilen; i++)
    cout << setprecision(OUTPUTPRECISION) << ", " << b[i];
  cout << " )";
  cout << endl << " Vektor c: ( " << cost[0];
  for (j=1; j<spalten; j++)
    cout << setprecision(OUTPUTPRECISION) << ", " << cost[j];
  cout << " )";
  cout << endl << "--";
  ////////// Ausgabe Ende //////////
#endif

  if (!(returncode = phase2(zeilen, spalten, A, cost, temperg)))
    goto cleanup;

  for (i=0; i<spalten; i++)
    ergebnis[i] = temperg[i];

cleanup:
  
  for (i=0; i<zeilen; i++)
    free(tempA[i]);

  free(tempA);
  free(tempc);
  free(temperg);

  return returncode;
}

bool phase2(const int &m, 
		const int &n, 
		double ** const A, 
		const double * const c,
		double * const p1)
{
  bool returncode = true;
  int *J, *Jc;

  double *p2, *tempb;
  double **x1, **x2, **tempA;
  
  int *tausch;
	
  int i, j, k, l, countJ, countJc, counter;
	
  double sum, min;

  x1 = (double **) calloc(n, sizeof(double));
  x2 = (double **) calloc(n, sizeof(double));
  tempA = (double **) calloc(m, sizeof(double));
  tempb = (double *) calloc(m, sizeof(double));
  tausch = (int *) calloc(m, sizeof(int));
  J  = (int *) calloc(m, sizeof(double));
  Jc = (int *) calloc(n, sizeof(double));
  p2 = (double *) calloc(n, sizeof(double));
	
  ASSERT(x1);
  ASSERT(x2);
  ASSERT(tempA);
  ASSERT(tempb);
  ASSERT(tausch);
  ASSERT(J);
  ASSERT(Jc);
  ASSERT(p2);

  for (i=0; i<n; i++)
  {
    x1[i] = (double *) calloc( n, sizeof(double));
    x2[i] = (double *) calloc( n, sizeof(double));
    
    if (i < m)
    {
      tempA[i] = (double *) calloc( m, sizeof(double));
      ASSERT(tempA[i]);
    }
    
    ASSERT(x1[i]);
    ASSERT(x2[i]);
  }

  countJ = 0;
  countJc = 0;

  // Erzeugung der Indexmengen
  for (i=0; i<n; i++)
  {
    if (fabs(p1[i]) == 0) 
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
  
  // Ergaenze J solange, 
  // bis countJ == m
  for (j=0; j<n; j++)
  {
    if (countJ == m)
      break;

    bool isElement = false;
    for (k=0; k<countJ; k++)
      if (J[k] == j)
      {
	isElement = true;
	break;
      }

    if (isElement)
      continue;

    for (i=0; i<m; i++)
      for (k=0; k<countJ; k++)
	tempA[i][k] = A[i][J[k]];
    
    for (i=0; i<m; i++)
      tempA[i][countJ] = A[i][j];
    
    if (gauss(m, tempA, tempb, tausch) > countJ)
    {
      J[countJ] = j; 
      countJ++;
      
      for (k=0; k<countJc; k++)
	if (Jc[k] == j)
	{
	  Jc[k] = Jc[countJc-1];
	  countJc--;
	  break;
	}
    }
  }
  
  if (countJ != m || countJc != n-m)
  {
    cerr << "phase2: Anzahl der Basisindizes ist != m --- Funktionsabbruch" << endl;
    returncode = false;
    goto cleanup;
  }
  // Alles ok, die Indexmengen
  // sind nun fertig belegt
  
  // Berechnung der Startwerte fuer x[i][j] 
  for (i=0; i<m; i++)
    for (j=0; j<m; j++)
      tempA[i][j] = A[i][J[j]];
  
  if (gauss(m, tempA, tempb, tausch) != m)
  {
    cerr << "phase2: Gauss-Verfahren - Der Rang der Matrix ist "
      "nicht maximal --- Funktionsabbruch" << endl;
    returncode = false;
    goto cleanup;
  }	
    
  for (j=0; j<n-m; j++)
  {
    for (i=0; i<m; i++)
      tempb[i] = A[i][Jc[j]];

    if (!solveLR(m, (const double ** const) tempA, tempb, tausch))
    {
      cerr << "phase2: Loesung des gestaffelten Systems - Der "
	"Rang der Matrix ist nicht maximal --- Funktionsabbruch" << endl;
      returncode = false;
      goto cleanup;
    }
      
    for (i=0; i<m; i++)
      x1[J[i]][Jc[j]] = tempb[i];
  }

  counter = 0;

  // Schleife bis max. Iterationszahl erreicht
  while (counter < MAXITERS) 
  {
    k = n; 
    
    // Bildung der negativen red. Kosten
    for (i=0; i<n-m; i++)
    {
      sum = 0;
      for (j=0; j<m; j++)
	sum += c[J[j]] * x1[J[j]][Jc[i]];
      sum -= c[Jc[i]];
      
      if (sum > EPSILON) // && Jc[i] < k) // Bland'sche Regel vorerst ausser Kraft gesetzt 
	k = Jc[i]; // k gefunden
    }

#ifdef VERBOSE
      ////////// Ausgabe des Tableau //////////
      int r, s;
      cout << endl << endl << "--" << endl;
      if (k != n)
        cout << " Tableau[" << (counter+1) <<"]:" << endl;
      else
        cout << " Schlusstableau:" << endl;
      cout << "--" << endl;
      cout << setw(OUTPUTWIDTH+1) << "|";
      for (s=0; s<countJc; s++)
    	cout << setw(OUTPUTWIDTH) << Jc[s];
      cout << "|" << setw(OUTPUTWIDTH+1) << "|" << endl << setw(1);
      for (r=0; r<3*OUTPUTWIDTH + countJc*OUTPUTWIDTH + 3; r++)
      {
	if (r == OUTPUTWIDTH || r == OUTPUTWIDTH + countJc*OUTPUTWIDTH + 1 || r == OUTPUTWIDTH + countJc*OUTPUTWIDTH + OUTPUTWIDTH + 2)
	  cout << "|";
	else
	  cout << "-";
      }
      for (r=0; r<countJ; r++)
      {
   	cout << endl << setw(OUTPUTWIDTH) << J[r] << "|";
      	for (s=0; s<countJc; s++)
  	  cout << setw(OUTPUTWIDTH) << setprecision(OUTPUTPRECISION) << x1[J[r]][Jc[s]];
  	cout << "|" << setw(OUTPUTWIDTH) << setprecision(OUTPUTPRECISION) << p1[J[r]];
	cout << "|" << setw(OUTPUTWIDTH); 
	if (k != n)
	{
	if (x1[J[r]][k] != 0)
	  cout << setprecision(OUTPUTPRECISION) << p1[J[r]] / x1[J[r]][k];
        else
	  cout << "--";
	}
      }
      cout << endl << setw(1);
      for (r=0; r<3*OUTPUTWIDTH + countJc*OUTPUTWIDTH + 3; r++)
      {
	if (r == OUTPUTWIDTH || r == OUTPUTWIDTH + countJc*OUTPUTWIDTH + 1 || r == OUTPUTWIDTH + countJc*OUTPUTWIDTH + OUTPUTWIDTH + 2)
	  cout << "|";
	else
	  cout << "-";
      }
      cout << endl << setw(OUTPUTWIDTH+1) << "|";
      for (s=0; s<countJc; s++)
      {
  	sum = 0;
  	for (r=0; r<countJ; r++)
	  sum += c[J[r]] * x1[J[r]][Jc[s]];
	sum -= c[Jc[s]];
	cout << setprecision(OUTPUTPRECISION) << setw(OUTPUTWIDTH) << sum;
      }
      cout << "|";
      sum = 0;
      for (r=0; r<countJ; r++)
	sum += c[J[r]]*p1[J[r]];
      cout << setw(OUTPUTWIDTH) << setprecision(OUTPUTPRECISION) << sum << "|" << endl;
      ////////// Tableau wurde ausgegeben //////////
      
      // Ausgabe von k, falls noch nicht optimal
      if (k != n)
	cout << "k = " << k << endl;
#endif
      
    if (k != n) 
    {
      for (j=0; j<m; j++)
  	if (x1[J[j]][k] > 0)
  	  break;
      if (j == m)
      {
	cerr << "phase2: Das Problem ist nach unten "
	 	 "nicht beschraenkt -- Funktionsabbruch" << endl;
	returncode = false;
	goto cleanup;
      }
      
      min = DBL_MAX; 
      l = n; 

      for (i=0; i<m; i++)
      {
	if (x1[J[i]][k] > 0)
	{
	  if ((p1[J[i]] / x1[J[i]][k]) < min)
	  {
	    min = p1[J[i]] / x1[J[i]][k];
	    l = J[i]; // l gefunden
	  }
	  else if ((p1[J[i]] / x1[J[i]][k]) == min && J[i] < l)
	     l = J[i]; 
	}
      }

#ifdef VERBOSE
      cout << "l = " << l << endl;
#endif
      
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
	    x2[k][l] = 1.0/x1[l][k];
	  else if (J[i] == k)
	    x2[k][Jc[j]] = x1[l][Jc[j]]/x1[l][k];
	  else if (Jc[j] == l)
	    x2[J[i]][l] = - (x1[J[i]][k]/x1[l][k]);
	  else
	  {
	    x2[J[i]][Jc[j]] = x1[J[i]][Jc[j]] 
	      - x1[l][Jc[j]]*(x1[J[i]][k]/x1[l][k]);
	  }
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
   
  // Ausgabe minimaler Funktionswert, Anzahl der Iterationen, p
  sum  = 0;
  for (i=0; i<m; i++)
    sum += c[J[i]]*p1[J[i]];

#ifdef VERBOSE
  cout << "\nMinimaler Funktionswert: " << sum;
  cout << "\nZugehoeriges p: ( " << setprecision(2) << p1[0];

  for (i=1; i<n; i++)
    cout << ", " << setprecision(2) << p1[i];

  cout << " )";
  cout << "\nAnzahl der Iterationen: " << (counter+1) << endl << endl;
#endif
  
cleanup:
  
  for (i=0; i<n; i++)
  {
    if (i < m)
      free(tempA[i]);
   
    free(x1[i]);
    free(x2[i]);
  }

  free(x1);
  free(x2);
  free(tempA);
  free(tempb);
  free(tausch);
  free(J);
  free(Jc);
  free(p2);

  if (counter >= MAXITERS)
    returncode = false;

  return returncode;
}

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
