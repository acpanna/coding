#include "armijo.h"
#include <iostream>
#include <cmath>
#include "defs.h"

using namespace std;

double armijo(const int &dimX, 
		double (* const func)(const double * const x),
		double * const x0, double * const d0, 
		const double &s, const double &beta, const double &sigma)
{
  if (s<=0 || beta<=0 || beta>=1 || sigma<=0 || sigma>=1.0/2.0)
  {
    cerr << "armijo: Parameter wurden falsch gewaehlt, es muss gelten:\n"
      "s>0, 0<beta<1, 0<sigma<1/2 -- Programmabbruch\n";
    exit(1);
  }

  int i, itercount;
  
  double alpha = s;
  
  double *x1 = new double[dimX];
  ASSERT(x1);
  
  for (itercount=0; itercount<MAXITERS; itercount++)
  {
    // x1 := x0 + alpha * d0
    for (i=0; i<dimX; i++)
      x1[i] = x0[i] + alpha * d0[i];

    // scalar := grad_f(x0) * d0  
    double scalar = 0.0;
    for (i=0; i<dimX; i++)
      scalar += (-1.0)*d0[i] * d0[i]; 
 
    // Wenn f(x0 + alpha * d0) <= f(x0) + sigma*alpha * grad_f(x0)*d0
    //   ====>  fertig 
    if (func(x1)-func(x0) <= sigma*alpha*scalar)
    {
      for (i=0; i<dimX; i++)
        x0[i] = x1[i];
      
      break;
    }
      
    else
      alpha = beta*alpha;
  }

  delete [] x1;
 
  if (itercount == MAXITERS)
    return -1;
  else
    return alpha;
}
