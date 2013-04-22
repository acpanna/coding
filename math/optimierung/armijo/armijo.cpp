#include <iostream>
#include <cstdio>
#include <cmath>

#define MAXITERS 10000
#define MINDERIVATIONABS 1.0/1000000.0

double armijo(double (*func)(double x), double (*funcDerivation)(double x), 
	      double x0, double d0, double s, double beta, double sigma);

double armijo_auf(double (*func)(double x), double (*funcDerivation)(double x), 
	      double x0, double d0, double s, double beta, double sigma);

void armijoMinimize(double (*func)(double x), double (*funcDerivation)(double x),
                  double x0, double d0, double s, double beta, double sigma);

double funcA(double x);
double funcADerivation(double x);
double funcB(double x);
double funcBDerivation(double x);
double funcCa(double x);
double funcCaDerivation(double x);
double funcCb(double x);
double funcCbDerivation(double x);
double funcC(double x, double c1, double c2);
double funcCDerivation(double x, double c1, double c2);

using namespace std;

int main(void)
{
  char wait;

  cout << "Funktion A:" << endl << endl;
  armijoMinimize(funcA, funcADerivation, 0, -funcADerivation(0), 1, 0.9, 1.0/10000.0);
  cout << "Bitte RETURN betaetigen ...";
  scanf("%c", &wait);
  cout << "Funktion B:" << endl << endl;
  armijoMinimize(funcB, funcBDerivation, 0, -funcADerivation(0), 1, 0.9, 1.0/10000.0);
  cout << "Bitte RETURN betaetigen ...";
  scanf("%c", &wait);
  cout << "Funktion Ca:" << endl << endl;
  armijoMinimize(funcCa, funcCaDerivation, 0, -funcADerivation(0), 1, 0.9, 1.0/10000.0);
  cout << "Bitte RETURN betaetigen ...";
  scanf("%c", &wait);
  cout << "Funktion Cb:" << endl << endl;
  armijoMinimize(funcCb, funcCbDerivation, 0, -funcADerivation(0), 1, 0.9, 1.0/10000.0);
  
  return 0;
}

double armijo(double (*func)(double x), double (*funcDerivation)(double x), 
	      double x0, double d0, double s, double beta, double sigma)
{
  if (s<=0 || beta<=0 || beta>=1 || sigma<=0 || sigma>=1.0/2.0)
  {
    cerr << "Parameter wurden falsch gewaehlt, es muss gelten:\n"
      "s>0, 0<beta<1, 0<sigma<1/2\n";
    exit(1);
  }

  int itercount = 0;
  double alpha = s;

  while(( func(x0+alpha*d0)-func(x0) ) > ( sigma*alpha*funcDerivation(x0)*d0 ) && itercount++ < MAXITERS)
    alpha = beta*alpha;

  return alpha;
}

double armijo_auf(double (*func)(double x), double (*funcDerivation)(double x),
                  double x0, double d0, double s, double beta, double sigma)
{
  int itercount = 0;
  double oldalpha, newalpha;
  
  oldalpha = armijo(func, funcDerivation, x0, d0, s, beta, sigma);
  newalpha = oldalpha/beta;

  while(( func(x0+newalpha*d0)-func(x0) ) <= ( sigma*newalpha*funcDerivation(x0)*d0 ) && itercount++ < MAXITERS)
  {
    oldalpha = newalpha;
    newalpha = oldalpha/beta;
  }

  return oldalpha;
}

void armijoMinimize(double (*func)(double x), double (*funcDerivation)(double x),
                  double x0, double d0, double s, double beta, double sigma)
{
  int itercount = 0;
  double x, d;
  
  x = x0; d = d0;
 
  while (fabs(d) > MINDERIVATIONABS && itercount<MAXITERS)
  {
    cout << "Armijo-Verfahren: " << itercount << ". Iteration: x = " << x;
    cout << ", alpha = " << armijo(func, funcDerivation, x, d, s, beta, sigma) << ", d = " << d << endl;
    x = x + armijo(func, funcDerivation, x, d, s, beta, sigma) * d;
    d = -funcDerivation(x);
    
    itercount++;
  }

  cout << "Bitte RETURN betaetigen ...";
  scanf("%c",&itercount);
  
  itercount = 0; 
  x = x0; d = d0;
  
  while (fabs(d) > MINDERIVATIONABS && itercount<MAXITERS)
  {
    cout << "Armijo-Verfahren mit Aufweitung: " << itercount << ". Iteration: x = " << x;
    cout << ", alpha = " << armijo_auf(func, funcDerivation, x, d, s, beta, sigma) << ", d = " << d << endl;
    x = x + armijo_auf(func, funcDerivation, x, d, s, beta, sigma) * d;
    d = -funcDerivation(x);

    itercount++;
  }
}

double funcA(double x)
{
  return (-x/(x*x + 2));
}

double funcADerivation(double x)
{
  return ((x*x - 2)/((x*x + 2)*(x*x + 2)));
}

double funcB(double x)
{
  return (pow((x+0.004), 5) - 2*pow((x+0.004), 4));
}

double funcBDerivation(double x)
{
  return ((5*pow((x+0.004), 4) - 8*pow((x+0.004), 3)));
}

double funcCa(double x)
{
  return funcC(x, 0.01, 0.001);
}

double funcCaDerivation(double x)
{
  return funcCDerivation(x, 0.01, 0.001);
}
double funcCb(double x)
{
  return funcC(x, 0.001, 0.01);
}

double funcCbDerivation(double x)
{
  return funcCDerivation(x, 0.001, 0.01);
}

double funcC(double x, double c1, double c2)
{
  return ((sqrt(1+c1*c1)-c1)*sqrt((1-x)*(1-x) + c2*c2) + (sqrt(1+c2*c2)-c2)*sqrt(x*x + c1*c1));
}

double funcCDerivation(double x, double c1, double c2)
{
  return (((-(sqrt(1+c1*c1)-c1)*2*(1-x))/(sqrt((1-x)*(1-x)+c2*c2)) + ((sqrt(1+c2*c2)-c2)*2*x)/sqrt(x*x+c1*c1)));
}
