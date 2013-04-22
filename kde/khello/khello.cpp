#include <kapp.h>
#include <qlabel.h>

int main(int argc, char **argv)
{
  KApplication app(argc, argv, "khello");
  QLabel *l = new QLabel("<h1>Hallo, Welt!</h1>", 0);

  l->show();
  app.setMainWidget(l);
  return app.exec();
}

