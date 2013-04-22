/***************************************************************************
                                 cgiparse.h  
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

#ifndef _CGIPARSE_H_
#define _CGIPARSE_H_

#include "cgimap.h"

#define OPTIONS 7

// Diese Klasse zerlegt den (Name, Value) - Paar - Vektor in die FD-Menge 
// und die gewuenschten Ausgabeoptionen 
class CGIparse
{
  public:
    CGIparse(CGImap & map);
   
	 std::string fdsetstring;
    bool options[OPTIONS];
    
  private:
	 std::string trimString(std::string str); // entfernt Leerzeichen aus dem String
};

#endif
