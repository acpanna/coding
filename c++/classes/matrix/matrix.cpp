#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"

Matrix::Matrix(char *nameneu, int zeileneu)
{
	zeilen = zeileneu;
	spalten = zeileneu;

	eintrag = (double **) calloc(zeilen, sizeof(double)); 

	assert(eintrag != 0);
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
        assert(eintrag[i] != 0);
	}

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	strcpy(name,nameneu);
}

Matrix::Matrix(char *nameneu, int zeileneu, int spalteneu)
{
	zeilen = zeileneu;
	spalten = spalteneu;

	eintrag = (double **) calloc(zeilen, sizeof(double));  

	assert(eintrag != 0);
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
        assert(eintrag[i] != 0);
	}

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	strcpy(name,nameneu);
}

Matrix::Matrix(char *nameneu, Matrix &matrix)
{
	zeilen = matrix.GetZeilen();
	spalten = matrix.GetSpalten();
    
	eintrag = (double **) calloc(zeilen, sizeof(double));   

	assert(eintrag != 0);
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
        assert(eintrag[i] != 0);
	}

	for (i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			eintrag[i][j] = matrix.GetEintrag(i,j);

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	strcpy(name,nameneu);
}

Matrix::~Matrix()
{
	for (int i=0; i<zeilen; i++)
		delete eintrag[i];

	delete eintrag;
	delete name;

	eintrag = 0;
	name = 0;
}

istream & operator>> (istream &thestream, Matrix &matrix)
{
	int zeil = 0;
	int spalt = 0;
	
	double eintragneu;

	thestream >> zeil;
	thestream >> spalt;

	Matrix tmp("", zeil, spalt);

	for (int i=0; i < zeil; i++)
		for (int j=0; j < spalt; j++)
		{
     		thestream >> eintragneu;
			tmp.SetEintrag(i, j, eintragneu);
		}
   
	matrix = tmp;

	return thestream;
}


ostream & operator<< (ostream &thestream, Matrix &matrix)
{
	thestream << matrix.GetZeilen();
	thestream << ' ';
	thestream << matrix.GetSpalten();
	
	for (int i=0; i < matrix.GetZeilen(); i++)
		for (int j=0; j < matrix.GetSpalten(); j++)
		{
			thestream << ' ';
			thestream << matrix.eintrag[i][j];
		}
    return thestream;
}

Matrix * Matrix::operator+ (const Matrix &matrix)
{
	Matrix *tmp = new Matrix("", zeilen, spalten);
	
	for (int i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			tmp->eintrag[i][j] = eintrag[i][j] + matrix.eintrag[i][j];
	return tmp;
}

Matrix & Matrix::operator= (const Matrix &matrix)
{	
	if (this == &matrix)
		return (*this);
	
    for (int i=0; i < zeilen; i++)
		delete eintrag[i];

	delete eintrag;
	
    zeilen = matrix.zeilen;
	spalten = matrix.spalten;

	eintrag = (double **) calloc(zeilen, sizeof(double));

	assert(eintrag != 0);

	for (i=0; i<zeilen ; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
		assert(eintrag[i] != 0);
	}
	
	for (i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			eintrag[i][j] = matrix.eintrag[i][j];
			
	return (*this);
}

Matrix * Matrix::operator* (const Matrix &matrix)
{
    Matrix *tmp = new Matrix("", zeilen, matrix.spalten);

	for (int k=0; k<tmp->spalten; k++)
		for (int i=0; i<tmp->zeilen; i++)
		{
			tmp->eintrag[i][k] = 0.0;
			for (int j=0; j<spalten; j++)
				tmp->eintrag[i][k] += eintrag[i][j] * matrix.eintrag[j][k];
		} 
		
	return tmp;
}

Matrix * Matrix::operator* (const double &skalar)
{
	Matrix *tmp = new Matrix("", zeilen, spalten);
	
	for (int i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
		{
			eintrag[i][j] *= skalar;
		    tmp->eintrag[i][j] = eintrag[i][j];
		}

	return tmp;
}

Matrix * Matrix::operator^ (const int &potenz)
{
	Matrix *tmp = new Matrix("", *this);
	
	for (int i=1; i<potenz; i++)
		tmp = (*tmp) * (*this);
    return tmp;
}
		
double Matrix::Det() const
{
	int j2;
	
	double erg = 0.0;
  
    if (zeilen == 1)
		return eintrag[0][0];

    Matrix tmp("", zeilen - 1);
	      
    for (int k=0; k<zeilen; k++)
	{
		for (int i=1; i<zeilen; i++)
		{
			j2 = 0;

			for (int j=0; j<zeilen; j++)
			{
				if ((j == k) && (k != zeilen - 1))
					j++;

	            else if ((j == k) && (k == zeilen - 1))
			        break;

	            tmp.eintrag[i-1][j2] = eintrag[i][j];
	            j2++;
			}
		}

        tmp.SetZeilen(zeilen - 1);
	    tmp.SetSpalten(spalten - 1);
		
	    erg += pow(-1, k+2) * eintrag[0][k] * tmp.Det();
	}

  return erg;
}

double Matrix::GetEintrag(int zeile, int spalte) const
{
	if (zeile > zeilen || spalte > spalten || zeile<0 || spalte<0)
		return 0.0;

	return eintrag[zeile][spalte];
}

Matrix * Matrix::Adj() const
{
	int k2, l2;
	
	Matrix *tmp = new Matrix("", zeilen);
	
	Matrix tmp2("", zeilen - 1);
  
	for (int i=0; i<zeilen; i++)
	{
		for (int j=0; j<zeilen; j++)
		{
			k2 = 0;

            for (int k=0; k<zeilen; k++)
			{
				if ((k == j) && (k != zeilen - 1))
					k++;
				else if ((k == j) && (k == zeilen - 1))
                    break;

                l2 = 0;

	            for (int l=0; l<zeilen; l++)
				{
					if ((l == i) && (l != zeilen - 1))
						l++;
					else if ((l == i) && (l == zeilen - 1))
					    break;
					 
					tmp2.eintrag[k2][l2] = eintrag[k][l];
					l2++;
				}

				k2++;
			}

			tmp2.SetZeilen(zeilen-1);
			tmp2.SetSpalten(spalten-1);

			tmp->eintrag[i][j] = pow(-1, i+j+2) * tmp2.Det();
		} 
	}

    return tmp;
}

Matrix * Matrix::Trans() const
{
	Matrix *tmp = new Matrix("", spalten, zeilen);

	for (int i=0; i<spalten; i++)
		for (int j=0; j<zeilen; j++)
			tmp->eintrag[i][j] = eintrag[j][i];
	return tmp;
}


void Matrix::SetEintrag(int zeile, int spalte, double eintragneu)
{
	if (zeile>zeilen || spalte>spalten || zeile<0 || spalte<0)
		return;

	eintrag[zeile][spalte] = eintragneu;
}

char * Matrix::GetName() const
{
	char *str = new char[strlen(name) + 1];
    assert(str != 0);

	strcpy(str, name);
	return str;
}

void Matrix::SetName(char *nameneu)
{
	delete name;
	name = new char[strlen(nameneu) + 1];
	assert(name != 0);
	
	strcpy(name, nameneu);
}

int main(void)
{
    Matrix A("",2,2);
	Matrix B("",2,2);

    cin >> A;
    cin >> B;

	B = *(A*B);

    cout << B;
	return 0;
}