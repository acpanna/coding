#ifndef _ARMIJO_H_
#define _ARMIJO_H

double armijo(const int &dimX, 
		double (* const func)(const double * const x), 
		void (* const funcGradient)(const double * const x, 
			double * const y),
		const int &restrictions,
		double (* const restrictFunc[])(const double * const x),
		const int &zeilen, 
		const double ** const A, const double * const b,
		double * const x0, double * const d0, 
		const double &s, const double &beta, const double &sigma);

#endif
