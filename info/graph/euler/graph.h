#ifndef _GRAPH_H_
#define _GRAPH_H_

class Graph
{
  public:
    // Konstruktoren
    Graph(int ** adjacency, int knotenzahl);
    Graph(Graph &src);
    Graph(int *vector); 
    
    // Destruktor
    ~Graph();

    // Liefert den transitiven Abschluss 
    // (Warshall - Algorithmus, vgl. Informatik III - Compilerbau) 
    void transitiveClosure();

    // Liefert die Information, welche Knoten  
    // vom Knoten start aus erreichbar sind
    void bfs(int start, bool *besucht); // 'Suche in die Breite'
    void dfs(int start, bool *besucht); // 'Suche in die Tiefe'
    
    // Liefert die Anzahl der Zusammenhangskomponenten
    int connectedComponents();
 
    // Prueft, ob der Graph 'ungerichtet' ist
    bool isUndirected();

    // Prueft, ob Voraussetzungen fuer eulerPath() erfuellt sind
    // (die Parameter start und end dienen als zusaetzliche Rueckgabefelder, 
    // und zeigen die Position von Start- und Endknoten an, falls diese
    // verschieden sind)
    bool isEulerApplicable(int &start, int &end);
        
    // Berechnet und gibt Euler'schen Pfad aus
    void eulerPath();

    // Gibt die Adjazenzenmatrix des Graphen aus
    void draw();
    
  private:
    // Initialisierung (wird vom Konstruktor aufgerufen)
    void initialize(int ** adj, int knt);
    
    // Anzahl der Knoten im Graph
    int vertices;

    // Adjazenzenmatrix
    int ** adjacencyMatrix;
};

#endif
