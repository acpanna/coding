#include "globals.h"
#include "matrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#define BUFFER 4096

using namespace std;

void usage(char *str) 
{
	ERROR("Usage: " + string(str) + " *.code [--slacks=0|1]");
}

int main(int argc, char **argv)
{
	register long i, j;
	
	long slacks = 0; // 1

	char buff[BUFFER], *ptr;
	string istr, ostr;

	Matrix<REAL> A_g, A_u;
	Vector<REAL> o;
	Vector<REAL> b_g;
	Vector<REAL> l_u, r_u, l_x, r_x;

	long n, d;

	if (argc < 2 || argc > 3)
		usage(argv[0]);

	for (i=1; i<argc; i++) {

		if (strncmp(argv[i], "--slacks=", 9) == 0) {
			strcpy(buff, argv[i]+9);
			istringstream iss(buff, istringstream::in);
			iss >> slacks;
		} else if (strncmp(argv[i], "-", 1) == 0) 
			usage(argv[0]);
		else 
			istr = argv[i];
	}

	strncpy(buff, istr.c_str(), BUFFER);
	ptr = strstr(buff, ".code");
	if (ptr == NULL) 
		usage(argv[0]);
	*ptr = 0;

	ostr = string(buff) + string(".prb");

	ifstream fin(istr.c_str());
	if (!fin.good())
		ERROR("The input file [ " + istr + " ] could not be opened!");

	ofstream fout(ostr.c_str());
	if (!fout.good())
		ERROR("The output file [ " + ostr + " ] could not be opened!");

	fin >> A_g;
	fin >> o;
	fin >> n;
	fin >> d;
	
	fin.close();

	if (slacks) {

		A_g.resize(A_g.M, A_g.N+A_g.M);

		for (i=1; i<=A_g.M; i++)
			for (j=A_g.N-A_g.M+1; j<=A_g.N; j++) {
				if (i+A_g.N-A_g.M == j)
					A_g[i][j] = -1;
				else
					A_g[i][j] = 0;
			}
	} 

	A_g.resize(A_g.M+1, A_g.N);
	for (j=1; j<=o.N; j++)
		A_g[A_g.M][j] = o[j];

	b_g.resize(A_g.M);

	if (slacks)
		for (i=1; i<A_g.M; i++)
			b_g[i] = 0;
	else
		for (i=1; i<A_g.M; i++)
			b_g[i] = n-d;	

	b_g[A_g.M] = n;

	l_x.resize(A_g.N);
	r_x.resize(l_x.N);

	for (j=1; j<=A_g.M-1; j++) {
		l_x[j] = 0;
		r_x[j] = 1;
	}
	
	for (j=A_g.M; j<=r_x.N; j++) {
		l_x[j] = 0;
		r_x[j] = n-d;
	}
	
	if (slacks) {

		A_u.resize(0);
		l_u.resize(0);
		r_u.resize(0);

	} else {

		A_u = A_g;
		A_u.resize(A_u.M - 1);
		
		A_g[1] = A_g[A_g.M];
		A_g.resize(1);

		r_u = b_g;
		r_u.resize(r_u.N - 1);
		
		b_g[1] = b_g[b_g.N];
		b_g.resize(1);
		
		l_u.resize(r_u.N);
		l_u.clear();
	}
	
	fout << ext_prec << "[ ]" << endl; // od_t
	fout << ext_prec << "[\n]" << endl; // A_t
	fout << endl;
	fout << ext_prec << A_g << endl;
	fout << ext_prec << b_g << endl;
	fout << endl;
	fout << ext_prec << A_u << endl;
	fout << ext_prec << l_u << endl;
	fout << ext_prec << r_u << endl;
	fout << ext_prec << endl;
	fout << ext_prec << "[ ]" << endl; // dp_x
	fout << ext_prec << l_x << endl;
	fout << ext_prec << r_x << endl;
	fout << ext_prec << endl;
	
	fout << endl << "// odt, At -- Ag, bg -- Au, lu, ru -- dpx, lx, rx" << endl;

	fout.close();

	return 0;
}
