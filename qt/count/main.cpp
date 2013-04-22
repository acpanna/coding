#include <qapplication.h>
#include <qpushbutton.h>
#include "counter.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QPushButton *b = new QPushButton("Click", 0);
  b->show();

  Counter *c = new Counter(b);

  QObject::connect(b, SIGNAL(clicked()), c, SLOT(countUp()));

  app.setMainWidget(b);
  return app.exec();
}
