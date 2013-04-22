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

#include "fdmengen.h"
#include <iostream>

// GLOBALE VARIABLE zum Aufnehmen der Attributszahl
unsigned AnzahlAttribute = 0;

// Pointer auf ein GLOBALES ARRAY von STRINGS um die Namen der Attribute aufzunehmen
std::string *AttributName;

using namespace std;

Attributmenge::Attributmenge()
{
  if (AnzahlAttribute < 1)
  {
    cout << "<font color=red>Fehler: Es wurde <b>weniger als ein Attribut</b> gew&uuml;nscht !!!</font><br>" << endl;
    exit(EXIT_FAILURE);
  }    
    
  boolVektor = new bool[AnzahlAttribute]; // Attributvektor anlegen
  ASSERT(boolVektor);
    
  for (unsigned i=0; i<AnzahlAttribute; i++)
    boolVektor[i] = false; // Mit false vorbelegen
}

Attributmenge::~Attributmenge()
{
    delete [] boolVektor;
    boolVektor = NULL;
}  

const Attributmenge & Attributmenge::operator=(const Attributmenge & Att) const
{
  for (unsigned i=0; i<AnzahlAttribute; i++) 
    boolVektor[i] = Att.boolVektor[i]; // Zuweisungen komponentenweise durchfuehren

  return (*this);
}

bool Attributmenge::operator<=(const Attributmenge & Att) const
{
  bool teilmenge = true;
  unsigned i = 0;

  do
  {
    if ((Att.getEintrag(i) == false) && (getEintrag(i) == true)) 
      teilmenge = false; 

    i++;
  } while ((teilmenge == true) && (i < AnzahlAttribute));

  return teilmenge;
}

void Attributmenge::setEintrag(const unsigned _Position, const bool _Wert)
{
  if (_Position >= AnzahlAttribute)
  {
    cout << "<font color=red>Fehler: Es wurde versucht <b>ausserhalb eines g&uuml;ltigen Bereichs</b> zuzugreifen !!!</font><br>" << endl;
    exit(EXIT_FAILURE);
  }

  boolVektor[_Position] = _Wert;
}

bool Attributmenge::getEintrag(const unsigned _Position) const
{
  if (_Position >= AnzahlAttribute)
  {
    cout << "<font color=red>Fehler: Es wurde versucht <b>ausserhalb eines g&uuml;ltigen Bereichs</b> zuzugreifen !!!</font><br>" << endl;
    exit(EXIT_FAILURE);
  }

  else
    return boolVektor[_Position];
}

unsigned Attributmenge::anzahlAktiveAttribute(void) const
{
  unsigned summe = 0;
  
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (getEintrag(i) == true) // Wenn Eintrag true ist ==> Attribut ist aktiv
      summe++;

  return summe;
}

void Attributmenge::printAttMenge(const string name) const
{
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (getEintrag(i) == true)
      cout << AttributName[i] << " ";
}


FDMenge::FDMenge()
{
  LinkeSeite = NULL;
  RechteSeite = NULL;
  AnzahlFDs = 0;

  for (unsigned i=0; i<OPTIONS; i++)
    ausgabe[i] = false;
}

FDMenge::FDMenge(const CGIparse & par)
{
  LinkeSeite = NULL;
  RechteSeite = NULL;
  AnzahlFDs = 0;

  for (unsigned i=0; i<OPTIONS; i++)
    ausgabe[i] = par.options[i];
  
  parseFDstring(par);
}

FDMenge::~FDMenge()
{
  delete [] LinkeSeite;
  LinkeSeite = NULL;
    
  delete [] RechteSeite;
  RechteSeite = NULL;
}

void FDMenge::initialisiere(const unsigned _AnzahlFDs)
{
  if (_AnzahlFDs <= 0)
  {
    cout << "<font color=red>Fehler: Es wurde versucht eine <b>FDMenge mit 0! FDs</b> zu erzeugen !!!</font><br>";
    exit(EXIT_FAILURE);
  }

  AnzahlFDs = _AnzahlFDs; // Hier wird die Membervariable gesetzt
    
  delete [] LinkeSeite;
  delete [] RechteSeite;
  
  // Initialisierung von LinkeSeite und RechteSeite
  LinkeSeite = new Attributmenge[_AnzahlFDs];
  RechteSeite = new Attributmenge[_AnzahlFDs];

  ASSERT(LinkeSeite);
  ASSERT(RechteSeite);
}

void FDMenge::setzeLinkeSeite(const unsigned FDNummer, const Attributmenge & Att)
{
  if (FDNummer >= AnzahlFDs)
  {
    cout << "<font color=red>Fehler: Es wurde versucht <b>ausserhalb eines g&uuml;ltigen Bereichs</b> zuzugreifen !!!</font><br>" << endl;
    exit(EXIT_FAILURE);
  }

  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (Att.getEintrag(i) == true)
      LinkeSeite[FDNummer].setEintrag(i, true);
    else
      LinkeSeite[FDNummer].setEintrag(i, false);
}

void FDMenge::setzeRechteSeite(const unsigned FDNummer, const Attributmenge & Att)
{
  if (FDNummer >= AnzahlFDs)
  {
    cout << "<font color=red>Fehler: Es wurde versucht <b>ausserhalb eines g&uuml;ltigen Bereichs</b> zuzugreifen !!!</font><br>" << endl;
    exit(EXIT_FAILURE);
  }

  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (Att.getEintrag(i) == true)
      RechteSeite[FDNummer].setEintrag(i, true);
    else
      RechteSeite[FDNummer].setEintrag(i, false);
}

void FDMenge::printFDMenge(const string name) const
{
  // Ausgabe der FD-Menge als HTML-Tabelle
  cout << "<table border=1 cellspacing=3>" << endl;
  cout << "<tr><th>" << name << "</th></tr>" << endl;
  cout << "<tr><td>";
  cout << "<table>" << endl;
  
  for (unsigned i=0; i<AnzahlFDs; i++)
  {
    cout << "<tr><td>";
    for (unsigned j=0; j<AnzahlAttribute; j++)
      if (LinkeSeite[i].getEintrag(j) == true)
        cout << AttributName[j] << " ";
	
    cout << "</td><td>-> <td>";

    for (unsigned j=0; j<AnzahlAttribute; j++)
      if (RechteSeite[i].getEintrag(j) == true)
        cout << AttributName[j] << " ";
	
    cout << "</td></tr>" << endl;
  }

  cout << "</table>" << endl;
  cout << "</td></tr>" << endl;
  cout << "</table>" << endl;
}

