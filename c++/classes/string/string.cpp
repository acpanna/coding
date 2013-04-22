#include <string.h>

#include "string.h"

String::String(void)
{
  itsLen = 0;
  itsString = new char[1];
  itsString[0] = '\0';
}

String::String(unsigned short len)
{
  itsString = new char[len+1];
  
  for (unsigned short i = 0; i <= len ; i++)
    itsString[i] = '\0';

  itsLen = len;
}

String::String(const char * const String)
{
  itsLen = strlen(String);
  itsString = new char[itsLen+1];
  
  for (unsigned short i = 0; i < itsLen ; i++)
    itsString[i] = String[i];

  itsString[itsLen] = '\0';
}

String::String(const String &classtring)
{
  itsLen = classtring.GetLen();
  itsString = new char[itsLen+1];

  for (unsigned short i = 0; i < itsLen ; i++)
    itsString[i] = classtring[i];

  itsString[itsLen] = '\0';
}

String::~String(void)
{
  delete [] itsString;
  itsLen = 0;
}

String & String::operator= (const String &classtring)
{
  if (this == &classtring)
    return *this;
  delete [] itsString;
  itsLen = classtring.GetLen();
  itsString = new char[itsLen+1];

  for (unsigned short i = 0; i < itsLen ; i++)
    itsString[i] = classtring[i];

  itsString[itsLen] = '\0';

  return *this;
}

char & String::operator[] (unsigned short offset)
{
  if (offset > itsLen)
    return itsString[itsLen-1];
  return itsString[offset];
}

char String::operator[] (unsigned short offset) const
{
  if (offset > itsLen)
    return itsString[itsLen-1];
  return itsString[offset];
}

String String::operator+ (const String &classtring)
{
  unsigned short totalLen = itsLen + classtring.GetLen();
  String temp(totalLen);
    
  for (unsigned short i = 0; i < itsLen ; i++)
    temp[i] = itsString[i];
  for (unsigned short j = 0; j < classtring.GetLen() ; j++, i++)
    temp[i] = classtring[j];

  temp[totalLen] = '\0';
  return temp;
}
  


