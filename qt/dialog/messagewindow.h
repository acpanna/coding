#ifndef _MESSAGEWINDOW_H_
#define _MESSAGEWINDOW_H_

#include <qwidget.h>

class QPushButton;
class QMultiLineEdit;

class MessageWindow : public QWidget
{
  Q_OBJECT

  public:
    MessageWindow();
    ~MessageWindow();

  protected:
    void resizeEvent(QResizeEvent *);

  private:
    QMultiLineEdit *messages;
    QPushButton *clear, *hide;
};

#endif
