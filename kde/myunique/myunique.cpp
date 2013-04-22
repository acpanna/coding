#include "myunique.h"
#include <kcmdlineargs.h>
#include <qlabel.h>

MyUnique::MyUnique(bool allowStyles, bool GUIenabled)
:KUniqueApplication(allowStyles, GUIenabled)
{
  l = new QLabel(0);
  l->show();
  setMainWidget(l);
}

int MyUnique::newInstance()
{
  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  if (args->isSet("beep"))
    KApplication::beep();
  l->setText(args->getOption("message"));
}
