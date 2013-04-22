#include "compalg1.h"

int euklid(int x1, int x2, int& a, int& b) {
  int a1,b1, a2,b2, p;
  a1=1; b1=0; 
  a2=0; b2=1;
  while(x2!=0) {  // _1<-_2; _2<- _1-p*_2;
    p=x1/x2;
    a1-=p*a2; swap(a1,a2);
    b1-=p*b2; swap(b1,b2);
    x1-=p*x2; swap(x1,x2);
  }
  a=a1; b=b1; return x1;
}

matrix& nullmatrix(int n, int m, matrix& ret) {
  ret.assign(n,vektor(m,0));
  return ret;
}
matrix& einsmatrix(int n, matrix& ret) {
  nullmatrix(n,n,ret);
  for(int i=0; i<n; ++i) ret[i][i]=1;
  return ret;
}

// Basis eines VR der Dimension k , UVR des R^n , vorerst mit 0'en gefuellt
basis& nullbasis(int n, int k, basis& ret) {
  ret.assign(k, vektor(n, 0)); return ret;
}

// Standardbasis des R^k, als UVR des R^n (die ersten k Standardbasisvektoren)
basis& stdbasis(int n, int k, basis& ret) {
  nullbasis(n,k,ret);
  for(int i=0; i<k; ++i) ret[i][i]=(K)1;
  return ret;
}

// Erzeuge die Eins-Permutation
permutation& id(int n, permutation& ret) {
  ret.assign(n,0);
  for(int i=0; i<n; i++) ret[i]=i;
  return ret;
}


// Polynome: Stelle sicher, dass keine führenden Nullen im Polynom sind
polynom& trim(polynom &p) {
  int i=p.size(); 
  for(i=p.size(); i>0; --i) if(p[i-1]!=0) break;
  p.resize(i);
  return p;
}

// Einlesen von Matrix A
bool read(istream& in, matrix& ret, int n,int m) {
  if(n==-1) in >> n;
  if(m==-1) in >> m;
  if(!in) return false;
  nullmatrix(n,m,ret);
  for(int i=0;i<n;++i) {
    for(int j=0;j<m;++j) {
      in >> ret[i][j];
    }
  }
  return(in.good());
}

bool read(istream& in, vektor& ret, int n) {
  if(n==-1) in >> n;
  if(!in) return false;
  ret.resize(n);
  for(int i=0;i<n;++i) {
    in >> ret[i];
  }
  return(in.good());
}

