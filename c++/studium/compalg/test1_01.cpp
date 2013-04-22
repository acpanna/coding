// *****************************************************************
// *
// *	Testprogramm zur Headerdatei compalg1_01.hpp
// *
// *****************************************************************

// In der Datei data.txt muﬂ zun‰chst die Dimension der nxn_Matrix
// angegeben werden. Danach folgen die Eintr‰ge.


#include"compalg1.h"
#include<fstream>
#include<iomanip>

using namespace std;

int main(int argc, char **argv)
{
if (argc != 3)
	{
	cout << "Falsche Parametereingabe!\nBitte die Syntax einhalten!";
	cout << "\nRichtige Eingabe: test n &&&" << endl << endl;
	cout << "Hierbei kann fuer n stehen:\n";
	cout << "1  -  Vektoraddition" << endl;
	cout << "2  -  Matrixaddition" << endl;
	cout << "3  -  Multiplikation von Skalar und Vektor" << endl;
	cout << "4  -  Multiplikation von Skalar und Matrix" << endl;
	cout << "5  -  Multiplikation von Matrix und Vektor" << endl;
	cout << "6  -  Matrixmultiplikation" << endl;
	cout << "7  -  Ausgabe einer Basis" << endl << endl;
	cout << "...und fuer &&& der Dateiname der einzulesenen Datei." << endl;

	exit(1);
	}

K zahl;
matrix A,B,mret;
vektor vret;
int zlaenge, slaenge, ret;
ifstream dh (argv[2]);

// Einlesen von Matrix A
dh >> slaenge;
dh >> zlaenge;
for(int pos=0;pos<slaenge;pos++)
	{
	vektor v;

	for(int position=0;position<zlaenge;position++)
		{
		dh >> zahl;

		v.push_back(zahl);
		}

	A.push_back(v);	
	}

// Einlesen von Matrix B
dh >> slaenge;
dh >> zlaenge;
for(int pos=0;pos<slaenge;pos++)
	{
	vektor v;

	for(int position=0;position<zlaenge;position++)
		{
		dh >> zahl;

		v.push_back(zahl);
		}

	B.push_back(v);	
	}

// Einlesen der Basis C
dh.seekg(0);
dh >> slaenge;
dh >> zlaenge;
basis C(slaenge,vektor(zlaenge,0));
for(int pos=0;pos<zlaenge;pos++)
	{
	for(int position=0;position<slaenge;position++)
		{
		dh >> zahl;
		C[position][pos]=zahl;
		}
	}

dh.close();

vektor v=A[0];
vektor w=B[0];

K c=3;

if(string(argv[1])=="1")
	{
	// Vektoraddition
	vret=v+w;
	cout << setw(10) << "v:\t";
	printvektor(v);
	cout << endl << setw(10) << "w:\t";
	printvektor(w);
	cout << "\n\nErgebnis:\t";
	printvektor(vret);
	}

if(string(argv[1])=="2")
	{
	// Addition zweier Matrizen
	mret=A+B;
	cout << "A:\n";
	printmatrix(A);
	cout << "\n\nB:\n";
	printmatrix(B);
	cout << "\n\nErgebnis:\n";
	printmatrix(mret);
	}

if(string(argv[1])=="3")
	{
	// Multiplikation von Skalar und Vektor
	vret=c*v;
	cout << setw(10) << "c:\t" << setw(4) << c;
	cout << endl << setw(10) << "v:\t";
	printvektor(v);
	cout << "\n\nErgebnis:\t";
	printvektor(vret);
	}

if(string(argv[1])=="4")
	{
	// Multiplikation von Skalar und Matrix
	mret=c*A;
	cout << "c: " << c;
	cout << "\n\nA:\n";
	printmatrix(A);
	cout << "\n\nErgebnis:\n";
	printmatrix(mret);
	}

if(string(argv[1])=="5")
	{
	// Multiplikation von Matrix und Vektor
	vret=A*v;
	cout << "v: ";
	printvektor(v);
	cout << "\n\nA:\n";
	printmatrix(A);
	cout << "\n\nErgebnis:\t";
	printvektor(vret);
	}

if(string(argv[1])=="6")
	{
	// Matrix-Multiplikation
	mret=A*B;
	cout << "A:\n";
	printmatrix(A);
	cout << "\n\nB:\n";
	printmatrix(B);
	cout << "\n\nErgebnis:\n";
	printmatrix(mret);
	}

if(string(argv[1])=="7")
	{
	cout << "Basis:\n";
	printbasis(C);
	}

return 0;
}	
