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

#include<iomanip>
#include "compalg1.h"

using namespace std;

static void    invert_dreiecksmatrix(matrix const& A, matrix& ret);
static void    permut_vektor(permutation const& P, vektor const& v, vektor& vret);
static void    transf_vektor(matrix const& M, vektor const& v, vektor& vret);
static bool    test_abh(vektor const& v, int anz_basis, int & komp);
static void    gauss_2(basis& A, permutation& P, matrix& M, vektor const& v, vektor & sigmarho_v, 
                       int komp);
static int     signum(permutation pi);
static void    invert_ob_dreiecksmatrix(basis const& Astrich,matrix & inv_Astrich);
static void    convert(basis const& A, matrix & M);
static void    permut_sp(permutation const& P, matrix const& M, matrix & erg);
static void    pi_v(vektor & v, int i, int j);


//*************************************************************************
// Invertiere eine untere Dreiecksmatrix M mit Einsen auf der Diagonale 
// Ergebnis ret = M^-1
//*************************************************************************
static void invert_dreiecksmatrix(matrix const& M, matrix& ret) { 
   int dim = (int) M.size();
   int sp = 0;
   int ze;
   
   einsmatrix(dim, ret);
   
   for(int i = 0; i < dim - 1; i++) {
      ze = i + 1;
      for(int j = 0; j <= sp; j++) {
      	 for(int k = ze; k < dim; k++) {
      	    ret[k][j] = ret[k][j] -  M[k][i] * ret[i][j];
      	 }   
      }
      sp++;
   }
}


//************************************************************************
// Permutiere die Komponenten des Vektors v unter der Permutation P
//************************************************************************
static void permut_vektor(permutation const& P, vektor const& v, vektor& vret) {
   int dim = (int) P.size();
   vret.assign(dim, 0);
   
   for(int i = 0; i < dim; i++) {
      vret[P[i]] = v[i];
   }
}	


//************************************************************************
// Transformiere die Komponenten des Vektors v unter M 
// (M ist untere Dreiecksmatrix mit Einsen auf der Diagonale)
//************************************************************************	
static void transf_vektor(matrix const& M, vektor const& v, vektor& vret) {
   int dim = (int) M.size();
   vret.assign(dim, 0);
   
   for(int i = 0; i < dim; i++) {
      for(int j = i; j < dim; j++) {
         vret[j] = vret[j] + v[i] * M[j][i];
      }
   }   	
}


//****************************************************************
// Test auf Abhaengigkeit des Vektors v von einer Basis
//****************************************************************
static bool test_abh(vektor const& v, int anz_basis, int & komp) {
   int dim = (int) v.size();
   bool linabh = true;
   for(int i = anz_basis; i < dim; i++) {
      if(v[i] != 0) {
      	 if(linabh == true) {
      	    komp = i;    // komp = erste Komponente des Vektors v ab
      	                 // anz_basis, die ungleich 0 ist
      	 }
      	 linabh = false;
      }
   }
   if(linabh == true) {
      komp = dim; // komp = dim kann regulaer nicht auftreten
   }
   return linabh;
}


//****************************************************************
// Gauss-Algorithmus nach Lueneburg
// gibt true zurueck, wenn v unabhaengig von den Basisvektoren
//****************************************************************
bool gauss(basis& A, permutation& P, matrix& M, vektor const& v, vector<K> & w) {
   bool abhaengig;
   int dimension = (int) v.size();
   int anzahl_basis = (int) A.size();
   int komponente;
   vektor rho_v, sigmarho_v, l;
   matrix inv_M;
   
   invert_dreiecksmatrix(M, inv_M);              // Berechne sigma^-1(rho(v))
   permut_vektor(P, v, rho_v);
   transf_vektor(inv_M, rho_v, sigmarho_v);
   
   abhaengig = test_abh(sigmarho_v, anzahl_basis, komponente);
                                                // Test auf Abhaengigkeit von v

   if(abhaengig == true) {
      w.assign(anzahl_basis, 0);                   // Erzeuge neuen Vektor w, in dem
                                                   // die Koeffizienten der Summe
                                                   // v = Sum w_i abgespeichert werden
      l.assign(dimension, 0);
      l = sigmarho_v;
      
      for(int i = anzahl_basis - 1; i >= 0; i--) {  // Berechne die Koeffizienten
         w[i] = ((K) 1 / A[i][i]) * l[i];            
         for(int j = 0; j < dimension; j++) {       // "Rueckwaertseinsetzen"
            l[j] = l[j] - w[i] * A[i][j];
         }
      }
      // 1 muss auf (K) gecastet werden, sonst Typumwandlungskonflikt!
   }
   else {
      gauss_2(A, P, M, v, sigmarho_v, komponente);
      // wenn v unabhaengig, stelle die Ausgangssituation wieder her
   }
   
   return !abhaengig;	
}


