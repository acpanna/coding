
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


#include<vector>
#include"compalg1.h"
#include<cmath>

const int q=K::p;


polynom& polysquar( polynom const& a ,int n ,polynom const&  p,polynom & b)     // Algorithmus zur effizienten Berechnung von (a)^n mod p
 						    				// mit a und p Polynome
{
 if(&a==&b) { polynom tmp=a; return polysquar(tmp,n,p,b); }
 if(&p==&b) { polynom tmp=p; return polysquar(a,n,tmp,b); }
 vector<int> dual;
 dual.clear();
 int i;

 for(i=0;n>0;i++)    // Euklidischer Algorithmus zur Bestimmung der Binärzahl von n
    {
     dual.push_back(n%2);  // Vektor mit Komponenten 0 oder 1
     n=n/2;
    }
 b=a;
 for (i=i-2;i>=0;i--)
    {
     if (dual[i]==1)      // falls an i-ter Stelle eine 1, dann wird b^2*a mod p gerechnet
        {
         b=(b*b*a) %p;
        }

     if (dual[i]==0)      // falls an i-ter Steller eine 0, dann wird b^2 mod p gerechnet
     	{
     	 b=(b*b) %p;
      	}

     if (dual[i]>=2)      // kann eigentlich nicht vorkommen
        {
         cout << "dual falsch besetzt" << endl;
         }
    }

 return b;
}


static polynom& normiere_poly(polynom& P)  // normiert ein Polynom (aus compalg1_07 Thema 7)
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





vector<polynom>& distinct( polynom const& f ,int n,vector<polynom> & ret )  // distinct-degree Algorithmus

{

 ret.clear();  // Nullvektor
 int i,j;
 polynom h (2);  // h = x
 h[1]=1;
 polynom x=h ;  // x = x
 polynom g,F,s;
 F=f;            // F ist Kopie von f und verändert sich in der for-Schleife

 for (i=1; i<=(deg(F)/2-1); i++)    // deg(F) <= 2(i+1)
	{
        	polysquar(h,n,f,h);     // Bestimmt h^n mod f
		s=h-x;                  // s ist Polynom der Form x^q^i-x
		g=ggT(s,F);             // "Kernstück" des Algorithmuses: g ist nun Produkt von irreduzieblen
					// Polynomen, deren Grad i teilen
		F=F/g;                  // der ggT wird heruasgeteilt (deshalb quadratfrei)
		ret.push_back(g);       // Vektor wird mit den g(i) aufgefüllt
	}

			             	// die for-Schleife wird nun nicht mehr durchlaufen, da i+1 > deg(F)/2 ist
 if(deg(F)!=0)			// F ist demnach irreduziebel oder konstant (F=1)
 {ret.push_back(F);}  		// F ist irreduziebel und wird zum Vektor ret hinzugefügt

 return ret;
}


int potenz(int a ,int n)  // berechnet a^(n)
{
 vector<int> dual;
 dual.clear();
 int i,h,b;
 n;
 h=0;
 for(i=0;n>0;i++)
    {
     dual.push_back(n%2);
     n=n/2;
     h=h+1;
    }
 b=a;

 for (i=h-2;i>=0;i--)
    {
     if (dual[i]==1){b=b*b*a;}
     if (dual[i]==0){b=b*b;}
     if (dual[i]>=2){cout << "dual falsch besetzt" << endl;}
    }
 return b;
}


polynom polyrand(int m)             // generiert Zufallspolynom vom Grad < m

{
 int j,i,l;
 if(m!=1){j=1+(int) (((double)(m-1))*rand()/(RAND_MAX+1.0));}  // Gradbestimmung per Zufall
 j=1;

 polynom a(j+1);
 a[j]=1+(int) ((double)(q-1)*rand()/(RAND_MAX+1.0)); // Leitkoeffizient darf nicht null sein

 for (i=0; i<=j-1; i++)
	{
	  a[i]=0+(int) ((double)(q)*rand()/(RAND_MAX+1.0));  // Restliche Koeffizienten werden per Zufall bestimmt
	}

 return a;
}


polynom& split( polynom const& f, int d, polynom & b )  // Sucht Polynom, so dass gilt ggT(b,f) nicht trivial
							// "Splitting Algorithmus"
{

 int n,i;
 i=deg(f);
 polynom a;
 polynom e(1); // e=1
 e[0]=1;

 error:
 a=polyrand(i);    // Zufallspolynom wird generiert
 b=ggT(f,a);

 if(deg(b)!=0)    // Grad von b ungleich 0

	{
	return b;    // Polynom b wird zurückgegeben
	}

 	else
 	{
	n=((potenz(q,d))-1)/2;    // Berechnet n=(q^(d)-1)/2
	polysquar(a,n,f,b);       // Berechnet a^(n) mod f
	b=b-e;
	b=ggT(b,f);
	if(deg(b)!=0 && deg(b)!=deg(f) ) // Grad von b ungleich 0 und ungleich f
		{
		return b; // Polynom b wird zürückgegeben
		}
		else
		{
		goto error;  //  goto new random
		}

	}

}


vector<polynom>& equal( polynom const& f, int d, vector<polynom> & ret ) // equql degree Algorithmus
{

 polynom g;

 if (deg(f)==d) { ret.push_back(f);}       // Grad von F = d   Polynom wird gespeichert

 else
 {
	split(f,d,g);    // Aufruf des Splitting Algorithmus

	equal(f/g,d,ret); // rekursiver Aufruf der Funktion equal mit g unf f/g
	equal(g,d,ret);   // "erzeugt binären Baum"
 }

 return ret;

}

vector<pair<polynom,int> >& irred(polynom const& p, vector<pair<polynom,int> > &ret) // Algorithmus zur vollständigen
										     // Zerlegung in irreduzieble Faktoren

{
 polynom f=p;
 int i,j;
 polynom x(2);    // x = x
 x[0]=0;
 x[1]=1;

 polynom h=x;  // h = x
 polynom g,F,n;
 vector<polynom> vec_equal;
 ret.clear();
 F=normiere_poly(f);           // Normiert Polynom
 for(i=1;i<=(deg(F)/2);i++)    // Beginn des i-ten Schrittes des distinct Algorithmuses
 {

	polysquar(h,q,f,h);   // berechnet h^q mod f
	g=ggT(F,h-x);         // "Kernstück des distinct-degree Algorithmus
	if( deg(g)!=0)
	{
		equal(g,i,vec_equal); // Anwendung des equal-degree Algorithmuses auf
    		                      // jeden einzelnen Schritt des distinct degree Algorithmuses
		for(j=0;j<vec_equal.size();j++)
		{                       // Vielfachheit des gefundenen irreduzieblen Plynoms wird ermittelt
			int e=0;
			while (F%vec_equal[j]==n){F=F/vec_equal[j]; e=e+1;}  // e ist Vielfachheit
			vec_equal[j]=normiere_poly(vec_equal[j]);
			ret.push_back(make_pair(vec_equal[j],e));  // das irred. Polynom und die zugehörige
								   // Vielfachheit werden gespeichert
 		}

		vec_equal.clear();

	}

 }

 F=normiere_poly(F);
 if (deg(F)!=0)

 {ret.push_back(make_pair(F,1));}  // F ist irreduziebel und hat Vielfachheit 1

 return ret;
}













