#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <qobject.h>

class Counter : public QObject
{
  Q_OBJECT

  public:
    Counter(QObject *parent = 0, const char *name = 0);
    ~Counter();

  public slots:
    void countUp();

  private:
    int n;
};

#endif
