#include "xlong.h"

class C_xstrlong                                 // Zwischenklasse zur Abspeicherung  
{												 // des/der eingegebenen/eingelesenen
public:											 // Strings und des entsprechenden 	
    C_xstrlong() { finput = ""; keystr = 0; }    // C_xlong - Objektes
	C_xstrlong(char *nstring);
	~C_xstrlong() { delete [] keystr; keystr = 0; }
	C_xstrlong& operator= (C_xstrlong& value);

	C_xlong finput;
	char *keystr;
};


class C_element                                  // Hilfsklasse für C_list
{
 friend class C_list;
 private:
	 C_element(C_xstrlong &value) { xstrlong = value; fnext = 0; }
	 C_element(C_xstrlong &value, C_element *eptr) { xstrlong = value; fnext = eptr; }
	 
 private:  
   C_xstrlong xstrlong;                          // Listeneintrag
   C_element *fnext;                             // Verkettung
};


class C_list 
{
 public:
	 C_list() { fbasis=0; fend=0; anzahl=0; }    // Konstruktor
	 ~C_list() { remove(); }                     // Destruktor 

   void append(C_xstrlong &);                    // Element am Ende einfuegen
   void remove();                                // alle Elemente entfernen
   int  remove(C_xstrlong &);                    // angegebenes Element entfernen     
   bool contain(char *value);                    // Element in Liste suchen
   bool empty() const;                           // Ueberpruefung auf leere Liste
   void output(CListBox *list);                  // Ausgabe der kompleten Liste
   void output(ostream &fout);
   C_xstrlong& operator[](int) const;            // Zugriff auf int-tes Element
                                                 // analog zum Zugriff auf Arrays
   int getAnzahl() const { return anzahl; }
   void setAnzahl(int neu) { anzahl = neu; }

 private:
  
   C_element *fbasis;                            // Listenkopf
   C_element *fend;                              // Listenende
   int anzahl;
};


