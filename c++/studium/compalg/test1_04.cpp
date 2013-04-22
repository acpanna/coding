#include <fstream>
#include <iomanip>
#include "compalg1.h"


int main(int argc, char **argv) {
   if (argc == 1) {
      cout << "Richtige Eingabe: test1_04 n &&&" << endl << endl
	   << "Hierbei steht fuer &&& einer der vorgegebenen Dateinamen.\n"
	   << "Fuer n kann stehen:\n\n"
	   << "1  -  Unabhaengigkeit eines Vektors pruefen" << endl
	   << "      aufrufbar mit: data1a.txt, data1b.txt" << endl 
	   << "                     data1c.txt, data1d.txt" << endl << endl
	   << "2  -  Berechnung einer Determinante" << endl 
	   << "      aufrufbar mit: data2.txt, data3.txt" << endl
	   << "                     data4.txt, data4b.txt " << endl
	   << "                     data5.txt" << endl << endl
	   << "3  -  Berechnung einer inversen Matrix" << endl 
	   << "      aufrufbar mit: data2.txt, data3.txt, " << endl
	   << "                     data4.txt, data4b.txt " << endl
	   << "                     data5.txt" << endl << endl
	   << "==================================================================" << endl
	   << "Hilfe:" << endl 
	   << "Aufruf mit test1_04 4" << endl
	   << "   -  Informationen zu den Datenfiles und der Abspeicherung der Daten" << endl;
	   

	exit(1);
   }

   int dim;

   // Fuer den Gauss-Algorithmus:
   int help;
   int anz_basis;
   bool linunabh;
   basis A;
   permutation P;
   matrix M;
   vektor v,w;
   
   // Fuer die Determinante:
   K determinante;
   matrix M2;
   
   // Fuer die inverse Matrix:
   matrix M3, inv_M3;
   
   
   ifstream in(argv[2]);	

	
   if(string(argv[1])=="1") {
      //*******************************************************
      // Gauss-Algorithmus - Ist v unabhaengig von den A[i]?
      //*******************************************************
      
      in >> dim;                // Dimension des Vektorraums
      in >> anz_basis;          // Anzahl der Basisvektoren in A
      
      if(anz_basis != 0) {
         nullbasis(dim, anz_basis, A);  // Erzeuge Basis (mit 0 vorbesetzt)
      }                                     // und Transformationsmatrix (mit 0
      einsmatrix(dim, M);                   // vorbesetzt, Diagonale mit 1)
                   
               
      help = anz_basis;
   
      for(int i = 0; i < help; i++) {     // Lese eine obere
         for(int j = 0; j <= i; j++) {    // Dreiecks"matrix"
            in >> A[i][j];                // von Spaltenvektoren
         }                                // ein
      }
      
      id(dim, P);
      for(int i = 0; i < dim; i++) {     // Einlesen der
         in >> P[i];                     // Permutation in
      }                                  // Listenschreibweise
      
      help = 1;
      for(int s = 0; s < anz_basis; s++) {   // Lese die Transformationsmatrix ein
         for(int z = help; z < dim; z++) {   // (nur Eintraege unterhalb der Diagonalen
      	    in >> M[z][s];                   // in den Spalten 1 bis anz_basis)
         }                                   // spaltenweise!
         help++;
      } 
      
      v.assign(dim,0);
      for(int i = 0; i < dim; i++) {      // Lese den neuen Vektor v ein, der
         in >> v[i];                      // auf Unabhaengigkeit von den A[i]
      }                                   // geprueft werden soll

      linunabh = gauss(A, P, M, v, w);               // Aufruf des Algorithmus
   
      
      if(!linunabh) {                  // v war abhaengig!
         cout << "v ist linear abhaengig von den Basisvektoren! " << endl << endl;
         cout << "v: "; 
         printvektor(v);
         cout << endl << endl;
         cout << "Koeffizienten, sd. v Linearkombination der urspruenglichen Basisvektoren: " 
              << endl;
         printvektor(w);
      }
      else {                           // v ist unabhaengig!
         cout << "Modifiziertes v: ";
         printvektor(A[anz_basis]);
         cout << endl << "Modifizierte Transformationsmatrix: " << endl;
         printmatrix(M);
         cout << endl << "Modifizierte Permutation: ";
         for(int i = 0; i < (int) P.size(); i++) {
		cout << setw(4) << P[i];
	 }
	 cout << endl;
      }
   
   }
 
   if(string(argv[1])=="2") {
      //*******************************************************
      // Determinantenberechnung
      //*******************************************************
      
      read(in, M2);       // Matrix einlesen mit Funktion aus compalg1_00
      
      if(M2.size() != M2[0].size()) {
         cout << "Matrix ist nicht quadratisch!" << endl;
         exit(1);
      }      
      determinante = det(M2);
      cout << "M: " << endl;
      printmatrix(M2);
      cout << endl;
      cout << "Determinante von M = " << determinante << endl;
   }
   
   if(string(argv[1])=="3") {
      //*******************************************************
      // Invertieren einer Matrix
      //*******************************************************
      
      read(in, M3);       // Matrix einlesen mit Funktion aus compalg1_00
      
      if(M3.size() != M3[0].size()) {
         cout << "Matrix ist nicht quadratisch!" << endl;
         exit(1);
      }
      
      inv_M3 = inv(M3,inv_M3);
      if(inv_M3.size() != 0) {                 // Falls Matrix nicht
      	 cout << "M: " <<endl;                 // invertierbar, wird das
         printmatrix(M3);                      // schon in der Funktion
         cout <<endl <<endl;                   // ausgegeben
         cout << "Inverse Matrix zu M: " << endl;
         printmatrix(inv_M3);
      cout << endl;
      }
   }
   
   if(string(argv[1])=="4") {
   cout    << "Hilfetext: " << endl 
           << "===========" << endl
           << "data1a.txt: Daten enthalten einen unabhaengigen Vektor v" << endl
	   << "            bei dem keine Zeilenvertauschung vorgenommen werden muss." << endl
	   << "data1b.txt," << endl
	   << "data1c.txt: " << endl
	   << "            Daten enthalten einen unabhaengigen Vektor v, " << endl
	   << "            bei dem Zeilen vertauscht werden muessen." << endl
	   << "data1d.txt: Daten enthalten einen zu den Basisvektoren " << endl
	   << "            abhaengigen Vektor v." << endl << endl
	   << "data2.txt," << endl
	   << "data3.txt, " << endl
	   << "data4b.txt: " << endl
	   << "            regulaere Matrizen" << endl
	   << "data4.txt," << endl
	   << "data5.txt: " << endl
	   << "            singulaere Matrizen" << endl << endl << endl
	   << "Format der Datenfiles:" << endl << endl
	   << "data1a.txt - data1d.txt:" << endl
	   << "========================" << endl
	   << "1. Dimension des Vektorraums" << endl
	   << "2. Anzahl vorgegebener Basisvektoren" << endl
	   << "3. Basisvektoren in oberer Dreiecksgestalt, d.h." << endl
	   << "   vom 1.Vektor nur die 1.Kompoente, " << endl
	   << "   vom 2.Vektor die ersten beiden Komponenten, ... " << endl
	   << "4. Die Permutation, " << endl
	   << "   abgelegt als (0 1 2 ... n-1) in Listenschreibweise" << endl
	   << "5. Die Transformationsmatrix, " << endl
	   << "   dabei werden nur die Elemente unterhalb der Hauptdiagonalen" << endl
	   << "   spaltenweise eingelesen, und auch nur so viele Spalten wie" << endl
	   << "   vorgegebene Basisvektoren" << endl
	   << "   Die restlichen Elemente werden auf 0, die Hauptdiagonale" << endl
	   << "   auf 1 gesetzt." << endl
	   << "6. Der neue Vektor v" << endl << endl
	   << "data2.txt - data5.txt:" << endl
	   << "======================" << endl
	   << "1. Anzahl der Zeilen der Matrix" << endl
	   << "2. Anzahl der Spalten der Matrix" << endl
	   << "3. Die Matrix selbst zeilenweise" << endl << endl;
   }
   
   return 0;   
}