void FDMenge::hinzufuegen(const Attributmenge & ls, const Attributmenge & rs)
{
  Attributmenge *templs = NULL;
  Attributmenge *temprs = NULL;

  AnzahlFDs++; // Die Membervariable wird um 1 hochgezählt
	
  templs = new Attributmenge[AnzahlFDs];
  temprs = new Attributmenge[AnzahlFDs];

  ASSERT(templs);
  ASSERT(temprs);

  for (unsigned i=0; i<AnzahlFDs-1; i++)
  {
    templs[i] = LinkeSeite[i];
    temprs[i] = RechteSeite[i];
  }

  delete [] LinkeSeite;
  delete [] RechteSeite;

  LinkeSeite = templs;
  RechteSeite = temprs;

  // Hier erfolgt das eigentliche Hinzufuegen der FD
  setzeLinkeSeite(AnzahlFDs-1, ls); 
  setzeRechteSeite(AnzahlFDs-1, rs);
}

void FDMenge::loesche(const bool output)
{
  Attributmenge *templs = NULL;
  Attributmenge *temprs = NULL;

  bool *DELIST = new bool[AnzahlFDs];
  ASSERT(DELIST);
  
  unsigned DELCOUNT = 0;
  unsigned j = 0;

  for (unsigned i=0; i<AnzahlFDs; i++)
    if (RechteSeite[i].anzahlAktiveAttribute() == 0)
    {
      if (output == true)
      {
        cout << "<br>Die FD: ";
        printFD(LinkeSeite [i], RechteSeite[i]);
        cout << "0 ist trivial und wird entfernt" << endl;
      }
      
      DELIST[i] = true;
      DELCOUNT++;
    }
    else
      DELIST[i] = false;

  templs = new Attributmenge[AnzahlFDs - DELCOUNT];
  temprs = new Attributmenge[AnzahlFDs - DELCOUNT];

  ASSERT(templs);
  ASSERT(temprs);
  
  for (unsigned i=0; i<AnzahlFDs; i++)
    if (DELIST[i] == false)  // (templ, temprs) repraesentieren nicht-triviale FDs
    {
      templs[j] = LinkeSeite[i];
      temprs[j] = RechteSeite[i];
      j++;
    }

  AnzahlFDs = AnzahlFDs - DELCOUNT; // AnzahlFDs wird auf den neuen Wert gesetzt                    

  delete [] LinkeSeite;
  delete [] RechteSeite;
  
  LinkeSeite = templs;
  RechteSeite = temprs;

  delete [] DELIST;
  DELIST = NULL;
}

void FDMenge::parseFDstring(const CGIparse & parstr)
{
  unsigned long int position;
  long int pos;

  string fdsetstring, fdstring, attribut, left, right;

  Attributmenge *eingabeLinkeSeite = NULL;
  Attributmenge *eingabeRechteSeite = NULL;
  Attributmenge *LEER = NULL;

  for (int run=0; run<=1; run++)
  {
    if (run == 1) // Befinden wir uns im zweiten Durchlauf, so ist die Anzahl der Attribute bekannt und Attrbutmengen koennen erzeugt werden
    {
      eingabeLinkeSeite = new Attributmenge();
      eingabeRechteSeite = new Attributmenge();
      LEER = new Attributmenge();

      ASSERT(eingabeLinkeSeite);
      ASSERT(eingabeRechteSeite);
      ASSERT(LEER);
    }

    fdsetstring = parstr.fdsetstring;

    if (fdsetstring == "" && run == 0)
    {
      cout << "Die eingebene <b>FD-Menge ist leer</b> -- Bitte benutzen Sie den Back-Button des Browsers, \
	um Ihre Eingabe zu &uuml;berpr&uuml;fen!<br>" << endl;
      exit(EXIT_FAILURE);
    }

    if (fdsetstring.at(fdsetstring.length()-1) != '\n') // fdsetstring soll mit \r\n aufhoeren
      fdsetstring = fdsetstring + "\r\n";

    while (fdsetstring != "")
    {
      bool parsed = false;

      position = fdsetstring.find('\r');

      fdstring = fdsetstring.substr(0, position); // fdstring enthaelt erste FD 
      fdsetstring = fdsetstring.substr(position+2); // fdsetstring enthaelt restl. FDs

      position = fdstring.find('>'); 

      if (position == fdstring.npos && run == 0) // In der FD wurde kein > gefunden ==> fehlerhafte FD
      {
        cout << "Es wurde eine <b>fehlerhafte FD</b> eingegeben -- Bitte benutzen Sie den Back-Button des Browsers, \
	  um Ihre Eingabe zu &uuml;berpr&uuml;fen!<br>" << endl;
        exit(EXIT_FAILURE);
      }

      left = fdstring.substr(0, position); // left enthaelt linke Seite der FD
      right = fdstring.substr(position+1); // right enthaelt rechte Seite der FD

      while (parsed == false)
      {
        position = left.find(',');

        if (position == left.npos) // gibt kein Komma mehr in linker Seite ==> left stellt nur noch ein einziges Attribut dar, also wurde die linke Seite geparst
        {
          attribut = left;
          parsed = true;
        }
        else
        {
          attribut = left.substr(0, position); // ansonsten: links vom Komma steht Attribut
          left = left.substr(position+1); // left enthaelt restl. linke Seite
        }

        if (attribut == "" && run == 0) // Falls zwischen zwei Kommas nix steht oder nur Whitespaces ==> leeres Attribut
        {
          cout << "Es wurde ein <b>&#039;leeres&#039; Attribut</b> eingegeben -- Bitte benutzen Sie den Back-Button des Browsers, \
	    um Ihre Eingabe zu &uuml;berpr&uuml;fen!<br>" << endl;
          exit(EXIT_FAILURE);
        }

        if (run == 0)
          attributErkannt(attribut); // Im ersten Durchlauf die Attribute erkennen
	else if (run == 1)
	{
	  pos = attributFound(attribut);  
          eingabeLinkeSeite->setEintrag(pos, true); // Im zweiten Durchlauf das Bit, das dem Attribut entspricht, setzen
	}
      }

      parsed = false;

      while (parsed == false)
      {
        position = right.find(',');

        if (position == right.npos) // gibt kein Komma mehr in rechter Seite ==> right stellt nur noch ein einziges Attribut dar, also wurde die rechte Seite geparst
        {
          attribut = right;
          parsed = true;
        }
        else
        {
          attribut = right.substr(0, position); // ansonsten: links vom Komma steht Attribut
          right = right.substr(position+1); // right enthaelt restl. rechte Seite
        }

        if (attribut == "" && run == 0) // Falls zwischen zwei Kommas nix steht oder nur Whitespaces ==> leeres Attribut
        {
          cout << "Es wurde ein <b>&#039;leeres&#039; Attribut</b> eingegeben -- Bitte benutzen Sie den Back-Button des Browsers, \
	    um Ihre Eingabe zu &uuml;berpr&uuml;fen!<br>" << endl;
          exit(EXIT_FAILURE);
        }

        if (run == 0)
          attributErkannt(attribut); // Im ersten Durchlauf die Attribute erkennen
        else if (run == 1)
        {
          pos = attributFound(attribut);
          eingabeRechteSeite->setEintrag(pos, true); // Im zweiten Durchlauf das Bit, das dem Attribut entspricht, setzen
        }
      }

      if (run == 1)
      {
        hinzufuegen((*eingabeLinkeSeite), (*eingabeRechteSeite)); // Hinzufuegen der erkannten FD 
        vereinige((*LEER), (*LEER), (*eingabeLinkeSeite));  // eingabeLinkeSeite wieder "reset"en
	vereinige((*LEER), (*LEER), (*eingabeRechteSeite)); // eingabeRechteSeite wieder "reset"en
      }
    }
  }

  delete eingabeLinkeSeite;
  delete eingabeRechteSeite;
  delete LEER;
  
  eingabeLinkeSeite = NULL;
  eingabeRechteSeite = NULL;
  LEER = NULL;
}

