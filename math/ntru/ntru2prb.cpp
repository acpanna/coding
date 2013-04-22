#include <NTL/ZZ_pX.h> 
#include <NTL/ZZX.h> 
#include <NTL/LLL.h>

#include <sstream> 
#include <fstream> 
#include <cstring> 

#include "matrix.h"

using namespace std;

void usage(char *str) 
{
	ERROR("Usage: " + string(str) + " *.ntru");
}

int main(int argc, char **argv)
{
	char buff[1024], *ptr;
	string istr, ostr;

	if (argc != 2)
		usage(argv[0]);

	istr = argv[1];

	buff[0] = 0;
	strcat(buff, istr.c_str());
	ptr = strstr(buff, ".ntru");
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

	long i, j, n, df, dg;

	NTL::mat_ZZ A_g;
	NTL::vec_ZZ b_g;

	NTL::ZZ q, N1, N2;

	fin >> df;
	fin >> dg;
	fin >> q;
	
	NTL::ZZ_p::init(q);
	NTL::ZZ_pX P, h, hP, modul;
	
	fin >> P;
	fin >> h;
	
	fin.close();

	n = NTL::deg(h)+1; 
	N1 = n;
	N2 = 10*N1;
	
	NTL::SetCoeff(modul, n, 1);
	NTL::SetCoeff(modul, 0, -1);
	NTL::MulMod(hP, h, P, modul);

	A_g.SetDims(n+2, 3*n);
	b_g.SetLength(n+2);

	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++) {
			A_g(j, i) = NTL::rep(NTL::coeff(h, j-1));

			A_g(n+1, j) = 1;
			A_g(n+2, j+n) = 1;
		}

		NTL::MulByXMod(h, h, modul);
		
		A_g(i, i+n) = -1;
		A_g(i, i+2*n) = q;

		b_g(i) = -NTL::rep(NTL::coeff(hP, i-1));
	}
		
	b_g(n+1) = df;
	b_g(n+2) = dg;

	Matrix<REAL> A_u;
	Vector<REAL> l_u, r_u, l_x, r_x;

	A_u.resize(0);
	l_u.resize(0);
	r_u.resize(0);

	l_x.resize(2*n);
	r_x.resize(2*n);
	for (j=1; j<=r_x.N; j++) {
		l_x[j] = 0;
		r_x[j] = 1;
	}

	fout << ext_prec << A_u << endl;
	fout << endl;
	fout << ext_prec << A_g << endl;
	fout << endl;
	fout << ext_prec << l_u << endl;
	fout << endl;
	fout << ext_prec << r_u << endl;
	fout << endl;
	fout << ext_prec << b_g << endl;
	fout << endl;
	fout << ext_prec << l_x << endl;
	fout << endl;
	fout << ext_prec << r_x << endl;
	fout << endl;
	
	fout << 1 << endl;
	
	fout << endl << "// A_u, A_g, l_u, r_u, b_g, l_x, r_x, aardal" << endl;

	fout.close();

	return 0;
}
