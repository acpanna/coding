#include <qpushbutton.h>
#include <qmultilinedit.h>

#include "messagewindow.h"

MessageWindow::MessageWindow() : QWidget()
{
  setCaption("Dialog mit resizeEvent");
  messages = new QMultiLineEdit(this);
  clear = new QPushButton("Clear", this);
  hide = new QPushButton("Hide", this);
  
  messages->setReadOnly(true);
  setMinimumSize(140, 110);
  resize(220, 150);
}

MessageWindow::~MessageWindow()
{}

void MessageWindow::resizeEvent(QResizeEvent *)
{
  int buttonWidth = (width() - 30) / 2;
  messages->setGeometry(10, 10, width()-20, height()-50);

  clear->setGeometry(10, height()-30, buttonWidth, 20);
  hide->setGeometry(width()-10-buttonWidth, height()-30, buttonWidth, 20);
}  
