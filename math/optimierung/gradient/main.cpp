#include "gradient_verfahren.h"
#include <iostream>
#include "defs.h"

double f(const double * const x);
void grad_f(const double * const x, double * const y);

using namespace std;

int main(void)
{
  int iters;
  
  double x[] = { 1.0, 0.5 };
  
  cout << "==" << endl;
  cout << " Gradienten-Verfahren fuer Funktion f(x1, x2) liefert:" << endl; 
  cout << "==" << endl;
  
  if ((iters = gradient_verfahren(2, f, grad_f, x)) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl;

  return 0;
}

double f(const double * const x)
{
  if (x[0] >= fabs(x[1]))
    return 5.0*sqrt(9*pow(x[0], 2) + 16.0*pow(x[1], 2));
  if (x[0] > 0 && x[0] < fabs(x[1]))
    return 9.0*x[0] + 16.0*fabs(x[1]);
  if (x[0] <= 0)
    return 9.0*x[0] + 16.0*fabs(x[1]) - pow(x[0], 3);
}

void grad_f(const double * const x, double * const y)
{
  if (x[0] >= fabs(x[1]))
  {
    y[0] = (45.0*x[0])/(sqrt(9*pow(x[0], 2) + 16.0*pow(x[1], 2)));
    y[1] = (80.0*x[1])/(sqrt(9*pow(x[0], 2) + 16.0*pow(x[1], 2)));
  }
  
  if (x[0] > 0 && x[0] < fabs(x[1]))
  {
    y[0] = 9.0;
    y[1] = (16.0*x[1])/fabs(x[1]);
  }
	      
  if (x[0] <= 0)
  {
    y[0] = 9.0 - 3*pow(x[0], 2);
    y[1] = (16.0*x[1])/fabs(x[1]);
  }
}
