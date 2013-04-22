/* This is  -*- C++ -*-  */
#ifndef COMPALG1_H
#define COMPALG1_H

#include<iostream>
#include<vector>
#include<complex>

// alte gcc-Versionen koennen keine io-manipulatoren. Hier ist ein workaround
#if __GNUC__ == 2
#include"gnustreams.h"
#endif

using namespace std;

#include "rational.h"

// *****************************************************************************
// ** Klasse Fp<p> -- Primkoerper
// *****************************************************************************
// **
// ** Ein neuer Datentyp zum Rechnen in Primkoerpern. Umgang wie mit 'int'.
// ** (Der C++ Code zur Definition von Fp<> muss zur Teilnahme am Seminar
// ** nicht vollstaendig verstanden sein.)
// **
// ** zB.:
// **
// ** Fp<5> a,b, c;
// ** a=3;  
// ** b=-12; // i.e. b==3 
// ** c=a*b; // i.e. c==4
// ** 
// *****************************************************************************

// Euklid fuer Integers (bereits implementiert)
int euklid(int x1, int x2, int& a, int& b);

template<int P>
class Fp {
 public:
  static const int p=P;

  // ***************************
  // Datenstruktur:
  int i;  
  // ***************************
  // Konstruktoren, Destruktoren, Typumwandlungen
  Fp(int n=0)              { i=n%P; if(i<0) i+=P; }  // Konstruktor   int -> Fp
//operator int() const     { return i; }             // Typumwandlung Fp  -> int
  // ***************************
  // Methoden:
  Fp  operator- ()     const { return -i;  }
  Fp  operator+ (Fp b) const { return i+b.i; }
  Fp  operator- (Fp b) const { return i-b.i; }
  Fp  operator* (Fp b) const { return i*b.i; }
  Fp  operator/ (Fp b) const { int x,y; euklid(P,b.i,x,y); return i*y; }//y==1/b
  Fp& operator+=(Fp b)       { return *this=i+b.i; }
  Fp& operator-=(Fp b)       { return *this=i-b.i; }
  Fp& operator*=(Fp b)       { return *this=i*b.i; }
  Fp& operator/=(Fp b)       { int x,y; euklid(P,b.i,x,y); return *this=i*y; }
  bool operator==(Fp b) const { return i==b.i; }
  bool operator!=(Fp b) const { return i!=b.i; }
  // Keine ordinalen Vergleiche (<,<=,>,>=)!
  ostream& print(ostream& out) const { return out << i; }
  istream& scan (istream& in)        { int x; in>>x; *this=x; return in; }
};

template<int P>
ostream& operator<<(ostream& out, Fp<P> const& x) { return x.print(out); }
template<int P>
istream& operator>>(istream& in,  Fp<P>& x)       { return x.scan(in);   }


// *****************************************************************************
// ** typedef K - In welchem Koerper rechnen wir?
// *****************************************************************************

// typedef complex<double> K;  
// typedef Fp<5> K;         
typedef Rational K;


// *****************************************************************************
// ** Grundlegende Datentypen: Polynom, Vektor, Matrix, Basis (alles ueber K)
// *****************************************************************************
// **
// ** Fuer den Compiler sind sowohl polynom und vektor, als auch matrix und 
// ** basis das gleiche, d.h. er kann sie nicht unterscheiden. Die Namen sollen
// ** lediglich zur leichteren Lesbarkeit des Codes beitragen.
// **
// ** Aber Achtung:
// **
// ** Bei matrix und basis ist die Interpretation grundlegend unterschiedlich:
// ** Eine Matrix speichern wir als Vektor von Zeilen, eine Basis als Vektor
// ** von Vektoren, was man auch als Vektor von Spalten interpretieren koennte.
// ** Also bitte nicht verwechseln!
// **
// *****************************************************************************

class polynom :public vector<K> {// Polynom: p[n]*x^n+...+p[0] (deg(p)=p.size()-1)
public:
  polynom(int sz=0 ,K const& def=K() ):vector<K>(sz,def) {}
};

// typedef vector<K>      polynom;// Polynom: p[n]*x^n+...+p[0] (deg(p)=p.size()-1)
typedef vector<K>      vektor;
typedef vector<int>    permutation;
typedef vector<vektor> matrix; // Zeilenweise!
typedef vector<vektor> basis;  // Basis eines Untervektorraumes (Spaltenweise)


