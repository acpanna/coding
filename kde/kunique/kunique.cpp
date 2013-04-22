#include <kuniqueapp.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <qlabel.h>
#include <stdio.h>

static KCmdLineOptions options[] = {{"b", 0, 0},
                                   {"beep", I18N_NOOP("Beep on startup"), 0},
				   {"message <text>", I18N_NOOP("Display this message"), "<h1>Hello, World!</h1>"},
				   {0, 0, 0}};

int main(int argc, char **argv)
{
  KCmdLineArgs::init(argc, argv, "hello-kde", "The Hello World program for KDE", "1.0");
  KCmdLineArgs::addCmdLineOptions(options);
  KUniqueApplication::addCmdLineOptions();

if (!KUniqueApplication::start())
  {  
    fprintf(stderr, "Das Programm laeuft schon !\n");
    exit(0);
  }
  KUniqueApplication app;

  QLabel *l = new QLabel("<h1>Hallo, Welt!</h1>", 0);
  l->show();
  app.setMainWidget(l);
  return app.exec();
}
