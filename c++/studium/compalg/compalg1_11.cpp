#include "rational.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

#include <cassert>
#include <climits>
#include <cmath>

#define KARATSUBA 750

using namespace std;

// USHORT_DECIMALS ist der Exponent der groessten Zehner-Potenz,
// die noch mit einer unsigned short dargestellt werden kann.
static const unsigned short USHORT_DECIMALS = (unsigned short) \
		((sizeof(unsigned short) * 8 * log(2.0))/log(10.0));

// BASE gibt an, bzgl. welcher Basis
// die LongInts intern dargestellt werden.
static const unsigned long BASE = (unsigned long) pow(10.0, USHORT_DECIMALS);


/******** Verschiedene Hilfsfunktionen ********/
inline unsigned long ushort_join(const unsigned short &high, 
				const unsigned short &low)
{
	return (unsigned long) high * BASE + (unsigned long) low;
}

inline void ulong_split(const unsigned long &join, unsigned short &high,
					unsigned short &low)
{
	high = (unsigned short) (join / (unsigned long) BASE);
        low = (unsigned short) (join - (unsigned long) high *
          					(unsigned long) BASE);
}

bool trim_string(char * const string)
{
	char ret = '+';
        char *ptr1 = string, *ptr2 = string;
	unsigned long i = 0;

        // Extrahiere ein evtl. Vorzeichen aus dem String
        while (string[i] != '+' && string[i] != '-' && string[i] != '\0') i++;
	if (string[i] != '\0')
        	ret = string[i];

	// Entferne alle Nicht-Ziffern != 0,...,9
        for (; *ptr2 != '\0'; ptr2++)
        	if (isdigit(*ptr2)) {
        		*ptr1 = *ptr2;
        		ptr1++;
        	}

	*ptr1 = '\0';
	ptr1 = ptr2 = string;
        
	// Entferne fuehrende Nullen
	while (*ptr2 == '0')
        	ptr2++;

	for (; *ptr2 != '\0'; ptr1++, ptr2++)
		*ptr1 = *ptr2;

	*ptr1 = '\0';
     
	// Falls der String nach Bereinigung "leer" ist, so
	// setze ret = '+' (leerer String wird als 0 interpretiert,
	// 0 hat in meiner Implementation pos. Vorzeichen)
	if (string[0] == '\0')
		ret = '+';
	
	// Gebe Vorzeichen des Strings zurueck
	if (ret == '+')
		return true;
	else
		return false;
}


/******** Implementierung der Klasse LongInt ********/
LongInt& LongInt::operator =(int src)
{
	unsigned short rest;
	clear(); 
	
	if (src == 0) {
		sign = true;
		push_back(0);
		return *this;
	} else if (src < 0) {
		sign = false;
		src = -src;
	} else  
		sign = true;

	while (src != 0) {
		rest = src % BASE;
		src = src / BASE;
		
		push_back(rest);
	}
	
	return *this;
}

LongInt& LongInt::operator =(const LongInt &src)
{
	if (this != &src) {
		Vector::operator=(src);
		sign = src.sign;
	}

	return *this;
}

LongInt& LongInt::operator =(const char * const src)
{
	char *ptr, *str = new char[strlen(src) + 1];
	assert(str);
	strcpy(str, src);

	clear();
	sign = trim_string(str); 
	
	ptr = str;
	while (*ptr != '\0')
		ptr++;
	
	while (ptr != str) {
		ptr -= USHORT_DECIMALS;

		if (ptr <= str) 
			ptr = str;

		push_back((unsigned short) atol(ptr));
		*ptr = '\0';
	}

	if (empty())
		*this = 0;

	delete [] str;
	return *this;
}

LongInt& LongInt::lshift(const size_type &steps)
{
	if (*this == 0)
		return *this;

	insert(begin(), steps, 0);
	
	return *this;
}

