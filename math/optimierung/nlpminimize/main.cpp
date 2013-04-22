#include "nlpminimize.h"
#include <iostream>
#include "defs.h"

double f(const double * const x);
double g1(const double * const x);
void grad_f(const double * const x, double * const y);
void grad_g1(const double * const x, double * const y);

using namespace std;

int main(void)
{
  int n = 2, m = 1, q1 = 1, q2 = 2;
  int iters;
  
  double (*restriction[1])(const double * const x);
  void (*restrictionGradient[1])(const double * const x, double * const y);
  
  restriction[0] = g1;
  restrictionGradient[0] = grad_g1;

  double b[] = { 10.0, 12.0 };
  double x[] = { 0.0, 0.0 };
  
  double **A = new double*[2];
  ASSERT(A);
  A[0] = new double[2];
  ASSERT(A[0]);
  A[1] = new double[2];
  ASSERT(A[1]);
  
  A[0][0] = 0.0;
  A[0][1] = 1.0;
  A[1][0] = 1.0;
  A[1][1] = 0.0;

  cout << "==" << endl;
  cout << " nlpminimize-Aufruf fuer Aufgabe a) liefert:" << endl; 
  cout << "==" << endl;
  
  if ((iters = nlpminimize(n, f, grad_f, 
		m, restriction, restrictionGradient, 
	      	q1, (const double ** const) A, b, 
	      	x, 1, 1.0/1000.0)) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da Fehler aufgetreten sind -- es lautet: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl;

  x[0] = 0.0;
  x[1] = 0.0;
  
  cout << "==" << endl;
  cout << " nlpminimize-Aufruf fuer Aufgabe b) liefert:" << endl;
  cout << "==" << endl;
  
  if ((iters = nlpminimize(n, f, grad_f, 
		m, restriction, restrictionGradient, 
		q2, (const double ** const) A, b, 
		x, 1, 1.0/1000.0)) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da Fehler aufgetreten sind -- es lautet: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
 
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;

  delete [] A[0];
  delete [] A[1];
  
  delete [] A;
  
  return 0;
}

double f(const double * const x)
{
  return ((1.0/2.0)*(x[0]*x[0] + x[1]*x[1] - 4.0*x[0]*x[1]) - x[0]);
}

double g1(const double * const x)
{
  return (100.0 - (x[0] - 12.0)*(x[0] - 12.0) - x[1]*x[1]);
}

void grad_f(const double * const x, double * const y)
{
  y[0] = x[0] - 2.0*x[1] - 1.0;
  y[1] = x[1] - 2.0*x[0];
}

void grad_g1(const double * const x, double * const y)
{
  y[0] = -2.0*(x[0] - 12.0);
  y[1] = -2.0*x[1];
}