//*******************************************************************************
// Unterfunktion des Gauss-Algorithmus nach Lueneburg:
// wird aufgerufen, falls v unabhaengig von den anderen Vektoren ist
// berechnet neues P, M und neuen angepassten Vektor v'
//*******************************************************************************
static void gauss_2(basis& A, permutation& P, matrix& M, vektor const& v, vektor & sigmarho_v, 
             int komp) {
   int dim = (int) M.size();
   int anz_basis = (int) A.size();
   bool test = false;
   bool test2 = false;
   int i = 0;
   K help;
   vektor rho_v;
   matrix inv_M;
   
   if(komp != anz_basis) { 
      do {  // rho auf rho' = pi*rho setzen
            // dabei ist pi die Permutation, die komp und anz_basis vertauscht
         if(P[i] == komp || P[i] == anz_basis) {
            if(P[i] == komp) {      // komp in P gefunden
               P[i] = anz_basis;    // setze diese Komponente auf anz_basis
               i++; 
               test = true;
            }
            else {                    // anz_basis in P gefunden
               P[i] = komp;           // setze diese Komponente auf komp
               i++;
               test2 = true;
            }
         }
         else {
            i++;
         }
         
      } while(i < dim && (test == false || test2 == false));
             // entweder beide Komponenten gefunden oder Ende der 
             // Permutation erreicht
      
      for(int j = 0; j < anz_basis; j++) { // sigma auf sigma'' = pi*sigma*pi setzen
         help = M[anz_basis][j];           // d.h. Zeilen anz_basis und komp tauschen
         M[anz_basis][j] = M[komp][j];     //  - nur bis zur Spalte anz_basis
         M[komp][j] = help;
      }	
      
      pi_v(sigmarho_v, komp, anz_basis);      // falls Zeilen vertauscht werden mussten
                                              // (1. relevante Komponente ungleich 0)
                                              // berechne sigma^-1(rho(v)) neu
                                              // d.h. vertausche zwei Komponenten
   }
   
   for(int j = anz_basis + 1; j < dim; j++) {
      M[j][anz_basis] = sigmarho_v[j] / sigmarho_v[anz_basis];
              // Berechne die neuen Komponenten von M
              // (in Spalte anz_basis + 1)
   }
   
   for(int k = anz_basis + 1; k < dim; k++) {    // Berechne modifizierten Vektor v
      sigmarho_v[k] = 0;                         // fuer die Basis
   }                                             // d.h. setze v[anz_basis+1] bis v[n] = 0
   

   A.push_back(sigmarho_v);    // Haenge modifizierten Vektor v an Basis an
}


//************************************************************************************
// Bestimme Determinante einer Matrix mit dem oben implementierten Gauss-Algorithmus
//************************************************************************************
K det(matrix const& A) {
   K det;
   K detAstrich = 1;
   K detrho;
   int dim = (int) A.size();
   int j = 0;
   bool linunabh;
   basis Astrich;
   permutation rho;
   matrix sigma;
   vektor v, w;
   
   id(dim, rho);          // Ausgangssituation fuer 0
   v.assign(dim, 0);      // Vektoren in der Basis herstellen
   einsmatrix(dim, sigma);
   
   do {
      for(int i = 0; i < dim; i++) {
         v[i] = A[i][j];          // Setze v im i-ten Schritt auf die i-te Spalte von A
      }
      
      linunabh = gauss(Astrich, rho, sigma, v, w);   
                                          // v von vorherigen (modifizierten) Spalten 
                                          // abhaengig?
                                          // JA: w wird besetzt ==> Abbruch der while-Schleife
                                          // NEIN: v wird modifiziert, und an Basis angehaengt
      
      j++;
   } while(j < dim && linunabh);
   
   if(!linunabh) {       // falls die Spaltenvektoren von A abhaengig sind
      det = 0;           // ==> det = 0
      
   }
   else {
      for(int i = 0; i < dim; i++) {
         detAstrich *= Astrich[i][i];  // det(A') = Spur(A'), da A' obere Dreiecksmatrix
      }
   
      detrho = signum(rho);
   
      det = detAstrich * detrho; // det(A) = det(sigma) * det(A') * det(rho)
                                 //        = 1 * det(A') * sgn(rho)
                                 // (sigma = obere Dreiecksmatrix mit Einsen auf der 
                                 //  Diagonale; rho = Permutation)
   }
   
   return det;
}


