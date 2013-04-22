#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>

int main(void)
{
  char datei[256];

  double **matrix;

  unsigned int i, j, N;

  cout << "\nBitte geben Sie den Wert fuer N ein : ";
  cin >> N;

  matrix = (double **) malloc((N+1)*sizeof(double));

  if (matrix == NULL)
  {
    cout << "\nNicht genuegend Speicher frei !!! Programmabbruch !";
    exit(1);
  }
  
  for (i=0; i<N+1; i++)
  {
    matrix[i] = (double *) malloc((N+1)*sizeof(double));

    if (matrix[i] == NULL)
    {
      cout << "\nNicht genuegend Speicher frei !!! Programmabbruch !";
      exit(1);
    }
  }

  for (i=1; i<N; i++)
    for(j=0; j<N+1; j++)
    {
      if (j == i-1)
	matrix[i][j] = 1.0;
      else if (j == i)
	matrix[i][j] = - ( pow(2.0/N,2) * ( 1 + pow((-1+i*2.0/N),2) ) + 2 );
      else if (j == i+1)
	matrix[i][j] = 1.0;
      else
	matrix[i][j] = 0.0;
    }

  matrix[0][0] = 1.0;
  matrix[N][N] = 1.0;

  for (i=1; i<N+1; i++)
    matrix[0][i] = 0.0;
  for (i=0; i<N; i++)
    matrix[N][i] = 0.0;

  cout << "\nBitte geben Sie einen Dateinamen an,\nunter dem die Matrix abgespeichert wird : ";
  cin >> datei;

  ofstream fout(datei);

  for (i=0; i<N+1; i++)
  {
    for (j=0; j<N+1; j++)
    {
      fout << " ";
      fout << matrix[i][j];
    }

    fout << "\n";
  }

  fout.close();

  cout << "\nBitte geben Sie einen Dateinamen an,\nunter dem der Ergebnisvektor abgespeichert wird : ";
  cin >> datei;

  ofstream fout2(datei);

  fout2 << 0.0;

  for (i=1; i<N; i++)
  {
    fout2 << " ";
    fout2 << pow(2.0/N,2);
  }

  fout2 << 0.0;

  fout2.close();

  return 0;
}

