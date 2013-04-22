#include "knoten.h"
#include <iostream>

using namespace std;

#define ASSERT(x)  if(x == NULL) { cout << "Speicherreservierung fehlgeschlagen -- Programmabbruch" << endl; exit(1); } 

Knoten::Knoten()
{
  nachbarn = 0;
  kante = NULL;
  bewertung = 0.0;
}

Knoten::Knoten(int *nachbarliste)
{
  int i, j;
  nachbarn = nachbarliste[0];

  kante = new Kante[nachbarn];
  ASSERT(kante);

  for (i=0; i<nachbarn; i++)
  {
    for (j=0; j<i; j++)
      if (kante[j].getZiel() == nachbarliste[i+1])
      {
	cerr << "Knoten(int*): Jeder Knoten v darf mit jedem Knoten w "
	  "lediglich eine einzige Kante  v --> w  haben" << endl; 
	exit(1);
      }
    
    kante[i].setZiel(nachbarliste[i+1]);
  }
    
  bewertung = 0.0;
}

Knoten::~Knoten()
{
  delete [] kante;
  kante = NULL;
}

void Knoten::operator=(const Knoten &rechts)
{
  int i;
  if (nachbarn < rechts.nachbarn)
  {
    delete [] kante;
    kante = new Kante[rechts.nachbarn];
    ASSERT(kante);
  }
  
  nachbarn = rechts.nachbarn;

  for (i=0; i<nachbarn; i++)
    kante[i] = rechts.kante[i];
}

bool Knoten::hatNachbar(const int &nachbar) const 
{
  int i;
  for (i=0; i<nachbarn; i++)
    if (kante[i].getZiel() == nachbar)
      return true;

  return false;
}

void Knoten::loescheNachbar(const int &nachbar)
{
  int i;
  for (i=0; i<nachbarn; i++)
    if (kante[i].getZiel() == nachbar)
    {
      kante[i] = kante[nachbarn-1];
      nachbarn--;
      return;
    }
} 

void Knoten::aendereNachbar(const int &nachbar, const double &weight)
{
  int i;

  for (i=0; i<nachbarn; i++)
    if (kante[i].getZiel() == nachbar)
    {
      kante[i].setBewertung(weight);
      return;
    }
  
  Kante *newkante = new Kante[nachbarn+1];
  ASSERT(newkante);
  
  for (i=0; i<nachbarn; i++)
    newkante[i] = kante[i];

  newkante[nachbarn].setZiel(nachbar);
  newkante[nachbarn].setBewertung(weight);
  
  delete [] kante;
  kante = newkante;
  nachbarn++;
}

void Knoten::printKnoten() const
{
  int i;
  for (i=0; i<nachbarn; i++)
    cout << " " << kante[i].getZiel();

  cout << endl;
}
