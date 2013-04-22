#include <kaction.h>
#include <kapp.h>
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstdaction.h>
#include <qlabel.h>
#include <qpopupmenu.h>

#include "mymainwindow.h"

MyMainWindow::MyMainWindow() : KMainWindow(0)
{
  text = new QLabel(i18n("<h1>Hello, World!</h1>"), this);
  setCentralWidget(text);

  QPopupMenu *filePopup = new QPopupMenu(this);
  KAction *quitAction = KStdAction::quit(this, SLOT(fileQuit()), actionCollection());
  clearAction = new KAction(i18n("&Clear"), "stop", Qt::CTRL + Qt::Key_X, this, SLOT(fileClear()), actionCollection(), "file_clear");

  clearAction->plug(filePopup);
  clearAction->plug(toolBar()); 
  quitAction->plug(filePopup);
  quitAction->plug(toolBar());

  menuBar()->insertItem(i18n("&File"), filePopup);
  menuBar()->insertSeparator();
  menuBar()->insertItem(i18n("&Help"), helpMenu());

  statusBar()->insertItem("Line xxx", 1);
  statusBar()->insertItem("Column xxx", 2);
  statusBar()->insertItem("Zoom: 100%", 3);
  
  //statusBar()->message("Ready...");         falls Statuszeile nur aus einem Feld besteht
  //statusBar()->message("Ready...", 2000);   zeige Nachricht fuer 2000 Millisekunden
}

MyMainWindow::~MyMainWindow()
{}

void MyMainWindow::fileQuit()
{
  int really = KMessageBox::questionYesNo(this, i18n("Do you really want to quit?"));
  if (really == KMessageBox::Yes)
    kapp->quit();
}

void MyMainWindow::fileClear()
{
  text->clear();
  clearAction->setEnabled(false);
}
