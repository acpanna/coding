#include <qapplication.h>

#include "dialog6.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  
  AddressDialog test;

  return test.exec();
}
