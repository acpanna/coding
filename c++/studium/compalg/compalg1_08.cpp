// *****************************************************************************
// ** THEMA 8: Elementarteiler, rationale NF
// *****************************************************************************
// ** Oehrlein, Stefanie 
// *****************************************************************************
// **
// ** Literatur: 
// ** - Vorlesungsskript Lineare Algebra II
// ** - H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag, 
// **   1993, 240-254
// **
// *****************************************************************************
// **
// ** // B sind die Vektoren mit Elementarteilern als Ordnungspolynom
// ** void elteiler(matrix const& A, basis const& V, 
// **	            vector<polynom>& elteiler, basis& B);  
// ** matrix& rationale_nf(matrix const& A, matrix& NF, basis& B); 
// **
// *****************************************************************************

#include "compalg1.h"

// Eingabe:
//   A: nxn-Matrix, die darst. Matrix einer Abb. bzgl. geg. Basis
//   V: Basis (->Groesse nxn)
// Korrektheit der Dimensionen wird nicht geprüft!
//
// Ausgabe:
//   elteiler: Die Elementarteilerfolge
//   B:        Vektoren mit Elementarteilern als Ordnungspolynom
void elteiler(matrix const& A, basis const& V, 
              vector<polynom>& elteiler, basis& B){
  int n=A.size();
  polynom m,tmp;
  vektor v, dummy;
  basis     U;
  gaussinfo Ugauss;     init(n, Ugauss);
  vector<K> f;
  while(U.size()<V.size()){
    minpoly(A,V,Ugauss,m,v,f);
#ifdef DEBUG
    printvektor(v); cout << "\t\t";
    printpoly(m); cout << "\t\t";
    printvektor(f); cout << endl;
#endif
    // Berechne vektor u
    vektor u(n,0);
    for(int i=0,j=0; i<elteiler.size();j+=deg(elteiler[i++])) {
      // fi <- Polynom, mit m*v = Sum fi*elteiler[i] (Siehe Handout Algorithmus RNF)
      polynom fi;   // mache aus f[x]...f[y] ein Polynom -> 
      fi.assign(&f[j], &f[j+deg(elteiler[i])]);
      trim(fi);  // loesche führende nullen
      add(u, mult(fi/m,A,B[i],tmp), u);  // u+= (fi/m)(A)*v
    }
    elteiler.push_back(m);
    B.push_back(v-u);
    U.push_back(v);  gauss(Ugauss,v,dummy);
    for(int i=1;i<deg(m);++i) { mult(A,v,v); U.push_back(v); /* B.push_back(v); */    gauss(Ugauss,v,dummy); }
  }
}


// Eingabe: 
//   A   : nxn-Matrix
// Korrektheit der Dimensionen wird nicht geprüft!
//
// Ausgabe:
//   NF: nxn-Matrix, die rationale Normalform von A
//   B:  basis, bzgl der die lineare Abb f_A in RNF ist
matrix& rationale_nf(matrix const& A, matrix& NF, basis& B) {
  int n=A.size();
  basis V; stdbasis(n,n,V);   // Die Standardbasis des R^n
  vector<polynom> polys;
  basis B1;
  elteiler(A,V,polys,B1);
  nullmatrix(n,n,NF);
  B.clear();
  for(int i=0,j=0; i<polys.size();j+=deg(polys[i++])) {
    polynom const& m=polys[i];    // Keine Kopie, nur Referenz
    vektor       & v=B1[i];       // Wird verändert (danach nicht mehr gebraucht)
    int d=deg(m);
    NF[j][j+d-1]=-m[0];
    B.push_back(v);
    for(int k=1; k<d;++k) {
      NF[j+k][j+k-1]=1;
      NF[j+k][j+d-1]=-m[k];
      B.push_back(mult(A,v,v));
    }
  }
  return NF;
}



