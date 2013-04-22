#include "graph.h"
#include <iostream>

using namespace std;

int main(void)
{
  int vec[] = 
  {7,10,13,17,21,24,25,  1,2,3,  0,2,3,  0,1,3,4,  0,1,2,4,  2,3,5,  4};

  /*
                 5
                 |
                 4
                / \
               2---3
               |\ /|
               |/ \|
               0---1
  */
  
  Graph graph(vec);

  cout << "==" << endl;
  cout << " Ausgabe des Graphen:" << endl;
  cout << "=="<< endl << endl;
  
  graph.printGraph();
 
  cout << endl << endl;
  cout << "==" << endl;
  cout << " BCCs des Graphen:" << endl;
  cout << "=="<< endl << endl;
  
  graph.bcc();
  
  return 0;
}
