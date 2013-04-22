#include <qcolor.h>
#include <qpen.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpalette.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QPushButton *b = new QPushButton("Alarm", this);
  QPalette p = QApplication::palette();
  p.setColor(QColorGroup::Button, Qt::red);
  b->setPalette(p);

  /* Besser:                                                         */ 
  /* QColor backgrd = QApplication::palette().active().background(); */
  /* QPalette p(Qt::red, backgrd);                                   */
  /* b->setPalette(p);                                               */

  /* Um die Farben aller Widgets der gesamten Applikation zu aendern: */
  /* QPalette pal(Qt::greenlight(200), Qt::blue.light(180));          */
  /* QApplication::setPalette(p);                                     */

  b->show();
}
