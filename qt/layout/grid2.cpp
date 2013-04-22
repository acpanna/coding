#include <qapplication.h>
#include <qpushbutton.h>
#include <qgrid.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QGrid *messageWindow = new QGrid(3, QGrid::Vertical);
  app.setMainWidget(messageWindow);
  
  QPushButton *b1 = new QPushButton("Pause", messageWindow);
  QPushButton *b2 = new QPushButton("Stop", messageWindow);
  QPushButton *b3 = new QPushButton("Slow", messageWindow); 
  QPushButton *b4 = new QPushButton("Rewind", messageWindow); 
  QPushButton *b5 = new QPushButton("Play", messageWindow);
  QPushButton *b6 = new QPushButton("FastForward", messageWindow);
  
  messageWindow->setCaption("einfacher Dialog");
  messageWindow->show();

  return app.exec();
}