bool FDMenge::starteAusgabe(void)
{
  cout << "Die Bedeutung der Begriffe:<p><b>Attribut, Attributmenge, Relationsschema, Relation, FD, FD-Menge, Abschluss einer Attributmenge,<br>Abschluss einer FD-Menge,\
    Erzeugnis einer FD-Menge und &Auml;quivalenz zweier FD-Mengen</b></p>wird als bekannt vorausgesetzt.<br>" << endl;
  cout << "<br>" << endl; 

  printFDMenge("eingelesene FD-Menge");
  
  minimaleUeberdeckung(*this);
  dritteNormalform(*this);

  return true;
}


void vereinige(const Attributmenge& Att1, const Attributmenge& Att2, Attributmenge& Ergebnis)
{
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if ((Att1.getEintrag(i) == true) || (Att2.getEintrag(i) == true))
      Ergebnis.setEintrag(i, true); // Wenn eine der beiden Attributmengen Attribut enthaelt ==> Ergebnis enthaelt Attribut
    else
      Ergebnis.setEintrag(i, false); // sonst ==> Ergebnis enthaelt Attribut nicht
}

void abziehen(const Attributmenge & Att1, const Attributmenge & Att2, Attributmenge & Ergebnis)
{
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if ((Att1.getEintrag(i) == true) && (Att2.getEintrag(i) == true))
      Ergebnis.setEintrag(i, false); // Wenn Att2 Attribut enthaelt ==> Ergebnis enthaelt Attribut nicht
    else
      Ergebnis.setEintrag(i, Att1.getEintrag(i)); // sonst ==> Eintrag im Ergebnis ist derselbe wie in Att1 
}

void printFD(const Attributmenge & left, const Attributmenge & right)
{
  for (unsigned j=0; j<AnzahlAttribute; j++)
    if (left.getEintrag(j) == true)
      cout << AttributName[j] << " ";

  cout << "-> ";

  for (unsigned j=0; j<AnzahlAttribute;j++)
    if (right.getEintrag(j) == true)
      cout << AttributName[j] << " ";
}

void linclosure(const Attributmenge & ATT, const FDMenge & FDM, Attributmenge & Ergebnis)
{
  unsigned i, j;
  unsigned fdanzahl = FDM.getAnzahlFDs();

  unsigned *count;
  unsigned *list;
	
  count = new unsigned[fdanzahl];
  ASSERT(count);
	
  list = new unsigned[fdanzahl * AnzahlAttribute];
  ASSERT(list);
  
  for (unsigned i=0 ; i<fdanzahl*AnzahlAttribute; i++)
    list[i] = 0;
	
  Attributmenge NEWDEP;
  Attributmenge UPDATE;
  Attributmenge ADD;
  Attributmenge NIX;

  // count[i] enthaelt Anzahl der aktiven Attribute der i-ten FD
  // list[i,j] enthaelt 1, wenn j-tes Attribut auf linker Seite der i-ten FD aktiv
  for (i=0; i<fdanzahl; i++)
  {
    count[i] = FDM.LinkeSeite[i].anzahlAktiveAttribute();

    for (j=0; j<AnzahlAttribute; j++)
    {
      if (FDM.LinkeSeite[i].getEintrag(j) == true)
        list[i * AnzahlAttribute + j] = 1;
    }
  }

  vereinige(NEWDEP, ATT, NEWDEP); // NEWDEP gleich ATT setzen
  vereinige(UPDATE, ATT, UPDATE); // UPDATE gleich ATT setzen

  while (UPDATE.anzahlAktiveAttribute() != 0) // Solange es noch aktiveAttribute in UPDATE gibt 
  {
    i = 0;

    while (UPDATE.getEintrag(i) == false)
      i++;

    UPDATE.setEintrag(i, false); // Waehle i-tes Attribut aus UPDATE
		
    for (j=0; j<fdanzahl; j++)
    {
      if (list[i + j * AnzahlAttribute] == 1)
      {
        count[j]--; // Verringere count Zaehler der j-ten FD, falls i-tes Attribut auf linker Seite aktiv ist

	if (count[j] == 0) // Falls count Zaehler = 0 ist ==> Rechte Seite der j-ten FD kann zum Abschluss mit dazugenommen werden
	{
	  abziehen(FDM.RechteSeite[j], NEWDEP, ADD);
	  vereinige(NEWDEP, ADD, NEWDEP); // Neuer Abschluss = alter Abschluss + rechte Seite der j-ten FD
	  vereinige(UPDATE, ADD, UPDATE); // Untersucht werden muessen ausserdem noch alle noch nicht im alten Abschluss gelegenen Attribute
	}
      }
    }
  }

  vereinige (NEWDEP, NIX, Ergebnis); // NEWDEP am Ende liefert Abschluss

  delete [] list;
  delete [] count;
  
  count = NULL;
  list = NULL;
}

