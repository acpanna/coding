#ifndef _COUNTER2_H_
#define _COUNTER2_H_

#include <qlabel.h>

class Counter : public QLabel
{
  Q_OBJECT

  public:
    Counter(QWidget *parent = 0, const char *name = 0);
    ~Counter();

  public slots:
    void countUp();

  private:
    int n;
};

#endif
