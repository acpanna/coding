/***************************************************************************
                                  cgimap.h  
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

#ifndef _CGIMAP_H_
#define _CGIMAP_H_

#include "cgipair.h"

#include <vector>
#include <string>

// Diese Klasse beschreibt einen Vektor von (Name, Value) - Paaren
class CGImap : public std::vector<CGIpair> 
{
  public:
    CGImap(std::string query);

  private:
    CGIpair nextPair(); // Liefert das naechste im CGI-String gespeicherte (Name, Value) - Paar
    
	 std::string gq;
};

#endif