bool mitglied(const FDMenge & FDM, const Attributmenge & ls, const Attributmenge & rs)
{
  Attributmenge erg;

  linclosure(ls, FDM, erg);

  if (rs <= erg) // Wenn rechte Seite der FD im Abschluss der linken Seite liegt ==> Mitglied, sonst nicht 
    return true;
  else
    return false;
}

void linksReduziert(FDMenge & FDM, const bool output)
{
  Attributmenge HILF;

  if (output == true && FDM.ausgabe[1] == true) 
  {
    cout << "<br><br><h3>Bestimmung der links-reduzierten &Uuml;berdeckung:</h3>" << endl;
    
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td colspan=2 align=center>Sei F eine nicht-redundante FD-Menge &uuml;ber dem Relationsschema R und X->Y ein Element von F.</td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Ein Attribut A aus R heisst <b>links-herausziehbar</b> aus X falls X = A Z (wobei A kein Element von Z) \
      und F&#039; = F - {X->Y} + {Z->Y} &auml;quivalent zu F ist.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>X->Y heisst <b>links-reduziert</b>, falls X kein links-herausziehbares Element besitzt. \
      Die Menge F heisst demnach links-reduziert, falls jede FD aus F links-reduziert ist.</i></td></tr>" << endl; 
    cout << "<tr><td valign=top>Folgerung:</td><td>Gibt es eine FD X->Y aus F und ein Attribut A aus X, so dass sich die FD X-A->Y aus F erzeugen l&auml;sst, \
      so ist die FD X->Y nicht links-reduziert und kann durch X-A->Y ersetzt werden.</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man &uuml;berpr&uuml;ft sukzessive alle FDs aus F, ob sie links-herausziehbare Attribute besitzen und geht dann, wie \
      in der Folgerung beschrieben vor. Ergebnis ist eine linksreduzierte FD-Menge.</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion LINKS_REDUZIERT():</i><br>" << endl; 
  }
    
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    bool notreduced = false;
    
    for (unsigned k=0; k<AnzahlAttribute; k++)
    {
      if (FDM.LinkeSeite[i].getEintrag(k) == true)
      {
        for (unsigned l=0; l<AnzahlAttribute; l++)
          HILF.setEintrag(l, false);  // HILF mit false vorbesetzen

	vereinige(FDM.LinkeSeite[i], HILF, HILF);  // HILF gleich linker linker Seite der i.ten FD setzen
        HILF.setEintrag(k, false); // k.tes Attribut aus HILF entfernen

	if (mitglied(FDM, HILF, FDM.RechteSeite[i]) == true) // Prüfen, ob rechte Seite der i.ten FD im Abschluss von HILF liegt, falls ja ==> nicht-linksreduziert
	{
	  if (notreduced == true && output == true && FDM.ausgabe[1] == true)
	    cout << " " << AttributName[k];
	  
	  if (notreduced == false && output == true && FDM.ausgabe[1] == true)
	  {
	    notreduced = true;
	    cout << "<br>Die FD: ";
	    printFD(FDM.LinkeSeite [i], FDM.RechteSeite[i]);
	    cout << " ist nicht links-reduziert, herausziehbare(s) Attribut(e): " << AttributName[k];
	  }
	  
	  FDM.LinkeSeite[i].setEintrag(k, false); // k.tes Attribut aus linker Seite der i.ten FD entfernen
	}
      }
    }
  }

  if (output == true && FDM.ausgabe[1] == true)
  {
    cout << "<br><br>" << endl;
    FDM.printFDMenge("links-reduzierte &Uuml;berdeckung");
  }
}

void rechtsReduziert(FDMenge & FDM, const bool output)
{
  Attributmenge HILF;

  if (output == true && FDM.ausgabe[2] == true)
  { 
    cout << "<br><br><h3>Bestimmung der rechts-reduzierten &Uuml;berdeckung:</h3>" << endl;
   
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td colspan=2 align=center>Sei F eine nicht-redundante FD-Menge &uuml;ber dem Relationsschema R und X->Y ein Element von F.</td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Ein Attribut A aus R heisst <b>rechts-herausziehbar</b> aus Y, falls Y = A W (wobei A kein Element von W) \
      und F&#039; = F - {X->Y, X->W} &auml;quivalent zu F ist.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>X->Y heisst <b>rechts-reduziert</b>, falls Y kein rechts-herausziehbares Element besitzt. Die Menge F \
      heisst demnach rechts-reduziert, falls jede FD aus F rechts-reduziert ist.</i></td></tr>" << endl;
    cout << "<tr><td valign=top>Folgerung:</td><td>Gibt es eine FD X->Y aus F und ein Attribut A aus Y, so dass sich die FD X->A aus der Menge \
      F&#039; = F - {X->Y} + {X->Y-A} erzeugen l&auml;sst, so ist die FD X->Y nicht rechts-reduziert und kann durch X->Y-A ersetzt werden.</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man &uuml;berpr&uuml;ft sukzessive alle FDs aus F, ob sie rechts-herausziehbare Attribute besitzen und geht wie\
      in der Folgerung beschrieben vor. Ergebnis ist eine rechts-reduzierte FD-Menge.</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion RECHTS_REDUZIERT():</i><br>" << endl; 
  }

  for (unsigned i=0 ; i<AnzahlAttribute; i++)
    HILF.setEintrag(i, false); // HILF mit false vorbesetzen
	
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    bool notreduced = false;
    
    for (unsigned k=0; k<AnzahlAttribute; k++)
    {
      if (FDM.RechteSeite[i].getEintrag(k) == true)
      {
        FDM.RechteSeite[i].setEintrag(k, false); // k.tes Attribut auf rechter Seite der i.ten FD entfernen
        HILF.setEintrag(k, true); // und in HILF setzen
		       
	if (mitglied(FDM, FDM.LinkeSeite[i], HILF) == false) // Wenn HILF (also entferntes Attribut) sich nicht durch linke Seite herleiten laesst ==> rechts-reduziert
          FDM.RechteSeite[i].setEintrag(k, true); // also muss zuvor entferntes Attribut wieder hinzugefuegt werden
	else // sonst nicht-rechtsreduziert
	{  
	  if (notreduced == true && output == true && FDM.ausgabe[2] == true)
	    cout << " " << AttributName[k];
	  
	  if (notreduced == false && output == true && FDM.ausgabe[2] == true)
	  {
	    notreduced = true;
	    FDM.RechteSeite[i].setEintrag(k, true);
	    cout << "<br>Die FD: ";
	    printFD(FDM.LinkeSeite[i], FDM.RechteSeite[i]);
	    cout << " ist nicht rechts-reduziert, herausziebare(s) Attribut(e): " << AttributName[k];
            FDM.RechteSeite[i].setEintrag(k, false);
	  }
	}
	
	HILF.setEintrag(k, false); // HILF wieder in Ausgangszustand versetzen
      }
    }
  }

  if (output == true && FDM.ausgabe[2] == true)
  {
    cout << "<br><br>" << endl;
    FDM.printFDMenge("rechts-reduzierte &Uuml;berdeckung");
  }
}

