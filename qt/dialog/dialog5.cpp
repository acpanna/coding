#include <qapplication.h>
#include <qpushbutton.h>
#include <qmultilineedit.h>
#include <qvbox.h>
#include <qhbox.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QVBox *messageWindow = new QVBox();
  app.setMainWidget(messageWindow);

  messageWindow->setSpacing(10);
  messageWindow->setMargin(10);

  QMultiLineEdit *messages = new QMultiLineEdit(messageWindow);
  QHBox *buttonBox = new QHBox(messageWindow);

  buttonBox->setSpacing(10);
  
  QPushButton *clear = new QPushButton("Clear", buttonBox);
  QPushButton *hide = new QPushButton("Hide", buttonBox);
  
  messageWindow->setCaption("einfacher Dialog");
  messages->setReadOnly(true);
  messages->append("Initialisierung abgeschlossen\n");

  messageWindow->show();

  return app.exec();
}

