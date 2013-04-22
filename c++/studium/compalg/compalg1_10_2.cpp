#include "compalg1.h"
#include <algorithm>
static inline bool isNull(K k) // Test auf numerisch 0
{
 return (k==0);
}

static basis & steinitz(const basis & sk, basis & tk)
{
 /* steinitz:
    Beschreibung:
     diese Funktion eweitert eine linear unabhaengig Familie von Vektoren durch Hinzunahme von Basisvektoren aus einer gegebenen Basis zu einer solchen.

    Eingabe:
    basis sk, Basis des Raumes
    basis tk, linear unabhaenge Familie
    
    Ausgabe:
    basis tk, die mit Vektoren aus sk erweiterte Basis
 */
 	
 // konstruiere aus base und sk eine Matrix
 // z_dim: die Anzahl der Zeilen
 // s_dim: die Anzahl der Spalten 
 size_t z_dim=sk[0].size(); //ein Vektor ist mindestens in der Basis
 size_t s_dim=tk.size() + sk.size();
 
 size_t dim=min(z_dim,s_dim); // der quadratische Anteil der Matrix
 matrix m;
 vektor v;
 size_t count=sk.size()-tk.size(); // die Anzahl der benoetigten Vektoren
 for (size_t i=0; i < z_dim; i++)
 {
  v.clear();
  for (size_t j=0; j < tk.size(); j++)
  {
   v.push_back(tk[j][i]); // bei BASIS werden Spaltenvektoren verwalten, bei m Zeilenvektoren
  }
  for (size_t j=0; j < sk.size(); j++)
  {
   v.push_back(sk[j][i]);
  }
  m.push_back(v);
 }
 permutation z_perm;
 id(z_dim, z_perm);
 size_t n=0;
 // Gauss Verfahren ohne Spaltenvertauschungen
 for (size_t j=0; j < s_dim; j++)
 {
  size_t l;
  // durchlaufe den quadratischen Anteil der Spalten der Matrix
  for (l=n; (l < z_dim) && (isNull(m[z_perm[l]][j]));l++); //Suche Zeile != 0
  if ((l != j) && (l < z_dim))
    swap(z_perm[l],z_perm[n]);
  if (l < z_dim) // falls nur noch Nullen unterhalb der Hauptdiagonalen stehen, ignoriere die Spalte
  {
   for(size_t i=n+1; i < z_dim; i++)
   {
    // durchlaufe die Zeilen der Matrix
    K multiplikator=m[z_perm[i]][j]/m[z_perm[n]][j];
    for (size_t k=j; k < s_dim; k++)
     m[z_perm[i]][k]-=multiplikator*m[z_perm[n]][k];
   }
   if(++n==z_dim) break; //letzte Zeile
  }
 }
 // Suche nach Vektoren, um base zu einer Basis zu erweitern
 size_t sk_begin=tk.size(); // der Spaltenindex ab dem die Spalten von sk in der Matrix m stehen
 size_t i=sk_begin;
 vector<bool> index(sk.size(),false); // die bereits ausgewaehlten Vektoren
 while(count > (size_t)0)
 {
  size_t j; 
  for (j=i; j < s_dim; j++)
  {
   if ( !isNull(m[z_perm[i]][j]) && (! index[j-sk_begin])) break;
  }
  if (j == s_dim)
  {
   cerr<<"Problem bei der Basisberechnung"<<endl;
   cerr<<"Die transformierte Matrix: "<<endl<<m;
   cerr<<"tk"<<endl;
   printbasis(tk);
   cerr<<"sk"<<endl,
   printbasis(sk);
   exit(1);
  }//nach Steinitz darf der Fall nicht auftreten, da sk BASIS.
  tk.push_back(sk[j-sk_begin]);
  index[j-sk_begin]=true;
  count--;
  i++;
 }
 return tk;
}
static basis & gauss_basis(matrix m, vector<bool> & bits, basis & b)
{
 /* gauss_basis:
    Beschreibung:
     diese Funkion liefert eine Basis des homogenen Systems m*x=0

    Eingabe:
     matrix m, das System
     vector<bool> bits, Bitvektor, der die zu betrachteten freien Parameter angibt -> Theorie

    Ausgabe:
     vector<bool> bits, Bitvektor, alle in die Basis aufgenommenen Parameter wurden auf true gesetzt
     basis b, Basis des Loesungsraumes
 */
 
 int z_dim=(int)m.size();
 if (m.size()==0)  return m; //leere Matrix
 int s_dim=(int)m[0].size();
 permutation z_perm, s_perm;
 id(z_dim, z_perm);
 id(s_dim, s_perm);
 // transformiere m auf Zeilenstufenform
 int nullbegin=z_dim; //Ab hier nur noch Nullzeilen
 for (int j=0; j < nullbegin; j++)
 {
  int l=j;
  if (isNull(m[z_perm[j]][s_perm[j]])) //Diagonalelement = 0
  {
   for (l=j+1; l < nullbegin; l++)
   //Suche Zeile != 0
    if (!isNull(m[z_perm[l]][s_perm[j]])) 
    {
     swap(z_perm[l],z_perm[j]);
     break;
    }
   if(l == nullbegin)
   {
    // suche eine Spalte !=0
    for (l=j+1; l < s_dim; l++)
     if (! isNull(m[z_perm[j]][s_perm[l]]))
     {
      swap(s_perm[l], s_perm[j]);
      break;
     }
     // sowohl die aktuelle Zeile als auch die aktuelle Spalte ist 0, tausche die Nullzeile nach unten 
    if (l == s_dim) 
    {
     swap(z_perm[j], z_perm[nullbegin-1]);
     nullbegin--;
     j--;
     continue;
    }
   }
  }// Ende Diagonalelement = 0
  for(int i=j+1; i < z_dim; i++)
  {
   K multiplikator=m[z_perm[i]][s_perm[j]]/m[z_perm[j]][s_perm[j]];
   for(int k=j; k < s_dim; k++)
    m[z_perm[i]][s_perm[k]]-=multiplikator*m[z_perm[j]][s_perm[k]];
  }
 }//Ende Zeilendurchlauf
 // berechne eine Basis des Loesungsraums
 vektor v(s_dim, (K)0);
 for(int i = z_dim-1; i >= nullbegin;i--)
 {
  // durchlaufe alle Zeilen 
  if (!bits[s_perm[i]])
  {
   //loese das gestaffelte System fuer v
   v[s_perm[i]]=(K)1;
   for(int k = nullbegin-1;  k >= 0; k--)
   {
    K sum=(K)0;
    for (int l=s_dim-1; l > k; l--)
     sum -= v[s_perm[l]]*m[z_perm[k]][s_perm[l]];
    v[s_perm[k]]=sum/m[z_perm[k]][s_perm[k]];
   }
   bits[s_perm[i]]=true; //makiere die Nullzeile
   b.push_back(v); //nehme v zur Basis des Raumes hinzu 
   v.clear();
   v.resize(s_dim, (K)0);
  }// Ende if m[i][i]==0     
 }// Ende 0-Zeilen Durchlauf
 return b;
}

