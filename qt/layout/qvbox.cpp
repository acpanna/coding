#include <qapplication.h>
#include <qvbox.h>
#include <qpushbutton.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QVBox *topWidget = new QVBox();
  QPushButton *b1 = new QPushButton("Ok", topWidget);
  QPushButton *b2 = new QPushButton("Defaults", topWidget);
  QPushButton *b3 = new QPushButton("Cancel", topWidget);

  app.setMainWidget(topWidget);
  topWidget->show();
  return app.exec();
} 
