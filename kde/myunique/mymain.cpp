#include "myunique.h"
#include <kcmdlineargs.h>
#include <klocale.h>

static KCmdLineOptions options[] = {{"b", 0, 0},
                                    {"nobeep", I18N_NOOP("Beep on startup"), 0},
				    {"message <text>", I18N_NOOP("Display this message"), "<h1>Hello, World!</h1>"},
				    {0, 0, 0}};

int main(int argc, char **argv)
{
  KCmdLineArgs::init(argc, argv, "hello-kde", "The Helloo World program for KDE", "1.0");
  KCmdLineArgs::addCmdLineOptions(options);
  MyUnique::addCmdLineOptions();
  MyUnique app;
  return app.exec();
}