static vector<basis> & stufenbasis(const matrix & m,  int grad, vector<basis> & s)
{
 /* stufenbasis:
    Beschreibung:
     diese Basis konstruiert zu einer Primaerkomponente eine Stufenbasis
    Eingabe:
     matrix m, die betrachtete Matrix
     K eigenwert, der zur Primaerkomponente gehoerige Eigenwert
    Rueckgabe:
     vector<basis> s, die Stufenbasis der Primaerkomponente
 */
   
 vektor perm;
 matrix potenz;
 basis l;
 vector<bool> bits(m.size(),false);
 potenz=m; 
 // Durchlaufe (A-lamda*E)^k bis Kern((A-lamda*E)^k) = Kern((A-lamda*E)^k+1)
 for (int i=0; i < grad; i++)
 {
  l.clear();
  gauss_basis(potenz, bits,l);
  s.push_back(l);
  potenz=m*potenz;
 }
 return s;
}

static basis & jordanbasis(const matrix & m, const vector<basis> & s, basis & base, vector<int> & zykel_len)
{
 /* jordanbasis:
    Beschreibung:
     diese Basis konstruiert aus einer Stufenbasis einer Primaerkomponente eine Jordanbasis
    Eingabe:
     matrix m, die betrachtete Matrix
     vector<basis> s, die Stufenbasis
    Rueckgabe:
     basis base, die Jordanbasis
     vector<size_t> zykel_len, die Groesse der einzelnen Jordanbloecke
  */
 vector<basis> t;
 vektor v;
 //Durchlaufe die Stufenbasis s von oben nach unten, sie ist nie leer, da lamda Eigenwert
 // Initialisierung
 basis tk_plus_1=s[s.size()-1]; // die oberste Stufe
 t.push_back(tk_plus_1);
 for (size_t i=s.size()-2; (int)i >= 0; i--)
 // zur Initialisierung: s enthält min. ein BASIS Element, da lamda Eigenwert.
 {
  // durchlaufe tk+1 mit v und nehme m(v) zu tk hinzu.
  basis tk; 
  for (size_t j=0; j < tk_plus_1.size(); j++)
  {
   v.clear();
   v=m*tk_plus_1[j];
   tk.push_back(v);
  }
  steinitz(s[i], tk); // fuelle tk mit Vektoren aus s[i] zu einer Basis auf 
  t.push_back(tk);
  tk_plus_1=tk;
 }
 size_t zykel=0;
 // generiere aus t eine Basis der Primärkomponente und hänge sie an base an
 for (size_t k=0; k < t.size(); k++) // Durchlaufe die Stufen der Basis
  for (; zykel < t[k].size(); zykel++) // durchlaufe die zu tk zugenommenen Vektoren aus sk mit v
  { 
   for (size_t j=k; j< t.size(); j++) // durchlaufe, die bereits berechneten Vektoren, v, m(v), m(m(v)), ...
   { 
    base.push_back(t[j][zykel]);
   }
   zykel_len.push_back(t.size()-k); // die Laenge des zykel.ten Zykel(die Groesse des Jordankaestchens)
  }
 return base;
}

