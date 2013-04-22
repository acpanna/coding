#include "compalg1.h"
#include <fstream>
#include <iomanip>

#define VERBOSE

//Wie euklid, nur mit Datentyp long long.
int euklid_long(long long x1, long long x2, long long& a, long long& b) {
  long long a1,b1, a2,b2, p;
  a1=1; b1=0;
  a2=0; b2=1;
  while(x2!=0) {
    p=x1/x2;
    a1-=p*a2; swap(a1,a2);
    b1-=p*b2; swap(b1,b2);
    x1-=p*x2; swap(x1,x2);
  }
  a=a1; b=b1; return x1;
}

//Einlesefunktion für eine ZxZ-Matrix (im Gegensatz zu den sonst betrachteten Matrizen über K := Fp<5>)
void input(char *argv, vector<vector<int> >& matrix)
{
	int rows, cols, entry;
	ifstream in (argv);

	in >> rows;
	in >> cols;

	vector<int> row_vector;

	for (int col_pos = 0; col_pos < cols; col_pos++)
	{
		for (int row_pos = 0; row_pos < rows; row_pos++)
		{
			in >> entry;
			row_vector.push_back(entry);
		}
		matrix.push_back(row_vector);
		row_vector.clear();
	}
}

//Gibt den betragsgroessten Eintrag einer Matrix zurueck.
int get_max(vector<vector<int> > matrix)
{
	int n = matrix.size();
	int max = 0;

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (abs(matrix[i][j]) > max)	max = abs(matrix[i][j]);
		}
	}

	return max;
}

void output(const vector<vector<int> >& matrix)
{
	int n = matrix.size();
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << setw(4) << matrix[i][j];
			if (j == n-1)	cout << "\n";
		}
	}
}

//Fuellt einen vector mit Primzahlen.
void get_primes(int length, vector<int>& primes)
{
	int interval = 0, k, count = 0;
	double estimated_primes;

	//Bestimmung eines Intervals, in dem ausreichend viele Primzahlen vorhanden sind.
	do
	{
		interval += length;
		estimated_primes = interval/log( (double) interval);
	} while (estimated_primes < length);

	//Workaround, da die Abschaetzung zuvor ein zu kleines Interval fuer 2 liefert. 
	if (length == 2)	interval = 4;

	//Sieb des Eratosthenes zur Primzahlenbestimmung
	bool flags[interval];

	for (int i=2; i<interval; i++)
		flags[i] = 1;

	flags[1] = 0;
	primes.push_back(2);

	for (int i=1; i<interval; i+=2)
	{
		if (flags[i] != 0)
		{
			primes.push_back(i);
			k = i+i;
				while (k < interval)
				{
					flags[k] = 0;
					k += i;
				}
		}
	}
	primes.resize(length);
}

//Spaltenpivotsuche, allerdings wird hier lediglich ein Element ungleich Null gesucht.
int pivot(const vector<vector<int> >& matrix, int col, int step)
{
	int i = step;
	int n = matrix.size();

	while ( (i < n) && (matrix[i][col] == 0) )
	{
		i++;
	}

	if (i == n)	return -1;
	else		return i;
}

//Rueckgabe der Determinante in Z[p]
int det_mod_p(vector<vector<int> >& matrix, int prime)
{
	int n = matrix.size(), count_swap = 0, det = 1, factor, a, b;

	for (int i=0; i<n-1; i++)
	{
		int piv = pivot(matrix, i, i);

		if (piv == -1)	return 0;

		if (piv != i)
		{
			swap(matrix[i], matrix[piv]);
			count_swap++;
		}

		for (int j=i+1; j<n; j++)
		{
			euklid(matrix[i][i], prime, a, b);
			factor = (a*matrix[j][i]);
			for (int k=i; k<n; k++)
			{
				matrix[j][k] = (matrix[j][k] - factor*matrix[i][k]) % prime;
				if ( matrix[j][k] < 0 )	matrix[j][k] +=prime;
			}
		}
	}

	#ifdef VERBOSE
		//Ausgabe der pivotisierten Matrix.
		cout << "\nA mod " << prime << ", trigonalisiert:" << endl;
		output(matrix);
	#endif

	for (int i=0; i<n; i++)
	{
		det = (det * matrix[i][i]) % prime;
	}

	if ( (count_swap % 2) != 0 )	det *= (-1);

	if (det < 0)	det += prime;

	return det;
}

