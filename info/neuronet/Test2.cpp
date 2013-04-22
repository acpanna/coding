#include "NeuroNet.h"

using namespace std;

int main(void)
{
	// Initialisierung der Gewichts-, Vorgaben- und der Ausgabenmatrix,
	// sowie der Matrix für Start-Eingabe und Start-Akt.zustand
	
	int i, j, nanz = 12, sanz = 3, panz = 6;

	double **matrix;
	double **einakt;

	double **vorgabe;
	double **ergebnis;

	int schicht[] = { 3, 6, 3 };

	vorgabe  = (double **) new (double *)[panz];
	ergebnis = (double **) new (double *)[panz];
	matrix   = (double **) new (double *)[nanz];
	einakt   = (double **) new (double *)[nanz];

	assert(vorgabe);
	assert(ergebnis);
	assert(matrix);
	assert(einakt);
		
	for (i=0; i<panz; i++)
	{
		vorgabe[i]  = (double *) new double[schicht[0]];
		assert(vorgabe[i]);
		
	  ergebnis[i] = (double *) new double[schicht[sanz-1]];
	  assert(ergebnis[i]);
	}
	
	for (i=0; i<nanz; i++)
	{
		matrix[i] = (double *) new double[nanz];
    assert(matrix[i]);

		einakt[i] = (double *) new double[2];
    assert(einakt[i]);
	}

	srand((unsigned int) time(NULL));

	for (i=0; i<nanz; i++)
	{
		for (j=0; j<nanz; j++)
			matrix[i][j] = 1.0/4.0 * (double) ((rand() - rand()) / ((double) RAND_MAX));
	}
	
	vorgabe[0][0]  = 0.0;
	vorgabe[0][1]  = 0.0;
	vorgabe[0][2]  = 0.0;
	ergebnis[0][0] = 0.0;
	ergebnis[0][1] = 0.0;
	ergebnis[0][2] = 0.0;
	vorgabe[1][0]  = 1.0,
	vorgabe[1][1]  = 0.0;
	vorgabe[1][2]  = 0.0;
	ergebnis[1][0] = 1.0;	
	ergebnis[1][1] = 0.0;	
	ergebnis[1][2] = 0.0;	
	vorgabe[2][0]  = 0.0;
	vorgabe[2][1]  = 1.0;
	vorgabe[2][2]  = 0.0;
        ergebnis[2][0] = 0.0;
        ergebnis[2][1] = 1.0;
        ergebnis[2][2] = 0.0;
	vorgabe[3][0]  = 1.0;
	vorgabe[3][1]  = 1.0;
	vorgabe[3][2]  = 0.0;
        ergebnis[3][0] = 1.0;
        ergebnis[3][1] = 1.0;
        ergebnis[3][2] = 0.0;
	
	vorgabe[4][0]  = 0.0;
	vorgabe[4][1]  = 1.0;
	vorgabe[4][2]  = 1.0;
        ergebnis[4][0] = 0.0;
        ergebnis[4][1] = 1.0;
        ergebnis[4][2] = 1.0;
	// abgeschlossen

	
	// Erklaerung:

	// Das Netz ist so aufgebaut, das nur Verbindungen zwischen Neuronen zweier benachbarter
	// Schichten erlaubt sind. Ausserdem gehe ich in der Implementierung der changeWeight() -
	// Funktion davon aus, das die Neuronen schichtweise durchnummeriert sind, d.h. Neuron 1 und Neuron 2 sind
	// Eingabeneuronen in der 1. Schicht, Neuronen 3, 4, 5 liegen in der 2. Schicht, Neuronen 6, 7, 8 in der 
	// 3. Schicht und Neuron 9 ist das Ausgabeneuron in der 4. Schicht.


	// Erzeugung eines Patterns aus den Vorgabe- und Ergebnismatrizen
	
	CPattern *pattern = new CPattern(panz, schicht[0], schicht[sanz-1], vorgabe, ergebnis);
	
	
	// Erzeugung des neuronalen Netzes mit den Daten aus den beiden Matrizen

	CNeuroNet *net = new CNeuroNet(nanz, sanz, schicht, matrix, einakt);
	

	// Trainieren des Netzes auf das Pattern
	
	net->trainNet(pattern);
	
	
	// Ausgabe des Netzes, nach erfolgreichem Training des Patterns
	
	cout << endl << endl;
	
	for (i=0; i<panz; i++)
	{	
	  for (j=0; j<sanz; j++)
	  {
	    net->setEingaben(pattern->vorgaben[i]);
		  net->berechneTakt();
		}
	
	  pattern->printVorgabe(i);
	  cout << ", ";
	  pattern->printAusgabe(i);
	  cout << ", ";
	  net->printAusgabe();
	  cout << endl;
	}
	net->printNeurons();

	// Aufräumarbeiten
		
	delete net;
	
for (i=0; i<nanz; i++)
{cout << endl;
for (j=0; j<nanz; j++)
	cout <<matrix[i][j]  << " ";
	}




for (i=0; i<nanz; i++)
	{
		delete [] einakt[i];
		delete [] matrix[i];
  }

	delete [] vorgabe;
	delete [] ergebnis;
	delete [] matrix;
	delete [] einakt;

	return 0;
}
