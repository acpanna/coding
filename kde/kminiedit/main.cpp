#include <kapp.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kminiedit.h"

static const char *description = I18N_NOOP("KMiniEdit - A simple editor");

static KCmdLineOptions options[] =  {{"+[arg1]", I18N_NOOP("Load that file or URL"), 0},
                                     {0, 0, 0}};

int main(int argc, char **argv)
{
  KAboutData aboutData("kminiedit", I18N_NOOP("KMiniEdit"), "0.1", description, KAboutData::License_GPL, "(c) 2000, Burkhard Lehner");
  aboutData.addAuthor("Burkhard Lehner", 0, "Burkhard.Lehner@gmx.de");
  KCmdLineArgs::init(argc, argv, &aboutData);
  KCmdLineArgs::addCmdLineOptions(options);
  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  
  if (args->count() > 1)
    KCmdLineArgs::usage("Only one file allowed!");
  
  KApplication a;
  KMiniEdit *kminiedit = new KMiniEdit();
  if (args->count() > 0)
    kminiedit->loadFile(args->url(0));

  kminiedit->show();

  return a.exec();
}
