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
  QMultiLineEdit *messages = new QMultiLineEdit(messageWindow);
  QPushButton *clear = new QPushButton("Clear", messageWindow);
  QPushButton *hide = new QPushButton("Hide", messageWindow);
  
  QBoxLayout *topLayout = new QBoxLayout(messageWindow, QBoxLayout::TopToBottom, 10);
  QBoxLayout *buttonsLayout = new QBoxLayout(QBoxLayout::LeftToRight);

  topLayout->addWidget(messages);
  topLayout->addLayout(buttonsLayout);

  buttonsLayout->addWidget(clear);
  buttonsLayout->addWidget(hide);

  app.setMainWidget(messageWindow);
  
  messageWindow->setCaption("einfacher Dialog");
  messageWindow->show();

  return app.exec();
}

