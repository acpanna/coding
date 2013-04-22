#include <kaction.h>
#include <kapp.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kmainwindow.h>
#include <kmenubar.h>
#include <kstdaction.h>
#include <qlabel.h>
#include <qpopupmenu.h>

int main(int argc, char **argv)
{
  QString aboutText("KDE- und Qt-Programmierung\n(c) 2000 Addison-Wesley Germany");
  KCmdLineArgs::init(argc, argv, "kexample", aboutText, "1.0");
  KApplication app;
  KMainWindow *top = new KMainWindow(0);
  QPopupMenu *filePopup = new QPopupMenu(top);
  KAction *quitAction;
  quitAction = KStdAction::quit(&app, SLOT(quit()));
  quitAction->plug(filePopup);
  top->menuBar()->insertItem(i18n("&File"), filePopup);
  top->menuBar()->insertSeparator();
  top->menuBar()->insertItem(i18n("&Help"), top->helpMenu());
  QLabel *text = new QLabel(i18n("<h1>Hello, world!</h1>"), top);
  top->setCentralWidget(text);
  top->show();

  return app.exec();
}
