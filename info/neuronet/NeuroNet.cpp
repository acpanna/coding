#include "NeuroNet.h"

using namespace std;

CNeuroNet::CNeuroNet(int neuroanz, int schichtanz, int *schichten, double **wmatrix, double **eingakt)
{
	bool check = false;
	int i, j, sum = 0;

	neuroanzahl = neuroanz;
	schichtanzahl = schichtanz;

	lernrate = 1.0;
	momentum = 1.0;

	neuron = new CNeuron[neuroanzahl];

	schicht = schichten;

	for (i=0; i<schichtanzahl; i++)
		sum += schicht[i];

	if (sum != neuroanzahl)
	{
		cerr << "\nDie Gesamtzahl der Neuronen stimmt nicht mit der Zahl der Neuronen im Schichtmuster ueberein !!!";
		exit(1);
	}
    
	weight = wmatrix;

	for (i=0; i<neuroanzahl; i++)
		for (j=0; j<neuroanzahl; j++)
			if (weight[i][j] != 0.0 && schichtCheck(i,j) == false)
			{
				weight[i][j] = 0.0;
				check = true;
			}
		
	if (check == true)
		cout << "\nDie Gewichtsmatrix wurde an das Schichtmuster angeglichen ...";

	for (i=0; i<neuroanzahl; i++)
	{
		getNeuron(i)->setEingabe(eingakt[i][0]);
		getNeuron(i)->setAktzustand(eingakt[i][1]);
	}
	
	cout << "\nNeuroNet erzeugt ...";
}

CNeuroNet::	CNeuroNet(int neuroanz, int schichtanz, int *schichten, double **wmatrix)
{
	bool check = false;
	int i, j, sum = 0;

	neuroanzahl = neuroanz;
	schichtanzahl = schichtanz;

	lernrate = 1.0;
	momentum = 1.0;

	neuron = new CNeuron[neuroanzahl];

	schicht = schichten;

	for (i=0; i<schichtanzahl; i++)
		sum += schicht[i];

	if (sum != neuroanzahl)
	{
		cerr << "\nDie Gesamtzahl der Neuronen stimmt nicht mit der Zahl der Neuronen im Schichtmuster ueberein !!!";
		exit(1);
	}
    
	weight = wmatrix;

	for (i=0; i<neuroanzahl; i++)
		for (j=0; j<neuroanzahl; j++)
			if (weight[i][j] != 0.0 && schichtCheck(i,j) == false)
			{
				weight[i][j] = 0.0;
				check = true;
			}
		
	if (check == true)
		cout << "\nDie Gewichtsmatrix wurde an das Schichtmuster angeglichen ...";

	cout << "\nNeuroNet erzeugt ...";
}

CNeuroNet::~CNeuroNet()
{
	delete [] neuron;
	cout << "\nNeuroNet zerstört ...\n";
}

void CNeuroNet::printNeurons()
{
	for (int i=0; i<neuroanzahl; i++)
		cout << "\nNeuron: " << i << ",\tEingabe: " << neuron[i].getEingabe() <<",\tAktivierungszustand: " << neuron[i].getAktzustand() << ",\tAusgabe: " << neuron[i].getAusgabe();
}

void CNeuroNet::changeLernrate()
{
	lernrate = lernrate - lernrate/10000.0;
}

void CNeuroNet::changeMomentum()
{ 
	momentum = momentum;
}

void CNeuroNet::changeWeight(double *ausgaben)
{
	int i, j;
	double *delta;

	delta = (double *) new double[neuroanzahl];
	assert(delta);
	
	for (i=neuroanzahl-1; i>=neuroanzahl-schicht[schichtanzahl-1]; i--)
		delta[i] = (ausgaben[i-neuroanzahl+schicht[schichtanzahl-1]] - getNeuron(i)->getAusgabe()) * K * getNeuron(i)->getAusgabe() * (1.0 - getNeuron(i)->getAusgabe());
		
	for (i=neuroanzahl-schicht[schichtanzahl-1]-1; i>=0; i--)
	{
		for (j=i; j<neuroanzahl; j++)
			delta[i] += delta[j] * weight[i][j];
		
		delta[i] *= K * getNeuron(i)->getAusgabe() * (1.0 - getNeuron(i)->getAusgabe());
	}

	for (i=0; i<neuroanzahl; i++)
		for (j=0; j<neuroanzahl; j++)
			if (schichtCheck(i,j) == true)
				weight[i][j] = weight[i][j] * momentum + lernrate * delta[j] * getNeuron(i)->getAusgabe();

	delete [] delta;
}