LongInt LongInt::abs(void) const
{ 
	LongInt ret;
	ret = *this;
	ret.sign = true;
	return ret;
}

int LongInt::compare(const LongInt &rts) const
{
	if (sign == true && rts.sign == false) 
		return 1;
	if (sign == false && rts.sign == true)
		return -1;
	
	int ret;
	size_type this_size = size(), rts_size = rts.size(), i;
	
	if (this_size > rts_size)
		ret = 1;
	else if (this_size < rts_size)
		ret = -1;
	else {
		for (i=this_size-1; i>0; i--)
			if ((*this)[i] != rts[i])
				break;

		if ((*this)[i] < rts[i])
			ret = -1;
		else if ((*this)[i] > rts[i])
			ret = 1;
		else
			ret = 0;
	}
		
	if (sign == true)
		return ret;
	else
		return -ret;
}

LongInt& LongInt::add(const LongInt &a, const LongInt &b, LongInt &ret)
{
	if (a == 0)
		return (ret = b);
	if (b == 0)
		return (ret = a);
	
	if (a.sign == true && b.sign == false) 
		return sub(a, b.abs(), ret);
	if (a.sign == false && b.sign == true) 
		return sub(b, a.abs(), ret);

	unsigned short carry = 0;
	unsigned long res;

	size_type i = 0, a_size = a.size(), b_size = b.size(), minlen, maxlen;
	
	minlen = min(a_size, b_size);
	maxlen = max(a_size, b_size);

	if (ret.size() != maxlen)
		ret.resize(maxlen);

	while (i < minlen) {
		res = a[i] + b[i] + carry;
		
		if (res > BASE-1) {
			res -= BASE;
			carry = 1;
		} else
			carry = 0;
		
		ret[i] = (unsigned short) res;
		i++;
	}

	while (i < a_size) {
		res = a[i] + carry; 
	
		if (res > BASE-1) {
			res -= BASE;
			carry = 1;
		} else
			carry = 0;
		
		ret[i] = (unsigned short) res;
		i++;
	}

	while (i < b_size) {
               	res = b[i] + carry;
		
		if (res > BASE-1) {
			res -= BASE;
			carry = 1;
		} else
			carry = 0;
		
		ret[i] = (unsigned short) res;
               	i++;
        }

	if (carry != 0)
		ret.push_back(carry);
	
	ret.sign = a.sign;
	return ret;
}

LongInt& LongInt::sub(const LongInt &a, const LongInt &b, LongInt &ret)
{
	if (b == 0)
		return (ret = a);
	if (a == 0) {
		ret = b;
		ret.sign = !b.sign;
		return ret;
	}
		
	if (a.sign == true && b.sign == false) 
		return add(a, b.abs(), ret);

	if (a.sign == false && b.sign == true) {
		add(a.abs(), b, ret);
		ret.sign = false;
		return ret;
	}
	
	if (a.sign == false && b.sign == false) 
		return sub(b.abs(), a.abs(), ret);
	
	if (a < b) {
		sub(b, a, ret);
		ret.sign = false;
		return ret;
	}
	
	size_type i = 0, a_size = a.size(), b_size = b.size();
	
	if (ret.size() != a_size)
		ret.resize(a_size);

	unsigned short carry = 0;
	long res;

	while (i < b_size) {
		res = a[i] - b[i] - carry;
			
		if (res < 0) {
			res += BASE;
			carry = 1;
		} else
			carry = 0;
		
		ret[i] = (unsigned short) res;
		i++;
	}

	while (i < a_size) {
		res = a[i] - carry;

		if (res < 0) {
			res += BASE;
			carry = 1;
		} else
			carry = 0;
				
		ret[i] = (unsigned short) res;
		i++;
	}

	while (ret.back() == 0 && ret.size() > 1)
		ret.pop_back();
	
	ret.sign = true;
	return ret;
}

