#include <qcolor.h>
#include <qpen.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qbitmap.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QPixmap pix(50, 50);
  QPainter p(&pix);
  
  pix.fill(white);
  p.setPen(QPen(red, 3));
  p.drawLine(0, 15, 50, 15);
  p.drawLine(0, 25, 50, 25);
  p.drawLine(0, 35, 50, 35);
  p.end();

  QBitmap mask(50, 50);
  mask.fill(color0);
  p.begin(&mask);
  p.setPen(QPen(color1, 5));
  p.setBrush(NoBrush);
  p.drawEllipse(0, 0, 50, 50);
  p.end();

  pix.setMask(mask);
  
  bitBlt(this, 0, 0, &pix);
}
