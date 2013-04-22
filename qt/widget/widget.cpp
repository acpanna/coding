#include <qapplication.h>
#include <qwidget.h>
#include <qframe.h>
#include <qpixmap.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QWidget *w = new QWidget();
  app.setMainWidget(w);

  w->resize(300, 100);
  w->setCaption("QWidget Example");

  QFrame *sub1 = new QFrame(w);
  QFrame *sub2 = new QFrame(w);
  sub1->setFrameStyle(QFrame::Box | QFrame::Plain);
  sub2->setFrameStyle(QFrame::Box | QFrame::Plain);
  sub1->setGeometry(40, 20, 150, 50);
  // alternativ: sub1->move(40, 20);  sub1->resize(150, 50);
  sub2->setGeometry(130, 40, 150, 40);

  sub1->raise();
  // alternativ: sub2->lower();
  w->setBackgroundPixmap(QPixmap("circuit.jpg"));
  w->show();

  return app.exec();
}
