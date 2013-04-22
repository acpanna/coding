#include "newton.h"
#include "gauss.h"
#include <iostream>

#define MAXITERS  10000
#define EPSILON   0.0001

#define ASSERT(x)  if(x == NULL) \
{ cout << "Speicherreservierung fehlgeschlagen -- Programmabbruch" << endl; exit(1); }

using namespace std;

int newton(const int &dimX, 
	double (*f[])(const double * const x), 
	void (*grad_f[])(const double * const x, double * const y), 
	double * const x0)
{
  int i, j, count = 1;
  
  double *x1 = new double[dimX];
  double *tempx = new double[dimX];
  int *tausch = new int[dimX];
  double **A = new double*[dimX];
  
  ASSERT(x1);
  ASSERT(tempx);
  ASSERT(tausch);
  ASSERT(A);
  
  for (i=0; i<dimX; i++)
  {
    A[i] = new double[dimX];
    ASSERT(A[i]);
  }

  while(count < MAXITERS)
  {
    for (i=0; i<dimX; i++)
      x1[i] = - f[i](x0);

    double sum = 0;
    for (i=0; i<dimX; i++)
      sum += pow(x1[i], 2);
    
    if (sqrt(sum) <= EPSILON)
      break;
    
    for (i=0; i<dimX; i++)
      for (j=0; j<dimX; j++)
	grad_f[i](x0, A[i]);

    for (i=0; i<dimX; i++)
      tempx[i] = x1[i];
    
    if(gauss(dimX, A, tempx, tausch) < dimX)
    {
      cerr << "gauss: Rang der Matrix ist nicht maximal -- Abbruch" << endl;
      exit(1);
    }
    if (!solveLR(dimX, (const double **) A, x1, tausch))
    {
      cerr << "solveLR: Rang der Matrix ist nicht maximal -- Abbruch" << endl;
      exit(1);
    }
      
    for (i=0; i<dimX; i++)
      x0[i] = x0[i] + x1[i];

    count++;
  }

  for (i=0; i<dimX; i++)
    delete [] A[i];

  delete [] A;
  delete [] x1;
  delete [] tausch;
  
  return count;
}
