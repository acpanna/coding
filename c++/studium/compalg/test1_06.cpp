#include "compalg1.h"
#include <vector>
#include <cmath>

int input(char *argv, vector<vector<int> >& matrix);
void get_primes(int length, vector<int>& primes);
int det(vector<vector<int> > const& matrix);
void output(const vector<vector<int> >& matrix);
long long det_naive(vector<vector<long long> >& matrix);
void input_naive(char *argv, vector<vector<long long> >& matrix);
void output_naive(vector<vector<long long> > const& matrix);

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "\n\tSyntax: \"test1_06 [p | d] [<datei> | <Anzahl>]\" "
		<< "\n\tp	-	Generiert beliebig viele Primzahlen"
		<< "\n\td	-	Berechnet eine ganzzahlige Determinante mit Hilfe des chinesischen Restsatzes"
		<< "\n\tn	-	Berechnet ebenfalls det(A) allerdings auf naive Weise"
		<< "\n\t<datei>	-	enthaelt eine nxn Matrix mit ganzzahligen Eintraegen"
		<< "\n\t<Anzahl>-	Anzahl der gewünschten Primzahlen\n"
		<< endl;
		exit(1);
	}

	if (string(argv[1]) == "p")
		{
			int nop;
			vector<int> primes;

			nop = atoi(argv[2]);
			get_primes(nop, primes);

			for (int i=0; i<nop; i++)
			{
				cout << primes[i];
				if (i != nop-1)	cout << ", ";
			}
		}
	else if (string(argv[1]) == "d")
		{
			vector<vector<int> > matrix;

			//Hier wird die Matrix eingelesen.
			input(argv[2], matrix);

			//Ausgabe der Matrix
			cout << "\nDie eingebene Matrix A mit Eintraegen aus Z:" << endl;
			output(matrix);
			cout << endl;

			//Ausgabe des Werts der tatsaechlichen Determinante in Z.
			cout << "\nDie Determinante der eingebenen Matrix ist " << det(matrix) << " ." << endl;
		}
	else if (string(argv[1]) == "n")
		{
			vector<vector<long long> > matrix;

			//Hier wird die Matrix eingelesen.
			input_naive(argv[2], matrix);

			//Ausgabe der Matrix
			cout << "\nDie eingebene Matrix A mit Eintraegen aus Z:" << endl;
			output_naive(matrix);
			cout << endl;

			//Ausgabe des Werts der tatsaechlichen Determinante in Z.
			cout << "\nDie Determinante der eingebenen Matrix ist " << det_naive(matrix) << " ." << endl;
		}
	else	cout << "Bitte ueberpruefen Sie die Eingabe.";

	cout << endl;

	return 0;
}
