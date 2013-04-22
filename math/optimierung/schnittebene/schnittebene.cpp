#include "defs.h"
#include "schnittebene.h"
#include "simplex.h"
#include <iostream>

using namespace std;

int schnittebenenverfahren(double * const x,
       const int &zeilen, const int &spalten, const double ** const A, 
       const double * const b, const double * const l, const double * const u, 
       double (* const f) (const double * const x), 
       void (* const subgrad_f) (const double * const x, double * const y))
{
  int i, j, iters = 1;
  
  int zeilen_gesamt = zeilen+2*spalten;
  int spalten_gesamt = spalten+1;
  
  double *c, *d, *d_temp, *x_temp, *lambda;
  double **M, **M_temp;

  c = new double[spalten_gesamt];
  ASSERT(c);
  d = new double[zeilen_gesamt];
  ASSERT(d);
  x_temp = new double[spalten_gesamt];
  ASSERT(x_temp);
  lambda = new double[spalten];
  ASSERT(lambda);
  M = new double*[zeilen_gesamt];
  ASSERT(M);

  // Initialisierung des Kostenvektors c
  //
  /////////////////
  //
  //    [ 0 ]
  //    [ 0 ]
  //      .
  // c =  .
  //      .
  //    [ 0 ]
  //    [ 1 ]
  //
  /////////////////
  
  for (i=0; i<spalten_gesamt-1; i++)
    c[i] = 0.0;

  c[spalten_gesamt-1] = 1.0;  

  // Initialisierung der Matrix M 
  // und der rechten Seite d
  //
  /////////////////
  //
  //     [                   A                       0 ]
  //     [     -1        0     ...          0        0 ]
  //	 [      0       -1     ...          0        0 ]
  //       .
  //       .
  //       .
  //     [      0        0     ...         -1        0 ]
  // M = [      1        0     ...          0        0 ]
  //	 [      0        1     ...          0        0 ]
  //	   .
  //	   .
  //	   .
  //	 [      0        0     ...          1        0 ]
  //
  /////////////////
  //
  //    [       b[0]      ]
  //    [       b[1]      ]
  //             .
  //             .
  //             .
  //    [   b[zeilen-1]   ]   
  //    [      -l[0]      ]
  //    [      -l[1]      ]
  //             .
  // d =         .
  //             .
  //    [  -l[spalten-1]  ]
  //    [       u[0]      ]
  //    [       u[1]      ]
  //             .
  //             .
  //             .
  //    [   u[spalten-1]  ]
  //
  /////////////////  
  
  for (i=0; i<zeilen_gesamt; i++)
  {
    M[i] = new double[spalten_gesamt];
    ASSERT(M[i]);
  }

  for (i=0; i<zeilen; i++)
  {
    d[i] = b[i];
    
    for (j=0; j<spalten_gesamt; j++)
    {
      if (j<spalten_gesamt-1)
        M[i][j] = A[i][j];
      else
        M[i][j] = 0.0;
    }
  }
   
  for (i=zeilen; i<zeilen_gesamt; i++)
    for (j=0; j<spalten_gesamt; j++)
    {
      if (i<zeilen+spalten && j==i-zeilen)
      { 
        M[i][j] = -1.0;
        d[i] = -l[i-zeilen];
      }
      else if(i<zeilen_gesamt && j==i-(zeilen+spalten))
      {
        M[i][j] = 1.0;
        d[i] = u[i-(zeilen+spalten)];
      }
      else 
        M[i][j] = 0.0;
    }
  
  while (iters<MAXITERS)
  {
    double scalar = 0.0, eps = 0.0;
   
    // Erweitere M und d um jeweils eine Zeile
    //
    ///////////////
    //
    // M = [                     M                        ]
    //	   [ lambda[0] lambda[1] ... lambda[spalten-1] -1 ]
    // 
    ///////////////
    // 
    // d = [        d        ]  
    //     [ lambda*x - f(x) ]
    ///////////////
 
    M_temp = new double*[zeilen_gesamt+1];
    ASSERT(M_temp);
    d_temp = new double[zeilen_gesamt+1];
    ASSERT(d_temp);
   
    for (i=0; i<zeilen_gesamt; i++)
    {
      M_temp[i] = M[i];
      d_temp[i] = d[i];
    } 

    M_temp[zeilen_gesamt] = new double[spalten+1];
    ASSERT(M_temp[zeilen_gesamt]);

    delete [] M;
    M = M_temp;
    delete [] d;

    d = d_temp;
    
    subgrad_f(x, lambda);
 
    for (i=0; i<spalten; i++)
      scalar += x[i]*lambda[i];

    for (j=0; j<spalten; j++)
      M[zeilen_gesamt][j] = lambda[j];
       
    M[zeilen_gesamt][spalten] = -1.0;
    d[zeilen_gesamt] = scalar - f(x);
   
    zeilen_gesamt++;

    ///// Testausgabe
/*
    cout << "c: ";
    for (i=0; i<spalten_gesamt; i++)
      cout << c[i] << " ";
    cout << endl << "d: ";
    for (i=0; i<zeilen_gesamt; i++)
      cout << d[i] << " ";
    cout << endl << "M: ";
    for (i=0; i<zeilen_gesamt; i++)
    {
      for (j=0; j<spalten_gesamt; j++)
        cout << "\t" << M[i][j];
      cout << endl;
    }
    cout << endl;
*/    
    ///// Ende Testausgabe
  
    simplex(zeilen_gesamt, spalten_gesamt, (const double ** const) M, 
    								d, c, x_temp);
    
    for (i=0; i<spalten; i++)   
      eps += (x[i]-x_temp[i])*(x[i]-x_temp[i]);
     
    eps = sqrt(eps);

    for (i=0; i<spalten; i++)
      x[i] = x_temp[i];

    if (eps < EPSILON)
      break;

    iters++;
  }

  delete [] x_temp;
  delete [] c;
  delete [] d;

  for (i=0; i<zeilen_gesamt; i++)
    delete [] M[i];

  delete [] M;

  return iters;
}
