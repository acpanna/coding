#include <qapplication.h>
#include <qlabel.h>
#include <qpushbutton.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  
  QLabel *l = new QLabel("<h1>Hallo, Welt!</h1>", 0);
  l->show();
  
  QPushButton *b = new QPushButton("Clear", 0);
  b->show();

  QObject::connect(b, SIGNAL(clicked()), l, SLOT(clear()));
  // alternativ: l->connect(b, SIGNAL(clicked()), SLOT(clear()));
  
  app.setMainWidget(l);
  return app.exec();
}