//Teilt die Eintraege einer Matrix modulo einer Primzahl & gibt die Determinante der entstandenen Matrix aus.
int mod_matrix(vector<vector<int> > matrix, int prime)
{
	int n = matrix.size();

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			matrix[i][j] %= prime;
			if ( matrix[i][j] < 0)	matrix[i][j] += prime;
		}
	}

	return (det_mod_p(matrix, prime));
}

//Berechnet aus gegebenen Resten, die Zahl, welche nach Modulo-Teilung mit Primzahlen diese Reste ergeben wuerde.
int chinese(const int primes[], vector<int> & remainders)
{
	int t = remainders.size();
	long long n0, n1, z, x0, x1, a, b;

	x0 = remainders[0];	n0 = primes[0];

	for (int i=1; i<t; i++)
	{
		euklid_long(n0, primes[i], a, b);
		z = ((remainders[i] - x0)*a) % primes[i];
		x1 = x0 + z*n0;
		n1 = n0*primes[i];
		x0 = x1;
		n0 = n1;
	}

	return x0;
}

//Berechnet die Determinante einer uebergegebenen Matrix.
int det(vector<vector<int> > const& matrix)
{
	const int primes[19] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
	vector<int> remainders;
	int n = matrix.size(), rem, max = get_max(matrix), r = 0;
	long long C, M = 1;

	//Hadamardsche Ungleichung, um die Determinante nach oben abzuschaetzen
	C = (long long) (pow( (double) n, ( (double) n/2 )) * pow( (double) max, (double) n));

	while (M < C)
	{
		M *= primes[r];
		r++;
		if (r > 19)	{cout << "\nErfordert spezielle Langzahlarithmetik.\n";	exit(1);}
	}	//Schleife zur Bestimmung der benoetigten Primzahlen.

	//Der vector remainders wird mit den Determinanten der nach modulo-Teilung
	//mit einer Primzahl entstandenen Matrix gefuellt.
	for (int i=0; i<r; i++)
	{
		rem = mod_matrix(matrix,primes[i]);
		#ifdef VERBOSE
			cout << "\ndet(A) mod " << primes[i] << ": " << rem << endl;
		#endif
		remainders.push_back(rem);
	}

	return chinese(primes,remainders);
}

//########################################################################################
//	Naive Implementation gaussscher Elimination zur Determinantenberechnung.
//########################################################################################

void input_naive(char *argv, vector<vector<long long> >& matrix)
{
	int rows, cols;
	long long entry;
	ifstream in (argv);

	in >> rows;
	in >> cols;

	vector<long long> row_vector;

	for (int col_pos = 0; col_pos < cols; col_pos++)
	{
		for (int row_pos = 0; row_pos < rows; row_pos++)
		{
			in >> entry;

			row_vector.push_back(entry);
		}

		matrix.push_back(row_vector);
		row_vector.clear();
	}
}

void output_naive(vector<vector<long long> > const& matrix)
{
	int n = matrix.size();

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << setw(10) << setprecision(2) << matrix[i][j];
			if (j == n-1)	cout << "\n";
		}
	}
}

int pivot_naive(vector<vector<long long> > const& matrix, int col, int step)
{
	int i = step;
	int n = matrix.size();

	while ( (i < n) && (matrix[i][col] == 0) )
	{
		i++;
	}

	if (i == n)	return -1;
	else		return i;
}

long long det_naive(vector<vector<long long> > & matrix)
{
	int n = matrix.size(), count_swap = 0;
	long long factor, det = 1;
	vector<long long> save;

	for (int i=0; i<n-1; i++)
	{
		int piv = pivot_naive(matrix, i, i);

		if ( piv == -1 )	exit(1);
		else
		{
			if (piv != i)
			{
				swap(matrix[i], matrix[piv]);
				count_swap++;
			}

			for (int j=i+1; j<n; j++)
			{
				factor = matrix[j][i];
				//Hier werden die Koeffizienten abgespeichert, womit Zeilen multipliziert werden.
				save.push_back(matrix[i][i]);
				for (int k=i; k<n; k++)
				{
					matrix[j][k] = matrix[j][k]*matrix[i][i] - matrix[i][k]*factor;
				}
			}
		}
		cout << endl;
		output_naive(matrix);
		cout << endl;
	}

	for (int i=0; i<n; i++)
	{
		det *= matrix[i][i];
	}

	for (int i=0; i<save.size(); i++)
	{
		det /= save[i];
	}

	if ( (count_swap % 2) != 0 )	det *= (-1);

	return det;
}
