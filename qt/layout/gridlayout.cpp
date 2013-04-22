#include <qapplication.h>
#include <qwidget.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  //Widgets erzeugen
  
  QWidget *messageWindow = new QWidget();
 
  QPushButton *b1 = new QPushButton("1", messageWindow);
  QPushButton *b2 = new QPushButton("2", messageWindow);
  QPushButton *b3 = new QPushButton("3", messageWindow);
  QPushButton *b4 = new QPushButton("4", messageWindow);
  QPushButton *b5 = new QPushButton("5", messageWindow);
  QPushButton *b6 = new QPushButton("6", messageWindow);
  QPushButton *b7 = new QPushButton("0", messageWindow);
  
  QGridLayout *topLayout = new QGridLayout(messageWindow, 3, 3, 1);
 
  topLayout->addWidget(b1, 0, 0);
  topLayout->addWidget(b2, 0, 1);
  topLayout->addWidget(b3, 0, 2);
  topLayout->addWidget(b4, 1, 0);
  topLayout->addWidget(b5, 1, 1);
  topLayout->addWidget(b6, 1, 2);
  topLayout->addMultiCellWidget(b7, 2, 2, 0, 2);
 
  app.setMainWidget(messageWindow);
  
  messageWindow->setCaption("einfacher Dialog");
  messageWindow->show();

  return app.exec();
}

