/***************************************************************************
                                 cgimap.cpp  
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

#include "cgimap.h"

using namespace std;

CGImap::CGImap(string query)
{
  gq = query;
  
  CGIpair p;

  while ((p = nextPair()) != 0)
    push_back(p); // Anhaengen des (Name, Value) - Paares an Vektor    
}

CGIpair CGImap::nextPair() // Liefert das naechste (Name, Value) - Paar im CGI-String
{
  if (gq.length() == 0)
    return CGIpair(); 
  if ((signed char) gq.find('=') == -1)
    return CGIpair(); 
  
  string name = gq.substr(0, gq.find('='));
  gq = gq.substr(gq.find('=') + 1);
  string value = gq.substr(0, gq.find('&'));
  gq = gq.substr(gq.find('&') + 1);
  
  return CGIpair(name, value);
}
