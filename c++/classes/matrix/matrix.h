#include <iostream.h>

class Matrix {
public:
	friend ostream & operator<< (ostream &thestream, Matrix &matrix);
	friend istream & operator>> (istream &thestream, Matrix &matrix);
	Matrix(char *, int zeileneu);
	Matrix(char *, int zeileneu, int spalteneu);
	Matrix(char *, Matrix &);
	~Matrix();
	Matrix & operator= (const Matrix &);
	Matrix * operator+ (const Matrix &);
	Matrix * operator* (const Matrix &);
	Matrix * operator^ (const int &);
	Matrix * operator* (const double &);
	Matrix * Adj() const;
	Matrix * Trans() const;
	
	double Det() const;

	inline int GetZeilen() { return zeilen; } const
	inline int GetSpalten() { return spalten; } const
	inline void SetZeilen(int zeileneu) { zeilen = zeileneu; }
	inline void SetSpalten(int spalteneu) { spalten = spalteneu; }
	
	double GetEintrag(int zeile, int spalte) const;
    void SetEintrag(int zeile, int spalte, double eintragneu);
	char * GetName() const;
	void SetName(char *nameneu);

private:
	int zeilen;
	int spalten;
	double **eintrag;
	char *name;
};