static basis & primbasis(const matrix & A, const pair<K, int> & eigenwert, basis & base, vector<int> & zykel_len)
{
 /* getbasis:
    Beschreibung:
     diese Funktion liefert eine Basis der Primaerkomponente (X-\lambda)
    Eingabe:
     matrix m, die darstellende Matrix des betrachteten Endomorphismusses
     K eigenwert, der zur Primaerkomponente zugehoerige Eigenwert
    Rueckgabe:
     basis base, die Jordanbasis der Primaerkomponente
     vector<size_t> zykel_len, die Groesse der einzelnen Jordanbloecke
 */
 matrix m=A;
 for (size_t i=0; i< m.size();i++)
   m[i][i]-= eigenwert.first; // M-lambda * E
 vector<basis> s;
 stufenbasis(m, eigenwert.second,s);
 jordanbasis(m, s, base, zykel_len);
 return base;
}
static vector<pair<K,int> > eigenwerte(const matrix & A, vector< pair<K, int> > & eigen)
{
 pair<K, int> prim;
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
  eigen.push_back(pair<K, int>(eigenwert, p_vec[i].second));
 }
 return eigen;
}

matrix & jnf(const matrix & m, matrix & jnf_matrix, basis & retbasis)
{
 /* jnf:
    Beschreibung:
     diese Funktion liefert zu einer gegebenen Matrix, die Jordansche Normalform und die zugehoerige Basis
    Eingabe:
     matrix m, die betrachtete Matrix
     vektor eigenwerte, die Eigenwerte der Matrix
    Rueckgabe.
     jnf_matrix, die Jordan Form der Matrix
     basis retbasis, die Jordan Basis der Matrix
 */
 int dim=(int)m.size();
 //Falls m und jnf_matrix auf die selbe Matrix zeigen
 if (&m==&jnf_matrix)
 {
  matrix source=m;
  return jnf(source,jnf_matrix, retbasis);
 }
 vector< pair<K, int> > eigen;
 eigenwerte(m,eigen);
 nullmatrix(dim, dim, jnf_matrix);
 vector<int> zykel_len;
 int pos=0;
 for (size_t k=0; k < eigen.size(); k++)
 {
  // durchlaufe alle Eigenwerte
  zykel_len.clear();
  primbasis(m, eigen[k], retbasis, zykel_len);
  // erstellen die Jordan Form der Matrix
  for (size_t i=0; i < zykel_len.size(); i++)
  {
   jnf_matrix[pos][pos]=eigen[k].first;
   pos++;
   for (int j=1; j < zykel_len[i]; j++)
   {
     jnf_matrix[pos][pos]=eigen[k].first;
     jnf_matrix[pos][pos-1]=(K)1;
     pos++;
   }
  }
 }
 return jnf_matrix;
} 


