#include <kapp.h>
#include <kcmdlineargs.h>
#include <klocale.h>

#include "mymainwindow.h"

int main(int argc, char **argv)
{
  QString aboutText("KDE und Qt Programmierung\n(c) Addison-Wesley");
  KCmdLineArgs::init(argc, argv, "khelloworld", aboutText, "1.0");
  KApplication app;

  MyMainWindow *top = new MyMainWindow();
  top->show();

  return app.exec();
}
