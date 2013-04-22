#include "counter.h"
#include <iostream.h>

Counter::Counter(QObject *parent, const char *name)
  :QObject(parent, name), n(0)
{}

Counter::~Counter()
{}

void Counter::countUp()
{
  n++;
  cout << "Anzahl Aktivierungen " << n << endl;
}
