#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qframe.h>
#include <kseparator.h>

#include "dialog6.h"

AddressDialog::AddressDialog(QWidget *parent, const char *name, WFlags f)
: QDialog(parent, name, true, f)
{
  nameW = new QLineEdit(this);
  emailW = new QLineEdit(this);
  ageW = new QSpinBox(0, 130, 1, this);

  QPushButton *add = new QPushButton("Add", this);
  connect(add, SIGNAL(clicked()), SLOT(accept()));
  QPushButton *cancel = new QPushButton("Cancel", this);
  connect(cancel, SIGNAL(clicked()), SLOT(reject()));

  add->setDefault(true);

  QVBoxLayout *top = new QVBoxLayout(this, 10);
  QGridLayout *contents = new QGridLayout(3, 2);
  QHBoxLayout *buttons = new QHBoxLayout();

  top->addLayout(contents);
  top->addWidget(new KSeparator(QFrame::HLine, this));
  top->addLayout(buttons);

  QLabel *l = new QLabel(nameW, "&Name : ", this);
  l->setAlignment(AlignRight | AlignVCenter);
  contents->addWidget(l, 0, 0);
  contents->addWidget(nameW, 0, 1);
  l = new QLabel(emailW, "e&Mail : ", this);
  l->setAlignment(AlignRight | AlignVCenter);
  contents->addWidget(l, 1, 0);
  contents->addWidget(emailW, 1, 1);
  l = new QLabel(ageW, "&Age :", this);
  l->setAlignment(AlignRight | AlignVCenter);  
  contents->addWidget(l, 2, 0);
  contents->addWidget(ageW, 2, 1);
 
  buttons->addStretch(1);
  buttons->addWidget(add);
  buttons->addWidget(cancel);

  top->activate();
}

void AddressDialog::clear()
{
  nameW->clear();
  emailW->clear();
  ageW->setValue(20);
}
