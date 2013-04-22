#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "knoten.h"
#include <stack>

typedef std::stack<int> Stack;

class Graph
{
  public:
    // Erzeuge leeren Graphen (ohne Knoten und Kanten)
    Graph();

    // Erzeuge Graph aus Nachbarschaftsliste
    // ohne Knoten- und Kantenbewertung
    Graph(int *nachbarschaftsliste);
  
    // Existiert eine Kante  start--> ziel  ?
    bool existiertKante(int startknoten, int zielknoten);
    
    // Fuegt die Kante  start --> ziel in den Graphen ein (falls noch nicht
    // vorhanden) und setzt die Bewertung der Kante gleich weight
    void aendereKante(int startknoten, int zielknoten, double weight);
    
    // Loesche die Kante  start --> ziel  
    void loescheKante(int startknoten, int zielknoten);
    
    // Erzeuge neuen unverbundenen Knoten im Graphen
    // Rueckgabewert ist die Nummer des neuen Knotens
    int erzeugeKnoten(double weight = 0.0);

    // Falls Start- und Zielknoten existieren,
    // wird eine Kante  start--->ziel  erzeugt
    void erzeugeKante(int startknoten, int zielknoten, double weight = 0.0);

    // Depth-first-Search zur Berechnung der BCCs
    void dfs_bcc(int v, bool *besucht, int &count,
		    int *parent, int *dfsnum, int *lowpt,
		    Stack * bccstack);
    
    // Berechnung und Ausgabe aller BCCs des Graphen
    void bcc();
    
    // Mache aus einem gerichteten Graphen einen ungerichteten
    void macheUngerichtet();
    
    // Gib den Graphen auf dem Bildschirm aus
    void printGraph();
    
  private:
    Knoten *knoten; // Zeiger auf Knoten des Graphen
    int knotenzahl; // Anzahl der Knoten des Graphen
};

#endif
