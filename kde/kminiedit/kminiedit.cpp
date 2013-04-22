#include <kaction.h>
#include <kapp.h>
#include <kfiledialog.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kstdaction.h>
#include <ktempfile.h>
#include <kmessagebox.h>
#include <qclipboard.h>
#include <qmultilineedit.h>
#include <qfile.h>
#include <qtextstream.h>

#include "kminiedit.h"

KMiniEdit::KMiniEdit() : KMainWindow()
{
  edit = new QMultiLineEdit(this);
  setCentralWidget(edit);

  KStdAction::openNew(this, SLOT(fileNew()), actionCollection());
  KStdAction::open(this, SLOT(fileOpen()), actionCollection());

  recentAction = KStdAction::openRecent(0, 0, actionCollection());
  recentAction->loadEntries(KGlobal::config());
  connect(recentAction, SIGNAL(urlSelected(const KURL &)), this, SLOT(fileOpenRecent(const KURL &)));

  saveAction = KStdAction::save(this, SLOT(fileSave()), actionCollection());
  checkEdited();
  connect(edit, SIGNAL(textChanged()), this, SLOT(checkEdited()));

  KStdAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
  KStdAction::quit(this, SLOT(fileQuit()), actionCollection());

  KAction *a;

  a = KStdAction::undo(edit, SLOT(undo()), actionCollection());
  a->setEnabled(false);
  connect(edit, SIGNAL(undoAvailable(bool)), a, SLOT(setEnabled(bool)));
  
  a = KStdAction::redo(edit, SLOT(redo()), actionCollection());
  a->setEnabled(false);
  connect(edit, SIGNAL(redoAvailable(bool)), a, SLOT(setEnabled(bool)));

  a = KStdAction::cut(edit, SLOT(cut()), actionCollection());
  a->setEnabled(false);
  connect(edit, SIGNAL(copyAvailable(bool)), a, SLOT(setEnabled(bool)));

  a = KStdAction::copy(edit, SLOT(copy()), actionCollection());
  a->setEnabled(false);
  connect(edit, SIGNAL(copyAvailable(bool)), a, SLOT(setEnabled(bool)));

  pasteAction = KStdAction::paste(edit, SLOT(paste()), actionCollection());
  checkClipboard();
  connect(kapp->clipboard(), SIGNAL(dataChanged()), this, SLOT(checkClipboard()));

  KStdAction::selectAll(edit, SLOT(selectAll()), actionCollection());

  createGUI();
}

KMiniEdit::~KMiniEdit()
{}

bool KMiniEdit::queryClose()
{
  if (!edit->edited())
    return true;

  QString text = i18n("<h2>Unsaved Changes</h2>"
                      "Save the changes in document %1 before "
		      "closing it?");
  int result = KMessageBox::warningYesNoCancel(this, text.arg(url.prettyURL()));
  
  if (result == KMessageBox::Yes)
    return saveFile(url);
    
  return (result == KMessageBox::No);
}

void KMiniEdit::fileNew()
{
  url = KURL();
  edit->clear();
  resetEdited();
}

void KMiniEdit::fileOpen()
{
  if (queryClose())
  {
    KURL newurl = KFileDialog::getOpenURL();
   
   if (!newurl.isEmpty())
      loadFile(newurl);
  }
}

void KMiniEdit::fileOpenRecent(const KURL &newurl)
{
  if (queryClose())
    loadFile(newurl);
}

void KMiniEdit::fileSave()
{
  saveFile(url);
}

void KMiniEdit::fileSaveAs()
{
  saveFile(KURL());
}

void KMiniEdit::fileQuit()
{
  if (queryClose())
    kapp->quit();
}
  
bool KMiniEdit::loadFile(KURL newurl)
{
  if (newurl.isMalformed())
  {
    QString text = i18n("<b>The URL %1 is not correct!</b>");
    KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
    return false;
  }

  QString filename;
  if (newurl.isLocalFile())
    filename = newurl.path();
  else
  {
    if (!KIO::NetAccess::download(newurl, filename))
    {
      QString text = i18n("<b>Error downloading %1!</b>");
      KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
      return false;
    }
  }

  QFile file(filename);
  file.open(IO_ReadOnly);
  QTextStream stream(&file);
  //stream.setEncoding(QTextStream::Unicode);
  edit->setText(stream.read());
  file.close();

  KIO::NetAccess::removeTempFile(filename);

  url = newurl;

  recentAction->addURL(url);
  recentAction->saveEntries(KGlobal::config());

  resetEdited();
  return true;
}

void KMiniEdit::saveToLocalFile(QFile *file)
{
  QTextStream stream(file);
  //stream.setEncoding(QTextStream::Unicode);
  stream << edit->text();
  file->close();
}

bool KMiniEdit::saveFile(KURL newurl)
{
  if (newurl.isEmpty())
    newurl = KFileDialog::getSaveURL();

  if (newurl.isEmpty())
    return false;

  if (newurl.isMalformed())
  {
    QString text = i18n("<b>THe URL %1 is not correct!</b>");
    KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
    return false;
  }

  if (newurl.isLocalFile())
  {
    QFile file(newurl.path());
    file.open(IO_WriteOnly);
    saveToLocalFile(&file);
  }

  else
  {
    KTempFile tempfile;
    saveToLocalFile(tempfile.file());
    if (!KIO::NetAccess::upload(tempfile.name(), newurl))
    {
      QString text = i18n("<b>Error uploading %1!</b>");
      KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
      tempfile.unlink();
      return false;
    }

    tempfile.unlink();
  }

  url = newurl;
  recentAction->addURL(url);
  recentAction->saveEntries(KGlobal::config());
  resetEdited();
  return true;
}

void KMiniEdit::checkClipboard()
{
  pasteAction->setEnabled(kapp->clipboard()->text() != QString::null);
}

void KMiniEdit::checkEdited()
{
  bool modified = edit->edited();
  saveAction->setEnabled(modified);
  if (url.isEmpty())
    setCaption(i18n("New Document"), modified);
  else
    setCaption(url.prettyURL(), modified);
}

void KMiniEdit::resetEdited()
{
  edit->setEdited(false);
  checkEdited();
}
  
