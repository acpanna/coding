#include <kapp.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kminiedit.h"

static const char *description = I18N_NOOP("KMiniEdit");

static KCmdLineOptions options[] = {{"+[arg1]", I18N_NOOP("Load that file or URL"), 0 },
                                    { 0, 0, 0 }};

int main(int argc, char *argv[])
{

  KAboutData aboutData("kminimdi", I18N_NOOP("KMiniMDI"), "0.1", description, KAboutData::License_GPL, "(c) 2000, Burkhard Lehner");
  aboutData.addAuthor("Burkhard Lehner",0, "Burkhard.Lehner@gmx.de");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions(options); 

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

  KApplication a;
  KMiniEdit *kminiedit = new KMiniEdit();
  
  for (int i=0; i<args->count(); i++)
    kminiedit->loadFile(args->url(i));
  
  kminiedit->show();

  return a.exec();
}
