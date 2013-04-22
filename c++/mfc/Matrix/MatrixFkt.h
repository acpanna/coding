#include <iostream.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class CMatrix {
public:
	friend ostream & operator<< (ostream &thestream, CMatrix &matrix);
	friend istream & operator>> (istream &thestream, CMatrix &matrix);
	CMatrix(char *, int zeileneu);
	CMatrix(char *, int zeileneu, int spalteneu);
	CMatrix(char *, CMatrix &);
	~CMatrix();
	CMatrix & operator= (const CMatrix &);
	CMatrix * operator+ (const CMatrix &);
	CMatrix * operator* (const CMatrix &);
	CMatrix * operator^ (const int &);
	CMatrix * operator* (const double &);
	CMatrix * Adj() const;
	CMatrix * Trans() const;
	
	double Det() const;

	inline int GetZeilen() { return zeilen; } const
	inline int GetSpalten() { return spalten; } const
	inline void SetZeilen(int zeileneu) { zeilen = zeileneu; }
	inline void SetSpalten(int spalteneu) { spalten = spalteneu; }
	
	double GetEintrag(int zeile, int spalte) const;
    void SetEintrag(int zeile, int spalte, double eintragneu);
	void SetName(char *nameneu);
	inline char * GetName() const { return name; }


private:
	int zeilen;
	int spalten;
	double **eintrag;
	char *name;
};