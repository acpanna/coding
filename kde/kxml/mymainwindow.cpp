#include <kaction.h>
#include <kapp.h>
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstdaction.h>
#include <kedittoolbar.h>
#include <qlabel.h>
#include <qpopupmenu.h>

#include "mymainwindow.h"

MyMainWindow::MyMainWindow() : KMainWindow(0)
{
  text = new QLabel(i18n("<h1>Hello, World!</h1>"), this);
  setCentralWidget(text);

  KAction *quitAction = KStdAction::quit(this, SLOT(fileQuit()), actionCollection());
  clearAction = new KAction(i18n("&Clear"), "stop", Qt::CTRL + Qt::Key_X, this, SLOT(fileClear()), actionCollection(), "file_clear");

  KStdAction::configureToolbars(this, SLOT(configToolBar()), actionCollection());

  createGUI();
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

void MyMainWindow::configToolBar()
{
  KEditToolbar dialog(actionCollection());
  if (dialog.exec())
    createGUI();
}
