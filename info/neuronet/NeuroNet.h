#include "Neuron.h"
#include "Pattern.h"

class CNeuroNet
{
private:
	int neuroanzahl;
	int schichtanzahl;

	double lernrate;
	double momentum;

	CNeuron *neuron; // Zeiger auf ein Array von Neuronen
	int *schicht;    // Array, mit Anzahl der Neuronen in den jeweiligen Schichten
	double **weight; // Gewichtsmatrix, wobei w(i,j) die Gewichtung der Verbdg.strecke vom Neuron i zum Neuron j bezeichnet
	
	void trainNet(double *eingaben, double *ausgaben); // Trainiere Netz auf das Paar (Eingabevektor, Ausgabevektor)
	void changeWeight(double *ausgaben);               // Funktion zum Ändern der Gewichtsmatrix (mit Hilfe der gewuenschten Ausgaben)
	void changeLernrate();                             // Funktion zum Ändern der Lernrate
	void changeMomentum();                             // Funktion zum Ändern des Momentums
	bool schichtCheck(int zeile, int spalte);          // Funktion zur Ueberpruefung, ob eine Verbindung zeile --> spalte erlaubt ist

public:
	CNeuroNet(int neuroanz, int schichtanz, int *schichten, double **wmatrix, double **eingakt);
	CNeuroNet(int neuroanz, int schichtanz, int *schichten, double **wmatrix);
	~CNeuroNet();

	CNeuron * getNeuron(int number);                   // Hole Zeiger auf Neuron an der Stelle number

	void trainNet(CPattern *pat);                      // Trainiere Netz auf ein Pattern
	void setEingaben(double *eingaben);                // Funktion zum Belegen der Eingaben der Neuronen in der ersten Schicht
	
	void berechneTakt(); // Berechnung eines Zeittakts
	void printNeurons(); // Ausgabe aller Neuronen
	void printAusgabe(); // Ausgabe aller Ausgabeneuronen
};

