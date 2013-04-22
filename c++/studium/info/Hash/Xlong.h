class C_xlong
{
 friend ostream& operator <<(ostream&, const C_xlong&);
                                                 // Ausgabeoperator ueberladen
 friend long tolong(const C_xlong&);             // Umwandlung in long-Objekt

 public:
   C_xlong(const char *);                        // Konstruktoren
   C_xlong(const C_xlong&);
   C_xlong(int);
   C_xlong();
   ~C_xlong() { delete [] fval; fval = 0; }      // Destruktor

   
   C_xlong& operator  =(const C_xlong&);         // Ueberladen von Operatoren 
   C_xlong& operator  =(const char *);           // für C_xlong-Objekte
   int      operator ==(const C_xlong&) const;
   int      operator !=(const C_xlong&) const; 
   int      operator  <(const C_xlong&) const;
   C_xlong  operator  *(int) const; 
   C_xlong  operator  *(const C_xlong&) const;
   C_xlong  operator  %(const C_xlong&) const;
   C_xlong  operator  +(const C_xlong&) const;
   C_xlong  operator  -(const C_xlong&) const;
   C_xlong  operator ()(int, int) const;         // Zugriff auf Substring 
   C_xlong  invert(int, int) const;              // Substring invertieren
   C_xlong& mini(void);                          // Beseitigung fuehrender Nullen
   int    getLength(void) const;                 // Anzahl der Stellen bestimmen 

private:                                         // Hilfsfunktionen
   C_xlong  compl(int) const;                    // 1-Komplement
   C_xlong& shift(int);                          // Stellenverschiebung


private:
   char *fval;                                   // repraesentierte Zahl (String)
   int flength;                                  // Anzahl der Stellen
};

