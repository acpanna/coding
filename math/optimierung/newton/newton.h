#ifndef _NEWTON_H_
#define _NEWTON_H_

// Newton-Verfahren zur Bestimmung der Nullstellen eines nicht-linearen
// Funktionsvektors F(x) = (f1(x), ..., fn(x)), wobei x = (x1, ..., xn).
// Voraussetzungen: F partiell diffbar, fi mind. 2-mal stetig partiell 
// diffbar in Umgebung einer Nullstelle x' von F und Jacobi F(x') ist 
// invertierbar
int newton(const int &dimX,
		double (*f[])(const double * const x),
		void (*grad_f[])(const double * const x, double * const y),
        	double * const x0);
#endif
