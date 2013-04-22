#include <kaction.h>
#include <kapp.h>
#include <kfiledialog.h>
#include <klocale.h>
#include <kstdaction.h>
#include <kmessagebox.h>
#include <qclipboard.h>
#include <qworkspace.h>

#include "kminiedit.h"

KMiniEdit::KMiniEdit() : KMainWindow()
{
  // Anlegen des Editor-Fensters

  workspace = new QWorkspace (this);
  setCentralWidget (workspace);
  connect(workspace, SIGNAL(windowActivated (QWidget *)), this, SLOT(updateBarsAndCaption()));

  // Erzeugen der Aktionen für das File-Menü
  KStdAction::openNew(this, SLOT(fileNew()), actionCollection());
  KStdAction::open(this, SLOT(fileOpen()), actionCollection());
  recentAction = KStdAction::openRecent(0, 0, actionCollection());
  recentAction->loadEntries(KGlobal::config());
  connect(recentAction, SIGNAL(urlSelected (const KURL &)), this, SLOT(fileOpenRecent (const KURL &)));

  saveAction = KStdAction::save(this, SLOT(fileSave()), actionCollection());

  KStdAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
  closeAction = KStdAction::close(this, SLOT(fileClose()), actionCollection());
  KStdAction::quit(this, SLOT(fileQuit()), actionCollection());

  // Erzeugen der Aktionen für das Edit-Menü
  undoAction = KStdAction::undo(this, SLOT(editUndo()), actionCollection());
  redoAction = KStdAction::redo(this, SLOT(editRedo()), actionCollection());
  cutAction = KStdAction::cut(this, SLOT(editCut()), actionCollection());
  copyAction = KStdAction::copy(this, SLOT(editCopy()), actionCollection());
  KStdAction::selectAll(this, SLOT(editSelectAll()), actionCollection());

  pasteAction = KStdAction::paste(this, SLOT(editPaste()), actionCollection());
  connect(kapp->clipboard(), SIGNAL(dataChanged()), this, SLOT(checkClipboard()));
  checkClipboard ();

  // Erzeugen der Aktionen für das Window-Menü
  new KAction("&Tile", "tile", 0, workspace, SLOT(tile()), actionCollection(), "window_tile");
  new KAction("&Cascade", "cascade", 0, workspace, SLOT(cascade()), actionCollection(), "window_cascade");
  windowSelectAction = new KSelectAction("&Windows", 0, 0, 0, 0, actionCollection(), "window_windowlist");
  connect(windowSelectAction, SIGNAL(activated (int)), this, SLOT(activateWindow (int)));

  createGUI();
  updateBarsAndCaption();
}

KMiniEdit::~KMiniEdit()
{
}

void KMiniEdit::loadFile (const KURL &newurl)
{
  fileOpenRecent (newurl);
}

bool KMiniEdit::queryClose ()
{
  while (!workspace->windowList().isEmpty())
  {
    QWidget *w = workspace->windowList().first();
    w->close(true);
    
    if (workspace->windowList().containsRef (w))
      return false;
  }
  return true;
}

void KMiniEdit::fileNew()
{
  EditorAndURL *w = new EditorAndURL (workspace);
  connect(w, SIGNAL(barsChanged()), this, SLOT(updateBarsAndCaption()));
  connect(w, SIGNAL(newURLused(const KURL &)), this, SLOT(addURLtoRecent(const KURL &)));
}

void KMiniEdit::fileOpen()
{
  KURL newurl = KFileDialog::getOpenURL();
  if (!newurl.isEmpty())
  {
    EditorAndURL *w = new EditorAndURL(workspace);
    connect(w, SIGNAL(barsChanged()), this, SLOT(updateBarsAndCaption()));
    connect(w, SIGNAL(newURLused(const KURL &)), this, SLOT(addURLtoRecent(const KURL &)));
    w->loadFile(newurl);
  }
}

void KMiniEdit::fileOpenRecent(const KURL &newurl)
{
  EditorAndURL *w = new EditorAndURL(workspace);
  connect(w, SIGNAL(barsChanged()), this, SLOT(updateBarsAndCaption()));
  connect(w, SIGNAL(newURLused(const KURL &)), this, SLOT(addURLtoRecent(const KURL &)));
  w->loadFile (newurl);
}

void KMiniEdit::fileSave()
{
  if (active() != 0)
    active()->saveFile(active()->url);
}

void KMiniEdit::fileSaveAs()
{
  if (active() != 0)
    active()->saveFile(KURL());
}

void KMiniEdit::fileQuit()
{
  close();
}

void KMiniEdit::checkClipboard()
{
  pasteAction->setEnabled(kapp->clipboard()->text() != QString::null);
}

void KMiniEdit::updateBarsAndCaption()
{
  if (active())
  {
    bool modified = active()->edited();
    
    if (active()->url.isEmpty())
      setCaption(i18n("New Document"), modified);
    else
      setCaption(active()->url.prettyURL(), modified);
    
    saveAction->setEnabled (modified);
    closeAction->setEnabled (true);

    undoAction->setEnabled(active()->hasUndo);
    redoAction->setEnabled(active()->hasRedo);
    cutAction->setEnabled(active()->hasCopy);
    copyAction->setEnabled(active()->hasCopy);
  }
  else
  {
    setCaption(i18n("No Document"), false);
    saveAction->setEnabled(false);
    closeAction->setEnabled(false);

    undoAction->setEnabled(false);
    redoAction->setEnabled(false);
    cutAction->setEnabled(false);
    copyAction->setEnabled(false);
  }

  QWidgetList l = workspace->windowList();
  QStringList urls;
  for (uint i=0; i<l.count(); i++)
  {
    QString urlname;
    EditorAndURL *w = (EditorAndURL *) (l.at(i));
    
    if (w->url.isEmpty())
      urlname = i18n ("New Document");
    else
      urlname = w->url.prettyURL();
    
    if (w->edited())
      urlname += " *";
    urls << urlname;
  }
  windowSelectAction->setItems(urls);
  windowSelectAction->setCurrentItem(l.findRef (active()));
}

void KMiniEdit::addURLtoRecent(const KURL &url)
{
  recentAction->addURL(url);
  recentAction->saveEntries(KGlobal::config());
}

void KMiniEdit::activateWindow(int i)
{
  QWidget *w = workspace->windowList().at (i);
  if (w)
    w->setFocus();
}

EditorAndURL *KMiniEdit::active()
{
  return (EditorAndURL*)(workspace->activeWindow());
}
