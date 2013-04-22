#include "Neuron.h"

using namespace std;

CNeuron::CNeuron(double eing, double akt, void (CNeuron::*aktFunction)())
{
	eingabe = eing;
	aktzustand = akt;
	ausgabe = 0.0;

	berechneAktzustand = aktFunction;

	cout << "\nNeuron erzeugt ...";
}

CNeuron::CNeuron(double akt, void (CNeuron::*aktFunction)())
{
	eingabe = 0.0;
	aktzustand = akt;
	ausgabe = 0.0;

	berechneAktzustand = aktFunction;

	cout << "\nNeuron erzeugt ...";
}

CNeuron::CNeuron()
{
	eingabe = 0.0;
	aktzustand = 0.0;
	ausgabe = 0.0;

	berechneAktzustand = &CNeuron::aktFunction1;  //  Standardeinstellung: Aktivierungszustand ändert sich nicht

	cout << "\nNeuron erzeugt ...";
}

CNeuron::~CNeuron()
{
	cout << "\nNeuron zerstört ...";
}
	
void CNeuron::setEingabe(double eing)
{
	eingabe = eing;
}

void CNeuron::setAktzustand(double zustand)
{ 
	aktzustand = zustand;
}

void CNeuron::setAusgabe(double ausg)
{
	ausgabe = ausg;
}

double CNeuron::getEingabe()
{
	return eingabe;
}

double CNeuron::getAktzustand()
{
	return aktzustand;
}

double CNeuron::getAusgabe()
{
	return ausgabe;
}

void CNeuron::berechneAusgabe()
{
	double net = eingabe - aktzustand;
	ausgabe = 1.0/(1.0 + exp(-K * net));
}

void CNeuron::berechneNeuron()
{
	berechneAusgabe();
  (this->*berechneAktzustand)();
}

void CNeuron::changeAktFunction(void (CNeuron::*aktFunction)())
{
	berechneAktzustand = aktFunction;
}

void CNeuron::aktFunction1()
{
	// Aktivierungszustand bleibt unverändert
}

void CNeuron::aktFunction2()
{
	aktzustand = (eingabe - aktzustand)/3.0 + aktzustand;
	// Aktivierungszustand wird der Eingabe angenaehert
}

void CNeuron::aktFunction3()
{
	aktzustand = eingabe;
	// Aktivierungszustand wird gleich der letzten Eingabe gesetzt
}
