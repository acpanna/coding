#ifndef _MYUNIQUE_H_
#define _MYUNIQUE_H_

#include <kuniqueapp.h>

class MyUnique : public KUniqueApplication
{
  Q_OBJECT

  public:
    MyUnique(bool allowStyles = true, bool GUIenabled = true);
    int newInstance();
};

#endif
