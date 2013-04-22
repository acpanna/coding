#include <iostream.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define K         5.0
#define TOLERANCE 0.4

class CNeuron
{
private:
	double eingabe;
	double aktzustand;
	double ausgabe;

	void setAusgabe(double ausg);

	void berechneAusgabe();
	void (CNeuron::*berechneAktzustand)();  // Funktionszeiger auf die Funktion, die den Aktivierungszustand f�r n�chsten Zeittakt berechnet
	void changeAktFunction(void (CNeuron::*aktFunction)());  // Zum �ndern des Funktionszeigers

	void aktFunction1();
	void aktFunction2();
	void aktFunction3();

public:
	CNeuron();
	CNeuron(double eing, double akt, void (CNeuron::*aktFunction)());
	CNeuron(double akt, void (CNeuron::*aktFunction)());
	~CNeuron();

	void  setEingabe(double eing);
	void  setAktzustand(double zustand);
	
	double getEingabe();
	double getAktzustand();
	double getAusgabe();
	
	void berechneNeuron();  // Hier wird Neuron, abh�ngig von Eingabe und Akt.zustand ausgewertet
};


