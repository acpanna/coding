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
// **
// ** polynom& div(polynom const& a, polynom const& b, polynom& q, polynom& r);
// ** polynom& euklid(polynom const& p, polynom const& q, 
// **		polynom& ggT, polynom& a, polynom& b);
// ** polynom& algo_r(polynom const& p, polynom const& q, polynom& r);
// **
// *****************************************************************************

#include"compalg1.h"

using namespace std;

static int div_unter(polynom & a, polynom const& b, polynom & q, polynom & r);

polynom& div(polynom const& a, polynom const& b, polynom& q, polynom& r)
{
  
  if(b.empty())                 //Aufruftest
    {
      cout << "Teilen durch Null nicht definiert" << endl;    
      exit (1);
    }

  if(a.empty())                 //Aufruftest
    {
      q.resize(0);              //q.clear();
      r.clear(); //[RG]  vorher war:  r = b; 
    return q;
    }
      
  if(a[deg(a)]==0)          //Aufruftest        
    {    
      cout << "1.Polynom nicht in Standard"<< endl; 
      exit (1);
    }
   
  if(b[deg(b)]==0)          //Aufruftest
    {
      cout << "2.Polynom nicht in Standard"<< endl; 
      exit (1);
    }
       
  q.resize(0);		  
  r.resize(0);
    
  polynom a_copy = a;                     //Kopie von Polynom a erstellen
         
  div_unter(a_copy,b,q,r);   
   
  return q;
}


static int div_unter(polynom & a, polynom const& b, polynom & q, polynom & r)
{
  
  if(a.size()<b.size())               	//Abbruchkriterium
    {
    r = a;
    return 0;
    }
  
  if(a.size()==b.size())                //Abbruchkriterium
    {                                                     
    K quotient = a[deg(a)]/b[deg(b)];   //Eintrag von q berechnen
    q.resize(1);
    q[0] = quotient;
    
    polynom p = b;			//Kopie von Polynom b erstellen
    r = a-quotient*p;			//Rest berechnen
        
    return 0;
    } 
  
  if(a.size()>b.size()) 
    {
    int delta_size = a.size()-b.size();          //Polynomgradunterschied berechnen
    K quotient = a[deg(a)]/b[deg(b)];
    polynom p (a.size());			//Polynom p = b * x^delta_size
        for(int i= deg(p) ; i>=delta_size ; i--)
          p[i] = b[i-delta_size];

    a = a-quotient*p;				//a_neu = a_alt - quotient * p
    
    int tmp = (p.size()-a.size())-1;		//hiermit wird die Anzahl der Nullen berechnet und gespeichert, die in q fehlen 
    						//wuerden wenn sich a_neu und a_alt um mehr als einen Grad unterscheiden   
    if( tmp>delta_size ) 			//hiermit wird verhindert, dass am Schluss zu viele Nullen angehaengt werden 
      tmp = delta_size;
    
    div_unter(a,b,q,r);
        
    for(int i=tmp ; i>0; i--)			//Abspeichern der berechneten Eintraege für q
      q.push_back(0);
    q.push_back(quotient);
    }
 
  return 0;
}

polynom& ggT(polynom const& A, polynom const& B, polynom& ggT)
{
  polynom a=A, b=B, r;
  while(!b.empty())
    {
      r=a%b;
      a = b;
      b = r;
    }
  ggT = a;
  return ggT;
}

 
polynom& euklid(polynom const& a1, polynom const& b1, polynom& ggT, polynom& x, polynom& y)
{
  if(a1.empty() && b1.empty())    //Aufruftest
    {
      cout << "Der ggT(0,0) ist nicht definiert" << endl;    
      exit (1);
    }
  if(a1.empty())                
    {
      x.clear();
      y = 1;
      ggT = b1;
      return ggT;
    }
  if(b1.empty())                 
    {
      x = 1;
      y.clear();
      ggT = a1;
      return ggT;
    }
  if(a1[deg(a1)]==0)          //Aufruftest        
    {    
      cout << "1.Polynom nicht in Standard"<< endl; 
      exit (1);
    }
  if(b1[deg(b1)]==0)          //Aufruftest
    {
      cout << "2.Polynom nicht in Standard"<< endl; 
      exit (1);
    }

  polynom a = a1;                //Kopie von Polynom a1 erstellen
  polynom b = b1;                //Kopie von Polynom b1 erstellen
  
  polynom q, r, tmp_x, tmp_y;

  polynom x0(1);
  x0[0] = 1;
  polynom x1;
  polynom y0;
  polynom y1(1);
  y1[0] = 1;   
  polynom sign(1);
  sign[0] = 1; 

  K minus_eins = -1;

  while(!b.empty())
    {
      div(a,b,q,r);     // q=a/b; r=a%b;

      a = b;
      b = r;
      tmp_x = x1;
      tmp_y = y1;
      x1 = q*x1 + x0;
      y1 = q*y1 + y0;
      x0 = tmp_x;
      y0 = tmp_y;
      sign = minus_eins*sign;
    }

  x = sign*x0;
  y = minus_eins*sign*y0;
  ggT = a;

  return ggT;
}

 
polynom& algo_r(polynom const& p, polynom const& q, polynom& r)
{
  if(p.empty() && q.empty())    //Aufruftest
    {
      cout << "Der ggT(0,0) ist nicht definiert" << endl;    
      exit (1);
    }
  if(q.empty())                 
    {
      r = p;
      return r;
    }
  if(p.empty())                 
    {
      r = q;
      return r;
    }
  if(p[deg(p)]==0)          //Aufruftest        
    {    
      cout << "1.Polynom nicht in Standard"<< endl; 
      exit (1);
    }
  if(q[deg(q)]==0)          //Aufruftest
    {
      cout << "2.Polynom nicht in Standard"<< endl; 
      exit (1);
    }

  polynom tmp1,tmp2,tmp3;
  polynom s;
  
  r = p;
  s = q;
  
  s = euklid(r,s,tmp1,tmp2,tmp3);
  
  while(deg(s)>0)
    {
      r = r/s;
     
      s = euklid(r,s,tmp1,tmp2,tmp3);
    }

  return r;
}
