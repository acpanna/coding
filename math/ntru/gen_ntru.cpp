#include <NTL/ZZX.h> 
#include <fstream>
#include <sstream> 
#include <cstring>

#include "error.h"
#include "functions.h"
#include "globals.h"

#define LIMIT 1000

using namespace std;

void usage(char *str) 
{
	ERROR("Usage: " + string(str) + " --N=* --q=* --df=* --dg=* file.ntru");
}

void Generate01Vec(NTL::ZZ_pX &vec, unsigned long einsen, unsigned long n);
NTL::ZZ_pX ComputeInverse(NTL::ZZ_pX const &A, unsigned long N, 
		unsigned long q);

int main(int argc, char *argv[])
{
	long i;
	unsigned long j = 0, N, q, df, dg;
	char suffix[1024], *ptr;
	string ostr;

	if (argc != 6) 
		usage(argv[0]);

	for (i=1; i<argc; i++) {
		if (strncmp(argv[i], "--N=", 4) == 0) {
			strcpy(suffix, argv[i]+4);
			istringstream iss(suffix, istringstream::in);
			iss >> N;
		} else if (strncmp(argv[i], "--q=", 4) == 0) {
			strcpy(suffix, argv[i]+4);
			istringstream iss(suffix, istringstream::in);
			iss >> q;
		} else if (strncmp(argv[i], "--df=", 5) == 0) {
			strcpy(suffix, argv[i]+5);
			istringstream iss(suffix, istringstream::in);
			iss >> df;
		} else if (strncmp(argv[i], "--dg=", 5) == 0) {
			strcpy(suffix, argv[i]+5);
			istringstream iss(suffix, istringstream::in);
			iss >> dg;
		} else if (strncmp(argv[i], "-", 1) == 0) 
			usage(argv[0]);
		else 
			ostr = argv[i];
	}

	ptr = strstr(( char *) ostr.c_str(), ".ntru");

	if (ptr == NULL)
		usage(argv[0]);

	if (*(ptr+5) != 0)
		usage(argv[0]);

	ofstream fout(ostr.c_str());
	if (!fout.good())
		ERROR("The output file [ " + ostr + " ] could not be opened!");

	
	NTL::ZZ sum;

	NTL::ZZ_p::init(NTL::to_ZZ(q));
	NTL::ZZ_pX p, P, F, f, f_q, g, h, modul, tmp1, tmp2;

	NTL::SetCoeff(p, 1, 1);
	NTL::SetCoeff(p, 0, 2);

	NTL::SetCoeff(modul, N, 1);
	NTL::SetCoeff(modul, 0, -1);

	P = ComputeInverse(p, N, q);
	new_seed();

	// Generiere, solange zufällige F's mit
	// df Einsen, bis f invertiertierbar ist.
	for (j=0; j<LIMIT; j++) {
		Generate01Vec(F, df, N);
		NTL::MulMod(f, p, F, modul);
		f += 1;

		sum = 0;
		for (i=0; i<=NTL::deg(f); i++)
			sum = (sum + NTL::rep(NTL::coeff(f, i))) % q;
		if (sum == 0 || NTL::GCD(sum, NTL::to_ZZ(q)) != 1) 
			continue;

		f_q = ComputeInverse(f, N, q);
		NTL::MulMod(tmp1, f, f_q, modul);

		if (NTL::deg(tmp1) == 0 && NTL::coeff(tmp1, 0) == 1)
			break;
	}

	if (j == LIMIT) {
		cerr << ext_prec << "Unguenstige Parameter-Wahl --> Abbruch\n";
		return 1;
	}

	Generate01Vec(g, dg, N);

	// Generiere Public-Key h
	NTL::MulMod(h, p, f_q, modul);
	NTL::MulMod(h, h, g, modul);

	// Mache die Probe, ob wirklich gilt:
	//		hF + hP == g 
	NTL::MulMod(tmp1, h, F, modul);
	NTL::MulMod(tmp2, h, P, modul);

	tmp2 = tmp1 + tmp2;

	// Probe ist ok
	if (tmp2 == g) {
		fout << ext_prec << df << endl;
		fout << ext_prec << dg << endl;
		fout << endl;
		fout << ext_prec << q << endl << endl;
		fout << ext_prec << P << endl << endl;
		fout << ext_prec << h << endl << endl;
		fout << ext_prec << F << endl << endl;
		fout << ext_prec << f << endl << endl;
		fout << ext_prec << f_q << endl << endl;
		fout << ext_prec << g << endl << endl;

		fout << ext_prec << "// df, dg, q, P, h, F, f, f_q, g" << endl;
	} else 
		cerr << ext_prec << "Probe fehlgeschlagen --> Abbruch" << endl;

	fout.close();

	return 0;
}

void Generate01Vec(NTL::ZZ_pX &vec, unsigned long einsen, unsigned long n)
{
	unsigned long i, j;
	unsigned long *ziehungstrommel = new unsigned long[n];

	for (i=0; i<n; i++) 
		ziehungstrommel[i] = i;

	vec = 0;

	for (i=0; i<einsen; i++) {
		j = rand_eq_long(0, n-1);
		n = n-1; 
		NTL::SetCoeff(vec, ziehungstrommel[j], 1);
		ziehungstrommel[j] = ziehungstrommel[n];
	}

	delete [] ziehungstrommel;
}

// Dies ist die Implementierung des Almost-Inverse Algorithmus, 
// nach http://www.ntru.com/cryptolab/pdf/NTRUTech014.ps.gz
NTL::ZZ_pX ComputeInverse(NTL::ZZ_pX const &A, unsigned long N, unsigned long q)
{
	long i;
	unsigned long k;
	NTL::ZZX a, b, c, f, g, modul;

	NTL::SetCoeff(modul, N, 1);
	NTL::SetCoeff(modul, 0, -1);

	k = 0;
	a = to_ZZX(A);
	b = 1;
	c = 0;

	for (i=0; i<=NTL::deg(a); i++)   
		if ((NTL::to_int(NTL::coeff(a, i)) % 2) != 0) 
			NTL::SetCoeff(f, i, 1);

	NTL::SetCoeff(g, N, 1);
	NTL::SetCoeff(g, 0, -1);

	while (1) {
		while (NTL::coeff(f, 0) == 0) {
			f = f >> 1;
			c = c << 1;
			k++;	
		}

		if (f == 1) {
			b = (b << ((2*N - k) % N));
			b = b % modul;
			for (i=0; i<=NTL::deg(b); i++) 
				NTL::SetCoeff(b, i, NTL::coeff(b,i) % NTL::to_ZZ(2));
			break;
		}

		if (NTL::deg(f) < NTL::deg(g)) {
			NTL::swap(f, g);
			NTL::swap(b, c);
		}

		f = (f + g);
		for (i=0; i<=NTL::deg(f); i++)
			NTL::SetCoeff(f, i, NTL::coeff(f,i) % NTL::to_ZZ(2));

		b = (b + c);
		for (i=0; i<=NTL::deg(b); i++)
			NTL::SetCoeff(b, i, NTL::coeff(b,i) % NTL::to_ZZ(2));
	}

	k = 2;

	while (k < q) {
		k = k * k;
		b = b * (2 - a*b);

		for (i=0; i<=NTL::deg(b); i++) 
			NTL::SetCoeff(b, i, NTL::coeff(b,i) % NTL::to_ZZ(k));
	}

	return NTL::to_ZZ_pX(b % modul);
}
