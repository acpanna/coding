#include <kaboutdata.h>
#include <klocale.h>
#include <kapp.h>
#include <kcmdlineargs.h>
#include <qlabel.h>

static KCmdLineOptions options[] = {{"b", 0 , 0},
                                    {"beep", I18N_NOOP("Beep on startup"), 0},
				    {"message <text>", I18N_NOOP("Display this message"), "<h1>Hello, World!</h1>"},
				    {0, 0, 0}};

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
  KCmdLineArgs::addCmdLineOptions(options);
  KApplication app;

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  if(args->isSet("b"))
    KApplication::beep();
    
  QLabel *l = new QLabel(args->getOption("message"), 0);

  l->show();
  app.setMainWidget(l);
  return app.exec();
}