// *****************************************************************************
// ** Einige Grundlegende Funktionen: Einlesen, Initialisieren 
// ** (nicht vollstaendig; weitere Vorschlaege samt Implementation willkommen.)
// *****************************************************************************

matrix& nullmatrix(int n, int m, matrix& ret);
matrix& einsmatrix(int n, matrix& ret);
bool read(istream& in, matrix& ret, int n=-1, int m=-1);
bool read(istream& in, vektor& ret, int n=-1);

// Basis eines VR der Dimension k, als UVR des R^n
// nullbasis: vorerst alles mit 0'en gefuellt
// stdbasis:  Standardbasis (die ersten k Standardbasisvektoren des R^n)
basis& nullbasis(int n, int k, basis& ret);
basis& stdbasis (int n, int k, basis& ret);

// Erzeuge die Eins-Permutation
permutation& id(int n, permutation& ret);

// Erzeuge Polynom wie einen Vektor (z.B. mit assign); 
// trim() stellt sicher, dass keine führenden Nullen da sind.
polynom& trim(polynom& p);

// *****************************************************************************
// ** THEMA 1: Datenstruktur Vektor, Matrix
// *****************************************************************************
// ** Schyma, Sebastian 
// *****************************************************************************
// **
// ** Elementare Funktionen wie Ausgabe, Addition, Multiplikation
// ** Multiplikation nach Strassen fuer quadratische Matrizen
// ** 
// ** Literatur zur Matrixmultiplikation: 
// **   Aho, Hopcroft, Ullmann: The Design and Analysis of Computer Algorithms
// **   1974, 230-232
// **
// *****************************************************************************

// Zu implementieren:
void printvektor(vektor const& v);
void printmatrix(matrix const& A);
void printbasis (basis  const& A);
vektor& add (vektor const& v, vektor const& w, vektor& ret);
matrix& add (matrix const& A, matrix const& B, matrix& ret);
vektor& sub (vektor const& v, vektor const& w, vektor& ret);
matrix& sub (matrix const& A, matrix const& B, matrix& ret);
vektor& mult(K      const& c, vektor const& v, vektor& ret); 
matrix& mult(K      const& c, matrix const& A, matrix& ret); 
vektor& mult(matrix const& A, vektor const& v, vektor& ret);
matrix& mult(matrix const& A, matrix const& B, matrix& ret);


// *****************************************************************************
// Folgender C++-Code (nicht Teil des THEMAs) macht das Leben leichter...
// statt `add(a,b,ret)` geht dann auch `ret=a+b` (Ist aber u.U. langsamer!)
inline ostream& operator<<(ostream& out, vektor const& v)   
                                                 { printvektor(v); return out; }
inline ostream& operator<<(ostream& out, matrix const& A)   
                                                 { printmatrix(A); return out; }
/* inline ostream& operator<<(ostream& out, basis  const& A)    */
/*                                                  { printbasis (A); return out; } */
inline vektor operator+(vektor const& v, vektor const& w) 
                                           { vektor ret; return add(v,w, ret); }
inline matrix operator+(matrix const& A, matrix const& B) 
                                           { matrix ret; return add(A,B, ret); }
inline vektor operator-(vektor const& v, vektor const& w) 
                                           { vektor ret; return sub(v,w, ret); }
inline matrix operator-(matrix const& A, matrix const& B) 
                                           { matrix ret; return sub(A,B, ret); }
inline vektor operator*(K      const& c, vektor const& v) 
                                          { vektor ret; return mult(c,v, ret); }
inline matrix operator*(K      const& c, matrix const& A) 
                                          { matrix ret; return mult(c,A, ret); }
inline vektor operator*(matrix const& A, vektor const& v)
                                          { vektor ret; return mult(A,v, ret); }
inline matrix operator*(matrix const& A, matrix const& B)
                                          { matrix ret; return mult(A,B, ret); }

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

void printpoly(polynom const& p);
polynom& add (polynom const& p, polynom const& q, polynom& ret);
polynom& sub (polynom const& p, polynom const& q, polynom& ret);
polynom& mult(K       const& c, polynom const& v, polynom& ret); 
polynom& mult(polynom const& p, polynom const& q, polynom& ret);
matrix&  mult(polynom const& p, matrix const& A, matrix& ret); 

// *****************************************************************************
// Wieder zur Vereinfachung des Programmierens...

