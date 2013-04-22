#include "globals.h"
#include "matrix.h"

#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void usage(char *prg);

int main(int argc, char **argv)
{
	char ch, buff[4096], *ptr;
	string istr, nstr, params;
	long i, j, N;

	if (argc > 3 || argc < 2) 
		usage(argv[0]);

	for (i=1; i<argc; i++) {
	
		if (strncmp(argv[i], "--help", 6) == 0 || strncmp(argv[i], "-h", 2) == 0)
			usage(argv[0]);
		else if (strncmp(argv[i], "-", 1) == 0) {
			usage(argv[0]);
		} else 
			istr = argv[i];
	}

#ifdef INF_DTYPE
	NTL::RR::SetPrecision(prec);
	prec = NTL::RR::precision();

	if (prec < PRECISION)
		ERROR("Please use a precision >= " << PRECISION);

	NTL::RR::SetOutputPrecision(EXT_OUT_PRECISION);
#endif

	strncpy(buff, argv[argc-1], 4096);
	ptr = strstr(buff, ".sol");

	if (!ptr) 
		usage(argv[0]);
	
	*ptr = 0;
	istr = string(buff);

	ifstream fin_sol(argv[argc-1]);
	if (!fin_sol.good()) {
		cerr << "The solution file [ " << argv[argc-1] << " ] can't be opened!";
		cerr << endl;
		return 1;
	}

	nstr = istr + string(".ntru");

	ifstream fin_ntru(nstr.c_str());
	if (!fin_ntru.good()) {
		cerr << "The ntru file [ " << nstr << " ] can't be opened!";
		cerr << endl;
		return 1;
	}

	REAL tmp_real;
	Vector<REAL> tmp_vec, F, g, Fg, sol, x, x1;

	fin_ntru >> tmp_real;
	fin_ntru >> tmp_real;
	fin_ntru >> tmp_real;

	fin_ntru >> tmp_vec;
	N = tmp_vec.N; // get the dimension from the P-polynom
	fin_ntru >> tmp_vec;

	fin_ntru >> F;

	fin_ntru >> tmp_vec;
	fin_ntru >> tmp_vec;

	fin_ntru >> g;

	fin_ntru.close();

	Fg.resize(2*N);

	for (j=1; j<=F.N; j++)
		Fg[j] = F[j];
	for (j=F.N+1; j<=N; j++)
		Fg[j] = 0;

	for (j=1; j<=g.N; j++)
		Fg[j + N] = g[j];
	for (j=N+g.N+1; j<=2*N; j++)
		Fg[j] = 0;

	while (1) {

		ch = fin_sol.peek();
		while (ch != '[') {
			if (fin_sol.eof()) {
				fin_sol.close();
				return 0;
			}

			fin_sol.get();
			ch = fin_sol.peek();

			if (ch == '|') 
				getline(fin_sol, params);
			
			ch = fin_sol.peek();
		}

		fin_sol >> x;

		if (x == Fg) 
			cout << ext_prec << x << endl;
		else {
			cerr << ext_prec << "x  = " << x << endl;
			cerr << ext_prec << "Fg = " << Fg << endl;

			cerr << ext_prec << "This solution is incorrect!" << endl;
		}
	}

	return 0; // is never reached
}

void usage(char *prg) 
{
	cerr << prg << " file.sol";
	cerr << endl;
	exit(1);
}
