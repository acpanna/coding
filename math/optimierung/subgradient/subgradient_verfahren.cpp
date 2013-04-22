#include "subgradient_verfahren.h"
#include <iostream>
#include "defs.h"

using namespace std;

int subgradient_verfahren(const int &dimX,  
                double (* const func)(const double * const x),
	        void (* const funcSubgradient)(const double * const x, 
			double * const y),
		double * const x0, int schrittstrategie, double optimum)
{
  int i, itercount;

  double *d0 = new double[dimX]; 
  ASSERT(d0);
  double *x1 = new double[dimX]; 
  ASSERT(x1);
  
  //Schleifenanfang
  for (itercount=0; itercount<MAXITERS; itercount++)
  {
    double sum = 0.0;
    double eps = 0.0;
    double alpha = 0.0;

    funcSubgradient(x0, d0);
    for (i=0; i<dimX; i++)
      sum += d0[i]*d0[i];
      
    if (schrittstrategie == 1)
      alpha = 1.0/(itercount+1); 
    else if (schrittstrategie == 2)
      alpha = (func(x0) - optimum)/sqrt(sum); 
     
    for (i=0; i<dimX; i++)
    {
      d0[i] = -d0[i]/sqrt(sum); // d0 = - subgrad_f(x0) / ||subgrad_f(x0)||  
      x1[i] = x0[i];
      x0[i] = x1[i] + alpha*d0[i];
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