void reduziert(FDMenge & FDM, const bool verbose)
{
  linksReduziert(FDM, verbose);
  rechtsReduziert(FDM, verbose);

  if (verbose == true && FDM.ausgabe[3] == true)
  {
    cout << "<br><br><h3>Bestimmung der reduzierten &Uuml;berdeckung:</h3>" << endl;
  
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine FD-Menge F heisst <b>reduziert</b>, wenn sie sowohl links-, als auch rechts-reduziert ist \
      und keine trivialen FDs der Form X->0 (0 = leeres Attribut) enth&auml;lt.</i></td></tr>" << endl;
    cout << "<tr><td valign=top>Folgerung:</td><td>Durch aufeinanderfolgende Anwendung der Funktionen NICHT_REDUNDANT(), LINKS_REDUZIERT(), RECHTS_REDUZIERT() \
      und anschliessendem Entfernen der FDs der Form X->0 erh&auml;lt man eine reduzierte FD-Menge.</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>analog Folgerung</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion REDUZIERT():</i><br>" << endl; 
  }

  FDM.loesche(verbose);
  
  if (verbose == true && FDM.ausgabe[3] == true)
  {
    cout << "<br><br>" << endl; 
    FDM.printFDMenge("reduzierte &Uuml;berdeckung");
  }
}

void nichtRedundanteUeberdeckung(FDMenge & FDM)
{
  Attributmenge ls, rs;

  if (FDM.ausgabe[0] == true)
  {
    cout << "<br><br><h3>Bestimmung der nicht-redundanten &Uuml;berdeckung:</h3>" << endl;
    
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine FD-Menge F über dem Relationsschema R heisst <b>nicht-redundant</b>, falls es keine \
      echte Teilmenge F&#039; von F gibt, die &auml;quivalent zu F ist.</i></td></tr>"<< endl;
    cout << "<tr><td valign=top>Folgerung:</td><td>Gibt es eine echte Teilmenge F&#039; von F, so dass die Mengen der FDs, die sich mit F bzw. F&#039; erzeugen lassen, \
      gleich sind ==&gt; die FDs aus F-F&#039; sind redundant und k&ouml;nnen weggelassen werden.</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man entfernt sukzessive FDs aus F und &uuml;berpr&uuml;ft, ob der Abschluss der resultierenden FD-Menge F&#039; \
      derselbe ist, wie der Abschluss von F. Falls ja, so setzt man F = F&#039;, andernfalls bleibt F unver&auml;ndert. \
      Dies f&uuml;hrt man solange fort, bis man alle FDs aus F auf diese Weise durchprobiert hat. \
      Die resultierende Menge ist dann eine nicht-redundante &Uuml;berdeckung der urspr&uuml;nglichen Menge.</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion NICHT_REDUNDANT():</i><br>" << endl; 
  }
  
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    for (unsigned j=0; j<AnzahlAttribute; j++)
    {
      ls.setEintrag(j, FDM.LinkeSeite[i].getEintrag(j)); // i.te FD waehlen
      rs.setEintrag(j, FDM.RechteSeite[i].getEintrag(j));
					
      FDM.LinkeSeite[i].setEintrag(j, false); // i.te FD aus F entfernen
      FDM.RechteSeite[i].setEintrag(j, false);
    }

    if (mitglied(FDM, ls, rs) == false) // Liegt FD X->Y nicht Abschluss von F-{X->Y} ==> FD darf nicht weggelassen werden 
    {
      FDM.setzeLinkeSeite(i, ls);
      FDM.setzeRechteSeite(i, rs);
    }

    else // sonst ==> FD ist redundant 
      if (FDM.ausgabe[0] == true)
      {
        cout << "<br>Die FD: ";
        printFD(ls, rs);
	cout << " ist redundant" << endl;
      }
  }

  FDM.loesche(false);

  if (FDM.ausgabe[0] == true)
  {
    cout << "<br><br>" << endl;
    FDM.printFDMenge("nicht-redundante &Uuml;berdeckung");
  }
}

bool direkteAbhaengigkeit(const FDMenge & FDM, const Attributmenge & ls, const Attributmenge & rs)
{
  FDMenge G;

  Attributmenge erg, HILF, NIX;

  unsigned *entf;
  unsigned zaehler = 0;

  entf = new unsigned[FDM.getAnzahlFDs()];
  ASSERT(entf);	
  
  linclosure(ls, FDM, erg);
	
  // Feststellen aller FDs deren linken Seiten aequivalent zu ls sind
  // Falls linke Seite der i.ten FD aequivalent ==> entf[i] = 1, sonst 0
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    entf[i] = 0;
    
    if (FDM.LinkeSeite[i] <= erg)
    {
      linclosure(FDM.LinkeSeite[i], FDM, HILF);
		
      if (ls <= HILF)
        entf[i] = 1;
    }
  }

  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
    if (entf[i] == 0)
      zaehler++;

  G.initialisiere(zaehler);
  zaehler = 0;
  
  // Bilde FD-Menge G, die alle FDs aus F enthaelt, deren linken Seiten nicht aequivalent zu ls sind
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    if (entf[i] == 0)
    {
      G.setzeLinkeSeite(zaehler, FDM.LinkeSeite[i]);
      G.setzeRechteSeite(zaehler, FDM.RechteSeite[i]);
      
      zaehler++;
    }
  }

  linclosure (ls, G, erg);

  delete [] entf;
  entf = NULL;
  
  if (rs <= erg) // Falls rs im Abschluss von ls unter G liegt ==> ls -.> rs, sonst nicht
    return true;
  else
    return false;
}

