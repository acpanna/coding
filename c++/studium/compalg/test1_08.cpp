#include "compalg1.h"
#include <fstream>

int elteiler(int argc, char **argv) {
  if(argc!=2) {
    cout << "Syntax: test1_08 1 <matrix>"<< endl;
    return 1;
  }
  
  matrix A;
  vector<polynom> polys;
  basis E,B;
  ifstream file1(argv[1]);
  if(!read(file1, A)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }
  int n=A.size(); 
  if(n>0 && n!=A[0].size()) {
    cout << "Fehler: Matrix muss quadratisch sein."<< endl;
    return 1;
  }
  stdbasis(n,n,E);
  elteiler(A,E,polys,B);
  cout << "A:\n";  printmatrix(A);
  for(int i=0; i<polys.size();++i) {
    printpoly(polys[i]); cout <<endl;
  }
  return 0;
}

int rnf(int argc, char **argv) {
  if(argc!=2) {
    cout << "Syntax: test1_08 2 <matrix>"<< endl;
    return 1;
  }
  
  matrix A, NF;
  basis B;
  ifstream file1(argv[1]);
  if(!read(file1, A)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }

  rationale_nf(A,NF,B);
  cout << "A:\n";  printmatrix(A);
  cout << "Rationale NF:\n";  printmatrix(NF);
  cout << "Basis:\n";  printbasis(B);
  return 0;
}



int main(int argc, char **argv) {
  if(argc>=2) { 
    switch(atoi(argv[1])) {
    case 1: return elteiler(argc-1, argv+1); 
    case 2: return rnf(argc-1, argv+1); 
    }
  }
  // Ein Fehler ist aufgetreten. Gebe Syntax aus:
  cout << "Syntax: test1_08 <n> " << endl;
  cout << "1  -  Ausgabe der Elementarteiler" << endl;
  cout << "2  -  Ausgabe der rationalen NF samt Basis" << endl;
  return 1; // Rueckgabewert !=0, d.h. Fehler
} 

