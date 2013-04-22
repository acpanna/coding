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

#include "compalg1.h"
#include <algorithm> //fuer swap Funktion
#include <cfloat>
#include <cstdlib>
//Eigenwerte inklusive Vielfachheit in Minpoly
typedef pair<K,int> primaer;
static vector<primaer> & eigenwerte(matrix const & A, vector<primaer> & eigen)
{
 primaer prim;
 vector<K> f;
 vektor v;
 basis b;
 gaussinfo ginfo;
 size_t dim=A.size();
 
 // erstelle kanonische Basis von V
 stdbasis(dim,dim, b);
 // initialiere die Informationen fuer Gauss
 init(dim, ginfo);
 //berechne das Minimalpolynom
 polynom min;
 minpoly(A, b, ginfo, min, v,f);
 //faktorisiere es
 vector<pair<polynom, int> > p_vec;
 irred(min,p_vec);
 
 for (size_t i=0; i < p_vec.size(); i++)
 {
  if (deg(p_vec[i].first) > 1) //first = Polynom
  {
   cerr<<"Minimalpolynom zerfaellt nicht in Linearfaktoren! Jordansche Normalform nicht moeglich"<<endl;
   exit(1);
  }
  K eigenwert = - (p_vec[i].first)[0]/p_vec[i].first[1]; //Konstanter Term des Polynoms inklusive Normierung
  eigen.push_back(primaer(eigenwert, p_vec[i].second));
 }
 return eigen;
}

//fuer COMPLEX oder double
/*
static bool inline isNull(const K & wert)
{
 return (abs(wert) < DBL_EPSILON);
}
*/

ostream & operator<<(ostream & out, const permutation & perm)
{
 size_t perm_len=perm.size();
 out <<"(";
 for (int i=0; i< perm_len-1;i++)
  out <<perm[i]<<",";
 out <<perm[perm_len-1]<<")";
 return out;
}
// Fuer F<p> 
static bool inline isNull(const K & wert)
{
 return (wert==0);
}

static basis & primaerbasis(const matrix & n, primaer const & eigenwert, basis & b)
{
 int grad=eigenwert.second;
 // m:=m-\lambda_i
 /* verlegt in jordansche_nf
 for (int i=0; i < m.size(); i++)
  m[i][i]-=eigenwert.first;*/
 // m^grad
 matrix m=n;
 polynom potenzierer(grad+1, (K)0); 
 potenzierer[grad]=1;
 m=potenzierer*m;
 size_t dim=m.size(); //dim von V
 // bringe m auf Zeilenstufenform
 permutation s_perm;
 id(dim, s_perm);
 permutation z_perm;
 id(dim, z_perm);
 size_t nullbegin=dim;
 for (size_t j=0; j < nullbegin; j++) // durchlaufe die Zeilen
 {
  size_t l=j;
  if (isNull(m[z_perm[j]][s_perm[j]])) //Diagonalelement = 0
  {
   //versuche eine Zeile mit Nichnullelement in der j. Spalte zu finden   
   for (l=j+1; l < dim; l++)
   {
    if (!isNull(m[z_perm[l]][s_perm[j]]))
    {
     // Zeilenvertauschung
     swap(z_perm[l], z_perm[j]);
     break;
    }
   }
   if (l == dim) // die j.Spalte besteht ab der j.Zeilen nur noch aus 0
   {
    //versuche Spalte mit Nichnullelement in der j. Zeile zu finden
    for (l=j+1; l < dim; l++)
    {
     if (! isNull(m[z_perm[j]][s_perm[l]]))
     {
      // Spaltenvertauschung
      swap(s_perm[j],s_perm[l]);
      break;
     }
    }
   }
   if (l==dim) // Weder passende Zeile noch Spalte => Nullzeile
   {
    swap(z_perm[j],z_perm[nullbegin-1]);
    nullbegin--;
    j--; //noch zu testen ob, nullbegin-1 tatsaechlich != 0
    continue;
   }
  }// Ende Diagonalelement = 0
  //NichtNullElement gefunden
   for (size_t i=j+1; i < dim; i++)
   {
    K mult=m[z_perm[i]][s_perm[j]]/m[z_perm[j]][s_perm[j]];
    for (size_t k=j; k < dim; k++)
     m[z_perm[i]][s_perm[k]]-=mult*m[z_perm[j]][s_perm[k]];
   }
 } // Ende Zeilendurchlauf
 // Loese das gestaffelte System
 vektor nullvektor(dim, (K)0);
 for (int l=(int) dim-1; l >= (int)nullbegin; l--) // durchlaufe alle Nullzeilen
 {	  
  vektor v=nullvektor;  
  v[s_perm[l]]=1;
  // loese mit v das gestaffelte System
  for (int j = (int)nullbegin-1; j>=0; j--)
  {	   
   K sum=(K)0;
   for (size_t i=dim-1; i>j; i--)
    sum -=v[s_perm[i]]*m[z_perm[j]][s_perm[i]];
   v[s_perm[j]]=sum/m[z_perm[j]][s_perm[j]];
  }
  b.push_back(v);
 }
 return b;
}
matrix & jordansche_nf(matrix const & A, matrix & NF, basis& B)
{
 size_t dim=A.size();//Dimension des Vektorraumes
 if (&A==&NF){matrix m=A; return jordansche_nf(m, NF, B);}
 matrix m = A;
 basis prim_b; //Basis der aktuellen Primaerkomponente
 vector<polynom> pol_vec;
 basis el_b;
 B.clear();
 // Vorarbeit
 vector<primaer> eigen;
 eigenwerte(m,eigen);
 // NF zur nxn Nullmatrix machen
 nullmatrix(dim,dim,NF);
 
 size_t index=0; //Begin des naechsten Jordanblocks
 // Iteration
 for(size_t i=0; i < eigen.size(); i++)
 {
  for(size_t j=0; j < m.size(); m[j][j] -= eigen[i].first , j++); //m-\lambda
  prim_b.clear();//loeschen einer evtl. alten Basis
  primaerbasis(m,eigen[i],prim_b);
  //evtl. alte Basis + Elteiler loeschen
  pol_vec.clear();
  el_b.clear();
  elteiler(A, prim_b, pol_vec, el_b);
  // Jordanmatrix
  size_t s=pol_vec.size();
  for (size_t k=0; k < s; k++) // durchlaufe alle Jordanbloecke
  {
   for (int l=1; l < deg(pol_vec[k]); l++) // durchlaufe den Jordanblock
   {
    NF[index][index]=eigen[i].first;
    NF[index+1][index]=(K) 1;
    index++;
   }
   NF[index][index]=eigen[i].first;
   index++;
  }  
  // Jordanbasis
  for (size_t k=0; k < s; k++) // durchlaufe die Elementarteiler
  {
   vektor v=el_b[k];
   B.push_back(v);
   for (int l=1; l < deg(pol_vec[k]); l++)
   {
    v=m*v;
    B.push_back(v);
   } 
  }
  for (size_t j=0; j < m.size(); m[j][j] += eigen[i].first, j++); //m+\lambda n Additionen an Stelle von n^2 Kopien
 }
 return NF;
}
