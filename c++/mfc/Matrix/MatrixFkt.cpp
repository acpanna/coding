#include "Stdafx.h"
#include "MatrixFkt.h"

CMatrix::CMatrix(char *nameneu, int zeileneu)
{
	zeilen = zeileneu;
	spalten = zeileneu;

	eintrag = (double **) calloc(zeilen, sizeof(double)); 

	if (eintrag == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
       
		if (eintrag[i] == 0)
		{
			AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	        return;
		}
	}

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	strcpy(name,nameneu);
}

CMatrix::CMatrix(char *nameneu, int zeileneu, int spalteneu)
{
	zeilen = zeileneu;
	spalten = spalteneu;

	eintrag = (double **) calloc(zeilen, sizeof(double));  

    if (eintrag == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
        
		if (eintrag[i] == 0)
		{
			AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	        return;
		}
	}

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	strcpy(name,nameneu);
}

CMatrix::CMatrix(char *nameneu, CMatrix &matrix)
{
	zeilen = matrix.GetZeilen();
	spalten = matrix.GetSpalten();
    
	eintrag = (double **) calloc(zeilen, sizeof(double));   

	if (eintrag == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	for (int i=0; i<zeilen; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
       	
		if (eintrag[i] == 0)
		{
			AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	        return;
		}
	}

	for (i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			eintrag[i][j] = matrix.GetEintrag(i,j);

	name = (char *) calloc(strlen(nameneu) + 1, sizeof(char));
	
	if (name == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	strcpy(name,nameneu);
}

CMatrix::~CMatrix()
{
	for (int i=0; i<zeilen; i++)
		delete [] eintrag[i];

	delete [] eintrag;
	delete [] name;

	eintrag = 0;
	name = 0;
}

istream & operator>> (istream &thestream, CMatrix &matrix)
{
	int zeil = 0;
	int spalt = 0;
	
	double eintragneu;

	thestream >> zeil;
	thestream >> spalt;

	CMatrix tmp("", zeil, spalt);

	for (int i=0; i < zeil; i++)
		for (int j=0; j < spalt; j++)
		{
     		thestream >> eintragneu;
			tmp.SetEintrag(i, j, eintragneu);
		}
   
	matrix = tmp;

	return thestream;
}


ostream & operator<< (ostream &thestream, CMatrix &matrix)
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

CMatrix * CMatrix::operator+ (const CMatrix &matrix)
{
	CMatrix *tmp = new CMatrix("", zeilen, spalten);
	
	for (int i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			tmp->eintrag[i][j] = eintrag[i][j] + matrix.eintrag[i][j];
	return tmp;
}

CMatrix & CMatrix::operator= (const CMatrix &matrix)
{	
	if (this == &matrix)
		return (*this);
	
    for (int i=0; i < zeilen; i++)
		delete [] eintrag[i];

	delete [] eintrag;
	
    zeilen = matrix.zeilen;
	spalten = matrix.spalten;

	eintrag = (double **) calloc(zeilen, sizeof(double));

	if (eintrag == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    exit(1);
	}

	for (i=0; i<zeilen ; i++)
	{
		eintrag[i] = (double *) calloc(spalten, sizeof(double));
	
		if (eintrag[i] == 0)
		{
			AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	        exit(1);
		}
	}
	
	for (i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
			eintrag[i][j] = matrix.eintrag[i][j];
			
	return (*this);
}

CMatrix * CMatrix::operator* (const CMatrix &matrix)
{
    CMatrix *tmp = new CMatrix("", zeilen, matrix.spalten);

	for (int k=0; k<tmp->spalten; k++)
		for (int i=0; i<tmp->zeilen; i++)
		{
			tmp->eintrag[i][k] = 0.0;
			for (int j=0; j<spalten; j++)
				tmp->eintrag[i][k] += eintrag[i][j] * matrix.eintrag[j][k];
		} 
		
	return tmp;
}

CMatrix * CMatrix::operator* (const double &skalar)
{
	CMatrix *tmp = new CMatrix("", zeilen, spalten);
	
	for (int i=0; i<zeilen; i++)
		for (int j=0; j<spalten; j++)
		{
			eintrag[i][j] *= skalar;
		    tmp->eintrag[i][j] = eintrag[i][j];
		}

	return tmp;
}

CMatrix * CMatrix::operator^ (const int &potenz)
{
	CMatrix *tmp = new CMatrix("", *this);
	
	for (int i=1; i<potenz; i++)
		tmp = (*tmp) * (*this);
    return tmp;
}
		
double CMatrix::Det() const
{
	int j2;
	
	double erg = 0.0;
  
    if (zeilen == 1)
		return eintrag[0][0];

    CMatrix tmp("", zeilen - 1);
	      
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

double CMatrix::GetEintrag(int zeile, int spalte) const
{
	if (zeile > zeilen || spalte > spalten || zeile<0 || spalte<0)
		return 0.0;

	return eintrag[zeile][spalte];
}

CMatrix * CMatrix::Adj() const
{
	int k2, l2;
	
	CMatrix *tmp = new CMatrix("", zeilen);
	
	CMatrix tmp2("", zeilen - 1);
  
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

CMatrix * CMatrix::Trans() const
{
	CMatrix *tmp = new CMatrix("", spalten, zeilen);

	for (int i=0; i<spalten; i++)
		for (int j=0; j<zeilen; j++)
			tmp->eintrag[i][j] = eintrag[j][i];
	return tmp;
}


void CMatrix::SetEintrag(int zeile, int spalte, double eintragneu)
{
	if (zeile>zeilen || spalte>spalten || zeile<0 || spalte<0)
		return;

	eintrag[zeile][spalte] = eintragneu;
}


void CMatrix::SetName(char *nameneu)
{
	delete [] name;
	name = new char[strlen(nameneu) + 1];
	
	if (name == 0)
	{
		AfxMessageBox("Zu wenig Speicherplatz !",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	strcpy(name, nameneu);
}
