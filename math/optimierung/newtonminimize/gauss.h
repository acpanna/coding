#ifndef _GAUSS_H_
#define _GAUSS_H_

#define ASSERT(x)  if(x == NULL) \
{ cout << "Speicherreservierung fehlgeschlagen -- Programmabbruch" << endl; exit(1); }

int gauss(const int &zeilen,
		double ** const matrix,
		double * const vektor,
		int * const zeilentausch);

bool solveLR(const int &zeilen,
		const double ** const matrix,
		double * const vektor,
		const int * const zeilentausch);
#endif