inline int deg(polynom const& p)                   { return ((int)p.size())-1; }

inline ostream& operator<<(ostream& out, polynom const& p)   
                                                  { printpoly(p); return out;  }
inline polynom operator+(polynom const& v, polynom const& w) 
                                          { polynom ret; return add(v,w, ret); }
inline polynom operator-(polynom const& v, polynom const& w) 
                                          { polynom ret; return sub(v,w, ret); }
inline polynom operator*(K const& c, polynom const& p)
                                         { polynom ret; return mult(c,p, ret); }
inline polynom operator*(polynom const& p, polynom const& q)
                                         { polynom ret; return mult(p,q, ret); }
inline matrix  operator*(polynom const& p, matrix const& q)
                                         { matrix ret;  return mult(p,q, ret); }

// *****************************************************************************
// ** THEMA 3: Algorithmen zu Polynome
// *****************************************************************************
// ** Loeb, Sven
// *****************************************************************************
// **
// ** Division mit Rest, Euklid, Algorithmus R
// **
// ** Literatur, z.B.: 
// ** - Vorlesungsskript Lineare Algebra II
// ** - Buchmann, Einfuehrung in die Kryptographie, 2. Auflage, Springer, 2000, 
// **   10-18 (Euklid),  47-49(Div. m. Rest)
// ** - H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag, 
// **   1993, 217-219 (Algorithmus r)
// **
// *****************************************************************************

polynom& div(polynom const& a, polynom const& b, polynom& q, polynom& r);
polynom& ggT(polynom const& p, polynom const& q, polynom& ret);
polynom& euklid(polynom const& p, polynom const& q, 
		polynom& ggT, polynom& a, polynom& b);
polynom& algo_r(polynom const& p, polynom const& q, polynom& r);

// *****************************************************************************
// Wieder zur Vereinfachung des Programmierens...

inline polynom operator/(polynom const& p, polynom const& q)
                                       { polynom d,r; div(p,q, d,r); return d; }
inline polynom operator%(polynom const& p, polynom const& q)
                                       { polynom d,r; div(p,q, d,r); return r; }
inline polynom ggT(polynom const& p, polynom const& q) 
                                            { polynom g; ggT(p,q,g); return g; }


// *****************************************************************************
// ** THEMA 4+5: Gauss-Algorithmus nach Lueneburg
// **              Determinante, Inverses einer Matrix
// *****************************************************************************
// ** Poellmann, Katja
// ** Valentin, Bianca
// *****************************************************************************
// **
// ** Literatur: 
// ** H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag, 
// ** 1993, 178-192
// **
// ** Iterativer Algorithmus, um lin. unabh. von r Vektoren im K^n zu testen. 
// ** (wird so benoetigt in Algorithmus Minpoly)
// **
// ** Eingabe: 
// ** - A:   r lin. unabh. Vektoren im K^n, bereits in ob. Dreiecksgestalt
// ** - P,M: Permutation und Transformation (eine unt. nxn-Dreiecksmatrix),
// **        fuehren zurueck zu urspruenglichen Vektoren P^-1 * M * A[i]
// ** - v:   Ein neuer Vektor, soll zu A hinzugefuegt werden
// ** Ausgabe: 
// ** - Return Wert: Ist v lin. unabh. von den A[i]?
// ** Falls ja:
// ** - A:   Erhaelt einen neuen Vektor (ein modifiziertes v)
// ** - P,M: Wurden entsprechend angepasst.
// ** Falls nein:
// ** - w:   v als Linearkombination der A[i]
// **
// *****************************************************************************


bool gauss(basis& A, permutation& P, matrix& M, vektor const& v, vector<K>& w);

// Sinnvolle Unterfunktionen: z.B.
//
// Vertauschung der Koordinaten:
//   void mult_basis(permutation const& P, basis const& A, basis& ret); 
//
// Transformation der Koordinaten:
//   void mult_basis(matrix      const& M, basis const& A, basis& ret); 
//
// Inverse einer unt. Dreiecksmatrix M:
//   invert_dreiecksmatrix(matrix const& A, matrix& ret);  


// Anwendung: Determinante, Inverses einer Matrix
K       det(matrix const& A);
matrix& inv(matrix const& A, matrix &ret);


// Die Information, die von Gauss zu gauss weitergegeben werden muss, 
// buendeln wir.
struct gaussinfo {
  basis A;
  permutation P; // Permutation
  matrix M;      // unt. Dreiecksmatrix der Transformationen
};

