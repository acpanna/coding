/***************************************************************************
                                   main.cpp  
                             -------------------
    begin                : Mon Jun 25 2001
    copyright            : (C) 2001 by Rafael Fink, Sascha Herrmann
                                                    & Heiko Vogel
    email                : Rafael.Fink@stud.uni-bayreuth.de, 
                           Sascha.Herrmann@uni-bayreuth.de
			   Heiko.Vogel@stud.uni-bayreuth.de
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
#include "cgimap.h"
#include "cgiparse.h"
#include "fdmengen.h"

#include <iostream>

using namespace std;

int main() 
{
  cout << "Content-type: text/html\n" << endl;
  cout << "<html>" << endl;
  cout << "<body>" << endl;
  cout << "<head>" << endl;
  cout << "<title>ThreeNF --  Eine Web-Applikation zur Berechnung der 3. Normalform eines Relationenschemas</title>" << endl;
  cout << "</head>" << endl;
  cout << "<body bgcolor=#ffffff>" << endl;
  cout << "<div align=center>" << endl;
  cout << "<h1>ThreeNF</h1>" << endl;
  cout << "<hr align=center width=500>" << endl;
  cout << "<br>" << endl;
  
  CGIpost p;               // Abholen der Daten von Standardeingabe
  CGImap query(p);         // Bilden eines Vektors mit (Name, Value) - Paaren 
  CGIparse parsed(query);  // Parsen des (Name, Value) - Paar - Vektors
  
  FDMenge fd(parsed);      // Konstruktion der FD-Menge aus den Daten des geparsten Vektors

  fd.starteAusgabe();      // Starte Ausgaberoutine

  cout << "</div>" << endl;
  cout << "</body>" << endl;
  cout << "</html>" << endl;

  return 0;  
}
