#include <kaboutdata.h>
#include <klocale.h>
#include <kapp.h>
#include <kcmdlineargs.h>
#include <qlabel.h>

int main(int argc, char **argv)
{
  KAboutData about("khello", I18N_NOOP("HelloWorld-KDE"), "1.0", 
                   I18N_NOOP("The Hello-World program for KDE"), KAboutData::License_GPL, 
		   "(c) 2000 Addison-Wesley", "http://www.addison.wesley.de", 
		   I18N_NOOP("Here is more text\neven more lines"), "Burkhard.Lehner@gmx.de");
  about.addAuthor("Burkhard Lehner", I18N_NOOP("Source and Testing"), 
                  "Burkard.Lehner@gmx.de", "http://www.burkhardlehner.de");
  about.addCredit("My mother", I18N_NOOP("cooking coffee"), "mom@gmx.de", "http://www.mother.de");
  
  KCmdLineArgs::init(argc, argv, &about);
  KApplication app;
  QLabel *l = new QLabel(i18n("<h1>Hallo, Welt!</h1>"), 0);

  l->show();
  app.setMainWidget(l);
  return app.exec();
}