void aequivalenzklassen(const FDMenge & FDM, unsigned * const klassenvek, const bool verbose)
{
  unsigned fdanz = FDM.getAnzahlFDs();
  unsigned klassenzaehler = 1;

  Attributmenge erg, HILF;

  for (unsigned i=0; i<fdanz; i++)
  {
    if (klassenvek[i] == 0)
    {
      klassenvek[i] = klassenzaehler; // Gibt an, in welcher Klasse die i.te FD liegt
      
      linclosure(FDM.LinkeSeite[i], FDM, erg);

      // Checke alle FDs, die noch nicht gecheckt wurden, ob sie aequivalent zur gewaehlten sind
      // Falls ja ==> sie liegen in derselben Klasse
      for (unsigned j=i+1; j<fdanz; j++)
      {
        if ((FDM.LinkeSeite[j] <= erg) && (klassenvek[j] == 0))
        {
	  linclosure(FDM.LinkeSeite[j], FDM, HILF);

	  if (FDM.LinkeSeite[i] <= HILF)
	    klassenvek[j] = klassenzaehler;
	}
      }
					
      klassenzaehler++;
    }
  }

  if (FDM.ausgabe[4] == true && verbose == true) 
  { 
    cout << "<br><br><h3>Bestimmung der &Auml;quivalenzklassen:</h3>" << endl;
   
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td colspan=2 align=center>Sei F eine FD-Menge &uuml;ber dem Relationsschema R und seien X, V zwei Teilmengen von R.</td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>X und V heissen <b>&auml;quivalent</b> unter F, X<->V, wenn sich die FDs X->V und V->X aus F \
      erzeugen lassen.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Sei E(X, F) die Menge aller FDs aus F, deren linken Seiten &auml;quivalent zu X sind, d.h. \
      <b>E(X, F)</b> := {V->W aus F: X<->V} und sei <b>E(F)</b> := {E(X, F): X Teilmenge von R und E(X, F) ist nicht leer}.\
      Dann ist E(X, F) ein &Auml;quivalenzklasse &uuml;ber F bzgl. <-> und E(F) ist die Menge der &Auml;quivalenzklassen &uuml;ber F.</i></td></tr>" << endl;
    cout << "<tr><td valign=top>Folgerung:</td><td>Gilt f&uuml;r zwei FDs X->Y, V->W aus F, dass X im Abschluss von V unter F und V im Abschluss von X unter F liegt, \
      dann ist X<->V.</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man w&auml;hlt sukzessive FDs aus F, etwa X->Y und vergleicht sie mit allen anderen FDs aus F, \
      wie in der Folgerung beschrieben. Gilt dann f&uuml;r eine FD V->W aus F, dass X<->V, so wird V->W der &Auml;quivalenzklasse von X->Y hinzugef&uuml;gt. \
      Auf diese Weise erh&auml;lt man schliesslich E(F), als Menge aller &Auml;quivalenzklassen.</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion AEQUIVALENZKLASSEN():</i><br>" << endl; 
    cout << "<br><br><table border=1>" << endl;
    cout << "<tr><th>&Auml;quivalenzklassen</th></tr>" << endl;
  
    for (unsigned j=1; j<fdanz+1; j++)
    {
      cout << "<tr><td>";
  
        for (unsigned i=0; i<fdanz; i++)
          if (klassenvek[i] == j)
          {
	    printFD(FDM.LinkeSeite[i], FDM.RechteSeite[i]);
	    cout << "<br>";
          }
	
      cout << "</td></tr>" << endl;
    }

    cout << "</table>" << endl;
  }	
}

