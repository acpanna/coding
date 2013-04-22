#include <qcolor.h>
#include <qpen.h>
#include <qpainter.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QColor::setLazyAlloc(true); // Pixelwert wird erst berechnet, wenn Farbe benoetigt wird (Default)

  int myAllocContext = QColor::enterAllocContext();
  
  static QColor himmelblau(190, 190, 255); // Farbe wird nur einmal allokiert 
                                           // und bleibt nach Ende des Paint-Events erhalten 

  QPen stift(himmelblau, 5);  // alternativ: QPen stift(Qt::cyan, 5);
  QPainter painter(this);
  painter.setPen(stift);
  painter.drawLine(10, 10, 50, 80);

  QColor blau(240, 255, 100, QColor::Hsv); // alternativ: QColor blau;  blau.setHsv(240, 255, 100);
  stift.setColor(blau);
  painter.setPen(stift);
  painter.drawLine(50, 80, 100, 200);

  QColor::leaveAllocContext();
  QColor::destroyAllocContext(myAllocContext);

  QColor mittelgruen(120, 255, 160, QColor::Hsv);
  QColor hellgruen = mittelgruen.light(150);
  QColor dunkelgruen = mittelgruen.dark(150);
}
