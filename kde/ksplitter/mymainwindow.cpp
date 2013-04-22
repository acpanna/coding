#include <kaction.h>
#include <kapp.h>
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstdaction.h>
#include <qlabel.h>
#include <qpopupmenu.h>
#include <qmultilineedit.h>
#include <qsplitter.h>

#include "mymainwindow.h"

MyMainWindow::MyMainWindow() : KMainWindow(0)
{
  QSplitter *box = new QSplitter(Qt::Vertical, this);

  new QLabel(i18n("<h1>Hello, World!</h1>"), box);
  new QMultiLineEdit(box);
  setCentralWidget(box);

  QPopupMenu *filePopup = new QPopupMenu(this);
  KAction *quitAction = KStdAction::quit(this, SLOT(fileQuit()), actionCollection());
  quitAction->plug(filePopup);

  menuBar()->insertItem(i18n("&File"), filePopup);
  menuBar()->insertSeparator();
  menuBar()->insertItem(i18n("&Help"), helpMenu());
}

MyMainWindow::~MyMainWindow()
{}

void MyMainWindow::fileQuit()
{
  int really = KMessageBox::questionYesNo(this, i18n("Do you really want to quit?"));
  if (really == KMessageBox::Yes)
    kapp->quit();
}