void minimaleUeberdeckung(FDMenge & FDM)
{
  unsigned *vek = NULL;
  unsigned *nichtmehrbenutzen = NULL;

  unsigned klassenanz = 0;

  Attributmenge vereinigung, NIX;
	
  nichtRedundanteUeberdeckung(FDM);
  reduziert(FDM, true);
	
  vek = new unsigned[FDM.getAnzahlFDs()];
  ASSERT(vek);
  
  nichtmehrbenutzen = new unsigned[FDM.getAnzahlFDs()];
  ASSERT(nichtmehrbenutzen);
  
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
  {
    vek[i] = 0;
    nichtmehrbenutzen[i] = 0;
  }
	
  aequivalenzklassen(FDM, vek, true);
	
  // Bestimmung der Anzahl der Aequivalenzklassen 
  for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)
    if (vek[i] > klassenanz)
      klassenanz = vek[i];

  if (FDM.ausgabe[5] == true)
  {
    cout << "<br><br><h3>Bestimmung der minimalen &Uuml;berdeckung:</h3>" << endl;
   
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td colspan=2 align=center>Seien F, G FD-Mengen &uuml;ber dem Relationsschema R und seien X, Y zwei Teilmengen von R.</td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Die FD-Menge F heisst <b>minimal</b>, falls es keine FD-Menge G gibt, die F &uuml;berdeckt \
      und weniger Elemente als F besitzt.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine <b>Ableitungsfolge</b> P(F) f&uuml;r X->Y, ist eine Menge von FDs, die sich &uuml;ber F erzeugen lassen, \
      so dass sich die FD X->Y, allein &uuml;ber P(F) erzeugen l&auml;sst.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i><b>X bestimmt Y direkt</b> unter F, X-.->Y, falls es eine nicht-redundante FD-Menge G &uuml;ber R gibt, \
      die F &uuml;berdeckt und es eine Ableitungsfolge P(G) f&uuml;r X->Y gibt, so dass der Schnitt von P(G) mit E(X, F) leer ist.</i></td></tr>" << endl;
    cout << "<tr><td valign=top>Satz:</td><td>X bestimmt Y direkt unter F, X-.->Y, falls es f&uuml;r jede nicht-redundante FD-Menge G &uuml;ber R, die F &uuml;berdeckt, \
      eine Ableitungsfolge P(G) f&uuml;r X->Y gibt, so dass der Schnitt von P(G) mit E(X, F) leer ist (zum Beweis, vgl. Informatik IV).</td></tr>" << endl;
    cout << "<tr><td valign=top>Satz:</td><td>Es sei F eine nicht-redundante FD-Menge &uuml;ber R, die nicht minimal ist. Dann gibt es eine Teilmenge X von R und \
      zwei verschiedene FDs Y->U, Z->V in E(X, F) mit Y-.->Z (zum Beweis, vgl. Informatik IV).</td></tr>" << endl;
    cout << "<tr><td valign=top>Folgerung:</td><td>Wenn F nicht-redundant ist und es f&uuml;r jede Teilmenge X von R keine zwei verschiedenen FDs Y->U, Z->V in \
      E(X, F) gibt mit Y-.->Z, dann ist F minimal (Beweis: Umkehrung des vorigen Satzes).</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man bestimmt \
      die &Auml;quivalenzklassen von F. Danach pr&uuml;ft man sukzessive in allen &Auml;quivalenzklassen nach, ob es zwei verschiedene FDs Y->U, Z->V in der gew&auml;hlten \
      Klasse gibt mit Y-.->Z. Falls ja, so setzt man F = F - {Y->U, Z->V} + {Z->UV}. Auf diese Weise hat man die direkte Abh&auml;ngigkeit aufgel&ouml;st und die resultierende \
      FD-Menge bleibt &auml;quivalent zur urspr&uuml;nglichen. Man f&auml;hrt nun solange auf diese Weise fort, bis es keine direkten Abh&auml;ngigkeiten zwischen den linken \
      Seiten zweier verschiedener FDs innerhalb einer Klasse mehr gibt. Ergebnis ist schliesslich eine minimale FD-Menge.</td></tr>" << endl;
    cout << "</table>" << endl;  
    
    cout << "<br><i>Ausgabe der Funktion MINIMAL():</i><br>" << endl; 
  }
  
  for (unsigned k=1; k<=klassenanz; k++) // Checke in der k-ten Klasse
  {
    for (unsigned i=0; i<FDM.getAnzahlFDs(); i++)  
    {
      if ((vek[i] == k) && (nichtmehrbenutzen[i] == 0)) // Falls i-te FD in k-ter Klasse liegt und noch nicht entfernt wurde
      {
        for (unsigned j=0; j<FDM.getAnzahlFDs(); j++) // Checke, ob es FD in derselben Klasse gibt, die direkt abhängig von der linken Seite der i-ten FD ist
        {
	  if ((vek[j] == k) && (i != j) && (nichtmehrbenutzen[j] == 0))
          {
	    if (direkteAbhaengigkeit(FDM, FDM.LinkeSeite[i], FDM.LinkeSeite[j]) == true)
            {
	      if (FDM.ausgabe[5] == true)
	      {
		cout << "<br>";
		FDM.LinkeSeite[j].printAttMenge();
		cout << "  ist direkt abh&auml;ngig von   ";
		FDM.LinkeSeite[i].printAttMenge();
		cout << endl;
	      }	
	      
	      vereinige(FDM.RechteSeite[i], FDM.RechteSeite[j], vereinigung); // Falls direkt abhaengig, vereinige die rechten Seiten der i-ten und j-ten FD 

              FDM.setzeRechteSeite(j, vereinigung);                         
              FDM.setzeLinkeSeite(i, NIX); // Loesche die i-te FD                          
              FDM.setzeRechteSeite(i, NIX);
	    
	      nichtmehrbenutzen[i] = 1; // i-te FD wird nicht mehr benutzt
	    }
	  }
	}
      }
    }
  }
  
  FDM.loesche(false);
  reduziert(FDM, false);	
  
  if (FDM.ausgabe[5] == true)
  {
    cout << "<br><br>" << endl;
    FDM.printFDMenge("minimale &Uuml;berdeckung");
  }
  
  delete [] vek;
  delete [] nichtmehrbenutzen;
  
  vek = NULL;
  nichtmehrbenutzen = NULL;
}

