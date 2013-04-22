// *****************************************************************************
// ** THEMA 7: Ordnungspolynom, Minimalpolynom
// *****************************************************************************
// ** Buchholzer, Hannes
// *****************************************************************************
// **
// ** Literatur:
// ** - Vorlesungsskript Lineare Algebra II
// ** - H. Lueneburg, Vorlesungen ueber lineare Algebra, BI Wissenschaftsverlag,
// **   1993, 223-239
// **
// ** Wir rechnen hier allgemein im Faktorraum V/U, U<=V<=\K^n.
// ** V und U werden (falls noetig) durch eine Basis angegeben.
// ** Der Ausgabevektor f sind die Koeffizienten, sodass
// **         o*v = f[0]*u[0] + ... + f[k]*u[k]
// ** (d.h. o*v liegt in U). Daraus werden im Algorithmus elteiler die Polynome
// ** f_i gewonnen.
// **
// *****************************************************************************
// #############################################################################
// ## Datum diese Version:  03.12.2003
// ## compalg1_07 stellt bereit:
// ## polynom& ordpoly(matrix const& A, vektor const& v, basis const& U,
// ##                  polynom& o, vector<K>& f)
// ## polynom& minpoly(matrix const& A, basis const& V, basis const& U,
// ##		       polynom& m, vektor& v, vector<K>& f)
// ##
// ## Hinweise zur Benutzung von ordpoly:
// ##   A muß eine quadratische Matrix sein. Anhand von A wird die Dimension
// ##   des Vektorraumes V bestimmt. v muß die gleiche Dimension wie A haben.
// ##   Wenn U={0} ist, wird nur in V gerechnet, dann wird f als leerer Vektor
// ##   zurückgegeben.
// ##   Wenn U nicht leer ist, wird in V/U gerechnet. Dazu muß die Matrix A
// ##   U invariant sein, d.h. A*U ist Teilmenge von U. Ansonsten bricht die
// ##   gesamte Theorie zusammen. Die Ergebnisse sind dann auch falsch.
// ##   In o wird das Ordnungspolynom geschrieben.
// ##   Der Vektor f wird dann berechnet. Er hat als Länge die Anzahl der
// ##   Basisvektoren von U und enthält die Linearkombination desjenigen
// ##   Elementes in U, das durch o*v gegeben ist.
// ## 
// ## Hinweise zur Benutzung von minpoly:
// ##   A muss wieder quadratisch sein. Die Dimension wird anhand von A 
// ##   bestimmt. Die Vektoren von V und U müssen diese Dimension haben.
// ##   V darf nicht leer sein. Diese Funktion nimmt auch einige Überprüfungen
// ##   vor. Je nach dem ob U={0} ist, wird in V oder V/U gerechnet. Falls
// ##   U nicht leer ist, muß A U-invariant sein d.h. A*U Teilmenge von U.
// ##   In m wird das Minimalpolynom geliefert. In v wird ein Vektor geliefert
// ##   , der das Minimalpolynom m als Ordnungspolynom hat. Ist U nicht leer,
// ##   wird in f die Linearkombination der Basis U von dem Element m*v geliefert d.h.
// ##   m*v = f[0]*U[0] + ... + f[k]*U[k].
// ##   Ist U leer, wird f unverändert belassen.
// ##
// ## Hinweis zu dem Parameter gaussinfo benutzt in minpoly und ordpoly:
// ##   gaussinfo enthält die ersten drei Parameter der Funkion gauss. Sei G vom
// ##   Typ gaussinfo. Wenn U={0} ist muss U.A leer sein, U.P muss die Identität
// ##   sein und U.M muss die Einheitsmatrix sein. Ist dim(U)>0, dann erzeugt man
// ##   G, indem man gauss nacheinander mit allen Basisvektoren von U aufruft, wobei
// ##   G am Anfang die Gestalt hat wie im Fall U={0}.
// ##
// ## V,U müssen Basen sein, ansonsten ist das Ergebnis unvorhersehbar.
// ##




#include "compalg1.h"



static polynom& normiere_poly(polynom& P);
static vektor& horner(matrix const& A, vektor const& v,
         polynom const& p,unsigned int pos, vektor& res);



polynom& ordpoly(matrix const& A, vektor const& v, gaussinfo const& U,
		 polynom& o, vector<K>& f)
{
  gaussinfo U2;

  vektor lin_komb, //Vektor mit der Linear Kombination
                  // der A^i*v zum Nullvektor
         v2 = v; // Kopie des Originalvektors v
  bool lin_unabh = true;

 
 // Kopie von gaussinfo
  U2 = U;

  int anz_basisU = U2.A.size();//Dimension von U

    //Der Vektor v wird eingefügt in Gauss
  lin_unabh = gauss(U2, v2, lin_komb);

  if( !lin_unabh ) {  //Falls der Gauss linear abhängig liefert, war v im Uterraum U, also 
      o.clear();    // 0 in V/U. Das Minimalpolynom ist  dann 1 .
      o.push_back(1); 
      f = lin_komb;   
      return o;
    }

  do { //Die Potenzen (A^i)*v werden eingefügt
      v2 = A*v2;      //bis (A^k)*v linear abhängig von den bisher eingefügten  (A^i)*v 
      lin_unabh = gauss(U2, v2, lin_komb);          // mit (i<k)
    } while (lin_unabh);

    //Der Anteil der linear Kombination, der in U liegt
    //wird in f geschrieben und anschließend aus lin_komb gelöscht.
    //Dies geschieht mit Hilfe von Iteratoren
  f = vektor( lin_komb.begin(),
              (lin_komb.begin() + anz_basisU ) );
  lin_komb.erase(lin_komb.begin(),
              (lin_komb.begin() + anz_basisU ) );


  //Aus der verkürzten lin_komb wird das Ordnungspolynom
  //erzeugt
  o.assign(lin_komb.begin(), lin_komb.end() ); 
  o = K(-1)*o;
  o.push_back(1);  // Die 1 steht für den letzten Vektor
  

  return o;
}



