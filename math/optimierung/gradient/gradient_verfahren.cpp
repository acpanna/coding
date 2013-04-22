#include "gradient_verfahren.h"
#include <iostream>
#include "defs.h"

using namespace std;

int gradient_verfahren(const int &dimX,  
                double (* const func)(const double * const x),
	        void (* const funcGradient)(const double * const x, 
			double * const y),
		double * const x0)
{
  int i, itercount;

  double *d0 = new double[dimX]; 
  ASSERT(d0);
  double *x1 = new double[dimX]; 
  ASSERT(x1);
  
  //Schleifenanfang
  for (itercount=0; itercount<MAXITERS; itercount++)
  {
    double eps = 0.0;

    funcGradient(x0, d0);
    for (i=0; i<dimX; i++)
    {
      d0[i] = -d0[i]; // d0 = - grad_f(x0)  
      x1[i] = x0[i];
    }

    if (armijo(dimX, func, x0, d0, 1.0, 0.5, 1.0/1000.0) == -1)
    {
      itercount = MAXITERS;
      break;
    }
    
    for (i=0; i<dimX; i++)
      eps += (x1[i]-x0[i])*(x1[i]-x0[i]);

    if (sqrt(eps) < EPSILON)
      break;
  } 
  // Schleifenende

  delete [] d0;
  delete [] x1;
  
  if (itercount == MAXITERS)
    return -1;
  else
    return itercount;
}
