#ifndef _KMINIEDIT_H_
#define _KMINIEDIT_H_

#include <kurl.h>
#include <kmainwindow.h>

class KAction;
class KRecentFilesAction;
class QMultiLineEdit;
class QFile;

class KMiniEdit : public KMainWindow
{
  Q_OBJECT
  public:
    KMiniEdit();
    ~KMiniEdit();

  protected:
    bool queryClose();

  private slots:
   void fileNew();
   void fileOpen();
   void fileOpenRecent(const KURL&);
   void fileSave();
   void fileSaveAs();
   void fileQuit();
   
   void checkClipboard();
   void checkEdited();

  public:
    bool loadFile(KURL newurl);

  private:
    void saveToLocalFile(QFile *);
    bool saveFile(KURL newurl);

    void resetEdited();

    KAction *saveAction, *pasteAction;
    KRecentFilesAction *recentAction;

    QMultiLineEdit *edit;
    KURL url;
};

#endif