// initialisiere für gauss:
inline gaussinfo& init(int n, gaussinfo& ret) 
                { ret.A.clear(); id(n,ret.P); einsmatrix(n,ret.M); return ret; }

inline bool gauss(gaussinfo &B, vektor const& v, vector<K>& w) 
                                              { return gauss(B.A,B.P,B.M,v,w); }



// *****************************************************************************
// ** THEMA 6: Chinesischer Restsatz
// **            Determinante in Z^nxn
// *****************************************************************************
// ** Kreisel, Tobias
// *****************************************************************************
// **
// ** Literatur: 
// ** J. von zur Gathen, J. Gerhard, Modern Computer Algebra, Cambridge, 1999, 
// ** 96-105
// **
// ** Berechnung einer ganzzahligen Determinante mittels chinesischen Restsatz
// **
// *****************************************************************************

int det(vector<vector<int> > const& A);

// *****************************************************************************
// ** THEMA 7: Ordnungspolynom, Minimalpolynom 
// *****************************************************************************
// ** Oehrlein, Caroline
// *****************************************************************************
// **
// ** Literatur: 
// ** - Vorlesungsskript Lineare Algebra II 
// ** - H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag,
// **   1993, 223-239
// **
// ** Wir rechnen hier allgemein im Faktorraum V/U, U<=V<=\K^n.
// ** V wird durch eine Basis angegeben.
// ** U wird (falls noetig) durch bereits in ob. dreiecksform gebrachte
// **   Basis angegeben (mit allem info)
// ** Der Ausgabevektor f sind die Koeffizienten, sodass 
// **         o*v = f[0]*u[0] + ... + f[k]*u[k] 
// ** (d.h. o*v liegt in U). Daraus werden im Algorithmus elteiler die Polynome 
// ** f_i gewonnen.
// **
// *****************************************************************************

// Berechne p(A)*v direkt 
vektor& mult(polynom const& p, matrix const& A, vektor const& v,
	     vektor& ret);  

polynom& ordpoly(matrix const& A, vektor const& v, gaussinfo const& U,
		 polynom& o, vector<K>& f);

// v ist der Vektor mit Ordnungspolynom gleich Minimalpolynom m
polynom& minpoly(matrix const& A, basis const& V, gaussinfo const& U, 
		 polynom& m, vektor& v, vector<K>& f); 

// *****************************************************************************
// Wieder zur Vereinfachung des Programmierens...

inline vektor mult(polynom const& p, matrix const& A, vektor const& v)
                                    { vektor ret; mult(p,A,v,ret); return ret; }


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

// B sind die Vektoren mit Elementarteilern als Ordnungspolynom
void elteiler(matrix const& A, basis const& V, 
	      vector<polynom>& elteiler, basis& B);  
matrix& rationale_nf(matrix const& A, matrix& NF, basis& B); 


// *****************************************************************************
// ** THEMA 9: Irreduzible Polynome 
// *****************************************************************************
// ** Neuendorf, Jan
// *****************************************************************************
// **
// ** Literatur: 
// ** J. von zur Gathen, J. Gerhard, Modern Computer Algebra, Cambridge, 1999, 
// ** 353-368
// **
// *****************************************************************************

vector<pair<polynom,int> >& irred(polynom const& p, vector<pair<polynom,int> > &ret);// Zerlegung in irreduzible komponenten (samt Vielfachheiten)

// *****************************************************************************
// ** THEMA 10: Jordansche NF
// *****************************************************************************
// ** Schwarz, Cornelius 
// *****************************************************************************
// **
// ** Literatur: 
// ** - Vorlesungsskript Lineare Algebra II
// ** - H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag, 
// **   1993, 255-262
// **
// *****************************************************************************

matrix& jordansche_nf(matrix const& A, matrix& NF, basis& B);


// *****************************************************************************
// ** THEMA 11: Langzahlarithmetik, Ersetze Koerper Fp<p> durch Q ?
// *****************************************************************************
// ** Vogel, Heiko
// *****************************************************************************
// **
// ** Implementiere Klassen
// ** class longint;  //  bel. grosse Integerzahlen samt +,-,*,/, Ausgabe
// ** class rational; //  Paar von longint-Zahlen (Zaehler und Nenner)
// **
// *****************************************************************************


#endif
