#include <qapplication.h>

#include "mywidget.h"

int main(int argc, char **argv)
{
  QApplication::setColorSpec(QApplication::ManyColor); // Farbspektrum der Applikation festlegen
                                                      
  QApplication app(argc, argv);

  MyWidget *main = new MyWidget();
  app.setMainWidget(main);

  main->show();
  
  return app.exec();
  }
