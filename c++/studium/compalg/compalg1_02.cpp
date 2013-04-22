// *****************************************************************************
// ** THEMA 2: normierte Polynome
// *****************************************************************************
// ** Groetsch, Annika 
// *****************************************************************************
// **
// ** Ausgabe 
// ** Multiplikation mittels schneller Fouriertransformation
// ** Polynom*Matrix (schnelle Exponentiation)
// **
// ** Literatur: 
// ** - M. Clausen, U. Baum, Fast Fourier Transforms, BI Wissenschaftsverlag, 
// **   1993, 9-14
// ** - Buchmann, Einfuehrung in die Kryptographie, 2. Auflage, Springer, 2000, 
// **   37-39 (schnelle Exponentiation)
// **
// *****************************************************************************
// **
// ** void printpoly(polynom const& p);
// ** polynom& add (polynom const& p, polynom const& q, polynom& ret);
// ** polynom& sub (polynom const& p, polynom const& q, polynom& ret);
// ** polynom& mult(K       const& c, polynom const& v, polynom& ret); 
// ** polynom& mult(polynom const& p, polynom const& q, polynom& ret);
// ** matrix&  mult(polynom const& p, matrix const& A, matrix& ret); 
// **
// *****************************************************************************

#include"compalg1.h"

// Erlaubt die Verwendung der Funktion "setw(int n)" 
// (d.h. Tabulatorsprung um n Zeichen)
#include<iomanip>

void printpoly(polynom const& p) {
  if(p.empty()) { cout << "  0";  return; }
  int n=p.size();
  bool first=true;
  for(int i=n-1; i>=0; --i) {
    if(p[i]==0 && !first) continue;
    if(first) { first=false; } else { cout <<"+"; }
    cout << setw(3) << right << p[i];
    if(i>1)  cout << " x^" << i << " ";
    if(i==1) cout << " x   ";
  }
}

// ACHTUNG: ret muss auf richtige Laenge gesetzt werden!
polynom& add(polynom const& p, polynom const& q, polynom& ret){
  int i;
  int n=p.size();
  int m=q.size();
  if(n<m) {
    return add(q,p,ret);
  } else if(n>m) {
    ret.resize(n);
    for(i=n-1; i>=m; --i) 
      ret[i]=p[i];
  } else { // Grad(p)==Grad(q); bestimme Grad(ret)
    for(i=n-1; i>=0; --i) 
      if(p[i]+q[i]!=0) break; 
    ret.resize(i+1); 
  }
  // Fuehre für die restlichen i die Addition durch
  for(; i>=0; --i) 
    ret[i]=p[i]+q[i];
  return ret;
}

polynom& sub(polynom const& p, polynom const& q, polynom& ret) {
  if(&p==&ret) { polynom tmp=p; return sub(tmp,q,ret); }
  K tmp=-1;
  return add(p, mult(tmp,q,ret),ret); // ret=tmp*q; ret=p+ret;+
}

polynom& mult(K       const& c, polynom const& p, polynom& ret) {
  if(c==0 || p.empty()) { ret.clear(); return ret; }
  int n=p.size();
  ret.resize(n);
  for(int i=0; i<=n-1; i++) 
    ret[i]=p[i] * c;
  return ret;
}

// NICHT nach DFT, sondern naiv!
polynom& mult(polynom const& p, polynom const& q, polynom& ret) {
  if(p.empty() || q.empty()) { ret.clear(); return ret; }
  if(&p==&ret) { polynom tmp=p; return mult(tmp,q,ret); }
  if(&q==&ret) { polynom tmp=q; return mult(p,tmp,ret); }

  int n=p.size(), m=q.size();
  int i,j;
  K x;

  ret.resize(n+m-1);
  for(i=0; i<n+m-1; ++i) {
    x=0;
    for(j=max(0,i-m+1); j<=min(n-1,i); ++j) 
      x+=p[j]*q[i-j];
    ret[i]=x;
  }
  return ret;
}

// NAIVER Algorithmus
matrix& mult(polynom const& p, matrix const& A, matrix& ret) {
  int deg=p.size(); deg-=1;
  int n  =A.size();

  ret=nullmatrix(n,n,ret);
  if(deg==-1) return ret;   // Nullpolynom
  ret=p[0]*einsmatrix(n,ret);
  if(deg==0) return ret;    // konstantes Polynom
  matrix Ai=A;
  ret=ret+p[1]*Ai;
  for(int i=2;i<=deg;++i) {
    Ai=Ai*A;
    ret=ret+p[i]*Ai;
  }
  return ret;
}
