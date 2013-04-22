
#include "compalg1.h"
#include <iomanip>
#include <fstream>


static int Hreadmatrix( matrix& M );
static void Hreadvektor( vektor& v, int dim);
static void Hreadbasis( matrix& M, int dim );



using namespace std;



int main(int argc,char* argv[])
{

  if(argc < 2) {
    cout << endl << endl;
    cout << "Syntax: test1_07 <n> [<Datei>]" << endl;
    cout << "1          Berechnung des Ordnungspolynoms zu einer Matrix und einem Vektor.\n"
         << "           Manuelle Eingabe einer Matrix und eines Vektors und eventuell\n"
         << "           eines Unterraumes U." << endl;
    cout << "2 <Datei>  Berechnung des Ordnungspolynoms zu einer Matrix und einem Vektor.\n"
         << "           Eine Matrix, ein Vektor und evtl. eine Basis von U werden in dieser\n"
	 << "           Reihenfolge aus einer Datei eingelesen. U kann auch weggelassen werden.\n"
	 << "           Fall Sie keine Datei angeben wird exa/07/bsp2a.dat verwendet." << endl;
    cout << "3          Berechnung von dem Minimalpoynom einer Matrix A.\n"
         << "           Manuelle Eingabe einer Matrix einer Basis für V und\n"
	 << "           evtl. einer Basis für U." << endl;
    cout << "4 <Datei>  Berechnung von dem Minimalpoynom einer Matrix A.\n"
         << "           Eine Matrix und eine Basis von V und von U werden aus\n"
         << "           <Datei> in dieser Reihenfolge eingelesen.U kann auch\n"
	 << "           weggelassen werden. Falls Sie keine Datei angeben wird\n"
	 << "           exa/07/bsp4a.dat verwendet." << endl << endl;
    cout << "Zum Format der Dateien: Matrizen und Vektoren werden im bisher üblichen\n"
	 << "Format abgespeichert, d.h. wie sie die read Funktionen einlesen. Aber eine Basis\n"
	 << "wird als transponierte Matrix abgespeichert, d.h. die Basisvektoren werden als\n"
	 << "Zeilen geschrieben." << endl;
    cout << "Gerechnet wird im Faktorraum V/U, oder V falls keine Basis für U eingegeben wird.\n"
         << "Dabei ist V der K^n und U ein Teilraum davon." << endl;
    cout << endl;
    return -1;
  }

  string arg=argv[1];
  string file;
  
  if(argc >= 3 ) file = argv[2];
  
  if(arg=="1") {
    polynom o;
    matrix A;
    vektor v,f;
    gaussinfo U;
    basis B;
    string antw;
    int dim;

    cout << endl << endl;
    dim = Hreadmatrix(A);
    Hreadvektor(v, dim);

    init(dim, U);

    cout << "Wollen Sie im Faktorraum V/U rechnen? (j/n)" << endl;
    cin >> antw;
    if( antw == "j"  || antw == "J" ) {
        cout << "Geben Sie jetzt eine Basis für den Unterraum U an:\n"; 
        Hreadbasis(B, dim);

	for(unsigned int i=0; i<B.size(); i++) gauss(U,B[i],f);
    }


    ordpoly(A,v,U,o,f);

    cout << "\nDas Ordnungspolynom ist:"
         << endl << o << endl;

    if( B.size() > 0 ) {
       cout << "\nDie Linearkombination von o*v in U ist :"
            << endl << f << endl;
    }

    cout << endl << endl;

  }

  if(arg=="2") {
    ifstream in;
    polynom o;
    matrix A;
    vektor v,f;
    gaussinfo U;
    basis B;


    if( !file.empty() )
        in.open( file.c_str() );
    else in.open( "exa/07/bsp2a.dat" );
    
    read(in,A);
    read(in,v);
    read(in,B);

    in.close();
    
    cout << endl << endl
         << "Dies ist die eingelesene Matrix:"
         << endl << A << endl;

    cout << "Dies ist der eingelesene Vektor:"
         << endl << v << endl << endl;

    if(B.size() > 0 ) {
      cout << "Dies ist die eingelesene Basis von U:" << endl;
      printbasis(B); cout << endl;     
    }

    init(v.size(),U);
    for(unsigned int i=0; i<B.size(); i++) gauss(U,B[i],f);

  
    ordpoly(A,v,U,o,f);

    cout << "\nDas Ordnungspolynom ist:"
         << endl << o << endl;

    if( B.size() > 0 ) {
       cout << "\nDie Linearkombination von o*v in U ist :"
            << endl << f << endl;
    }

    cout << endl << endl;
  }   
  
  
  if(arg=="3") {
    polynom m;
    matrix A;
    vektor v,f;
    gaussinfo U;
    basis V,B;
    string antw;
    int dim;

    cout << endl << endl;
    dim = Hreadmatrix(A);
    
    cout << "Wollen Sie die Standartbasis?(j/n)" << endl;
    cin >> antw;
    if( antw == "j"  || antw == "J" ) {
    einsmatrix(dim,V);
    }
    else {
    Hreadbasis(V, dim);
    }
    
    init(dim,U);

    antw.resize(0);
    cout << "Wollen Sie im Faktorraum V/U rechnen? (j/n)" << endl;
    cin >> antw;
    if( antw == "j"  || antw == "J" ) {
        cout << "Geben Sie jetzt eine Basis für den Unterraum U an:\n"; 
        Hreadbasis(B, dim);

	for(unsigned int i=0; i<B.size(); i++) gauss(U,B[i],f);
    }


    minpoly(A,V,U,m,v,f);

    cout << "\nDas Minimalpolynom ist:"
         << endl << m << endl << endl;

    cout << "Dies ist der Vektor, der das Minimalpolynom als Ordnungspolynom hat:"
         << endl << v << endl << endl;

    if( B.size() > 0 ) {
       cout << "Die Linearkombination von m*v in U ist :"
            << endl << f << endl;
    }

  cout << endl << endl;

  }



  if(arg=="4") {
    ifstream in;
    polynom m;
    matrix A;
    vektor v,f;
    basis V,B;
    gaussinfo U;
    
    if( !file.empty() ) 
        in.open( file.c_str() );
    else in.open( "exa/07/bsp4a.dat" );
    
    read(in,A);
    read(in,V);
    read(in,B);
    
    in.close();
    
    cout << endl << endl;
    cout << "Dies ist die eingelesene Matrix:"
         << endl << A << endl;
    cout << "Dies ist die eingelesene Basis von V:" << endl;
    printbasis(V); cout << endl;
    


    if(B.size() > 0 ) {
      cout << "Dies ist die eingelesene Basis von U:" << endl;
      printbasis(B); cout << endl;    
    }


    init(A.size(),U);
    for(unsigned int i=0; i<B.size(); i++) gauss(U,B[i],f);

    gaussinfo U2=U;
    minpoly(A,V,U2,m,v,f);
    
    cout << "\nDas Minimalpolynom ist:"
         << endl << m << endl << endl;

    cout << "Dies ist der Vektor, der das Minimalpolynom als Ordnungspolynom hat:"
         << endl << v << endl << endl;

    if( B.size() > 0 ) {
       cout << "Die Linearkombination von m*v in U ist :"
            << endl << f << endl;
    }
  cout << endl << endl;
  }  


return 0;
}






static int Hreadmatrix( matrix& M )
{
  int dim;
  cout << "Eingabe einer Matrix: " << endl;
  cout << "Geben Sie die Dimension einer quadratischen Matrix ein:" << endl;
  cin >> dim;
  cout << "Geben Sie die Elemente ein:" << endl; ;
  read(cin, M, dim, dim);
  return dim;
} 


static void Hreadbasis( matrix& M, int dim )
{
  int anz;
  cout << "Eingabe einer Basis : " << endl;
  cout << "Geben Sie die Anzahl der Vektoren ein:" << endl;
  cin >> anz;
  cout << "Geben Sie " << anz << " Vektor(en) der Länge " << dim
       << " zeilenweise ein:" << endl;

  read(cin, M, anz, dim);
} 



static void Hreadvektor( vektor& v,int dim)
{
  cout << "Geben Sie einen Vektor der Länge " << dim << " ein:" << endl;

  read(cin, v, dim);
}        





