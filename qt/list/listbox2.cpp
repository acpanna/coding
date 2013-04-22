#include <qapplication.h>
#include <qlabel.h>
#include <qlistbox.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  
  QLabel *l = new QLabel("Hallo, Welt!", 0);
  l->show();
  
  QListBox *b = new QListBox(0);
  b->insertItem("George");
  b->insertItem("Paul");
  b->insertItem("Ringo");
  b->insertItem("John");
  b->show();

  QObject::connect(b, SIGNAL(selected(int)), l, SLOT(setNum(int)));
  
  app.setMainWidget(l);
  return app.exec();
}
