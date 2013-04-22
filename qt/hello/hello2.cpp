#include <qapplication.h>
#include <qlabel.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QLabel *l1 = new QLabel("Fenster1", 0);
  QLabel *l2 = new QLabel("Fenster2", 0);
  l1->show();
  l2->show();

  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));

  return app.exec();
}
