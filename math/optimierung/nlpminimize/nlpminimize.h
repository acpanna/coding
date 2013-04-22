#ifndef _NLPMINIMIZE_H_
#define _NLPMINIMIZE_H_

#include "simplex.h"
#include "armijo.h"

// Rueckgabe: Falls Fehler auftreten bzw. maximale Iterationszahl erreicht --> -1
//            sonst --> benoetigte Anzahl an Iterationen
int nlpminimize(const int &dimX, 
		double (* const func)(const double * const x),
		void (* const funcGradient)(const double * const x, 
			double * const y),
		const int &restrictions,
		double (* const restrictFunc[]) (const double * const x),
		void (* const restrictFuncGradient[]) (const double * const x, 
			double * const y),
		const int &zeilen,
		const double ** const A, const double * const b, 
		double * const x0, const double &delta, const double &epsilon);

#endif
