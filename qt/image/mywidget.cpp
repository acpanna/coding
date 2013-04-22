#include <math.h>
#include <qcolor.h>
#include <qpen.h>
#include <qapplication.h>
#include <qimage.h>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qpalette.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QImage img(50, 50, 32);
  int x, y;

  double diag = sqrt(2.0)*50;
  for (y=0; y<50; y++)
    for (x=0; x<50; x++)
    {
      double rx = x-24.5;
      double ry = y-24.5;

      double abstand = sqrt(rx*rx + ry*ry);

      int abstandInt = (int) (abstand/diag*2*255);

      QRgb farbe = qRgb(abstandInt, abstandInt, 255);

      img.setPixel(x, y, farbe);
    }   
  
  QPainter p(this);
  p.drawImage(80, 70, img);
}
