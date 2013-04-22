#include <iostream.h>
#include <qcolor.h>
#include <qpen.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpalette.h>
#include <qpicture.h>

#include "mywidget.h"

MyWidget::MyWidget() : QWidget() 
{}

MyWidget::~MyWidget()
{}

void MyWidget::paintEvent(QPaintEvent *ev)
{
  QPicture pic;
  QPainter p;

  if (pic.load("output.dat"))
  {
    p.begin(this);
    p.drawPicture(pic);
    p.end();
    
    return;
  }
  
  p.begin(&pic);

  // Einige Zeichenoperationen
  
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

  p.end();
  if (!pic.save("output.dat"))
    cerr <<"Datei konnte nicht gespeichert werden!"<<endl;
}
