#ifndef _KMINIEDIT_H
#define _KMINIEDIT_H

#include <qmultilineedit.h>
#include <kurl.h>
#include <kmainwindow.h>

#include "editorandurl.h"

class KAction;
class KRecentFilesAction;
class KSelectAction;
class QFile;
class QWorkspace;

class KMiniEdit : public KMainWindow
{
  Q_OBJECT 
  public:
    KMiniEdit();
    ~KMiniEdit();
    void loadFile(const KURL &url);

  protected:
    bool queryClose();

  private slots:
    void fileNew();
    void fileOpen();
    void fileOpenRecent(const KURL&);
    void fileSave();
    void fileSaveAs();
    void fileClose()      {if (active()) active()->close();}
    void fileQuit();

    void editUndo()       {if (active()) active()->undo();}
    void editRedo()       {if (active()) active()->redo();}
    void editCut()        {if (active()) active()->cut();}
    void editCopy()       {if (active()) active()->copy();}
    void editPaste()      {if (active()) active()->paste();}
    void editSelectAll()  {if (active()) active()->selectAll();}

    void checkClipboard();
    void updateBarsAndCaption();
    void activateWindow (int);
    void addURLtoRecent (const KURL&);

private:
    EditorAndURL *active ();

    KAction *saveAction, *closeAction, *undoAction, *redoAction,
            *cutAction, *copyAction, *pasteAction;
    
    KRecentFilesAction *recentAction;
    KSelectAction *windowSelectAction;

    QWorkspace *workspace;
};

#endif
