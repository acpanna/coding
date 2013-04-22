#include <qapplication.h>
#include <qpushbutton.h>
#include "counter2.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QPushButton *b = new QPushButton("Click", 0);
  b->show();

  Counter *c = new Counter(0);
  c->show();

  QObject::connect(b, SIGNAL(clicked()), c, SLOT(countUp()));

  app.setMainWidget(b);
  return app.exec();
}
