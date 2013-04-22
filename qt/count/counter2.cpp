#include "counter2.h"

Counter::Counter(QWidget *parent, const char *name)
  :QLabel(parent, name), n(0)
{
  setNum(0);
}

Counter::~Counter()
{}

void Counter::countUp()
{
  n++;
  setNum(n);
}