CNeuron * CNeuroNet::getNeuron(int number)
{
	return &(neuron[number]);
}

void CNeuroNet::setEingaben(double *eingaben)
{	
	for (int i=0; i<schicht[0]; i++)
		getNeuron(i)->setEingabe(eingaben[i]);
}

void CNeuroNet::berechneTakt()
{
	int i, j;

	for (i=0; i<neuroanzahl; i++)
		neuron[i].berechneNeuron();
	
	for (i=0; i<neuroanzahl; i++)
	{
		double sum = 0.0;
	
		for (j=0; j<neuroanzahl; j++)
			sum += weight[j][i] * neuron[j].getAusgabe(); // Eingabeberechnung für i-tes Neuron aus dem Produkt der transponierten Gewichtsmatrix mit dem Ausgabenvektor der Neuronen

		neuron[i].setEingabe(sum);
	}
}

bool CNeuroNet::schichtCheck(int zeile, int spalte)
{
	int i, sum = 0;

	for (i=0; i<schichtanzahl; i++)
	{
		sum += schicht[i];

		if (zeile < sum)
		{
			if (spalte >= sum)
				if (spalte < sum + schicht[i+1])
					return true;

			return false;
		}
	}

	cerr << "\nEin Fehler ist aufgetreten, es wurden fehlerhafte Daten an die Funktion schichtCheck() uebergeben !!!";
	exit(1);
}

void CNeuroNet::trainNet(double *eingaben, double *ausgaben)
{
	int i, j;
	bool learned;
	
	while (1)
  {
		learned = true;
		
		for (j=0; j<schichtanzahl; j++)
		{
	    setEingaben(eingaben);
	    berechneTakt();
	  }
				
		for (i=neuroanzahl-schicht[schichtanzahl-1]; i<neuroanzahl; i++)
			if (fabs(getNeuron(i)->getAusgabe() - ausgaben[i-neuroanzahl+schicht[schichtanzahl-1]]) > TOLERANCE)
			{
			  learned = false;
				break;
			}
		
		if (learned == true)
			break;
	
		changeWeight(ausgaben);
		changeLernrate();
		changeMomentum();
	}
			
	//cout << "\nNetz wurde auf das (Eingaben, Ausgaben) - Paar trainiert ...";
}

void CNeuroNet::trainNet(CPattern *pat)
{
  int i, j;

  while(1)
  {
    bool learned = true;

  	for (i=0; i<(pat->patternanzahl); i++)
    	trainNet(pat->vorgaben[i], pat->ausgaben[i]);

  	for (i=0; i<(pat->patternanzahl); i++)
  	{
  	  for (j=0; j<schichtanzahl; j++)
  	  {
    	  setEingaben(pat->vorgaben[i]);
        berechneTakt();
      }
          	
    	for (j=neuroanzahl-schicht[schichtanzahl-1]; j<neuroanzahl; j++)
				if (fabs(getNeuron(j)->getAusgabe() - pat->ausgaben[i][j-neuroanzahl+schicht[schichtanzahl-1]]) > TOLERANCE)
			  	learned = false;

			if (learned == false)
		  	break;
		  else
		  {
		    cout << "\nNetz wurde auf das vorgegebene Pattern trainiert (Toleranz: " << TOLERANCE << ") ...";
		    return;
		  }
		}
	
		continue;
	}
} 	

void CNeuroNet::printAusgabe()
{
  cout << "Ausgabe des Netzes: ";

  for (int i=neuroanzahl-schicht[schichtanzahl-1]; i<neuroanzahl; i++)
    cout << getNeuron(i)->getAusgabe() << " ";
}


