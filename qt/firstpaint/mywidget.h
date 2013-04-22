#include <qwidget.h>

class MyWidget : public QWidget
{
  Q_OBJECT

  public:
    MyWidget();
    ~MyWidget();

  protected:
    void paintEvent(QPaintEvent *ev);
};  
