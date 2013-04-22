/***************************************************************************
                                cgiparse.cpp  
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

#include "cgiparse.h"

using namespace std;

CGIparse::CGIparse(CGImap & map)
{
  for (unsigned i=0; i<OPTIONS; i++)
    options[i] = false;

  for (CGImap::iterator it=map.begin(); it!=map.end(); it++)
  { 
    if ((*it).first == "fd")
      fdsetstring = trimString((*it).second);
    if ((*it).first == "ausgabe")
    {
      if ((*it).second == "redun")
	options[0] = true;
      if ((*it).second == "lreduz")
	options[1] = true;
      if ((*it).second == "rreduz")
	options[2] = true;
      if ((*it).second == "reduz")
	options[3] = true;
      if ((*it).second == "aequi")
	options[4] = true;
      if ((*it).second == "mini")
	options[5] = true;
      if ((*it).second == "3nf")
	options[6] = true;
    }
  }
}

string CGIparse::trimString(string str)
{
  unsigned long int position;

  while((position = str.find(' ')) != str.npos) // Whitespaces entfernen
    str.erase(position, 1);

  return str;
}
