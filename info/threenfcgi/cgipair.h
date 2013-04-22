/***************************************************************************
                                  cgipair.h  
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

#ifndef _CGIPAIR_H_
#define _CGIPAIR_H_

#include <vector>
#include <string>

// Diese Klasse repraesentiert ein 2-Tupel von Strings,
// und decodiert CGI-Sonderzeichen in den Strings
class CGIpair : public std::pair<std::string, std::string> 
{
  public:
    CGIpair();
    CGIpair(std::string name, std::string value);
    
    operator bool() const;

  private:
    static std::string decodeURLString(std::string URLstr); // Umwandeln der codierten CGI-Sonderzeichen
    static char translateHex(char hex);           // Hex-Zahlen in ASCII-Zeichen umwandeln
};

#endif
