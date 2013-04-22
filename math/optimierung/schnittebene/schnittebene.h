#ifndef _SCHNITTEBENE_H_
#define _SCHNITTEBENE_H_

int schnittebenenverfahren(double * const x,
       const int &zeilen, const int &spalten, const double ** const A, 
       const double * const b, const double * const l, const double * const u, 
       double (* const f) (const double * const x), 
       void (* const subgrad_f) (const double * const x, double * const y));

#endif