polynom& minpoly(matrix const& A, basis const& V, gaussinfo const& U,
		 polynom& m, vektor& v, vector<K>& f)
{
  unsigned int dim_V = V.size(),i;//Die Anzahl der Vektoren, die V aufspannen. V kann auch
                                   // ein Untervektorraum sein.   
                                 
  unsigned int dim_U = U.A.size(); //Anzal der Vektoren, die U ( <= V) aufspannen.
  				  
  vector<polynom> ordpol(dim_V);//Vektor mit Ordnungspolynomen
         // zu den Vektoren der Basis V

  polynom c,d,C,D,D2,t,T;//Diese Polynome werden für der Algorithmus weiter unten benötigt.
  vektor ret,ret2; // Dies sind lediglich Dummy Variablen, die für die
                   // Funktion mult unten benutzt werden.


// Einige Tests

  if( A[0].size() != A.size() ) {//Matrix quadraisch ?
    cout << "Fehler in minpoly(...):\nDie Matrix A ist"
         << " nicht quadratisch.\n";
    exit(1);
    }
  
  if( V[0].size() != A.size() ) {//sind die Dimensionen der Matrix und der
                                  // Vektoren gleich?
    cout << "Fehler in minpoly(...):\nDie Matrix A und die Vektoren "
         << "der Basis V haben nicht die gleiche Dimension.\n" ;
    exit(1);
    }
  


  //Vorarbeit: Erzeuge das Ordnungspolynom für die
  // Vektoren einer Basis V
  for(i=0; i<dim_V ; i++ ) {
    ordpoly(A,V[i],U,ordpol[i],f);
    }

   //Initialisierung für den Algorithmus
    m = ordpol[0];
    v = V[0];
     
     
     
//Dies ist der eigentliche Algorithmus um aus den
//Ordnungspolynomen das Minimalpolynom zu berechnen.
//Der Algorithmus könnte viel einfacher sein, wenn man
//keinen Vektor v haben wollte, der das Minimalpolynom
//als Ordnungspolynom hat.

    for( i=1; i<dim_V ; i++ ) {
      if( deg(ordpol[i]) == 0 ) continue;
      c=m;
      d=ordpol[i];
      t = ggT(c,d);
      algo_r(c,d/t,C);
      algo_r(d,c/t,D);
      T = ggT(C,D);
      D2=D/T;
      m=C*D2;
      v = mult(c/C,A,v,ret) + mult(d/D2,A,V[i],ret2);
      if( deg(m) == dim_V - dim_U ) break; // Minimalpolynom kann nicht grösser werden
    }

  normiere_poly(m);

  if( U.A.size() > 0 )
       ordpoly(A,v,U,ordpol[0],f);
  //Dieser Aufruf geschieht um f zu berechnen.
  //Dies macht nur Sinn, wenn U.A  nicht leer ist.
  //ordpol[0] ist hier lediglich ein dummy.

  return m;
}






//#######################################################
//            Einige Hilfsfunktionen
//#######################################################



// Diese Funktion normiert ein gegebenes
// Polynom. Das Polynom sollte nicht leer sein.

static polynom& normiere_poly(polynom& P)
{ 

  trim(P);//Stelle sicher, dass P in Standartform ist.
  if( deg(P) == -1 ) return P;
  if( P[deg(P)] == K(1) ) return P;//Polynom
  //ist schon normiert.

  int i,grad;
  K LeitKoeff;

  grad = deg(P);
  LeitKoeff = P[grad];
  P[grad] = 1;//Leitkoeff normiert

   // Teile die restlichen Koeff. durch den Leitkoeff.
  for( i=grad-1;i>=0;i--)
       P[i] = P[i]/LeitKoeff ;

  return P;
}



//Diese Funktion berechnet auf effiziente Weise ( mit einem modifizierten
// Horner-Algorithmus ) das Produkt p(A)*v, wobei p ein Polynom ist
// A eine Matrix und v ein Vektor.

vektor& mult(polynom const& p, matrix const& A, vektor const& v,
	     vektor& ret)
{
  if( deg(p)<1 ) {
  // Wenn das Nullpolynom vorliegt, wird der Nullvektor zurückgegeben.
    if( p.size() == 0 ) {
    ret = vektor( v.size(),0);
    return ret;
    }
    ret = p[0]*v;
    return ret;
  }
  ret = horner(A,v,p,0,ret);
  return ret;
}



// Diese Funktion berechnet für eine Matrix A und ein
// Polynom p den Vektor : (p[n]*A^n + ... + p[0]*E)*v
// Dies wird mit einer Abwandlung des Horner-Algorithmus
// durchgeführt.Die Funkion arbeitet rekursiv.

static vektor& horner(matrix const& A, vektor const& v,
         polynom const& p,unsigned int pos, vektor& res)
{

  if( pos == p.size()-2 ){  //pos ist auf der vorletzten Stelle im Vektor
    res = p[pos+1]*(A*v) + p[pos]*v;
    return res;
  }
  
  res = p[pos]*v + A*horner(A,v,p,pos+1,res);
  return res;


}




