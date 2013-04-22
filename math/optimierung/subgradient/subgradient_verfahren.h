#ifndef _SUBGRADIENT_VERFAHREN_H_
#define _SUBGRADIENT_VERFAHREN_H_

// Rueckgabe: Falls maximale Iterationszahl erreicht --> -1
//            sonst --> benoetigte Anzahl an Iterationen
int subgradient_verfahren(const int &dimX, 
		double (* const func)(const double * const x),
		void (* const funcSubgradient)(const double * const x, 
			double * const y),
		double * const x0, int schrittstrategie, double optimum);

#endif
