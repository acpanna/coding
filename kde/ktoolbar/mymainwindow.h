#ifndef _MYMAINWINDOW_H_
#define _MYMAINWINDOW_H_

#include <kmainwindow.h>

class QLabel;
class KAction;

class MyMainWindow : public KMainWindow
{
  Q_OBJECT

  public:
    MyMainWindow();
    ~MyMainWindow();

  private slots:
    void fileQuit();
    void fileClear();

  private:
    QLabel *text;
    KAction *clearAction;
};

#endif
