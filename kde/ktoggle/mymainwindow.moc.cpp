/****************************************************************************
** MyMainWindow meta object code from reading C++ file 'mymainwindow.h'
**
** Created: Thu Aug 2 14:08:36 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.1.1   edited 2000-03-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MyMainWindow
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 7
#elif Q_MOC_OUTPUT_REVISION != 7
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mymainwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MyMainWindow::className() const
{
    return "MyMainWindow";
}

QMetaObject *MyMainWindow::metaObj = 0;

void MyMainWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(KMainWindow::className(), "KMainWindow") != 0 )
	badSuperclassWarning("MyMainWindow","KMainWindow");
    (void) staticMetaObject();
}

QString MyMainWindow::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MyMainWindow",s);
}

QMetaObject* MyMainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KMainWindow::staticMetaObject();
    typedef void(MyMainWindow::*m1_t0)(bool);
    typedef void(MyMainWindow::*m1_t1)();
    typedef void(MyMainWindow::*m1_t2)();
    typedef void(MyMainWindow::*m1_t3)();
    typedef void(MyMainWindow::*m1_t4)();
    m1_t0 v1_0 = Q_AMPERSAND MyMainWindow::toggleToolBar;
    m1_t1 v1_1 = Q_AMPERSAND MyMainWindow::fileQuit;
    m1_t2 v1_2 = Q_AMPERSAND MyMainWindow::fileClear;
    m1_t3 v1_3 = Q_AMPERSAND MyMainWindow::justifyLeft;
    m1_t4 v1_4 = Q_AMPERSAND MyMainWindow::justifyRight;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    slot_tbl[0].name = "toggleToolBar(bool)";
    slot_tbl[1].name = "fileQuit()";
    slot_tbl[2].name = "fileClear()";
    slot_tbl[3].name = "justifyLeft()";
    slot_tbl[4].name = "justifyRight()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    metaObj = QMetaObject::new_metaobject(
	"MyMainWindow", "KMainWindow",
	slot_tbl, 5,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
