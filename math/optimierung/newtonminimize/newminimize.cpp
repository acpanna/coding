#include "gauss.h"
#include <iostream>

#define MAXITERS   10000
#define EPSILON    0.0001

double f(const double * const x);
void grad_f(const double * const x, double * const y);
void hess_f(const double * const x, double ** const y);

// Dient zum Loesen von Problemen der Art:
// Minimiere f(x) unter den NB A*x=b mit x aus R^n, b aus R^m
// Voraussetzungen:
// f(x) 2*stetig diff.bar und konvex, hess_f(x) pos. definit, 
// rang A = m und m<=n 
int newtonMinimize(double (*zielfunktion)(const double * const x),
		void (*gradient_zielfunktion)(const double * const x, 
						double * const y),	
		void (*hesse_zielfunktion)(const double * const x, 
						double ** const y),	
		int &dimX, int &dimLambda,
  		const double ** const A, const double * const b,
		double * const x,
		double * const lambda);

using namespace std;

int main(void)
{
  int n = 2, m = 1;
  
  double **A;
  
  double b[] = { -4.0 };
  double x[] = { 0.0, 0.0 };
  double lambda[] = { 0.0 };
  
  A = new double*[1];
  ASSERT(A);
  A[0] = new double[2];
  ASSERT(A[0]);

  A[0][0] =  2.0;
  A[0][1] = -1.0;
  
  cout << "Minimiere f(x1, x2) = 2*x1^4 + x2^4 + 4*x1^2 - x1*x2 + 6*x2^2,\n";
  cout << "unter den NB: A*x = b, wobei A = (2 -1), b = (-4)" << endl;
  cout << endl << "| Ausgabe |" << endl << endl;
  cout << "Epsilon: " << EPSILON << endl;
  cout << "Hoechstiterationszahl: " << MAXITERS << endl;
  cout << "Anzahl der Iterationen: " << newtonMinimize(f, grad_f, hess_f, 
		  n, m, (const double ** const) A, b, x, lambda) << endl; 
  cout << "Optimum bei: x = ( " << x[0] << ", " << x[1] <<" ), lambda = ( " 
    		<< lambda[0] << " )" << endl;
  
  delete [] A[0];
  delete [] A;
  
  return 0;
}

int newtonMinimize(double (*zielfunktion)(const double * const x),
		void (*gradient_zielfunktion)(const double * const x, 
						double * const y),	
		void (*hesse_zielfunktion)(const double * const x, 
						double ** const y),	
		int &dimX, int &dimLambda,
  		const double ** const A, const double * const b,
		double * const x,
		double * const lambda)
{
  int i, j, iterations = 1;
  double sum;
  
  double **B, **hesse;
  double *c, *tempc;
  int *tausch;
  
  B = new double*[dimX+dimLambda];
  hesse = new double*[dimX];
  c = new double[dimX+dimLambda];
  tempc = new double[dimX+dimLambda];
  tausch = new int[dimX+dimLambda];
  
  ASSERT(B);
  ASSERT(hesse);
  ASSERT(c);
  ASSERT(tempc);
  ASSERT(tausch);
  
  for (i=0; i<dimX+dimLambda; i++)
  {
    B[i] = new double[dimX+dimLambda];
    ASSERT(B[i]);
    
    if (i<dimX)
    {
      hesse[i] = new double[dimX];
      ASSERT(hesse[i]);
    }
  }
  
  while (iterations < MAXITERS)
  {
    hesse_zielfunktion(x, hesse); // hesse wird mit Hess_f(x) belegt 
   
    // B = [ hesse trans(A) ]
    //     [   A       0    ]
    for (i=0; i<dimX+dimLambda; i++)
      for (j=0; j<dimX+dimLambda; j++)
      {
	if (i<dimX && j<dimX)
	  B[i][j] = hesse[i][j];
      	else if (i<dimX && j>=dimX)
	  B[i][j] = A[j-dimX][i];
     	else if (i>= dimX && j<dimX)
	  B[i][j] = A[i-dimX][j];
	else 
	  B[i][j] = 0.0;
      }
     

    gradient_zielfunktion(x, c); // dimX-Komponente von c wird 
                                 // mit grad_f(x) belegt
    
    // c =  [ grad_f(x) + trans(A)*lambda ] 
    //      [           A*x - b           ]
    for (i=0; i<dimX; i++)
      for (j=0; j<dimLambda; j++)
	  c[i] += A[j][i] * lambda[j];
    
    for (i=dimX; i<dimX+dimLambda; i++)
    {
      c[i] = -b[i-dimX];
      
      for (j=0; j<dimX; j++)
	c[i] += A[i-dimX][j] * x[j];
    }
    
    // Falls ||c|| <= EPSILON
    // breche ab, denn dann ist 
    // (x, lambda) "optimal"
    sum = 0.0;
    for (i=0; i<dimX+dimLambda; i++)
      sum += pow(c[i], 2);
      
    if (sqrt(sum) <= EPSILON)
      break;
    
    // c = -c + B * [   x    ]
    //              [ lambda ]
    for (i=0; i<dimX+dimLambda; i++)
    {
      c[i] = -c[i];
          
      for (j=0; j<dimX+dimLambda; j++)
      {
	if (j<dimX)
	  c[i] += B[i][j] * x[j];
	else  
	  c[i] += B[i][j] * lambda[j-dimX];
      }
    }

    // Erstelle Kopie von c 
    for (i=0; i<dimX+dimLambda; i++)
      tempc[i] = c[i];
    
    // Loese das LGS B * [    x   ] = c
    //                   [ lambda ]
    if (gauss(dimX+dimLambda, B, tempc, tausch) < dimX+dimLambda)
    {
      cerr << "gauss: Der Rang der Matrix ist nicht maximal -- Abbruch" << endl;
      exit(1);
    }
    if (!solveLR(dimX+dimLambda, (const double ** const) B, c, tausch))
    {
      cerr << "solveLR: Der Rang der Matrix ist nicht maximal -- Abbruch" 
	<< endl;
      exit(1);
    }
    
    // Kopiere die entsprechenden Komponenten der Loesung des 
    // vorherigen LGS nach x bzw. lambda
    for (i=0; i<dimX+dimLambda; i++)
    {
      if (i<dimX)
        x[i] = c[i];
      else
	lambda[i-dimX] = c[i];
    }
      
    iterations++;
  }

  for (i=0; i<dimX+dimLambda; i++)
  {
    delete [] B[i];

    if (i<dimX)
      delete [] hesse[i];
  }

  delete [] B;
  delete [] hesse;
  delete [] c;
  delete [] tempc;
  delete [] tausch;

  return iterations;
}

double f(const double * const x)
{
  return (2.0*pow(x[0], 4) + pow(x[1], 4) + 4.0*pow(x[0], 2) 
		  - x[0]*x[1] + 6.0*pow(x[1], 2));
}

void grad_f(const double * const x, double * const y)
{
  y[0] = 8.0*pow(x[0], 3) + 8.0*x[0] - x[1];
  y[1] = 4.0*pow(x[1], 3) - x[0] + 12.0*x[1];
}

void hess_f(const double * const x, double ** const y)
{
  y[0][0] = 24.0*pow(x[0], 2) + 8.0;
  y[0][1] = -1.0;
  y[1][0] = -1.0;
  y[1][1] = 12.0*pow(x[1], 2) + 12.0;
}
