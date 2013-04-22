/***************************************************************************
                          fdmengen.h  -  description
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

#ifndef _FDMENGEN_H_
#define _FDMENGEN_H_

#include "cgiparse.h"
#include <string>
#include <cstdlib>

#define ASSERT(x)  { if (x == NULL) { cout << "<font color=red>Fehler: Speicherreservierung fehlgeschlagen (" << #x << " == NULL) !!!</font><br>" << endl; exit(EXIT_FAILURE); } }


// --- BEGIN --- CLASS ATTRIBUTMENGE --- BEGIN ---
// "Attributmenge" ist die zugrundeliegende Struktur für die Aufschlüsselung von Attributen zu den FDs
// @author Rafael Fink & Sascha Herrmann
class Attributmenge 
{
  public:
    // boolVektor um die "Bitinformationen" aufzunehmen 
    bool *boolVektor;	

    // KONSTRUKTOR von class Attributmenge
    Attributmenge(); // Standartkonstruktor, liest IMMER "AnzahlAttribute" aus!!!

    // DESTRUKTOR von class Attributmenge
    ~Attributmenge();
   
    // Zuweisungsoperator fuer Attributmengen, setzt Member-Attributmenge gleich Att
    const Attributmenge & operator=(const Attributmenge & Att) const;
    
    // operator<= liefert TRUE zurück, falls die Member-Attributmenge TEILMENGE von Att ist 
    bool operator<=(const Attributmenge & Att) const;
    
    // Belegt die _Position im Attributsvektor mit _Wert 
    void setEintrag(const unsigned _Position, const bool _Wert);
    
    // Liefert den Eintrag des "boolVektor"s an der _Position zurück, eine 1 besagt dass das Attribut mit der Nummer _Position in der Attributmenge vorhanden ist! 
    bool getEintrag(const unsigned _Position) const;
  
    // "AnzahlAktiverAttribute" liefert die Zahl der Attribute in der zugehörigen Attributmenge zurück
    unsigned anzahlAktiveAttribute(void) const;

    // Schreibt die Attributmenge auf die Standardausgabe
    void printAttMenge(const std::string name = "") const;
};
// --- ENDE --- CLASS ATTRIBUTMENGE --- ENDE ---


// --- BEGIN --- CLASS FDMENGE --- BEGIN ---
// Enthält die Informationen für die FD-Mengenbeschreibung
// @author Rafael Fink & Sascha Herrmann
class FDMenge 
{
  public:                         	
    // Pointer auf ein ARRAY von LinkenSeiten der FD (Zusammenhang mit RechterSeite über ARRAY-Index!!)
    Attributmenge *LinkeSeite;
    
    // Pointer auf ein ARRAY von RechtenSeiten der FD (BSP: LinkeSeite[1] -> RechteSeite[1])
    Attributmenge *RechteSeite;

  private:
    // Gibt an wieviele FDs die FD-Menge enthaelt
    unsigned AnzahlFDs;

    // Dient zur Initialisierung der FDMenge aus einem CGIparse-Objekt
    void parseFDstring(const CGIparse & parstr);

  public:
    // KONSTRUKTOREN von class FDMenge
    FDMenge();
    FDMenge(const CGIparse & par);

    // DESTRUKTOR von class FDMenge	
    ~FDMenge();

    // Der Ausgabeumfang des Programms richtet sich nach diesem Vektor
    bool ausgabe[OPTIONS];
    
    // Liefert die Anzahl der FDs in dem zug. Object zurück 
    inline unsigned getAnzahlFDs(void) const { return AnzahlFDs; }

    // Erzeugt die Felder "Linke- und RechteSeite" vom Typ Attributmenge 
    void initialisiere(const unsigned _AnzahlFDs);
  
    // Setzen der linken Seite für einen ausgewählte FD 
    void setzeLinkeSeite(const unsigned FDNummer, const Attributmenge & Att);
  
    // Setzen der rechten Seite für einen ausgewählte FD 
    void setzeRechteSeite(const unsigned FDNummer, const Attributmenge & Att);
  
    // Gibt alle FDs aus (als <TABLE> im HTML-Format) 
    void printFDMenge(const std::string name = "") const;
  
    // Hinzufügen einer FD zu einer bestehenden FD-Menge 
    void hinzufuegen(const Attributmenge & LinkeSeite, const Attributmenge & RechteSeite);

    // Löschen überflüssiger FDs aus der FD-Menge über ihren Index 
    void loesche(const bool output);

    // Starte CGI-Output-Routine der FD-Menge
    bool starteAusgabe(void);
};
// --- ENDE --- CLASS FDMENGE --- ENDE ---


// GLOBALE Funktionen

// vereinige kennzeichnet die VEREINIGUNG zweier Attributmengen, also ODER Verknüpfung 
void vereinige(const Attributmenge& Att1, const Attributmenge& Att2, Attributmenge& Ergebnis);

// abziehen kennzeichnet die DIFFERENZ zweier Attributmengen, NICHT KOMMUTATIV 
void abziehen(const Attributmenge& Att1, const Attributmenge& Att2, Attributmenge& Ergebnis);

// Gibt die, durch die beiden Attributmengen left und right bestimmte, FD aus
void printFD(const Attributmenge & left, const Attributmenge & right);

// Berechnet den Abschluss einer Attributmenge bzgl. einer FD-Menge
void linclosure(const Attributmenge& ATT, const FDMenge& FDM, Attributmenge& Ergebnis);

// Mitgliedschaftstest: Impliziert FD-Menge F die FD X->Y, RÜCKGABE: true oder false
bool mitglied(const FDMenge& FDM, const Attributmenge& ls, const Attributmenge& rs);

// Reduziere die FD_Menge auf der LinkenSeite
void linksReduziert(FDMenge& FDM, const bool output);

// Reduziere die FD_Menge auf der RechtenSeite
void rechtsReduziert(FDMenge& FDM, const bool output);

// Reduzieren einer FD-Menge 
void reduziert(FDMenge& FDM, const bool verbose);

// Entfernt überflüssige FDs
void nichtRedundanteUeberdeckung(FDMenge& FDM);

// Gibt an, ob eine einzelne FD direkt von F impliziert wird 
bool direkteAbhaengigkeit(const FDMenge& FDM, const Attributmenge& ls, const Attributmenge& rs);

// Ordnet die FDs nach äquivalenten linken Seiten in einem Klassenvektor an 
// Klassenvektor muß vorher bereits angelegt sein (mit 0 vorinitialisiert) !!!!!!!
void aequivalenzklassen(const FDMenge& FDM, unsigned * const klassenvek, const bool verbose);

// Liefert eine minimale Überdeckung für die FD-Menge zurück
void minimaleUeberdeckung(FDMenge& FDM);

// Liefert die dritte Normalform, die aus einer minimalen, reduzierten FD-Menge resultiert
void dritteNormalform(const FDMenge& FDM);

// Durchsucht den Vektor AttributName[] nach dem in text stehenden string und trägt es ein, falls nicht gefunden
unsigned attributErkannt(const std::string text2);

// Durchsucht den Vektor AttributName[] nach dem in text stehenden string und liefert Position
long int attributFound(const std::string text2);

#endif
