#ifndef _GRADIENT_VERFAHREN_H_
#define _GRADIENT_VERFAHREN_H_

#include "armijo.h"

// Rueckgabe: Falls maximale Iterationszahl erreicht --> -1
//            sonst --> benoetigte Anzahl an Iterationen
int gradient_verfahren(const int &dimX, 
		double (* const func)(const double * const x),
		void (* const funcGradient)(const double * const x, 
			double * const y),
		double * const x0);

#endif
