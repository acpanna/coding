#include <iostream.h>

class CPattern
{
public:
	int patternanzahl;
	int vorgabenbreite;
	int ausgabenbreite;

	double **vorgaben;
	double **ausgaben;

public:
	CPattern(int panzahl, int vbreite, int abreite, double **vgabe, double **agabe);

	void printVorgabe(int number);
	void printAusgabe(int number);
};
