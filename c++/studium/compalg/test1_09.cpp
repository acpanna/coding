
// *****************************************************************
// *
// *	Testdatei zu compalg1_09
// *
// *****************************************************************


#include<iostream>
#include"compalg1.h"
#include <fstream>


vector<polynom>& distinct( polynom const& p ,int n,vector<polynom> & ret );
polynom& split( polynom const& p, int d, polynom & b );
vector<polynom>& equal( polynom const& f, int d, vector<polynom> & ret );


using namespace std;


int distalg(int argc, char **argv, int what){
  if(argc!=2) {
    cout << "Syntax: test1_09 " << what << " <polynom> "<< endl;
    return 1;
  }

int i,j;


 polynom f;
 ifstream file1(argv[1]);          // einlesen von f

 if(!read(file1, f) )
      {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }


 int n;             // Körperordnung
 cout << endl;
 cout << f;    cout << endl;
 cout << endl;
 cout << "Bitte Körperordnung eingeben:" << endl;
 cin >> n;
 cout << endl;

 vector<polynom> vec_g;
 distinct(f,n,vec_g);  // Aufruf der Funktion distinct

 j=vec_g.size();    // Länge des Vektors mit den Polynomen
 for(i=0; i<j;i++)
 {
 cout << vec_g[i];  // Ausgabe des Vektors mit den Polynomen als Komponenten
 cout << endl;
 }
  cout << endl;
 return 0;
}



int findggtalg(int argc, char **argv, int what) {
  if(argc!=2) {
    cout << "Syntax: test1_09 " << what << " <polynom> "<< endl;
    return 1;
  }

  polynom f;
  ifstream file1(argv[1]);                     // einlesen von f

  if(!read(file1, f))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }


 int j,d;
 cout << endl;
 cout << f;      cout << endl;
 cout << endl;
 cout << "Bitte erforderlichen Teiler d eingeben:"<< endl;
 cin >> d;

 cout << endl;

 polynom b;

 split(f,d,b);     // Aufruf des Splitting Algorithmus
 cout << b;  cout << endl;

 cout << endl;
 return 0;
}


int gleichalg( int argc, char **argv, int what) {
  if(argc!=2) {
    cout << "Syntax: test1_09 " << what << " <polynom> "<< endl;
    return 1;
  }

  polynom f;				// einlesen von Polynom f
  ifstream file1(argv[1]);
  if(!read(file1, f))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }



 int j,i,d;    // d ist Grad der irreduzieblen Polynome
 cout << endl;
 cout << f;   cout << endl;
 cout << endl;
 cout << "Bitte erforderlichen Teiler d eingeben:"<< endl;
 cin >> d;

 vector<polynom> vec_equal;

 equal(f,d,vec_equal);  // Equal-degree Algorithmus

 j=vec_equal.size();    // Länge des Vektors mit den Polynomen

 cout << endl;
 for(i=0; i<j;i++)
 {
 cout << vec_equal[i];  // Ausgabe des Vektors mit den Polynomen als Komponenten
 cout << endl;
 }

 cout << endl;
 return 0;
}




int zerlegung(int argc, char **argv, int what) {
  if(argc!=2) {
    cout << "Syntax: test1_09 " << what << " <polynom> "<< endl;
    return 1;
  }


  polynom f;
  ifstream file1(argv[1]);                  // einlesen von Polynom f
  if(!read(file1, f))
    {
    cout << "Fehler beim einlesen der Dateien"<< endl;
    return 1;
    }

 int j,i;

 cout << endl;
 printpoly(f);
 cout << endl;

 vector<pair<polynom,int> > ret;

 irred(f,ret);  // Aufruf des irred algorithmuses

 cout << endl;
 for(i=0;i<ret.size();i++)
 {
 cout << ret[i].first; cout <<"   Vielfachheit   "; cout << ret[i].second;  // Ausgabe des Vektors mit den Polynomen als Komponenten
 cout << endl;
 }


 cout << endl;
 return 0;
}



int main(int argc, char **argv) {
  if(argc>=2) {
    switch(atoi(argv[1])) {
    case 1: return distalg(argc-1, argv+1,1);
    case 2: return findggtalg(argc-1, argv+1,2);
    case 3: return gleichalg(argc-1, argv+1,3);
    case 4: return zerlegung(argc-1, argv+1,4);
    }
  }
  // Ein Fehler ist aufgetreten. Gebe Syntax aus:
  cout << endl;
  cout << "Syntax: test1_09 <n> " << endl;
  cout << "1  -  distinct-degree Algorithmus " << endl;
  cout << "2  -  splitting Algorithmus" << endl;
  cout << "3  -  equal-degree Algorithmus" << endl;
  cout << "4  -  vollständige Zerlegung in irreduzible Polynome" << endl << endl;
  return 1; // Rueckgabewert !=0, d.h. Fehler
}




