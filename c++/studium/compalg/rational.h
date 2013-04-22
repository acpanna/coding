// *****************************************************************************
// ** THEMA 11: Langzahlarithmetik, Ersetze Koerper Fp<p> durch Q ?
// *****************************************************************************
// ** Vogel, Heiko
// *****************************************************************************
// **
// ** Implementiere Klassen
// ** class longint;  //  bel. grosse Integerzahlen samt +,-,*,/, Ausgabe
// ** class rational; //  Paar von longint-Zahlen (Zaehler und Nenner)
// **
// *****************************************************************************

#include <vector>

typedef std::vector<unsigned short> Vector;
class LongInt : public Vector {
	public: 
		// Konstruktoren (dienen zur Initialisierung) 
		LongInt() { push_back(0); sign = true; }
		LongInt(int src) { *this = src; }
		LongInt(const LongInt &src) { *this = src; }
		LongInt(const char * const src) { *this = src; }
		
		// Zuweisungsoperatoren 
		LongInt& operator =(int);
		LongInt& operator =(const LongInt&);
		LongInt& operator =(const char * const);
		
		void clear(void) { Vector::clear(); sign = true; }
		LongInt& lshift(const size_type&);
	
		LongInt abs(void) const;
	
		// liefert -1, falls *this <  rts
		// liefert  0, falls *this == rts
		// liefert  1, falls *this >  rts
		int compare(const LongInt &rts) const;
		
		static LongInt& add(const LongInt &a, const LongInt &b, 
						LongInt &ret);
		static LongInt& sub(const LongInt &a, const LongInt &b, 
						LongInt &ret);
		static LongInt& mul(const LongInt &a, const LongInt &b, 
						LongInt &ret);
		static LongInt& pow(LongInt a, LongInt b, 
						LongInt &ret);
		
		// Liefert q=x/y, r=x-qy und r.sign=x.sign
		static void div(const LongInt &x, const LongInt &y, 
						LongInt &q, LongInt &r);
		
		static LongInt& ggT(const LongInt &a, const LongInt &b,
						LongInt &ret);
		static LongInt& kgV(const LongInt &a, const LongInt &b,
						LongInt &ret);
	private:
		static LongInt& schul_mul(const LongInt &x, 
				const LongInt &y, LongInt &ret);
		static LongInt& karatsuba_mul(const LongInt &x, 
				const LongInt &y, LongInt &ret);
	public:
		// true  entspricht "+", bzw. vorzeichenlos
		// false entspricht "-" 
		bool sign;
};
		
inline bool operator ==(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) == 0); }

inline bool operator !=(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) != 0); }

inline bool operator <(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) < 0); }

inline bool operator <=(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) <= 0); }

inline bool operator >(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) > 0); }

inline bool operator >=(const LongInt &lts, const LongInt &rts)
{ return (lts.compare(rts) >= 0); }

inline LongInt operator +(const LongInt &lts, const LongInt &rts) 
{ LongInt c; return LongInt::add(lts, rts, c); }
		
inline LongInt operator -(const LongInt &lts, const LongInt &rts) 
{ LongInt c; return LongInt::sub(lts, rts, c); }
		
inline LongInt operator *(const LongInt &lts, const LongInt &rts)
{ LongInt c; return LongInt::mul(lts, rts, c); }

inline LongInt operator /(const LongInt &lts, const LongInt &rts) 
{ LongInt q, r; LongInt::div(lts, rts, q, r); return q; }
		
inline LongInt operator %(const LongInt &lts, const LongInt &rts) 
{ LongInt q, r; LongInt::div(lts, rts, q, r); return r; }

std::ostream& operator <<(std::ostream&, const LongInt&); 
std::istream& operator >>(std::istream&, LongInt&); 

class Rational {
	friend std::ostream& operator <<(std::ostream&, const Rational&);
	public:
		Rational() { zaehler = 0; nenner = 1; }
		Rational(int src) { *this = src; }
		Rational(const Rational &src) { *this = src; }
		Rational(const LongInt &src) { *this = src; }
		Rational(const char * const src) { *this = src; }
    
		Rational& operator =(int);
		Rational& operator =(const Rational&);
		Rational& operator =(const LongInt&);
		Rational& operator =(const char * const);
		
		Rational& kuerzen(void);
		Rational& negate(void);

		int compare(const Rational&) const;
	
		static void com_denom(const Rational &a, const Rational &b, 
				LongInt &a_z, LongInt &b_z, LongInt &ab_n);
	
		static Rational& add(const Rational &a, const Rational &b,
							Rational &ret);
		static Rational& sub(const Rational &a, const Rational &b,
							Rational &ret);
		static Rational& mul(const Rational &a, const Rational &b,
							Rational &ret);
		static Rational& pow(const Rational &a, const LongInt &b,
							Rational &ret);
		static Rational& div(const Rational &a, const Rational &b,
							Rational &ret);
	private:
		LongInt zaehler;
		LongInt nenner;
};    

inline bool operator ==(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) == 0); }

inline bool operator !=(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) != 0); }

inline bool operator <(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) < 0); }

inline bool operator <=(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) <= 0); }

inline bool operator >(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) > 0); }

inline bool operator >=(const Rational &lts, const Rational &rts)
{ return (lts.compare(rts) >= 0); }

inline Rational operator +(const Rational &lts, const Rational &rts) 
{ Rational c; return Rational::add(lts, rts, c); }

inline Rational& operator +=(Rational &lts, const Rational &rts)
{ return Rational::add(lts, rts, lts); }

inline Rational operator -(const Rational &lts, const Rational &rts) 
{ Rational c; return Rational::sub(lts, rts, c); }

inline Rational& operator -=(Rational &lts, const Rational &rts) 
{ return Rational::sub(lts, rts, lts); }

inline Rational operator *(const Rational &lts, const Rational &rts) 
{ Rational c; return Rational::mul(lts, rts, c); }

inline Rational& operator *=(Rational &lts, const Rational &rts) 
{ return Rational::mul(lts, rts, lts); }
	
inline Rational operator /(const Rational &lts, const Rational &rts) 
{ Rational c; return Rational::div(lts, rts, c); }	
		
inline Rational& operator /=(Rational &lts, const Rational &rts) 
{ return Rational::div(lts, rts, lts); }

inline Rational operator -(const Rational &src)
{ Rational ret(src); return ret.negate(); }	
				
std::istream& operator >>(std::istream&, Rational&);
