#include "compalg1.h"
#include <fstream>

int polydiv(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_01 " << what << " <polynom> <polynom>"<< endl;
    return 1;
  }
  
  polynom p1,p2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p1) ||  !read(file2,p2))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }
  polynom q,r;
  div(p1,p2,q,r);
  
  cout<<"q = a/b =";printpoly(q);cout<<endl;
  cout<<"r = a%b =";printpoly(r);cout<<endl; 
  
  return 0;
}
int erw_euklid(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_03 " << what << " <polynom> <polynom>"<< endl;
    return 1;
  }
  
  polynom p1,p2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p1) ||  !read(file2,p2))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }
  polynom ggT,x,y;
  euklid(p1,p2,ggT,x,y);
  
  cout<<"ggT =";printpoly(ggT);cout<<endl;
  cout<<"x =";printpoly(x);cout<<endl;
  cout<<"y =";printpoly(y);cout<<endl;
  
  return 0;
}
int gegeTe(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_03 " << what << " <polynom> <polynom>"<< endl;
    return 1;
  }
  
  polynom p1,p2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p1) ||  !read(file2,p2))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }
  polynom ggt;
  ggT(p1,p2,ggt);
  
  cout<<"ggT =";printpoly(ggt);cout<<endl;
    
  return 0;
}
int algo_r(int argc, char **argv, int what) {
  if(argc!=3) {
    cout << "Syntax: test1_03 " << what << " <polynom> <polynom>"<< endl;
    return 1;
  }
  
  polynom p1,p2;
  ifstream file1(argv[1]);
  ifstream file2(argv[2]);
  if(!read(file1, p1) ||  !read(file2,p2))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }
  polynom r;
  algo_r(p1,p2,r);
  
  cout<<"r =";printpoly(r);cout<<endl;
    
  return 0;
}
int main(int argc, char **argv) {
  if(argc>=2) { 
    switch(atoi(argv[1])) {
    case 1: return polydiv(argc-1, argv+1,1); 
    case 2: return gegeTe(argc-1, argv+1,2); 
    case 3: return erw_euklid(argc-1, argv+1,3);
    case 4: return algo_r(argc-1, argv+1,4);
    }
  }
  // Ein Fehler ist aufgetreten. Gebe Syntax aus:
  cout << "Syntax: test1_02 <n> " << endl;
  cout << "1  -  Polynomdivision" << endl;
  cout << "2  -  Groeßter Gemeinsamer Teiler" << endl;
  cout << "3  -  Erweiterter Euklidischer Algorithmus" << endl;
  cout << "4  -  Algorithmus r" << endl << endl;
  return 1; // Rueckgabewert !=0, d.h. Fehler
} 

