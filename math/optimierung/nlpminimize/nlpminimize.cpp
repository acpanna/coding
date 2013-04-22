#include "nlpminimize.h"
#include <iostream>
#include "defs.h"

using namespace std;

int nlpminimize(const int &dimX,  
                double (* const func)(const double * const x),
	        void (* const funcGradient)(const double * const x, 
			double * const y),
		const int &restrictions,
		double (* const restrictFunc[]) (const double * const x),
		void (* const restrictFuncGradient[]) (const double * const x, 
			double * const y),
		const int &zeilen, 
		const double ** const A, const double * const b, 
		double * const x0, const double &delta, const double &epsilon)
{
  int i, j;
  int itercount, active;

  double gamma, arm;
  
  int *Iepsilon = new int[restrictions];
  ASSERT(Iepsilon); 
  double *gradient = new double[dimX]; 
  ASSERT(gradient);
  double *c = new double[2*dimX+2];
  ASSERT(c);
  double *z = new double[2*dimX+2];
  ASSERT(z);
 
  // Besetzen von c
  for (i=0; i<2*dimX; i++)
    c[i] = 0.0;

  c[2*dimX] = 1.0;
  c[2*dimX+1] = -1.0;
  
  //     [  0 ] 
  //     [  0 ]
  // c = [ ...]
  //     [  0 ]
  //     [  1 ]
  //     [ -1 ]
  
  //Schleifenanfang
  for (itercount=0; itercount<MAXITERS; itercount++)
  {
    active = 0;
  
    // Iepsilon = { i = 1, ..., m | gi(x) >= -epsilon }
    // active = |Iepsilon|
    for (i=0; i<restrictions; i++)    
    {
      if (restrictFunc[i](x0) >= -epsilon)
      {
	Iepsilon[active] = i;
	active++;
      }
      
      if (restrictFunc[i](x0) > 0)
	cerr << "nlpminimize: Achtung !!! x0 liegt nicht in M --> Fehler" << endl;
    }
  
    double **W = new double*[1+active+dimX+zeilen+dimX+dimX];
    ASSERT(W);
    double *d = new double[1+active+dimX+zeilen+dimX+dimX];
    ASSERT(d);
    
    for (i=0; i<1+active+dimX+zeilen+dimX+dimX; i++)
    {
      W[i] = new double[2*dimX+2];
      ASSERT(W[i]);
    }

    ////////// Intialisierung -- Anfang //////////

    // Besetzen von W
    for (i=0; i<1+active+dimX+zeilen+dimX+dimX;i++)
      for (j=0; j<2*dimX+2; j++)
      {
	// W[0][] = [ trans(grad_f(x0))  -trans(grad_f(x0))  -1  1 ]
	if (i == 0)
	{
	  if (j == 0) 
	    funcGradient(x0, gradient);
          if (j < dimX)
            W[i][j] = gradient[j];
          if ((j >= dimX) && (j < 2*dimX))
            W[i][j] = -gradient[j-dimX];
          if (j == 2*dimX)
	    W[i][j] = -1.0;
	  if (j == 2*dimX+1)
	    W[i][j] = 1.0;
        }
      
        // W[1][]  = [ trans(grad_g[i0](x0))   trans(grad_gi1(x0))  -1  1 ]
        // W[2][]  = [ trans(grad_g[i1](x0))   trans(grad_gi2(x0))  -1  1 ]
        // ...            
        // W[ie][] = [ trans(grad_g[ie-1](x0)) trans(grad_gie(x0))  -1  1 ]
        if ((i >= 1) && (i < 1+active))
        {
	  if (j == 0)
	    restrictFuncGradient[Iepsilon[i-1]](x0, gradient);
          if (j < dimX)
            W[i][j] = gradient[j];
          if ((j >= dimX) && (j < 2*dimX))
	    W[i][j] = -gradient[j-dimX];
	  if (j == 2*dimX)
	    W[i][j] = -1.0;
	  if (j == 2*dimX+1)
	    W[i][j] = 1.0;
        }	
	
        // W[ie+1]    = [ -1  0 ...   0 1 0 ... 0 0 0 ]
        // W[ie+2]    = [  0 -1 ...   0 0 1 ... 0 0 0 ]
        // ...
        // W[ie+dimX] = [  0  0 .... -1 0 0 ... 1 0 0 ]
        if ((i >= 1+active) && (i < 1+active+dimX))
        {
	  if (j == i-(1+active))
	    W[i][j] = -1.0;
	  else if (j-dimX == i-(1+active))
	    W[i][j] = 1.0;
	  else
	    W[i][j] = 0.0;
        }

        // W[ie+dimX+1]      = [         A[0] -A[0]        0 0 ]
        // W[ie+dimX+2]      = [         A[1] -A[1]        0 0 ]
        // ...
        // W[ie+dimX+zeilen] = [  A[zeilen-1] -A[zeilen-1] 0 0 ]
        if ((i >= 1+active+dimX) && (i < 1+active+dimX+zeilen))
        {
	  if (j < dimX)
	    W[i][j] = A[i-(1+active+dimX)][j];
	  else if (j < 2*dimX)
	    W[i][j] = -A[i-(1+active+dimX)][j-dimX];
	  else
	    W[i][j] = 0.0;
        }

        // W[ie+dimX+zeilen+1]    = [ 1  0 ...  0 -1  0 ...  0 0 0 ]
        // W[ie+dimX+zeilen+2]    = [ 0  1 ...  0  0 -1 ...  0 0 0 ]
        // ...
        // W[ie+dimX+zeilen+dimX] = [ 0  0 .... 1  0  0 ... -1 0 0 ]
        if ((i >= 1+active+dimX+zeilen) && (i < 1+active+dimX+zeilen+dimX))
        {
	  if (j == i-(1+active+dimX+zeilen))
	    W[i][j] = 1.0;
	  else if (j-dimX == i-(1+active+dimX+zeilen))
	    W[i][j] = -1.0;
	  else
	    W[i][j] = 0.0;
        }

        // W[ie+dimX+zeilen+dimX+1]    = [ -1  0 ...   0 1 0 ... 0 0 0 ]
        // W[ie+dimX+zeilen+dimX+2]    = [  0 -1 ...   0 0 1 ... 0 0 0 ]
        // ...
        // W[ie+dimX+zeilen+dimX+dimX] = [  0  0 .... -1 0 0 ... 1 0 0 ]
        if ((i >= 1+active+dimX+zeilen+dimX) && 
			(i < 1+active+dimX+zeilen+dimX+dimX))
        {
	  if (j == i-(1+active+dimX+zeilen+dimX))
	    W[i][j] = -1.0;
	  else if (j-dimX == i-(1+active+dimX+zeilen+dimX))
	    W[i][j] = +1.0;
	  else
	    W[i][j] = 0.0;
        }
    } 

    // Besetzen von d
    for (i=0; i<1+active+dimX+zeilen+dimX+dimX; i++)
    {
      //     [      0     ]
      //     [  -gi0(x0)  ]
      //     [  -gi1(x0)  ]
      //           ...
      //     [ -gie-1(x0) ]
      // d = [     x0     ]
      //     [  b - A*x0  ]
      //     [   delta    ]
      //           ...
      //     [   delta    ]
      
      if (i == 0)
        d[i] = 0.0;
      else if (i < 1+active)
        d[i] = -restrictFunc[Iepsilon[i-1]](x0);
      else if (i < 1+active+dimX)
        d[i] = x0[i-(1+active)];
      else if (i< 1+active+dimX+zeilen)
      {
        double sum = 0.0;
        for (j=0; j<dimX; j++)
	  sum += A[i-(1+active+dimX)][j] * x0[j];
      
        d[i] = b[i-(1+active+dimX)] - sum;
      }
      else 
        d[i] = delta;
    }

    ////////// Initialisierung -- Ende //////////

    if (!simplex(1+active+dimX+zeilen+dimX+dimX, 2*dimX+2, 
			    (const double ** const) W, d, c, z))
    {
      cerr << "nlpminimize: Fehler beim Simplex-Verfahren aufgetreten "
	"-- Funktionsabbruch\n";
      itercount = -1;
      break;
    }
    
    gamma = z[2*dimX] - z[2*dimX+1];
    
    if (gamma >= -EPSILON)
     break;
    
    for (i=0; i<dimX; i++)
      gradient[i] = z[i] - z[dimX + i];
  
    arm = armijo(dimX, func, funcGradient, restrictions, restrictFunc,
		    zeilen, A, b, x0, gradient, 1.0, 0.5, 1.0/1000.0);
    
    for (i=0; i<dimX; i++)
      x0[i] = x0[i] + arm*gradient[i];

    for (i=0; i<1+active+dimX+zeilen+dimX+dimX; i++)
      delete [] W[i];
    
    delete [] W;
    delete [] d;
  } // Schleifenende

  delete [] Iepsilon;
  delete [] gradient;
  delete [] c;
  delete [] z;
  
  if (itercount == MAXITERS)
  {
    cerr << "nlpminimize: Maximale Iterationszahl wurde erreicht -- Funktionsabbruch\n";
    return -1;
  }
  else
    return itercount;
}
