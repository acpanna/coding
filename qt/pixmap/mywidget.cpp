#include <qcolor.h>
#include <qpen.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpalette.h>
#include <qpixmap.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QPixmap pix(20, 20);
  QPainter p(&pix);
  
  p.setBrush(red);
  p.setPen(NoPen);
  p.drawEllipse(0, 0, 20, 20);
  p.end();

  for (int i=0; i<5; i++)
    bitBlt(this, i*20, 0, &pix);
}
