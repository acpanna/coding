#ifndef _ARMIJO_H_
#define _ARMIJO_H

double armijo(const int &dimX, 
		double (* const func)(const double * const x), 
		double * const x0, double * const d0, 
		const double &s, const double &beta, const double &sigma);

#endif
