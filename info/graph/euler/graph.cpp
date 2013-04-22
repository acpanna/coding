#include "graph.h"

#include <cassert>
#include <queue>
#include <iostream>

using namespace std;

Graph::Graph(int **adjacency, int knotenzahl)
{
  this->initialize(adjacency, knotenzahl);
}
  
Graph::Graph(Graph &src)
{
  this->initialize(src.adjacencyMatrix, src.vertices);
}

Graph::Graph(int *vector)
{
  int i, j;
  
  vertices = vector[0]-1;

  adjacencyMatrix = new int*[vertices];
  assert(adjacencyMatrix);
  
  for (i=0; i<vertices; i++)
  {
    adjacencyMatrix[i] = new int[vertices];
    assert(adjacencyMatrix[i]);
  }

  for (i=0; i<vertices; i++)
    for (j=vector[i]; j<vector[i+1]; j++)
    {
      int neighbour = vector[j];
      adjacencyMatrix[i][neighbour] = 1;
    }
}
 
Graph::~Graph()
{
  int i;
  
  for (i=0; i<vertices; i++)
  {
    delete [] adjacencyMatrix[i];
    adjacencyMatrix[i] = 0;
  }

  delete [] adjacencyMatrix;
  adjacencyMatrix = 0;
}

void Graph::initialize(int **adj, int knt)
{
  int i, j;
  
  vertices = knt;
  
  adjacencyMatrix = new int*[vertices];
  assert(adjacencyMatrix);

  for (i=0; i<vertices; i++)
  {
    adjacencyMatrix[i] = new int[vertices];
    assert(adjacencyMatrix[i]);
  }
    
  for (i=0; i<vertices; i++)
    for (j=0; j<vertices; j++)
    	adjacencyMatrix[i][j] = adj[i][j];
}

void Graph::transitiveClosure() // Algorithmus von Warshall 
{
  int i, j, k;

  for (k=0; k<vertices; k++)
    for (i=0; i<vertices; i++)
      for (j=0; j<vertices; j++)
      {
	if (adjacencyMatrix[i][j])
	  adjacencyMatrix[i][j] = 1;
        else if (adjacencyMatrix[i][k] && adjacencyMatrix[k][j])
	  adjacencyMatrix[i][j] = 1;
      }
}

void Graph::bfs(int start, bool *besucht)
{
  int j;
  queue<int> schlange;

  if (start >= vertices || start < 0)
  {
    cout << "Startknoten liegt ausserhalb des gueltigen Bereichs...\n";
    exit(1);
  }
  
  besucht[start] = true; // Markiere den Startknoten als besucht
  schlange.push(start);  // und schiebe ihn in die Schlange

  while (!schlange.empty())    // Solange die Schlange nicht leer ist,
  {                            // entferne den Kopf der Schlange 
    int &v = schlange.front(); // und speichere ihn in v
    schlange.pop();
    
    for (j=0; j<vertices; j++)
    {
      if (adjacencyMatrix[v][j] && !besucht[j]) // Schiebe alle noch nicht besuchten Nachbarn
      {                                         // des Knotens v in die Schlange und markiere
	schlange.push(j);                       // sie als besucht (Suche in die Breite)
	besucht[j] = true;
      }
    }
  }
}

void Graph::dfs(int start, bool *besucht)
{
  int j;
  
  if (start >= vertices || start < 0)
  {
    cout << "Startknoten liegt ausserhalb des gueltigen Bereichs...\n";
    exit(1);
  }

  besucht[start] = true; // Markiere den Startknoten als besucht
  
  for (j=0; j<vertices; j++)
    if (adjacencyMatrix[start][j] && !besucht[j]) // Fuer all noch nicht besuchten Nachbarn
      dfs(j, besucht);                            // des Startknotens, rufe diese Prozedur
}                                                 // rekursiv auf (Suche in die Tiefe)
  
int Graph::connectedComponents()
{
  bool allvisited = false;
  int i, nextVertex = 0, counter = 1;
  
  bool *besucht = new bool[vertices];
  assert(besucht);
  
  for (i=0; i<vertices; i++) 
    besucht[i] = false;
  
  while(!allvisited)
  {
    dfs(nextVertex, besucht); // Pruefe, welche Knoten vom Knoten nextVertex aus erreichbar sind
    allvisited = true;
    
    for (i=0; i<vertices; i++) 
      if (!besucht[i])  // Falls es noch nicht besuchte Knoten gibt,
      {                 // inkrementiere die Anzahl der Zusammenhangskomponenten
	nextVertex = i; // und waehle den ersten nicht besuchten Knoten
	counter++;      // fuer den naechsten bfs/dfs Durchlauf
	allvisited = false;
	break;
      }
  }

  delete [] besucht;
  besucht = 0;
 
  return counter;
}