LongInt& LongInt::mul(const LongInt &a, const LongInt &b, LongInt &ret)
{
	if (a == 0 || b == 0) {
		ret = 0;
		return ret;
	}
	
	if (&a == &ret)
	{
		LongInt tmp(a);
		return mul(tmp, b, ret);
	}
	
	if (&b == &ret)
	{
		LongInt tmp(b);
		return mul(a, tmp, ret);
	}
	
	if (a.size() * b.size() <= KARATSUBA) 
		return schul_mul(a, b, ret);

	return karatsuba_mul(a, b, ret);
}

LongInt& LongInt::schul_mul(const LongInt &x, const LongInt &y, LongInt &ret)
{
	unsigned short lo, hi, carry = 0;
	unsigned long res;

	size_type i, j, k, x_size = x.size(), y_size = y.size();
	
	ret.clear();
	ret.resize(x_size + y_size, 0);
		
	for (i=0; i<x_size; i++) {
		for (j=0; j<y_size; j++) {
			res = x[i] * y[j];
			ulong_split(res, hi, lo);

			for (k=0; k<2; k++) {
				res = ret[i+j+k] + lo + carry;
				if (res > BASE-1) {
					res -= BASE;
					carry = 1;
				} else
					carry = 0;

				ret[i+j+k] = (unsigned short) res;
				lo = hi;
			}
			
			while (carry) {
				res = ret[i+j+k] + carry;
				if (res > BASE-1) {
					res -= BASE;
					carry = 1;
				} else
					carry = 0;

				ret[i+j+k] = (unsigned short) res;
				k++;
			}
		}
	}

	while (ret.back() == 0)
		ret.pop_back();
	
	ret.sign = !(x.sign ^ y.sign);
	return ret;
}

LongInt& LongInt::karatsuba_mul(const LongInt &x, const LongInt &y, 
							LongInt &ret)
{
	LongInt a, b, c, d, temp1, temp2, temp3;

	size_type x_size = x.size(), y_size = y.size();
	size_type k = max(x_size, y_size), i;
	
	if (k % 2 == 1)
		k = k + 1;

	a.clear();
	b.clear();
	c.clear();
	d.clear();

	// Besetze b mit niedrigen Stellen aus x
	for (i=0; i<x_size && i<k/2; i++)
		b.push_back(x[i]);
		
	while (b.back() == 0 && b.size() > 1)
			b.pop_back();

	// Wichtig, sonst gibts evtl. negative Nullen!
	if (b.back() != 0)
		b.sign = x.sign;
	
	// Besetze a mit hohen Stellen aus x
	if (x_size <= k/2)
		a = 0;
	else {
		for (i=k/2; i<x_size; i++)
			a.push_back(x[i]);
	
		a.sign = x.sign;
	}

	// Besetze d mit niedrigen Stellen aus y	
	for (i=0; i<y_size && i<k/2; i++) 
		d.push_back(y[i]);
		
	while (d.back() == 0 && d.size() > 1)
		d.pop_back();
		
	// Wichtig, sonst gibts evtl. negative Nullen!
	if (d.back() != 0)
		d.sign = y.sign;
		
	// Besetze c mit hohen Stellen aus y	
	if (y_size <= k/2)
		c = 0;
	else {
		for (i=k/2; i<y_size; i++)
			c.push_back(y[i]);
	
		c.sign = y.sign;
	}
	
	// temp1 = (a-b) * (d-c);
	sub(a, b, temp2);
	sub(d, c, temp3);
	mul(temp2, temp3, temp1);

	// temp2 = a * c
	mul(a, c, temp2);

	// temp3 = b * d
	mul(b, d, temp3); 

	// temp1 = temp1 + temp2 + temp3
	add(temp1, temp2, temp1);
	add(temp1, temp3, temp1); 
	
	temp1.lshift(k/2);
	temp2.lshift(k);

	// ret = temp1 + temp2 + temp3
	add(temp1, temp2, ret);
	add(ret, temp3, ret);
	
	return ret;
}
	
