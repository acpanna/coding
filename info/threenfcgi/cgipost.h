/***************************************************************************
                                 cgipost.h
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

#ifndef _CGIPOST_H_
#define _CGIPOST_H_

#include <string>
#include <cstdlib>

// Diese Klasse liest den CGI-Eingabestring von der Standardeingabe
class CGIpost : public std::string 
{
  public:
    CGIpost();
};

#endif
