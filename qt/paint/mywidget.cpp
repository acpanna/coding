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
  QPainter p(this);

  p.setPen(NoPen);
  p.setBrush(black);
  p.drawChord(50, 0, 100, 100, 90*16, 180*16);
  p.setBrush(white);
  p.drawChord(50, 0, 100, 100, 270*16, 180*16);
  p.drawChord(75, 50, 50, 50, 90*16, 180*16);
  p.setBrush(black);
  p.drawChord(70, 0, 50, 50, 270*16, 180*16);
  p.drawEllipse(92, 67, 16, 16);
  p.setBrush(white);
  p.drawEllipse(92, 17, 16, 16);
  p.setBrush(NoBrush);
  p.setPen(QPen(black, 2));
  p.drawEllipse(50, 0, 100, 100);
}
