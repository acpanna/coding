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
  KToggleAction *toolbarAction = new KToggleAction(i18n("Show &Toolbar"), 0, actionCollection(), "settings_show_toolbar");
  toolbarAction->setChecked(true);
  connect(toolbarAction, SIGNAL(toggled(bool)), this, SLOT(toggleToolBar(bool)));

  KRadioAction *leftJustifyAction = new KRadioAction("Justify &Left", "leftjust", 0, this, SLOT(justifyLeft()), actionCollection(), "justify_left");
  leftJustifyAction->setExclusiveGroup("justify");
  KRadioAction *rightJustifyAction = new KRadioAction("Justify &Right", "rightjust", 0, this, SLOT(justifyRight()), actionCollection(), "justify_right");
  rightJustifyAction->setExclusiveGroup("justify");  
  leftJustifyAction->setChecked(true);

  QPopupMenu *settingsMenu = new QPopupMenu();

  leftJustifyAction->plug(toolBar());
  rightJustifyAction->plug(toolBar());
  toolbarAction->plug(settingsMenu);
  clearAction->plug(filePopup);
  clearAction->plug(toolBar()); 
  quitAction->plug(filePopup);
  quitAction->plug(toolBar());

  menuBar()->insertItem(i18n("&File"), filePopup);
  menuBar()->insertSeparator();
  menuBar()->insertItem("&Settings", settingsMenu);
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

void MyMainWindow::fileClear()
{
  text->clear();
  clearAction->setEnabled(false);
}

void MyMainWindow::toggleToolBar(bool doShow)
{
  if (doShow)
    toolBar()->show();
  else
    toolBar()->hide();
}

void MyMainWindow::justifyRight()
{}

void MyMainWindow::justifyLeft()
{}
