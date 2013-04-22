#include <kaboutdata.h>
#include <kapp.h>
#include <kcmdlineargs.h>
#include <qlabel.h>

int main(int argc, char **argv)
{
  KAboutData about("khello", "HelloWorld-KDE", "1.0", 
                   "The Hello-World program for KDE", KAboutData::License_GPL, 
		   "(c) 2000 Addison-Wesley", "http://www.addison.wesley.de", 
		   "Here is more text\neven more lines", "Burkhard.Lehner@gmx.de");
  about.addAuthor("Burkhard Lehner", "Source and Testing", 
                  "Burkard.Lehner@gmx.de", "http://www.burkhardlehner.de");
  about.addCredit("My mother", "cooking coffee", "mom@gmx.de", "http://www.mother.de");
  
  KCmdLineArgs::init(argc, argv, &about);
  KApplication app;
  QLabel *l = new QLabel("<h1>Hallo, Welt!</h1>", 0);

  l->show();
  app.setMainWidget(l);
  return app.exec();
}

