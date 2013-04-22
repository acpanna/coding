// *****************************************************************************
// ** THEMA 1: Datenstruktur Vektor, Matrix
// *****************************************************************************
// ** Schyma, Sebastian 
// *****************************************************************************
// **
// ** Elementare Funktionen wie Ausgabe, Addition, Multiplikation
// ** Multiplikation nach Strassen fuer quadratische Matrizen
// ** 
// ** Literatur zur Matrixmultiplikation: 
// **   Aho, Hopcroft, Ullman: The Design and Analysis of Computer Algorithms
// **   1974, 230-232
// **
// *****************************************************************************
// **
// ** Zu implementieren:
// **
// ** 	void printvektor(vektor const& v);
// ** 	void printmatrix(matrix const& A);
// ** 	void printbasis (basis  const& A);
// ** 	vektor& add (vektor const& v, vektor const& w, vektor& ret);
// **	matrix& add (matrix const& A, matrix const& B, matrix& ret);
// **	vektor& mult(K      const& c, vektor const& v, vektor& ret); 
// **	matrix& mult(K      const& c, matrix const& A, matrix& ret); 
// **	vektor& mult(matrix const& A, vektor const& v, vektor& ret);
// **	matrix& mult(matrix const& A, matrix const& B, matrix& ret);
// **
// *****************************************************************************


#include"compalg1.h"

// Erlaubt die Verwendung der Funktion "setw(int n)" (d.h. Tabulatorsprung um n Zeichen)
#include<iomanip>

using namespace std;

// *****************************************************************************
// ** Zum erleichtern der Programmierarbeit zuerst ein paar nützliche Funktionen 
// *****************************************************************************


// Funktion zum Aufsplitten einer Matrix in 4 gleichgroße Teile
void aufsplitten(matrix const& A, matrix& A1, matrix& A2, matrix& A3, matrix& A4)
	{
	// Die Dimension der (quadratischen) Matrix herausfinden
	int laenge=A.size();

	matrix B;
	int neu;

	// Ist die Dimension durch 2 teilbar?
	// Falls die Dimension nicht durch 2 teilbar ist, wird A in eine neue 
	// Matrix der Dimension "laenge+1" eingebettet.
	if (laenge%2 != 0)
		{
		neu=laenge+1;		

		// An jede Zeile der Matrix 0 anfügen
		for (int pos=0; pos<laenge; pos++)
			{
			vektor zeile;
			zeile=A[pos];
			zeile.push_back(0);
		
			B.push_back(zeile);
			}

		// Einen Nullvektor der Länge "neu" erzeugen...
		vektor v;
		for (int pos=0; pos<neu; pos++)
			{v.push_back(0);}

		// ...und ihn an die Matrix anfügen
		B.push_back(v);
		}
	else
		{
		neu=laenge;
		B=A;
		}

	int teil=neu/2;

	// Teilmatrix A1 wird erstellt
	for(int pos=0; pos<teil; pos++)
		{
		vektor v,w;
		v=B[pos];
	
		for(int zaehler=0; zaehler<teil; zaehler++)
			{
			K eintrag;
			eintrag=v[zaehler];

			w.push_back(eintrag);
			}

		A1.push_back(w);
		}		

	// Teilmatrix A2 wird erstellt
	for(int pos=0; pos<teil; pos++)
		{
		vektor v,w;
		v=B[pos];

		for(int zaehler=teil; zaehler<neu; zaehler++)
			{
			K eintrag;
			eintrag=v[zaehler];

			w.push_back(eintrag);
			}

		A2.push_back(w);
		}

	// Teilmatrix A3 wird erstellt
	for(int pos=teil; pos<neu; pos++)
		{
		vektor v,w;
		v=B[pos];

		for(int zaehler=0; zaehler<teil; zaehler++)
			{
			K eintrag;
			eintrag=v[zaehler];

			w.push_back(eintrag);
			}
	
		A3.push_back(w);
		}

	// Teilmatrix A4 wird erstellt
	for(int pos=teil; pos<neu; pos++)
		{
		vektor v,w;
		v=B[pos];

		for(int zaehler=teil; zaehler<neu; zaehler++)
			{
			K eintrag;
			eintrag=v[zaehler];

			w.push_back(eintrag);
			}

		A4.push_back(w);
		}
	}


