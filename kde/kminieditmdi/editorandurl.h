#ifndef _EDITORANDURL_H
#define _EDITORANDURL_H

#include <kurl.h>
#include <qwidget.h>
#include <qmultilineedit.h>

class QFile;

class EditorAndURL : public QMultiLineEdit  
{
  Q_OBJECT
  
  public:
    EditorAndURL(QWidget *parent, const char *name = 0);
    ~EditorAndURL () {}

    KURL url;
    bool hasUndo;
    bool hasRedo;
    bool hasCopy;

  signals:
    void barsChanged();
    void newURLused(const KURL &);

  protected:
    void closeEvent(QCloseEvent *ev);

  private slots:
    void updateUndo (bool b);
    void updateRedo (bool b);
    void updateCopy (bool b);

  public:
    bool loadFile (KURL newurl);
    bool saveFile (KURL newurl);

  private:
    void saveToLocalFile (QFile *);
};

#endif
