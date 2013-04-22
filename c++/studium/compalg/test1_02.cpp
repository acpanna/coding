#include "compalg1.h"
#include <fstream>

int polyprint(int argc, char **argv) {
  if(argc!=2) {
    cout << "Syntax: test1_01 1 <polynom>"<< endl;
    return 1;
  }
  
  polynom p;
  ifstream file1(argv[1]);
  if(!read(file1, p)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }

  printpoly(p); // Hier passiert alles wichtige!
  cout << endl;

  return 0;
}

int matrixmult(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_01 " << what << " <matrix1> <matrix2>"<< endl;
    return 1;
  }
  
  matrix m1, m2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, m1) ||  !read(file2,m2)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }

  printmatrix(m1*m2); // Hier passiert alles wichtige!

  return 0;
}

int polymatmult(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_01 " << what << " <polynom> <matrix2>"<< endl;
    return 1;
  }
  
  polynom p;
  matrix m;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p) ||  !read(file2,m)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }

  printmatrix(p*m); // Hier passiert alles wichtige!

  return 0;
}

int polypoly(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_01 " << what << " <polynom> <polynom>"<< endl;
    return 1;
  }
  
  polynom p1,p2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p1) ||  !read(file2,p2)) {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
  }

  switch (what) {
  case 2: printpoly(p1+p2); break; // Hier passiert alles wichtige!
  case 3: printpoly(p1-p2); break;
  case 4: printpoly(p1*p2); break;
  }
  cout << endl;
  return 0;
}



int main(int argc, char **argv) {
  if(argc>=2) { 
    switch(atoi(argv[1])) {
    case 1: return polyprint(argc-1, argv+1); 
    case 2: return polypoly(argc-1, argv+1,2); // +
    case 3: return polypoly(argc-1, argv+1,3); // -
    case 4: return polypoly(argc-1, argv+1,4); // *
    case 5: return matrixmult(argc-1, argv+1,5); 
    case 6: return polymatmult(argc-1, argv+1,6); 
    }
  }
  // Ein Fehler ist aufgetreten. Gebe Syntax aus:
  cout << "Syntax: test1_02 <n> " << endl;
  cout << "1  -  Ausgabe eines Polynoms" << endl;
  cout << "2  -  Polynom+Polynom" << endl;
  cout << "3  -  Polynom-Polynom" << endl;
  cout << "4  -  Polynom*Polynom" << endl;
  cout << "5  -  Matrix*Matrix" << endl;
  cout << "6  -  Polynom*Matrix" << endl;
  return 1; // Rueckgabewert !=0, d.h. Fehler
} 