LongInt& LongInt::pow(LongInt a, LongInt b, LongInt &ret)
{
	if (b < 0) {
		cerr << "[ LongInt::operator ^ ] ist fuer Exponenten < 0 "\
			"nicht implementiert -- Programmabbruch!" << endl;
		exit(1);
	}

	ret = 1;
	LongInt tmp;

	while (b != 0) {
		if (b.front() % 2 != 0)
		{
			// ret = ret * a
			mul(ret, a, ret);
		}
		
		// a = a * a
		mul(a, a, a);

		// b = b / 2
		div(b, 2, b, tmp); 
	}

	return ret;
}
			
void LongInt::div(const LongInt &x, const LongInt &y, LongInt &q, LongInt &r)
{
	if (&q == &r) {
		cerr << "[ LongInt::operator / ] &q == &r " \
			"-- Programmabbruch!" << endl;
		exit(1);
	}
	
	if (y == 0) {
		cerr << "[ LongInt::operator / ] Division durch Null " \
			"-- Programmabbruch!" << endl;
		exit(1);
	}

	LongInt a, b, tmp, tmp2;
	long d = BASE / (y.back() + 1);
	
	// Multiplikation mit d bewirkt, dass bei der 
	// folgenden Berechnung von quot, dieses hoechstens 
	// um 2 groesser ist als der wahre Wert
	
	// a = |x| * d
	// b = |y| * d
	mul(x.abs(), d, a);
	mul(y.abs(), d, b);
	
	if (a < b) {
		// Reihenfolge nicht vertauschen!
		// Es kann passieren, dass &q == &x
		r = x; 
		q = 0;
		return;
	}
		
	size_type a_size = a.size(), b_size = b.size(), i, j;

	if (a_size == 1) {
		a.push_back(0);
		a_size++;
	}

	// Falls der Quotient aus den ersten beiden Stellen des Dividenden a
	// und der ersten Stelle des Divisors b, nicht mehr mit einer Ziffer 
	// der Zahlenbasis dargestellt werden kann, erweitere Dividend mit
	// fuehrender Null
	if (ushort_join(a[a_size-1], a[a_size-2]) / b.back() > BASE-1) {
		a.push_back(0);
		a_size++;
	}

	j = a_size - b_size;
	q.resize(j);
		
	// Speichere die führenden (b_size)
	// Stellen von a in tmp
	tmp.resize(b_size);
	for (i=b_size; i>0; i--) 
		tmp[i-1] = a[j-1+i];
	
	while (j > 0) {
		// tmp durch Hinzufuegen von fuehrenden 
		// Nullen auf die Groesse b_size bringen 
		while (tmp.size() != b_size) 
			tmp.push_back(0);
		
		// Hole die naechste Stelle des Dividenden 
		// und haenge sie an tmp an
		tmp.insert(tmp.begin(), 1, a[j-1]);
	
		// Berechne aktuelle Stelle des Quotienten 
		unsigned short quot = min(BASE-1, 
			ushort_join(tmp[b_size], tmp[b_size-1]) / b.back());
		
		// Fuehrende Nullen aus tmp entfernen
		while (tmp.back() == 0 && tmp.size() > 1) 
			tmp.pop_back();

		// tmp = tmp - b * quot
	 	mul(b, quot, tmp2);
		sub(tmp, tmp2, tmp);
		
		// Falls tmp negativ ist, so wurde quot
		// zu gross gewaehlt --> verkleinere quot 
		while (tmp.sign == false) {
			quot = quot - 1;
			
			// tmp = tmp + b
			add(tmp, b, tmp);
		}
		
		// Updaten des Quotienten 
		j--; q[j] = quot;
	}

	// Fuehrende Nullen im Ergebnis entfernen 
	while (q.back() == 0) 
		q.pop_back();
		
	// Fuehrende Nullen aus tmp entfernen
	while (tmp.back() == 0 && tmp.size() > 1) 
		tmp.pop_back();

	// Bestimmung von |r|
       	// |r| = tmp/d
	div(tmp, d, r, tmp2);
	
	// Setze das Vorzeichen des Quotienten und des Rests
	q.sign = !(x.sign ^ y.sign);
	r.sign = x.sign;

	return;
}
	
