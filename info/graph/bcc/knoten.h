#ifndef _KNOTEN_H_
#define _KNOTEN_H_

#include "kante.h"

class Knoten
{
  public:
    // Erzeuge Knoten ohne Kanten und Knotenbewertung = 0.0
    Knoten(); 

    // Erzeuge Knoten mit Kanten aus nachbarliste
    Knoten(int *nachbarliste);
    ~Knoten();

    void operator=(const Knoten &rechts);
    
    // Loescht die Kante  akt.Knoten --> nachbar
    void loescheNachbar(const int &nachbar);

    // Setze die Knotenbewertung gleich weight
    void setBewertung(const double &weight) { bewertung = weight; }
    
    // Fuege eine Kante vom aktuellen Knoten zum Knoten nachbar ein (falls 
    // noch nicht vorhanden), und setze die Bewertung der Kante gleich weight
    void aendereNachbar(const int &nachbar, const double &weight);

    // Gibt einen (readonly) Zeiger auf die Kanten des Knotens zurueck
    const Kante * const getKante() const { return kante; }  
    
    // Gibt Anzahl der vom Knoten wegfuehrenden Kanten aus
    int getNachbarn() const { return nachbarn; } 
    
    // Prueft ob eine Kante  akt.Knoten --> nachbar  existiert
    bool hatNachbar(const int &nachbar) const;
    void printKnoten() const;
    
  private:
    int nachbarn; // Anzahl der vom Knoten wegfuehrenden Kanten
    Kante *kante; // Zeiger auf diese Kanten
   
    double bewertung; // Knotenbewertung
};

#endif