// Funktion zum Zusammensetzen von 4 gleichgroßen Matrizen zu einer großen Matrix
void zusammensetzen(matrix const& A1, matrix const& A2, matrix const& A3, matrix const& A4, matrix& ret)
	{
	int laenge;
	ret.clear();
	laenge=A1.size();

	for(int pos=0; pos<laenge; pos++)
		{
		vektor v,w;
		v=A1[pos];
		w=A2[pos];

		for(int zaehler=0; zaehler<laenge; zaehler++)
			{
			K eintrag;
			eintrag=w[zaehler];
			v.push_back(eintrag);
			}
		
		ret.push_back(v);
		}

	for(int pos=0; pos<laenge; pos++)
		{
		vektor v,w;
		v=A3[pos];
		w=A4[pos];

		for(int zaehler=0; zaehler<laenge; zaehler++)
			{
			K eintrag;
			eintrag=w[zaehler];
			v.push_back(eintrag);
			}
		
		ret.push_back(v);
		}
	}


// Funktion zum Zusammensetzen von 4 Einzelwerten zu einer Matrix
void zusammensetzen(K const& a1, K const& a2, K const& a3, K const& a4, matrix& ret)
	{
	vektor v,w;
	
	v.push_back(a1);
	v.push_back(a2);
	w.push_back(a3);
	w.push_back(a4);

	ret.clear();
	ret.push_back(v);
	ret.push_back(w);
	}


template <class T>
void strassen(T const& A1,T const& A2,T const& A3, T const& A4,T const& B1,T const& B2,T const& B3,T const& B4,T& ret1,T&  ret2,T& ret3,T& ret4)
	{
	T m1,m2,m3,m4,m5,m6,m7;	

	// Rekursion
	m1=(A2-A4)*(B3+B4);
	m2=(A1+A4)*(B1+B4);
	m3=(A1-A3)*(B1+B2);
	m4=(A1+A2)*B4;
	m5=A1*(B2-B4);
	m6=A4*(B3-B1);
	m7=(A3+A4)*B1;

	ret1=m1+m2-m4+m6;
	ret2=m4+m5;
	ret3=m6+m7;
	ret4=m2-m3+m5-m7;
	}
	

// *****************************************************************************
// ** Die zu implementierenden Funktionen
// *****************************************************************************

// Ausgabe eines Vektors
void printvektor(vektor const& v)
	{
	int laenge;
	laenge=v.size();

	for(int pos=0; pos < laenge; pos++)
		{
		K eintrag;
		eintrag=v[pos];
		cout << setw(4) << eintrag;
		}
	}


// Ausgabe einer Matrix
void printmatrix(matrix const& A)
	{
	int zeilen;
	zeilen=A.size();

	for(int zpos=0; zpos < zeilen; zpos++)
		{
		vektor v;
		v=A[zpos];

		int spalten;
		spalten=v.size();
		
		for(int spos=0; spos < spalten; spos++)
			{
			K eintrag;
			eintrag=v[spos];
			cout << setw(4) << eintrag;
			}

		cout << endl;
		}
	}


// Ausgabe einer Basis
void printbasis (basis  const& A)
	{
	int vektorlaenge;
	int dim;
	vektorlaenge=A.size();
	dim=A[0].size();

	for(int pos=0; pos < dim; pos++)
		{
		for(int basisvektor=0; basisvektor < vektorlaenge; basisvektor++)
			{
			K eintrag;
			eintrag=A[basisvektor][pos];
	
			cout << setw(4) << eintrag << setw(4) << "|";
			}

		cout << endl;
		}	
	}


