#include "subgradient_verfahren.h"
#include <iostream>
#include "defs.h"

double f(const double * const x);
void subgrad_f(const double * const x, double * const y);
double g1(const double * const x);
void subgrad_g1(const double * const x, double * const y);
double g2(const double * const x);
void subgrad_g2(const double * const x, double * const y);
double g3(const double * const x);
void subgrad_g3(const double * const x, double * const y);
double g4(const double * const x);
void subgrad_g4(const double * const x, double * const y);

using namespace std;

int main(void)
{
  int iters;
  
  //////////////////////////////////////////////////////////////////////////
  
  double x[] = { 1.0, 0.5 };
  double x_opt[] = { -sqrt(3.0), 0 };
  
  cout << "==" << endl;
  cout << " Subgradienten-Verfahren fuer\n" \ 
          " die Funktion aus Uebung1 / Aufg3\n" \
	  " mit Startwert x = ( " << x[0] << ", " << x[1] << " ) liefert:\n"; 
  cout << "==" << endl << endl;
  cout << "( alpha_k = 1 / k )" << endl;
  
  if ((iters = subgradient_verfahren(2, f, subgrad_f, x, 1, f(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

  x[0] = 1.0;
  x[1] = 0.5;
  
  cout << "( alpha_k = (f(x_k) - f(x_opt)) / ||subgrad_f(x_k)|| )" << endl;
  
  if ((iters = subgradient_verfahren(2, f, subgrad_f, x, 2, f(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;
  
  //////////////////////////////////////////////////////////////////////////
 
  x[0] = 1.0;
  x[1] = 1.0;

  x_opt[0] = 3.0;
  x_opt[1] = 0.5;
  
  cout << "==" << endl;
  cout << " Subgradienten-Verfahren fuer\n" \ 
          " die Funktion aus Uebung3 / Aufg9a\n" \
	  " mit Startwert x = ( " << x[0] << ", " << x[1] << " ) liefert:\n"; 
  cout << "==" << endl << endl;
  cout << "( alpha_k = 1 / k )" << endl;
  
  if ((iters = subgradient_verfahren(2, g1, subgrad_g1, x, 1, g1(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

  x[0] = 1.0;
  x[1] = 1.0;
  
  cout << "( alpha_k = (f(x_k) - f(x_opt)) / ||subgrad_f(x_k)|| )" << endl;
  
  if ((iters = subgradient_verfahren(2, g1, subgrad_g1, x, 2, g1(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;
  
  //////////////////////////////////////////////////////////////////////////
  
  x[0] = -1.5;
  x[1] = 2.0;

  x_opt[0] = 0.0;
  x_opt[1] = 0.0;
 
  cout << "==" << endl;
  cout << " Subgradienten-Verfahren fuer\n" \ 
          " die Funktion aus Uebung3 / Aufg9b\n" \
	  " mit Startwert x = ( " << x[0] << ", " << x[1] << " ) liefert:\n"; 
  cout << "==" << endl << endl;
  cout << "( alpha_k = 1 / k )" << endl;
  
  if ((iters = subgradient_verfahren(2, g2, subgrad_g2, x, 1, g2(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

  x[0] = -1.5;
  x[1] = 2.0;
  
  cout << "( alpha_k = (f(x_k) - f(x_opt)) / ||subgrad_f(x_k)|| )" << endl;
  
  if ((iters = subgradient_verfahren(2, g2, subgrad_g2, x, 2, g2(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl;
  
  //////////////////////////////////////////////////////////////////////////
 
  x[0] = 2.0;
  x[1] = 2.0;

  x_opt[0] = 1.0;
  x_opt[1] = 1.0;
  
  cout << "==" << endl;
  cout << " Subgradienten-Verfahren fuer\n" \ 
          " die Funktion aus Uebung3 / Aufg9c\n" \
	  " mit Startwert x = ( " << x[0] << ", " << x[1] << " ) liefert:\n"; 
  cout << "==" << endl << endl;
  cout << "( alpha_k = 1 / k )" << endl;
  
  if ((iters = subgradient_verfahren(2, g3, subgrad_g3, x, 1, g3(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

  x[0] = 2.0;
  x[1] = 2.0;
  
  cout << "( alpha_k = (f(x_k) - f(x_opt)) / ||subgrad_f(x_k)|| )" << endl;
  
  if ((iters = subgradient_verfahren(2, g3, subgrad_g3, x, 2, g3(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;
  
  //////////////////////////////////////////////////////////////////////////
 
  x[0] = 1.0;
  x[1] = 0.0;

  x_opt[0] = 21.0;
  x_opt[1] = 10.0;
  
  cout << "==" << endl;
  cout << " Subgradienten-Verfahren fuer\n" \ 
          " die Funktion aus Uebung3 / Aufg9d\n" \
	  " mit Startwert x = ( " << x[0] << ", " << x[1] << " ) liefert:\n"; 
  cout << "==" << endl << endl;
  cout << "( alpha_k = 1 / k )" << endl;
  
  if ((iters = subgradient_verfahren(2, g4, subgrad_g4, x, 1, g4(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

  x[0] = 1.0;
  x[1] = 0.0;
  
  cout << "( alpha_k = (f(x_k) - f(x_opt)) / ||subgrad_f(x_k)|| )" << endl;
  
  if ((iters = subgradient_verfahren(2, g4, subgrad_g4, x, 2, g4(x_opt))) < 0)
  {
    cerr << "\nDas Ergebnis ist eventuell nicht optimal, \n"
      "da die maximale Iterationszahl erreicht wurde: ";
  }
  
  cout << "x = ( " << x[0] << ", " << x[1] << " )" << endl;
  
  if (iters > 0)
    cout << "Iterationszahl: " << iters << endl;
 
  cout << endl << endl;

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

void subgrad_f(const double * const x, double * const y)
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

double g1(const double * const x)
{
  return ( pow(1.5   - x[0]*(1-x[1]), 2) 
         + pow(2.25  - x[0]*(1-pow(x[1], 2)), 2) 
	 + pow(2.625 - x[0]*(1-pow(x[1], 3)), 2) );
}

void subgrad_g1(const double * const x, double * const y)
{
  y[0] = -2*(1-x[1])        * (1.5   - x[0]*(1-x[1])) 
         -2*(1-pow(x[1],2)) * (2.25  - x[0]*(1-pow(x[1],2))) 
	 -2*(1-pow(x[1],3)) * (2.625 - x[0]*(1-pow(x[1],3)));
  
  y[1] = 2*x[0]             * (1.5   - x[0]*(1-x[1])) 
        +4*x[0]*x[1]        * (2.25  - x[0]*(1-pow(x[1],2))) 
        +6*x[0]*pow(x[1],2) * (2.625 - x[0]*(1-pow(x[1],3)));
}

double g2(const double * const x)
{
  return max(pow(x[0],2)+pow((x[1]-1),2)+x[1]-1,
            -pow(x[0],2)-pow((x[1]-1),2)+x[1]+1);
}

void subgrad_g2(const double * const x, double * const y)
{
  if ((pow(x[0],2)+pow((x[1]-1),2)+x[1]-1) 
       >= (-pow(x[0],2)-pow((x[1]-1),2)+x[1]+1))
  {
    y[0] = 2*x[0];
    y[1] = 2*(x[1]-1) + 1;
  }

  else
  {
    y[0] = -2*x[0];
    y[1] = -2*(x[1]-1) + 1;
  }
}	 

double g3(const double * const x)
{
  return max(max(pow(x[0],4)+pow(x[1],2), 
                 pow(2-x[0],2)+pow(2-x[1],2)), 
		 2*exp(x[1]-x[0]));
}

void subgrad_g3(const double * const x, double * const y)
{
  double erg1, erg2, erg3;
 
  if ((erg1 = pow(x[0],4)+pow(x[1],2)) >= (erg2 = pow(2-x[0],2)+pow(2-x[1],2))
         && erg1 >= (erg3 = 2*exp(x[1]-x[0])))
  {
    y[0] = 4*pow(x[0],3);
    y[1] = 2*x[1];
  }
  else if (erg2 >= erg1 && erg2 >= erg3)
  {
    y[0] = 2*(2-x[0]);
    y[1] = 2*(2-x[1]);
  }
  else
  {
    y[0] = -2*exp(x[1]-x[0]);
    y[1] = 2*exp(x[1]-x[0]);
  }
}

double g4(const double * const x)
{
  return (0.5*(pow(x[0],2)+pow(x[1],2)-4*x[0]*x[1])-x[0] 
          + 100*(max(100-pow((x[0]-12),2) - pow(x[1],2), 0) 
	        +max(x[1]-10, 0) 
		+max(-x[0], 0) 
		+max(-x[1], 0)));
}

void subgrad_g4(const double * const x, double * const y)
{
  double erg1 = max(100-pow((x[0]-12),2) - pow(x[1],2), 0);
  double erg2 = max(x[1]-10, 0);
  double erg3 = max(-x[0], 0);
  double erg4 = max(-x[1], 0);
  
  y[0] = x[0] - 2*x[1] -1;
  y[1] = x[1] - 2*x[0];
  
  if (erg4 != 0)
    y[1] = y[1] - 100;
  if (erg3 != 0)
    y[0] = y[0] - 100;
  if (erg2 != 0)
    y[1] = y[1] + 100;
  if (erg1 != 0)
  {
    y[0] = y[0] - 200*(x[0]-12);
    y[1] = y[1] - 200*x[1];
  }
  
  return;
} 

  
