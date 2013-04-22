#include "armijo.h"
#include <iostream>
#include <cmath>
#include "defs.h"

using namespace std;

double armijo(const int &dimX, 
		double (* const func)(const double * const x),
		void (* const funcGradient)(const double * const x, 
			double * const y),
		const int &restrictions,
		double (* const restrictFunc[])(const double * const x),
	 	const int &zeilen,
	        const double ** const A, const double * const b,
		double * const x0, double * const d0, 
		const double &s, const double &beta, const double &sigma)
{
  if (s<=0 || beta<=0 || beta>=1 || sigma<=0 || sigma>=1.0/2.0)
  {
    cerr << "armijo: Parameter wurden falsch gewaehlt, es muss gelten:\n"
      "s>0, 0<beta<1, 0<sigma<1/2 -- Programmabbruch\n";
    exit(1);
  }

  int i, j;
  int itercount;
  
  double alpha = s;
  
  double *x1 = new double[dimX];
  ASSERT(x1);
  double *gradient = new double[dimX];
  ASSERT(gradient);
  
  for (itercount=0; itercount<MAXITERS; itercount++)
  {
    // x1 := x0 + alpha * d0
    for (i=0; i<dimX; i++)
      x1[i] = x0[i] + alpha * d0[i];

    // gradient := grad_f(x0) 
    funcGradient(x0, gradient);
    
    // scalar := grad_f(x0) * d0  
    double scalar = 0.0;
    for (i=0; i<dimX; i++)
      scalar += gradient[i] * d0[i]; 
 
    // M := { z=(z1, ..., zn) >= 0 | A*z<=b, z>=0,
    //        restrictFunc[i](z) <= 0, (i=1, ..., restrictions) }
    //
    // Pruefe, ob x1 in M liegt
    
    // Ist x1>=0 ?   
    bool element = true;
    for (i=0; i<dimX; i++)
      if (x1[i] < 0) 
      {
	element = false;
	break;
      }
	
    // Ist A*x1<=b ?
    if (element)
      for (i=0; i<zeilen; i++)
      {
    	double sum = 0.0;
    	for (j=0; j<dimX; j++)
	  sum += A[i][j] * x1[j];
      	
	if (sum > b[i])
	{
	  element = false;
	  break;
	}
      }
    
    // Ist restrictFunc[i](x1) <= 0 (i=1, ..., restrictions) ?
    if (element)
      for (i=0; i<restrictions; i++)
    	if (restrictFunc[i](x1) > 0)
    	{
    	  element =false;
    	  break;
    	}
    
    // Wenn f(x0 + alpha * d0) <= f(x0) + sigma*alpha * grad_f(x0)*d0
    // und x1 liegt in M  ====>  fertig 
    if (element && (func(x1)-func(x0)  <=  sigma*alpha*scalar))
      break;
    else
      alpha = beta*alpha;
  }

  delete [] x1;
  delete [] gradient;
  
  return alpha;
}
