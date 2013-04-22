#include <kfiledialog.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <ktempfile.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qevent.h>

#include "editorandurl.h"

EditorAndURL::EditorAndURL(QWidget *parent, const char *name = 0)
: QMultiLineEdit(parent, name), url()
{
   hasUndo = hasRedo = hasCopy = false;
   connect (this, SIGNAL (undoAvailable (bool)), this, SLOT (updateUndo (bool)));
   connect (this, SIGNAL (redoAvailable (bool)), this, SLOT (updateRedo (bool)));
   connect (this, SIGNAL (copyAvailable (bool)), this, SLOT (updateCopy (bool)));
   connect (this, SIGNAL (textChanged()), this, SIGNAL (barsChanged()));

   setCaption (i18n ("New Document"));
   show();
}

void EditorAndURL::closeEvent(QCloseEvent *ev)
{
  ev->accept();
  
  if (edited())
  {
    QString text = i18n ("<H2>Unsaved Changes</H2>\nSave the changes in document %1 before closing it?");
    int result = KMessageBox::warningYesNoCancel(this, text.arg (url.prettyURL()));
    if (result == KMessageBox::Yes)
      if (!saveFile(url))
        ev->ignore();
    
    if (result == KMessageBox::Cancel)
      ev->ignore();
  }
}

void EditorAndURL::updateUndo(bool b)
{
  hasUndo = b;
  barsChanged();
}

void EditorAndURL::updateRedo (bool b)
{
  hasRedo = b;
  barsChanged();
}

void EditorAndURL::updateCopy (bool b)
{
  hasCopy = b;
  barsChanged();
}

bool EditorAndURL::loadFile (KURL newurl)
{
  if (newurl.isMalformed())
  {
    QString text = i18n ("<B>The URL %1 is not correct!</B>");
    KMessageBox::sorry (this, text.arg (newurl.prettyURL()));
    return false;
    
  }
  QString filename;
  if (newurl.isLocalFile())
    filename = newurl.path();
  else
  {
    if (!KIO::NetAccess::download (newurl, filename))
    {
      QString text = i18n ("<B>Error downloading %1!</B>");
      KMessageBox::sorry (this, text.arg (newurl.prettyURL()));
      return false;
    }
  }

  QFile file (filename);
  file.open (IO_ReadOnly);
  QTextStream stream(&file);
  stream.setEncoding (QTextStream::UnicodeUTF8);
  setText(stream.read());
  file.close();
  KIO::NetAccess::removeTempFile (filename);

  url = newurl;
  setCaption (url.prettyURL());
  newURLused (url);
  setEdited (false);
  barsChanged();
  return true;
}

void EditorAndURL::saveToLocalFile (QFile *file)
{
  file->open (IO_WriteOnly);
  QTextStream stream (file);
  stream.setEncoding (QTextStream::UnicodeUTF8);
  stream << text();
  file->close();
}

bool EditorAndURL::saveFile (KURL newurl)
{
  if (newurl.isEmpty())
    newurl = KFileDialog::getSaveURL ();
  if (newurl.isEmpty())
    return false;

  if (newurl.isMalformed())
  {
    QString text = i18n ("<B>The URL %1 is not correct!</B>");
    KMessageBox::sorry (this, text.arg (newurl.prettyURL()));
    return false;
  }

  if (newurl.isLocalFile())
  {
    QFile file (newurl.path());
    saveToLocalFile (&file);
  }
  else
  {
    KTempFile tempfile;
    saveToLocalFile (tempfile.file());
    if (!KIO::NetAccess::upload (tempfile.name(), newurl))
    {
      QString text = i18n ("<B>Error uploading %1!</B>");
      KMessageBox::sorry (this, text.arg (newurl.prettyURL()));
      tempfile.unlink();
      return false;
    }
    tempfile.unlink();
  }
  url = newurl;
  setCaption (url.prettyURL());
  newURLused (url);
  setEdited(false);
  barsChanged();
  return true;
}