// Addition zweier Vektoren
vektor& add(vektor const& v, vektor const& w, vektor& ret)
	{
	// Zum Herausfinden der Länge der beiden Vektoren
	int laenge;
	laenge=v.size();

	ret.resize(laenge);

	for (int pos=0; pos < laenge; pos++)
		{
		K veintrag, weintrag, ergebnis;

		// Auslesen des Wertes in der Zeile "pos" (beider Vektoren)
		veintrag=v[pos];
		weintrag=w[pos];

		// Addition der Einträge
		ergebnis=veintrag+weintrag;

		// Aufnahme des errechneten Wertes an der entsprechenden
		// Stelle des Ergebnisvektors
		ret[pos]=ergebnis;
		}

	return ret;
	}


// Addition zweier Matrizen
matrix& add(matrix const& A, matrix const& B, matrix& ret)
	{
	int laenge;
	laenge=A.size();

	ret.resize(laenge,vektor(laenge));

	for (int pos=0; pos < laenge; pos++)
		{
		vektor Aeintrag, Beintrag, ergebnis;

		// Auslesen der Spalte in der Zeile "pos" (beider Matrizen)
		Aeintrag=A[pos];
		Beintrag=B[pos];

		// Addition der Einträge (Vektoraddition)
		add(Aeintrag,Beintrag,ergebnis);
	
		// Aufnahme der errechneten Spalte an der entsprechenden
		// Stelle der Ergebnismatrix
		ret[pos]=ergebnis;
		}

	return ret;
	}


// Subtraktion zweier Vektoren
vektor& sub(vektor const& v, vektor const& w, vektor& ret)
	{
	// Zum Herausfinden der Länge der beiden Vektoren
	int laenge;
	laenge=v.size();

	ret.resize(laenge);

	for (int pos=0; pos < laenge; pos++)
		{
		K veintrag, weintrag, ergebnis;

		// Auslesen des Wertes in der Zeile "pos" (beider Vektoren)
		veintrag=v[pos];
		weintrag=w[pos];

		// Addition der Einträge
		ergebnis=veintrag-weintrag;

		// Aufnahme des errechneten Wertes an der entsprechenden
		// Stelle des Ergebnisvektors
		ret[pos]=ergebnis;
		}

	return ret;
	}


// Subtraktion zweier Matrizen
matrix& sub(matrix const& A, matrix const& B, matrix& ret)
	{
	int laenge;
	laenge=A.size();

	ret.resize(laenge,vektor(laenge));

	for (int pos=0; pos < laenge; pos++)
		{
		vektor Aeintrag, Beintrag, ergebnis;

		// Auslesen der Spalte in der Zeile "pos" (beider Matrizen)
		Aeintrag=A[pos];
		Beintrag=B[pos];

		// Subtraktion der Einträge (Vektorsubtraktion)
		sub(Aeintrag,Beintrag,ergebnis);

		// Aufnahme der errechneten Spalte an der entsprechenden
		// Stelle der Ergebnismatrix
		ret[pos]=ergebnis;
		}

	return ret;
	}
	
// (RG) Hab ich in Header-Datei verschoben, damit es global benutzbar wird.
//
// // Zur Subtraktion werden zur Erleichterung der Programmierarbeit noch folgende Operatoren definiert:
// inline vektor operator-(vektor const& v, vektor const& w) 
//                                            { vektor ret; return sub(v,w, ret); }
// inline matrix operator-(matrix const& A, matrix const& B) 
//                                            { matrix ret; return sub(A,B, ret); }


// Multiplikation von Skalar und Vektor
vektor& mult(K const& c, vektor const& v, vektor& ret)
	{
	// Zum Herausfinden der Länge des eingegebenen Vektors:
	int laenge=v.size();

	ret.resize(laenge);

	// Beginn der Multiplikation
	for (int pos=0; pos < laenge; pos++)
		{
		K eintrag, ergebnis;

		// Auslesen des Wertes in der Zeile "pos"
		eintrag=v[pos];

		// Multiplikation des Eintrags mit dem Skalar
		ergebnis=c*eintrag;

		// Aufnahme des errechneten Wertes an der entsprechenden
		// Stelle des Ergebnisvektors
		ret[pos]=ergebnis;
		}

	return ret;
	}