LongInt& LongInt::ggT(const LongInt &x, const LongInt &y, LongInt &ret)
{	
	LongInt a, b, tmp;
	
	a = x.abs();
	b = y.abs();
	
	while (b != 0) {
		// ret = a % b
		div(a, b, tmp, ret);
	
		a = b;
		b = ret;
	}

	ret = a;
	return ret;
}

LongInt& LongInt::kgV(const LongInt &a, const LongInt &b, LongInt &ret)
{
	LongInt tmp;

	// ret = a * b / ggT(a, b)
	mul(a, b, tmp);
	ggT(a, b, ret);
	div(tmp, ret, ret, tmp);
	
	return ret;
}

ostream& operator <<(ostream &OS, const LongInt &value)
{
	if (!value.sign)
		OS << "-";
	
	for (Vector::const_reverse_iterator iter=value.rbegin();
			iter != value.rend(); iter++)
	{
		char *str = new char[USHORT_DECIMALS + 1];
		assert(str);
		
		sprintf(str, "%u", *iter);
	
		if (iter != value.rbegin()) {
			for (unsigned short i=0; 
					i<USHORT_DECIMALS-strlen(str); i++)
				OS << 0;
		}
		
		OS << *iter;
		delete [] str;
	}
	
	return OS;
}
	
istream& operator >>(istream &IS, LongInt &value)
{
	string str;
	
	IS >> str;
	value = str.c_str();

	return IS;
}


/******** Implementierung der Klasse Rational ********/
Rational& Rational::operator =(int zahl)
{
	zaehler = zahl;
        nenner = 1;

	return *this;
}

Rational& Rational::operator =(const LongInt &li)
{
	zaehler = li;
	nenner = 1;

	return *this;
}

Rational& Rational::operator =(const Rational &rts)
{
	zaehler = rts.zaehler;
	nenner = rts.nenner;

	return *this;
}

Rational& Rational::operator =(const char * const str)
{
	char *ptr, *str2 = new char[strlen(str) + 1];
	assert(str2);

	strcpy(str2, str);

	ptr = str2;
	while (*ptr != '/' && *ptr != '\0')
		ptr++;

	if (*ptr == '/') {
		*ptr = '\0';
		ptr++;
	}

	zaehler = str2;
	
	if (*ptr == '\0') 
		nenner = 1;
	else { 
		nenner = ptr;
		if (nenner == 0) {
			cerr << "[ Rational::operator = ] Division durch " \
				"Null -- Programmabbruch!" << endl;

			delete [] str2;
			exit(1);
		}
	}
		
	delete [] str2;
	return this->kuerzen();
}

int Rational::compare(const Rational &rts) const
{
	LongInt z_a, z_b, n;
	com_denom(*this, rts, z_a, z_b, n); 
	
	if (z_a == z_b)
		return 0;
	if (n.sign == true) {
		if (z_a < z_b)
			return -1;
		else 
			return 1;
	} else {
		if (z_a < z_b)
			return 1;
		else 
			return -1;
	}
}	

Rational& Rational::kuerzen(void)
{
	if (zaehler == 0) {
		nenner = 1;
		return *this;
	}
	
	LongInt ggt, tmp;
	LongInt::ggT(zaehler, nenner, ggt);
	
	LongInt::div(zaehler, ggt, zaehler, tmp);
	LongInt::div(nenner, ggt, nenner, tmp);
	
	if (nenner.sign == false) {
		zaehler.sign = !zaehler.sign;
		nenner.sign = true;
	}

	return *this;
}

