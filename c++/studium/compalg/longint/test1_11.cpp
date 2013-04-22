#include "rational.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void usage(char *name)
{
	cout << "Testprogramm fuer die Klassen LongInt und Rational\n";
	cout << "Aufruf:\n";
	cout << "\t" << name << " 1 (nicht-interaktive Ausgabe)\n";
	cout << "\t" << name << " 2 (interaktive Ausgabe)\n";
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc != 2) 
		usage(argv[0]);
	
	if (atoi(argv[1]) == 1) 
	{ 
		LongInt l1("10");
		LongInt l2("566124323757458643794");
 		LongInt l3("-1256447655");
		Rational r1("1/2");
		Rational r2("-1/4");
		Rational r3("3/-5");
		Rational r4("4676765623/96323898567545645");
		Rational r5;
		cout << "l1 = " << l1 << endl;
		cout << "l2 = " << l2 << endl;
		cout << "l3 = " << l3 << endl;
		cout << "r1 = " << r1 << endl;
		cout << "r2 = " << r2 << endl;
		cout << "r3 = " << r3 << endl;
		cout << "r4 = " << r4 << endl << endl;
		cout << "l1 == l1 : " << (l1==l1) << endl;
		cout << "l1 == l2 : " << (l1==l2) << endl;
		cout << "l1 != l1 : " << (l1!=l1) << endl;
		cout << "l1 != l2 : " << (l1!=l2) << endl << endl;
		cout << "r1 + r2 = " << (r1+r2) << endl;
		cout << "r1 - r3 = " << (r1-r3) << endl;
		cout << "r1 * r4 = " << (r1*r4) << endl;
		cout << "r2 / r3 = " << (r2/r3) << endl;
		Rational::pow(r2, l1, r5);
		cout << "pow(r2, l1) = " << r5 << endl;
		cout << "r3 * l3 = " << (r3 * l3) << endl;
		cout << "r4 + l2 = " << (l2 + r4) << endl;
		cout << "r1 + r2 * r3 = " << (r1 + r2 * r3) << endl;
		cout << "r2 * r3 + r1 = " << (r2 * r3 + r1) << endl;
		cout << "r2 * (r3 + r1) = " << (r2 * (r3 + r1)) << endl;
		cout << "l2 / l3 = " << (l2/l3) << endl;
		cout << "l2 % l3 = " << (l2%l3) << endl;
		cout << "(l2/l3)*l3 + (l2%l3)  = "; 
		cout << ((l2/l3)*l3 + (l2%l3)) << endl;

	} else if (atoi(argv[1]) == 2) {
		char op;
		Rational r1, r2;
		cout << "Bitte die erste Zahl eingeben: ";
		cin >> r1;
		cout << "Bitte die zweite Zahl eingeben: ";
		cin >> r2;
		cout << "Gewuenschte Berechnung (+, -, *, /): ";
		cin >> op;
		switch (op)
		{
			case '+': 	cout << "Ergebnis: " << (r1+r2) << endl;
					break;
			case '-': 	cout << "Ergebnis: " << (r1-r2) << endl;
				  	break;
			case '*': 	cout << "Ergebnis: " << (r1*r2) << endl;
				  	break;
			case '/': 	cout << "Ergebnis: " << (r1/r2) << endl;
				  	break;
			default:  	cerr << "Fehlerhafte Eingabe ";
					cerr << "-- Abbruch" << endl;
					exit(1);
		}
	} else
		usage(argv[0]);

	return 0;
}
