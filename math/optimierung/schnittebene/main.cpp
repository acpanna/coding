#include "defs.h"
#include "schnittebene.h"
#include <iostream>

double f(const double * const x);
void subgrad_f(const double * const x, double * const y);

using namespace std;

int main(void)
{
  int iters; 
  
  double x [] = { 1.0, 1.0 };
  double l [] = { -10.0, 10.0 };
  double u [] = {  10.0, 10.0 };
  double a [] = { 1.0, 1.0 };
  double b [] = { 10.0 };

  double **A;
  A = new double*[1];
  ASSERT(A);
  A[0] = a;

  iters = schnittebenenverfahren(x, 1, 2, (const double ** const) A, b, l, u, 
  								f, subgrad_f);
 
  cout << "Das Schnittebenenverfahren liefert nach " << iters \
       << " Iteration(en)\n( MAXITERS = " << MAXITERS << " ) " \
       << "folgendes Ergebnis:" << endl;
								
  cout << endl << "\tx_opt = ( " << x[0] << ", " << x[1] << " )" << endl;

  return 0;
}

double f(const double * const x)
{
  return max(max(5*x[0]+x[1], -5*x[0]+x[1]), x[0]*x[0]+x[1]*x[1]+4*x[1]);
}

void subgrad_f(const double * const x, double * const y)
{
  double m1, m2, m3;

  if ((m1 = 5*x[0]+x[1]) >= (m2 = -5*x[0]+x[1]) 
		&& m1 >= (m3 = x[0]*x[0]+x[1]*x[1]+4*x[1]))
  {
    y[0] = 5.0;
    y[1] = 1.0;
  }

  else if (m2 >= m1 && m2 >= m3)
  {
    y[0] = -5.0;
    y[1] = 1.0;
  }

  else
  {
    y[0] = 2*x[0];
    y[1] = 2*x[1] + 4.0;
  }
}
