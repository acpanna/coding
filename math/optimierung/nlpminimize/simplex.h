#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_

// Wird vor den Aufruf des eigentlichen Simplex-Algorithmus geschaltet, 
// um Ungleichungen der Form A*x<=b in Gleichungen zu verwandeln 
// (durch Einfuehrung von Schlupfvariablen). 
// Ausserdem wird hierdurch zusaetzlich erreicht, 
// dass rang A = #Zeilen von A
bool simplex(const int &zeilen,
		const int &spalten,
		const double ** const A,
		const double * const b,
		const double * const cost,
		double * const ergebnis);

// Eigentlicher Simplex-Algorithmus, der Probleme der folgenden Form loest: 
//       Minimiere c'x unter den Nebenbedingungen A*x=b, x>=0 
//                 und rang A = #Zeilen von A
bool simplex_with_equations(const int &zeilen,
		const int &spalten,
		double ** const A,
		double * const b,
		const double * const cost,
		double * const ergebnis);

bool phase2(const int &m,
		const int &n,
		double ** const A,
		const double * const c,
		double * const p1);

int gauss(const int &zeilen,
		double ** const matrix,
		double * const vektor,
		int * const zeilentausch);

bool solveLR(const int &zeilen,
		const double ** const matrix,
		double * const vektor,
		const int * const zeilentausch);

#endif