bool Graph::isUndirected()
{
  int i, j;

  for (i=0; i<vertices; i++)
    for (j=0; j<i; j++)
      if ((adjacencyMatrix[i][j] != adjacencyMatrix[j][i]))
	return false;

  return true;
}

bool Graph::isEulerApplicable(int &start, int &end)
{
  int i, j, count = 0;

  if (!isUndirected()) // Wenn Graph gerichtet ist
    return false;      // --> Euler (vorerst) nicht anwendbar
 
  if (connectedComponents() > 1) // Wenn Graph nicht zusammenhaengend 
    return false;                // --> false

  for (i=0; i<vertices; i++) 
  {
    int sum = 0;
    
    for (j=0; j<vertices; j++) // Bestimme den Knotengrad des Knotens i 
      sum += adjacencyMatrix[i][j];

    if ((sum % 2) != 0) // Prüfe ob Knotengrad gerade ist
    {  
      if (count == 0) // Erster Knoten ungeraden Grades
      {               // wird Startknoten
	start = i;
	count++;
      }
      else if (count == 1) // Zweiter Knoten ungeraden Grades
      {                    // wird Endknoten
	end = i;
	count++;
      }
      else if (count == 2) // Falls mehr wie 2 Knoten ungeraden Grad haben
	return false;      // --> false
    }
  }

  if (count == 0 || count == 2)  // Falls alle Knoten geraden Grad haben,
    return true;                 // oder alle bis auf 2 --> true
  else 
    return false;                // sonst --> false
}

void Graph::eulerPath()
{
  int j;
  int first = 0, last = 0, nextVertex;
  
  if (!isEulerApplicable(first, last))
  {
    cerr << "Die Berechnung eines Euler'schen Pfades ist nicht moeglich, da\n" 
	"der Graph entweder gerichtet, nicht zusammenhaengend, oder die Zahl\n"
	"der Knoten ungeraden Grades ==1, bzw. >2 ist !" << endl;
    return;
  }

  Graph tempGraph(*this);
  
  if (first != last)    // Fall Start- und Endknoten verschieden sind, 
    nextVertex = first; // beginne Pfad mit Startknoten, ansonsten
  else                  // beginne mit Knoten 0
    nextVertex = 0;
  
  cout << "Euler'scher Pfad :\n " << nextVertex;
  
  while(tempGraph.connectedComponents() != tempGraph.vertices)
  { //  Solange #Zush.kp. != #Knoten
    // --> es gibt noch Kanten im Graph
    // --> also mache weiter                                          
    
    bool foundEdge = false;
    int components = tempGraph.connectedComponents();
    
    for (j=0; j<vertices; j++) 
    {
      if (tempGraph.adjacencyMatrix[nextVertex][j]) // Pruefe sukzessiv Kanten, die mit nextVertex 
      {                                             // inzidieren und entferne diese
        tempGraph.adjacencyMatrix[nextVertex][j]--; // aus dem Graphen
        tempGraph.adjacencyMatrix[j][nextVertex]--; 
	
        if (tempGraph.connectedComponents() == components) // Bleibt #Zush.kp unveraendert
        {                                                  // --> richtige Kante wurde entfernt      
	  foundEdge = true;
	  nextVertex = j;
	  break;
        }
        else // ansonsten fuege die Kante wieder hinzu
	{
	  tempGraph.adjacencyMatrix[nextVertex][j]++;
	  tempGraph.adjacencyMatrix[j][nextVertex]++;
	} 
      }
    }
     
    if (foundEdge == false) // Egal, welche Kante ich entferne, die Anzahl
    {                       // der Zush.kp. wird groesser  
      for (j=0; j<vertices; j++)
      {  
        if (tempGraph.adjacencyMatrix[nextVertex][j]) // Entferne die naechste Kante, die
        {                                             // mit nextVertex inzidiert
	  tempGraph.adjacencyMatrix[nextVertex][j]--; 
	  tempGraph.adjacencyMatrix[j][nextVertex]--;
	  nextVertex = j;                             // und setze nextVertex gleich dem 
	  break;                                      // anderem Knoten, mit dem die entfernte 
        }                                             // Kante inzidiert hatte
      }
    }

    cout << " --> " << nextVertex;
  }

  cout << endl;
}

void Graph::draw()
{
  int i, j;

  cout << "Adjazenzenmatrix :\n";
 
  for (i=0; i<vertices; i++)
  {
    for (j=0; j<vertices; j++)
      cout << " " << adjacencyMatrix[i][j];
    
    cout << endl;
  }
}
