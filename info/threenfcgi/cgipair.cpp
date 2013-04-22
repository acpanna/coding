/***************************************************************************
                                 cgipair.cpp  
                             -------------------
    begin                : Mon Dec 3 2001
    copyright            : (C) 2001 by Heiko Vogel
                                                    
    email                : Heiko.Vogel@stud.uni-bayreuth.de
			   
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "cgipair.h"

using namespace std;

CGIpair::CGIpair()
{}

CGIpair::CGIpair(string name, string value)
{
  first  = decodeURLString(name);
  second = decodeURLString(value);
}
  
CGIpair::operator bool() const
{
  return (first.length() != 0);
}
  
string CGIpair::decodeURLString(string URLstr)
{
  const int len = URLstr.length();
  string result;
  
  for (int i=0; i<len; i++) 
  {
    if (URLstr[i] == '+') // + durch <space> ersetzen
      result += ' ';
    else if (URLstr[i] == '%') // % maskiert Hexzahl
    {
      result += translateHex(URLstr[i+1]) * 16 + translateHex(URLstr[i+2]);
      i += 2; 
    } 
    else 
      result += URLstr[i]; // sonst normales ASCII-Zeichen
  }
    
  return result;
}
  
char CGIpair::translateHex(char hex) // Umrechnen Hex in ASCII
{
  if (hex >= 'A')
    return (hex - 'A' + 10);
  else
    return (hex - '0');
}
