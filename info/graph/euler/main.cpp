#include "graph.h"
#include <iostream>

using namespace std;

int main(void)
{
  int vec[] = {6,9,12,16,20,22,  1,2,3,  0,2,3,  0,1,3,4,  0,1,2,4,  2,3};
  // vec enthaelt die Daten des 'Haus vom Nikolaus'
  
  ////////////////////////////////////////////////////
 
  cout << "'Das Haus vom Nikolaus' :\n";

  cout << "   4\n";
  cout << "  / \\\n";
  cout << " 2---3\n";
  cout << " |\\ /|\n";
  cout << " |/ \\|\n";
  cout << " 0---1\n\n";
  
  // Erzeuge den Graphen   
  Graph graph(vec);
  
  // Gib die Adjazenzenmatrix des Graphen aus
  graph.draw();
  
  cout << endl;

  // Berechne und gebe den Euler'schen Pfad aus
  graph.eulerPath();

  ////////////////////////////////////////////////////
  
  return 0;
}