// Multiplikation von Skalar und Matrix
matrix& mult(K const& c, matrix const& A, matrix& ret)
	{
	int laenge;
	laenge=A.size();

	ret.resize(laenge,vektor(laenge));

	for (int pos=0; pos < laenge; pos++)
		{
		vektor eintrag, ergebnis;

		// Auslesen der Spalte in der Zeile "pos"
		eintrag=A[pos];

		// Multiplikation der Zeile "pos" mit dem Skalar (Multiplikation von Vektor und Skalar)
		mult(c,eintrag,ergebnis);

		// Aufnahme der errechneten Spalte an der entsprechenden
		// Stelle der Ergebnismatrix
		ret[pos]=ergebnis;
		}

	return ret;
	}


// Multiplikation von Matrix und Vektor
vektor& mult(matrix const& A, vektor const& v, vektor& ret)
{
if(&v==&ret)
	{
	vektor temp;
	mult (A,v,temp);
	ret=temp;
	return ret;  // BUGFIX by RG.
	}
else
	{
	// Zum Herausfinden der Länge des Vektors (und der quadratischen Matrix)
	int laenge;
	laenge=v.size();
	
	for(int pos=0; pos<laenge; pos++)
		{
		// Abrufen der Zeile "pos" von A
		vektor eintrag;
		eintrag=A[pos];

		K ergebnis=0;
		int position=0;

		// In der Zeile "pos" und dem Vektor wird Wert für Wert vorgegangen:
		// erst werden beide Werte an der Stelle "position" multipliziert und zum 
		// Schluß alle Produkte aufsummiert
		for(int position=0; position<laenge; position++)
			{
			K wert1, wert2, produkt;
			
			wert1=eintrag[position];
			wert2=v[position];

			produkt=wert1*wert2;

			ergebnis=ergebnis+produkt;			
			}

		ret.push_back(ergebnis);
		}
		
	return ret;
	}
}


//-------------------------------------------------------------
// Algorithmus zur Matrix-Multiplikation nach Strassen
//-------------------------------------------------------------
matrix& mult(matrix const& A, matrix const& B, matrix& ret)
	{
	// Die Länge von A herausfinden
	int length;
	length=A.size();

	matrix A1,A2,A3,A4,B1,B2,B3,B4; 	

	aufsplitten(A,A1,A2,A3,A4);
	aufsplitten(B,B1,B2,B3,B4);

	// Die Länge von A1 herausfinden (dieselbe Länge haben auch A2, A3, A4)
	int laenge;
	laenge=A1.size();

	if (laenge == 1)
		{
		K a1,a2,a3,a4,b1,b2,b3,b4,ret1,ret2,ret3,ret4;

		// Umwandeln von einzeiligen, einspaltigen Matrizen in einen K-Wert
		a1=A1[0][0];
		a2=A2[0][0];
		a3=A3[0][0];
		a4=A4[0][0];
		b1=B1[0][0];
		b2=B2[0][0];
		b3=B3[0][0];
		b4=B4[0][0];

		strassen(a1,a2,a3,a4,b1,b2,b3,b4,ret1,ret2,ret3,ret4);
		zusammensetzen(ret1,ret2,ret3,ret4,ret);
		}
	else
		{
		matrix ret1,ret2,ret3,ret4;
		strassen(A1,A2,A3,A4,B1,B2,B3,B4,ret1,ret2,ret3,ret4);
		zusammensetzen(ret1,ret2,ret3,ret4,ret);
		}

	// Die für den Algorithmus eingefügten Zeilen und Spalten entfernen
	ret.resize(length);
	
	for(int pos=0;pos<length;pos++)
		{
		ret[pos].resize(length);
		}	

	return ret;
	}