void dritteNormalform(const FDMenge & FDM)
{
  unsigned fdanz = FDM.getAnzahlFDs();
	
  unsigned *klassenvek;

  unsigned klassenanz = 0;
  unsigned formatzaehler = 0;

  Attributmenge erg;

  klassenvek = new unsigned[fdanz];
  ASSERT(klassenvek);

  for (unsigned i=0 ; i<fdanz; i++)
    klassenvek[i] = 0;

  aequivalenzklassen(FDM, klassenvek, false);
	
  // Bestimmung der Anzahl der Aequivalenzklassen 
  for (unsigned i=0; i<fdanz; i++)
    if (klassenvek[i] > klassenanz)
      klassenanz = klassenvek[i];

  if (FDM.ausgabe[6] == true)
  {
    cout << "<br><br><h3>Bestimmung der dritten Normalform:</h3>" << endl;
  
    cout << "<table width=650 border=0 cellspacing=10>" << endl;
    cout << "<tr><td colspan=2 align=center>Es sei R ein relationales Schema und F eine FD-Menge &uuml;ber R.</td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Es sei K eine Teilmenge von R, dann heisst K <b>echter Schl&uuml;ssel</b> von R, falls sich die \
      FD K->R &uuml;ber F erzeugen l&auml;sst und f&uuml;r jede echte Teilmenge K&#039; von K gilt, dass sich die FD K&#039;->R nicht &uuml;ber \
      F erzeugen l&auml;sst.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine Attribut A aus R heisst <b>Nicht-Primattribut</b>, falls es in keinem echten Schl&uuml;ssel K \
      von R enthalten ist.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Sei X eine Teilmenge von R und A ein Attribut aus R. <b>A h&auml;ngt transitiv von X (&uuml;ber Y) ab</b>, \
      falls es eine Teilmenge Y von R gibt mit:</i> \
      <br><blockquote><i> \
          (i) X->Y l&auml;sst sich &uuml;ber F erzeugen<br> \
          (ii) Y->X l&auml;sst sich nicht &uuml;ber F erzeugen<br> \
          (iii) Y->A l&auml;sst sich &uuml;ber F erzeugen<br> \
          (iv) A ist kein Element von X vereinigt mit Y<br> \
	  </i></blockquote></td></tr>" << endl;	
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Ein relationales Schema R ist in <b>dritter Normalform (3NF)</b> bzgl. einer FD-Menge F, \
      falls (R in in 1NF und) kein Nichtprimattribut transitiv von einem echten Schl&uuml;ssel von R abh&auml;ngt.</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine <b>zusammengesetzte funktionale Abh&auml;ngigkeit (CFD)</b> ist von der Form \
      (X<font size=-4>1</font>, ..., X<font size=-4>k</font>)->Y, wobei X<font size=-4>i</font> Teilmenge von R f&uuml;r i=1,...,k, Y Teilmenge von R, \
      X<font size=-4>i</font>!=X<font size=-4>j</font> f&uuml;r i!=j und es gilt: X<font size=-4>i</font><->X<font size=-4>j</font> f&uuml; alle i!=j, \
      sowie X<font size=-4>i</font>->Y f&uuml;r i=1,..,k</i></td></tr>" << endl;
    cout << "<tr><td valign=top><i>Definition:</i></td><td><i>Eine CFD-Menge heisst <b>ringf&ouml;rmig</b>, falls es keine Teilmengen X, Z von R in verschiedenen linken \
      Seiten von CFDs gibt mit X<->Z.</i></td></tr>" << endl;
    cout << "<tr><td valign=top>Satz:</td><td>Sei G eine reduzierte, minimale, ringf&ouml;rmige CFD-&Uuml;berdeckung von F. Konstruiert man f&uuml;r jede \
      CFD (X<font size=-4>1</font>, ..., X<font size=-4>k</font>)->Y in G ein relationales Schema R = X<font size=-4>1</font> ... X<font size=-4>k</font> Y \
      mit Schl&uuml;sseln K = {X<font size=-4>1</font>, ..., X<font size=-4>k</font>}, so erh&auml;lt man eine vollst&auml;ndige Zerlegung \
      in ein 3NF-Datenbankschema (zum Beweis vgl. Informatik IV).</td></tr>" << endl;
    cout << "<tr><td valign=top>Vorgehensweise:</td><td>Man bestimmt eine minimale, reduzierte &Uuml;berdeckung G von F. Dann darf man die FDs innerhalb einer \
      &Auml;quivalenzklasse von G gerade zu einer CFD zusammenfassen und erh&auml;lt auf diese Weise eine ringf&ouml;rmige CFD-&Uuml;berdeckung von F.\
      Unter Anwendung des Satzes erh&auml;lt man damit eine Zerlegung in die dritte Normalform.</td></tr>" << endl;
    cout << "</table>" << endl;
    
    cout << "<br><i>Ausgabe der Funktion DRITTE_NORMALFORM():</i><br>" << endl; 
    cout << "<br>Es gibt " << klassenanz << " Relationenschamata<br>" << endl;
    cout << "<br><br><table border=1 cellspacing=2>" << endl;
    cout << "<tr><th>Relationsschema</th><th>Schl&uuml;ssel</th></tr>" << endl;
  }
  
  for (unsigned k=1; k<=klassenanz; k++)
  {
    if (FDM.ausgabe[6] == true)
      cout << "<tr><td>";
			
    formatzaehler = 0;
			
    for (unsigned i=0; i<fdanz; i++)
    {
      // Checke welche Attribute in den FDs innerhalb einer Klasse verwendet werden ==> Relationsschema
      if ((klassenvek[i] == k) && (formatzaehler == 0))
      {
        for (unsigned l=0; l<AnzahlAttribute; l++)
	  erg.setEintrag(l, true); // erg mit true vorbesetzen
							 
	for (unsigned l=0; l<fdanz; l++)
	  if (klassenvek[l] == k) // Falls FD in derselben Klasse liegt ==> Abziehen der rechten und linken Seite von erg
	    abziehen(erg, FDM.RechteSeite[l], erg);
							 
	for (unsigned l=0; l<fdanz; l++)
	  if (klassenvek[l] == k)
	    abziehen(erg, FDM.LinkeSeite[l], erg);
							
	// Ausgabe der false - Attribute in erg 
        for (unsigned r=0; r<AnzahlAttribute; r++)
          if (erg.getEintrag(r) == false && FDM.ausgabe[6] == true)
	    cout << AttributName[r] << " ";
	
	formatzaehler = 1;
      }
    }		
    
    if (FDM.ausgabe[6] == true) 
      cout << "</td><td>";
        
    formatzaehler=0;
			
    // Linken Seiten der FDs innerhalb einer Klasse sind allesamt echte Schluessel    
    for (unsigned j=0; j<fdanz; j++)
    {
      if (klassenvek[j] == k)
      {
        if (formatzaehler != 0 && FDM.ausgabe[6] == true)
 	  cout << "<br>";
 								
	formatzaehler++;
 								
	// Ausgabe der Attribute von FDM.LinkeSeite[j]
 	for (unsigned r=0; r<AnzahlAttribute; r++)
 	{
 	  if (FDM.LinkeSeite[j].getEintrag(r) == true && FDM.ausgabe[6] == true)
 	    cout << AttributName[r] << " ";
 	}
      } 							
    }

    if (FDM.ausgabe[6] == true) 
      cout << "</td></tr>";
  }

  if (FDM.ausgabe[6] == true)
    cout << "</table>" << endl;

  delete [] klassenvek;
  klassenvek = NULL;
}

unsigned attributErkannt(const string text2)
{
  string *temp = NULL;

  // Suche in AttributName[] nach text2;

  // Falls noch keine Attribute vorhanden ==> Wert auf 0-te Position legen
  if (AnzahlAttribute == 0)
  {
    AttributName = new string[1];
    ASSERT(AttributName);
    
    AttributName[0] = text2;
    AnzahlAttribute++;
    
    return 0; // 0-te Position
  }
	
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (text2 == AttributName[i])
      return i;
	
  // Attribut wurde nicht gefunden, wird also hinzugefügt, an letzter Position
  temp = new string[AnzahlAttribute + 1];
  ASSERT(temp);
  
  for (unsigned i=0; i<AnzahlAttribute; i++)
    temp[i] = AttributName[i];
	
  temp[AnzahlAttribute] = text2; // text2 wird abgelegt und AnzahlAttribute hochgezählt
  AnzahlAttribute++;

  delete [] AttributName;
  AttributName = temp;
	
  return (AnzahlAttribute - 1);
}

long int attributFound(const string text2)
{
  for (unsigned i=0; i<AnzahlAttribute; i++)
    if (text2 == AttributName[i])
      return ((long int) i);
	
  // Attribut wurde nicht gefunden, Fehler wird ausgegeben!!!
  return -1;
}
