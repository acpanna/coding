#include <iostream.h>

#include "array.h"

Array::Array()
{
    itsArray = 0;
    itsLen = 0;
}

Array::Array(unsigned int len)
{
	itsLen = len;
	itsArray = new DATATYPE[itsLen];
	
	ZeroArray();
}

Array::Array(const DATATYPE *array, unsigned int len)
{
	itsLen = len;
	itsArray = new DATATYPE[itsLen];
	
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] = array[i];
}

Array::Array(const Array &srArray)
{
	itsLen = srArray.GetLen();
	itsArray = new DATATYPE[itsLen];
	itsArray = srArray.GetArray();
}

Array::~Array()
{
	itsLen = 0;
	delete [] itsArray;
}

DATATYPE * Array::GetArray(void) const
{
	DATATYPE *array;
	array = new DATATYPE[itsLen];

	for (unsigned int i=0; i<itsLen; i++)
		array[i] = itsArray[i];
	return array;
}

unsigned int Array::GetLen(void) const
{
	return itsLen;
}

void Array::SetArray(const DATATYPE *array, unsigned int len)
{
	if (itsLen < len)
	    len = itsLen;
		
	for (unsigned int i=0; i<len; i++)
		itsArray[i] = array[i];
}

void Array::SetArray(const DATATYPE *array, unsigned int len, unsigned int start)
{
	if (start > itsLen)
		start = itsLen;
	if (itsLen < start + len)
		len = itsLen - start;

	for (unsigned int i=start; i<start+len; i++)
		itsArray[i] = array[i-start];
}

void Array::ZeroArray(void)
{
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] = 0.0;
}

void Array::operator += (const Array &array)
{
	Array newArray(itsLen + array.GetLen());

	newArray.SetArray(itsArray, itsLen);
	newArray.SetArray(array.GetArray(), array.GetLen(), itsLen);
    
    delete [] itsArray;
    itsLen += array.GetLen();

	itsArray = new DATATYPE[itsLen];

	SetArray(newArray.GetArray(), itsLen);
}
 
Array Array::operator + (const Array &array)
{
	Array newArray(itsLen + array.GetLen());

	newArray.SetArray(itsArray, itsLen);
	newArray.SetArray(array.GetArray(), array.GetLen(), itsLen);
    
	return newArray;
}
 
Array & Array::operator++ (void)
{
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] += 1.0;
    return (*this);
}

Array Array::operator++ (int)
{
	Array temp(*this);
	
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] += 1.0;
	
	return temp;
}

Array & Array::operator= (Array &array)
{
	if (this == &array)
      return (*this);
    
    delete [] itsArray;
	
	itsLen = array.GetLen();
	itsArray = new DATATYPE[itsLen];

	SetArray(array.GetArray(), itsLen);

	return (*this);
}

Array & Array::operator-- (void)
{
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] -= 1.0;
    return (*this);
}

Array Array::operator-- (int)
{
	Array temp(*this);
	
	for (unsigned int i=0; i<itsLen; i++)
		itsArray[i] -= 1.0;
	
	return temp;
}
  
DATATYPE Array::operator[] (unsigned int offset) const
{
	if (offset > itsLen-1)
		offset = itsLen - 1;
	
	return itsArray[offset];
}

DATATYPE & Array::operator[] (unsigned int offset)
{
	if (offset > itsLen-1)
		offset = itsLen - 1;
	
	return itsArray[offset];
}






