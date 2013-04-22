/***************************************************************************
                                 cgipost.cpp  
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

#include "cgipost.h"
#include <iostream>

using namespace std;

CGIpost::CGIpost()
{
  char* clen = getenv("CONTENT_LENGTH"); // Laenge des Eingabestrings steht hier drin
  
  if (clen == 0) 
  {
    cout << "CONTENT_LENGTH = 0: Stellen Sie sicher, dass es sich um ein POST und kein GET handelt !!!<br>" << endl;
    exit(1);
  }
   
  int len = atoi(clen);
  char* s = new char[len];
  
  cin.read(s, len); // Einlesen des Eingabestrings
  append(s, len);   // Haengt den eingelesenen Eingabestring an internes string-Objekt 
                    // ( CGIpost ist abgeleitet von string ) 
  
  delete []s;
} 