Rational& Rational::negate(void)
{
	if (zaehler != 0)
		zaehler.sign = !zaehler.sign;
	
	return *this; 
}

void Rational::com_denom(const Rational &a, const Rational &b, 
		LongInt &a_z, LongInt &b_z, LongInt &ab_n)
{
	if (&a_z == &b_z || &a_z == &ab_n || &b_z == &ab_n) {
		cerr << "[ Rational::com_denom() ] Die uebergebenen LongInts " \
			"haben gleiche Adressen -- Programmabbruch!" << endl;
		exit(1);
	}

	LongInt tmp;
	
	// ab_n = kgv(a.nenner, b.nenner)
	LongInt::kgV(a.nenner, b.nenner, ab_n);
	
	// a_z = (ab_n / a.nenner) * a.zaehler 
	// b_z = (ab_n / b.nenner) * b.zaehler
	LongInt::div(ab_n, a.nenner, a_z, tmp);
	LongInt::div(ab_n, b.nenner, b_z, tmp);
	LongInt::mul(a_z, a.zaehler, a_z);
	LongInt::mul(b_z, b.zaehler, b_z);

	return;
}

Rational& Rational::add(const Rational &a, const Rational &b, Rational &ret)
{
	LongInt z_a, z_b, n;
	com_denom(a, b, z_a, z_b, n); 
	
	// ret.zaehler = z_a + z_b
	LongInt::add(z_a, z_b, ret.zaehler);

	ret.nenner = n;
	return ret.kuerzen();
}

Rational& Rational::sub(const Rational &a, const Rational &b, Rational &ret)
{
	LongInt z_a, z_b, n;
	com_denom(a, b, z_a, z_b, n); 
	
	// ret.zaehler = z_a - z_b
	LongInt::sub(z_a, z_b, ret.zaehler);
	
	ret.nenner = n;
	return ret.kuerzen();
}

Rational& Rational::mul(const Rational &a, const Rational &b, Rational &ret)
{
	Rational r1, r2;

	r1.zaehler = a.zaehler;
	r1.nenner = b.nenner;
	r2.zaehler = b.zaehler;
	r2.nenner = a.nenner;
	
	r1.kuerzen();
	r2.kuerzen();

	// ret = r1 * r2
	LongInt::mul(r1.zaehler, r2.zaehler, ret.zaehler);
	LongInt::mul(r1.nenner, r2.nenner, ret.nenner);
	
	return ret;
}

Rational& Rational::div(const Rational &a, const Rational &b, Rational &ret)
{
    	if (b.zaehler == 0)
	{
		cerr << "[ Rational::operator / ] " \
			"Division durch Null -- Programmabbruch!" << endl;
		exit(1);
	}

	Rational tmp;
	
	tmp.zaehler = b.nenner;
	tmp.nenner = b.zaehler;
	
	Rational::mul(a, tmp, ret);
	return ret;
}

Rational& Rational::pow(const Rational &a, const LongInt &b, Rational &ret)
{
	if (b.sign == false) {
		if (a.zaehler == 0) {
			cerr << "[ Rational::operator ^ ] " \
			"Division durch Null -- Programmabbruch!" << endl;
			exit(1);
		}

		LongInt::pow(a.nenner, b.abs(), ret.zaehler);
		LongInt::pow(a.zaehler, b.abs(), ret.nenner);
	} else {
		LongInt::pow(a.zaehler, b, ret.zaehler);
		LongInt::pow(a.nenner, b, ret.nenner);
	}

	return ret;
}

std::ostream& operator <<(std::ostream &OS, const Rational &value)
{
	OS << "(" << value.zaehler << " / " << value.nenner << ")";
	return OS;
}
    
std::istream& operator >>(std::istream &IS, Rational &value)
{
	string str;
	
	IS >> str;
	value = str.c_str();

	return IS;
}
