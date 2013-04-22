#include "compalg1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
matrix & jnf(const matrix & m, matrix & jnf_matrix, basis & retbasis);
matrix & basis2matrix (const basis & b, matrix & m)
{
 // mach aus einem Vector von Spalten einen Vector von Zeilen
 vektor nullzeile=vektor(b.size());
 for (int i=0; i < (int)b.size(); i++) m.push_back(nullzeile);
 
 for(int i=0; i < (int)b.size(); i++)
  for(int j=0; j < (int)b.size(); j++)
   m[i][j]=b[j][i];
 return m;
}

void init(matrix & m, char * datei)
{
 ifstream fin(datei);
 read(fin, m);
}

int main(int args, char ** argv)
{
 if (args==1)
 {
  cout <<"Programm zur Berechnung der Jordanschen Normalform"<<endl;
  cout <<"Aufruf : "<<argv[0]<<" <testnummer> [<parameter>]"<<endl<<endl;
  cout <<"Implementierte Tests"<<endl;
  cout <<"Testnummer:     erwartete Parameter"<<endl;
  cout <<"1               [<dateiname fuer Matrix>]+"<<endl<<endl;
  cout <<"Fuer das Format der Datei gilt:"<<endl;
  cout <<"Es wird nur mit quadratischen Matrixen gerechnet"<<endl;
  cout <<"Die erste Zeile gibt die Dimension an (ein int Wert)"<<endl;
  cout <<"Danach folgen zeilenweise die einzelen Zeilen der Matrix"<<endl;
  cout <<"die einzelnen Spalten sind dabei durch Whitespaces getrennt."<<endl;
  return EXIT_SUCCESS;
 }
 matrix m;
 vektor v;
 basis retbasis;
 matrix jnf_matrix;
 switch(atoi(argv[1]))
 {
   case 1:
    if (args < 3)
    {
     cout <<"Bitte mindestens einen Dateinamen als Parameter eingeben"<<endl;
     exit(EXIT_FAILURE);
    }
    for (int i=2; i < args; i++)
    {
     init(m, argv[i]); //Beispielmatrix erzeugen
     clock_t bevor, after, diff_lueneburg, diff_rep;
     bevor=clock();
     cout<<"clock vor Aufruf der Lueneburg Version: "<<bevor<<endl;
     jordansche_nf(m, jnf_matrix, retbasis);
     after=clock();
     cout<<"clock nach Aufruf der Lueneburg Version: "<<after<<endl;
     diff_lueneburg=after-bevor;
     cout <<"Die Matrix : "<<endl;
     printmatrix(m);
     cout <<"Die Jordanform:"<<endl;
     printmatrix(jnf_matrix);
     cout <<"Die Jordanbasis:"<<endl;
     printbasis(retbasis);
     cout <<"Kontrollrechnung (B^{-1} * m * B):"<<endl;
     matrix b;
     matrix b_inv;
     basis2matrix(retbasis,b);
     cout<<(inv(b, b_inv)*m*b);
     jnf_matrix.clear();
     retbasis.clear();
     b.clear();
     b_inv.clear();
     bevor=clock();
     cout<<"clock vor Aufruf der Repetitorium Version: "<<bevor<<endl;
     jnf(m, jnf_matrix, retbasis);
     after=clock();
     cout<<"clock nach Aufruf der Repetitorium Version: "<<after<<endl;
     diff_rep=after-bevor;
     cout <<"Die Matrix: "<<endl;
     printmatrix(m);
     cout <<"Die Jordanform:"<<endl;
     printmatrix(jnf_matrix);
     cout<<"Die Jordanbasis:"<<endl;
     printbasis(retbasis);
     cout<<"Kontrollrechnung (B^{-1} * m * B):"<<endl;
     basis2matrix(retbasis,b);
     cout<<(inv(b, b_inv)*m*b);
     cout<<"Benoetigte clocks Lueneburg:    "<<diff_lueneburg<<endl<<"Benoetigte clocks Repetitorium: "<<diff_rep<<endl;
     cout<<"Die Repetitorium Version braucht also "<<diff_rep - diff_lueneburg<<" clocks, das sind "<<(diff_rep-diff_lueneburg)/CLOCKS_PER_SEC<<" sec mehr."<<endl;
    }
    break;
   default:
    cout <<"Unbekannter Test. Rufen Sie "<<argv[0]<<" auf, um die Testmoeglichkeiten zu erfahren."<<endl;
    exit(EXIT_FAILURE);
 } 
 return EXIT_SUCCESS;
}
