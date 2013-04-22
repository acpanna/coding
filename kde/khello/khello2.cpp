#include <kapp.h>
#include <kcmdlineargs.h>
#include <qlabel.h>

int main(int argc, char **argv)
{
  KCmdLineArgs::init(argc, argv, "khello", "The Hello-World program for KDE", "1.0");
  KApplication app;
  QLabel *l = new QLabel("<h1>Hallo, Welt!</h1>", 0);

  l->show();
  app.setMainWidget(l);
  return app.exec();
}

