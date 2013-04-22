#include <qapplication.h>

#include "messagewindow.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  MessageWindow *messageWindow = new MessageWindow();
  app.setMainWidget(messageWindow);

  messageWindow->show();

  return app.exec();
}

