#include <iostream>

#define MAXITERS 10000
#define EPSILON  0 // Maximalabweichung des Optimalwerts

#define ASSERT(x)  if(x == NULL) { cout << "Speicherreservierung fehlgeschlagen -- Programmabbruch" << endl; exit(1); } 

bool kelleyMinimize(const int &dimension, 
		const double * const costVector,
		const double * const lowBound, 
		const double * const upBound,
		const int &restrictions, 
		double (* const restrictFunc[]) (const double * const x),
		void (* const restrictFuncGradient[]) (const double * const x, double * const y), 
		double * const result);

bool simplex(const int &zeilen, 
		const int &spalten, 
		const double ** const A, 
		const double * const b, 
		const double * const cost, 
		double * const ergebnis);

double g1(const double * const x);
void g1Gradient(const double * const x, double * const y);
double g2(const double * const x);
void g2Gradient(const double * const x, double * const y);

using namespace std;

int main(void)
{
  double costs[] = { 2.0, 1.0 };
  double lower[] = { 0.0, 0.0 };
  double upper[] = { 5.0, 4.0 };

  double resultat[2];

  double (*restriction[2])(const double * const x);
  void (*restrictionGradient[2])(const double * const x, double * const y);

  restriction[0] = g1;
  restriction[1] = g2;

  restrictionGradient[0] = g1Gradient;
  restrictionGradient[1] = g2Gradient;

  cout << "Schnittebenenverfahren von Kelley " << endl;
  cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
  cout << endl;
  cout << " f(x1, x2) = 2 * x1 + x2 ist zu minimieren"<< endl;
  cout << endl << "Restriktionen:" << endl;
  cout << "  g1(x1, x2) = 2 * (x1 - 3)^2  + (x2 - 4)^2 - 4 <= 0,\n" 
          "  g2(x1, x2) = (x1 - 3)^2 - x2 <= 0,\n"   
          "  0<= x1 <=5, 0<= x2 <= 4" << endl;
  cout << endl << "Ausgabe:" << endl;
  
  if (kelleyMinimize(2, costs, lower, upper, 2, 
			  restriction, restrictionGradient, resultat))
    cout << "\nDas gefundene Resultat ist optimal und lautet: (";
  else
  {
    cout << "\nDa Fehler aufgetreten sind, ist das gefundene Resultat" << endl;
    cout << "nicht notwendig optimal, es lautet: (";
  }

  cout << resultat[0] << ", " << resultat[1] << ")" << endl;

  return 0;
}

double g1(const double * const x)
{
  return ((x[0] - 3.0)*(x[0] - 3.0) + (x[1] - 2.0)*(x[1] - 2.0) - 4.0);
}

void g1Gradient(const double * const x, double * const y)
{
  y[0] = 2.0*(x[0] - 3.0);
  y[1] = 2.0*(x[1] - 2.0);
}

double g2(const double * const x)
{
  return ((x[0] - 3.0)*(x[0] - 3.0) - x[1]);
}

void g2Gradient(const double * const x, double * const y)
{
  y[0] = 2.0*(x[0] - 3.0);
  y[1] = -1.0;
}

bool kelleyMinimize(const int &dimension, 
		const double * const costVector, 
		const double * const lowBound, 
		const double * const upBound,
                const int &restrictions, 
		double (* const restrictFunc[]) (const double * const x),
		void (* const restrictFuncGradient[]) (const double * const x, double * const y), 
		double * const result)
{
  bool returncode = false;

  int i, j, iterations = 0;

  double **A, **tempA;
  double *b, *tempb, *gradient;

  A        = new double*[2*dimension];
  b        = new double[2*dimension];
  gradient = new double[dimension];

  ASSERT(A);
  ASSERT(b);
  ASSERT(gradient);

  for (i=0; i<2*dimension; i++)
  {
    A[i] = new double[dimension];
    ASSERT(A[i]);
  }

  for (i=0; i<2*dimension; i++)
    for (j=0; j<dimension; j++)
      A[i][j] = 0.0;

  for (i=0; i<2*dimension; i+=2)              // Besetze die Matrix A und den
  {                                           // Beschraenkungsvektor b
    A[i][i/2] = -1.0; b[i] = lowBound[i/2];   // -x[i] <= -lowBound[i]
    A[i+1][i/2] = 1.0; b[i+1] = upBound[i/2]; // x[i] <= upBound[i]
  }

  // Falls Iterationszahl zu gross, breche ab
  while (iterations < MAXITERS) 
  {
    int k;
    double sum = 0.0, diff = 0.0;
    bool isOptimal = true;

    if (!simplex(2*dimension+iterations, dimension,
		(const double ** const ) A, b, costVector, result))
    {
      cerr << "kelleyMinimize: Fehler bei der Anwendung des "
		"Simplex-Verfahrens --- Abbruch" << endl;
      returncode = false;
      break;
    }

    // Falls berechnetes Resultat
    // alle Restriktionen erfuellt
    // --> es ist optimal
    for (i=0; i<restrictions; i++)
      isOptimal = isOptimal && (restrictFunc[i](result) <= EPSILON); 
    if (isOptimal)    
    {
      returncode = true;
      break;
    }

    for (i=0; i<restrictions; i++)
    {
      // Hier wird der Index derjenigen Restriktion 
      // gesucht, die am staerksten verletzt ist 
      if (restrictFunc[i](result) > diff) 
      {                                   
        diff = restrictFunc[i](result);     
        k = i; // k = diesem Index
      }
    }
  
    // Berechne den Wert des Gradienten der k-ten Restriktion an
    // der Stelle result und speichere den Ergebnisvektor in gradient
    restrictFuncGradient[k](result, gradient); 
          
    ////////////////// Vergroessere die Zeilendimension um 1 /////////////////
  
    tempb = b; 
    tempA = A;
       
    // Vergroessere die Matrix A und den Vektor b
    // um 1 in der Zeilendimension
    A = new double*[2*dimension+iterations+1];
    b = new double[2*dimension+iterations+1]; 

    ASSERT(A);  
    ASSERT(b);
    
    for (i=0; i<2*dimension+iterations; i++)
    {
      A[i] = tempA[i]; 
      b[i] = tempb[i];
    }

    delete [] tempA;
    delete [] tempb;

    A[2*dimension+iterations] = new double[dimension];
    ASSERT(A[2*dimension+iterations]);
    
    /////////////////// Zeilendimension um 1 vergroessert ////////////////////
    
    // weiter gehts im eigentlichen Algorithmus

    // gradient wird die 'neue' Zeile der Matrix
    for (i=0; i<dimension; i++)
      A[2*dimension+iterations][i] = gradient[i]; 
      
    // Bilde das Skalarprodukt zwischen dem Gradienten der k-ten
    // Restriktion an der Stelle result mit dem Vektor result
    for (i=0; i<dimension; i++)
      sum += gradient[i]*result[i]; 
      
    // der 'neue' Platz in b wird mit
    // der Differenz aus dem zuvor berechnetem
    // Skalarprodukt und dem Wert der k-ten Restriktion
    // an der Stelle result, belegt
    b[2*dimension+iterations] = sum - restrictFunc[k](result); 
   
    iterations++;
  } // beginne von vorne

  // fertig

  for (i=0; i<2*dimension+iterations; i++)
    delete [] A[i];

  delete [] A;
  delete [] b;
  delete [] gradient;

  return returncode;
}