//**************************************************************************
// Berechnet sgn(pi) durch Zaehlen der vorgenommenen Zeilenvertauschungen
//**************************************************************************
static int signum(permutation pi) {
   int dim = (int) pi.size();
   bool test = false;
   int merk = 0;
   int j, sign;
   
   for(int i = 0; i < dim; i++) { // durchlaufe Permutation
      j = i;
      
      if(pi[i] != i) {        // falls pi(i) != i ==> Zeilenvertauschung noetig
      	 do {
      	    if(pi[j] == i) {   // suche i in der Permutation
      	       pi[j] = pi[i];            // falls bei j gefunden, setze pi(j) auf pi(i)
      	       test = true;
      	    }
      	    j++;
      	 } while(j < dim && test == false);
      	 
         pi[i] = i;                      // ... und pi(i) auf i
         merk++;
      }
      
      test = false;
   }
   
   if(merk % 2 == 0) {  // sgn = -1^(Anzahl Vertauschungen)
      sign = 1;         // falls also Anzahl Vertauschungen gerade ==> sgn = 1
   }
   else {
      sign = -1;        // falls Anzahl Vertauschungen ungerade ==> sgn = -1
   }
   	   
   return sign;
}


//************************************************************************************
// Bestimme Inverse einer Matrix mit dem oben implementierten Gauss-Algorithmus
//************************************************************************************
matrix& inv(matrix const& A, matrix &ret) {
   int dim = (int) A.size();
   int j = 0;
   bool linunabh;
   basis Astrich;
   permutation rho;
   matrix sigma, inv_sigma, inv_Astrich, mul;
   vektor v, w;
   
   id(dim, rho);                    // Ausgangssituation fuer 0
   v.assign(dim, 0);                // Vektoren in der Basis herstellen
   einsmatrix(dim, sigma);
   
   do {
      for(int i = 0; i < dim; i++) {
         v[i] = A[i][j];        // Setze v im i-ten Schritt auf die i-te Spalte von A
      }
      
      linunabh = gauss(Astrich, rho, sigma, v, w);   
                                          // v von vorherigen (modifizierten) Spalten 
                                          // abhaengig?
                                          // JA: w wird erzeugt ==> Abbruch der while-Schleife
                                          // NEIN: v wird modifiziert, und an Basis angehaengt
      j++;
      
   } while(j < dim && linunabh);
   
   if(!linunabh) { // falls die Spaltenvektoren von A abhaengig sind
      cout << "M nicht invertierbar!" << endl;
      
   }
   else {
      invert_dreiecksmatrix(sigma, inv_sigma);
      invert_ob_dreiecksmatrix(Astrich, inv_Astrich);
      permut_sp(rho, mult(inv_Astrich, inv_sigma, mul), ret);
      // A^-1 = (pi^-1 * sigma * A')^-1 = A'^-1 * sigma^-1 * pi
   }  
   
   return ret;
}


//***********************************************************************************
// Invertiere eine obere Dreiecksmatrix mit beliebigen Elementen auf der Diagonale
// diese wird als Basis uebergeben
// Ergebnis inv_Astrich ist Matrix = M^-1
//***********************************************************************************
static void invert_ob_dreiecksmatrix(basis const& Astrich, matrix & inv_Astrich) {
   matrix matA;
   int dim = (int) Astrich[0].size();
   int ze;
   int sp = dim - 1;
   
   convert(Astrich, matA); // konvertiere Basis in "Hilfsmatrix"
   
   nullmatrix(dim, dim, inv_Astrich);
   
   for(int i = 0; i < dim; i++) {               // Teile alle Zeilen durch die
      inv_Astrich[i][i] = (K) 1 / matA[i][i];   // Diagonalelemente
      for(int j = i + 1; j < dim; j++) {
         matA[i][j] = matA[i][j] / matA[i][i];
      }
      matA[i][i] = 1;
   }
   
   for(int i = dim - 1; i > 0; i--) {
      ze = i - 1;
      for(int j = dim - 1; j >= sp; j--) {       // invertieren einer Dreiecksmatrix 
         for(int k = ze; k >= 0; k--) {          // mit Einsen auf der Diagonale
            inv_Astrich[k][j] = inv_Astrich[k][j] - matA[k][i] * inv_Astrich[i][j];
         }
      }
      sp--;
   }
   
}

//***************************************************************
// Erzeuge aus einer Basis A eine entsprechende Matrix M
// d.h. Vertausche Zeilen und Spalten
//***************************************************************
static void convert(basis const& A, matrix & M) {
   int dim = (int) A.size();
   
   nullmatrix(dim, dim, M);
   
   for(int i = 0; i < dim; i++) {
      for(int j = 0; j < dim; j++) {
         M[i][j] = A[j][i];
      }
   }
}


//*******************************************************
// Vertausche die Spalten von M mit Permutation P
//*******************************************************
static void permut_sp(permutation const& P, matrix const& M, matrix & erg) {
   int dim = (int) P.size();
   nullmatrix(dim, dim, erg);
   
   for(int sp = 0; sp < dim; sp++) {
      for(int ze = 0; ze < dim; ze++) {
         erg[ze][sp] = M[ze][P[sp]]; // Vertausche Zeile ze
      }
   }
}


//**********************************************************
// Vertausche die Elemente von v mit der Transposition
// pi = (i j)
//**********************************************************
static void pi_v(vektor & v, int i, int j) {
   K help;
   help = v[i];
   v[i] = v[j];
   v[j] = help;
}
