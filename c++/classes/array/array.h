typedef double DATATYPE;

class Array {

private:
	DATATYPE *itsArray;
	unsigned int itsLen;

public:
	Array();
	Array(unsigned int len);
	Array(const DATATYPE *array, unsigned int len);
	Array(const Array &srArray);
	~Array();

	DATATYPE * GetArray(void) const;
	unsigned int GetLen(void) const;
	void SetArray(const DATATYPE *array, unsigned int len);
	void SetArray(const DATATYPE *array, unsigned int len, unsigned int start);
	void ZeroArray(void);
	void operator+= (const Array &array);
	Array operator+ (const Array &array);
	Array & operator++ (void);
	Array operator++ (int);
	Array & operator= (Array &array);
    Array & operator-- (void);
	Array operator-- (int);
	DATATYPE operator[] (unsigned int offset) const;
	DATATYPE & operator[] (unsigned int offset);
};