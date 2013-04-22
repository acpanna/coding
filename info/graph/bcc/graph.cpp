#include "graph.h"
#include <iostream>
#include <stack>

using namespace std;

#define ASSERT(x)  if((x) == NULL) { cout << "Speicherreservierung fehlgeschlagen -- Programmabbruch" << endl; exit(1); }

#define MIN(x, y) ( (x) < (y) ? (x) : (y) ) 

Graph::Graph()
{
  knoten = NULL;
  knotenzahl = 0;
}

Graph::Graph(int *nachbarschaftsliste)
{
  int i, j;
  knotenzahl = nachbarschaftsliste[0]-1;
  
  knoten = new Knoten[knotenzahl];
  ASSERT(knoten);

  for (i=0; i<knotenzahl; i++)
    for (j=nachbarschaftsliste[i]; j<nachbarschaftsliste[i+1]; j++)
      knoten[i].aendereNachbar(nachbarschaftsliste[j], 0.0);
}

bool Graph::existiertKante(int startknoten, int zielknoten)
{
  if (startknoten >= knotenzahl || zielknoten >= knotenzahl)
    return false;
  
  if (knoten[startknoten].hatNachbar(zielknoten))
    return true;

  return false;
}
 
void Graph::loescheKante(int startknoten, int zielknoten)
{
  if (startknoten >= knotenzahl || zielknoten >= knotenzahl)
  {
    cerr << "loescheKante: Kante  start --> ziel  konnte nicht geloescht "
     "werden, da start >= knotenzahl oder ziel >=knotenzahl -- Abbruch" << endl;
    return;
  }
  
  knoten[startknoten].loescheNachbar(zielknoten);
}

void Graph::aendereKante(int startknoten, int zielknoten, double weight)
{
  if (startknoten >= knotenzahl || zielknoten >= knotenzahl)
  {
    cerr << "aendereKante: Kante  start --> ziel  konnte nicht geaendert "
     "werden, da start >= knotenzahl oder ziel >=knotenzahl -- Abbruch" << endl;
    return;
  }

  knoten[startknoten].aendereNachbar(zielknoten, weight);
}
  
int Graph::erzeugeKnoten(double weight)
{
  int i;
  Knoten *newknoten = new Knoten[knotenzahl+1];
  ASSERT(newknoten);

  for (i=0; i<knotenzahl; i++)
    newknoten[i] = knoten[i];

  delete [] knoten;
  knoten = newknoten;
  knotenzahl++;

  knoten[knotenzahl-1].setBewertung(weight);
  return knotenzahl-1; 
}

void Graph::erzeugeKante(int startknoten, int zielknoten, double weight)
{
  if (startknoten >= knotenzahl || zielknoten >= knotenzahl)
  {
    cerr << "erzeugeKante: Kante  start --> ziel  konnte nicht erzeugt werden, "
      "da start >= knotenzahl oder ziel >= knotenzahl -- Abbruch" << endl;
    return;
  }
  
  knoten[startknoten].aendereNachbar(zielknoten, weight);
}

void Graph::dfs_bcc(int v,  
		bool *besucht, int &count, 
		int *parent, int *dfsnum, int *lowpt, 
		Stack *bccstack)
{
  int i;
  int w;
  
  count++;
  dfsnum[v] = count;
  besucht[v] = true;
  lowpt[v] = dfsnum[v];
  bccstack->push(v);

  for (i=0; i<knoten[v].getNachbarn(); i++)
  {
    w = (knoten[v].getKante())[i].getZiel();
    if (!besucht[w])
    {
      parent[w] = v;
      dfs_bcc(w, besucht, count, parent, dfsnum, lowpt, bccstack);
      lowpt[v] = MIN(lowpt[v], lowpt[w]);
    }
    else
      lowpt[v] = MIN(lowpt[v], dfsnum[w]);
  } 
  
  if (dfsnum[v] >= 2 && lowpt[v] == dfsnum[parent[v]])
  {
    cout << parent[v];
    do 
    {
      w = bccstack->top(); 
      bccstack->pop(); 
      cout << " " << w;
    } while(w != v);
    
    cout << endl;
  }
}    

void Graph::bcc()
{
  int i;
  int count = 0;

  bool *besucht = new bool[knotenzahl];
  int *parent = new int[knotenzahl];
  int *dfsnum = new int[knotenzahl];
  int *lowpt = new int[knotenzahl];
  
  ASSERT(besucht);
  ASSERT(parent);
  ASSERT(dfsnum);
  ASSERT(lowpt);
 
  Stack *bccstack = new Stack;
  
  for (i=0; i<knotenzahl; i++)
    besucht[i] = false;

  for (i=0; i<knotenzahl; i++)
    if (!besucht[i])
      dfs_bcc(i, besucht, count, parent, dfsnum, lowpt, bccstack);

  delete [] besucht;
  delete [] parent;
  delete [] dfsnum;
  delete [] lowpt;
  delete bccstack;
}

void Graph::macheUngerichtet()
{
  int i, j;
  for (i=0; i<knotenzahl; i++)
    for (j=0; j<knoten[i].getNachbarn(); j++)
    {
      int ziel = (knoten[i].getKante())[j].getZiel();
      double weight = (knoten[i].getKante())[j].getBewertung();
     
      if (ziel > i)
        aendereKante(ziel, i, weight);
    }
}

void Graph::printGraph()
{
  int i;

  cout << "Knoten\tNachbarn\n";
  cout << "------\t--------\n";
  
  for (i=0; i<knotenzahl; i++)
  {
    cout << i << "\t";
    knoten[i].printKnoten();
  }
}
