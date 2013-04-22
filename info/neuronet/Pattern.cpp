#include "Pattern.h"

using namespace std;

CPattern::CPattern(int panzahl, int vbreite, int abreite, double **vgabe, double **agabe)
{
  patternanzahl = panzahl;
  vorgabenbreite = vbreite;
  ausgabenbreite = abreite;
  vorgaben = vgabe;
  ausgaben = agabe;
}

void CPattern::printVorgabe(int number)
{
  cout << "Vorgabepattern: ";

  for (int i=0; i<vorgabenbreite; i++)
    cout << vorgaben[number][i] << " ";
}

void CPattern::printAusgabe(int number)
{
  cout << "Ausgabepattern: ";

  for (int i=0; i<ausgabenbreite; i++)
    cout << ausgaben[number][i] << " ";
}
