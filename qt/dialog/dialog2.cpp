#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qmultilineedit.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QWidget *messageWindow = new QWidget();
  app.setMainWidget(messageWindow);
  messageWindow->setFixedSize(220, 150);

  QMultiLineEdit *messages = new QMultiLineEdit(messageWindow);
  messages->setGeometry(10, 10, 200, 100);
  QPushButton *clear = new QPushButton("Clear", messageWindow);
  clear->setGeometry(10, 120, 95, 20);
  QPushButton *hide = new QPushButton("Hide", messageWindow);
  hide->setGeometry(115, 120, 95, 20);

  messageWindow->setCaption("einfacher Dialog");
  messages->setReadOnly(true);
  messages->append("Initialisierung abgeschlossen\n");

  messageWindow->show();

  return app.exec();
}

