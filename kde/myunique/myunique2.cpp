#include "myunique2.h"
#include <kcmdlineargs.h>
#include <qlabel.h>

MyUnique::MyUnique(bool allowStyles, bool GUIenabled)
:KUniqueApplication(allowStyles, GUIenabled)
{
  connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
}

int MyUnique::newInstance()
{
  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  if (args->isSet("beep"))
    KApplication::beep();

  QLabel *l = new QLabel(args->getOption("message"), 0);
  l->show();
}
