/****************************************************************************
** MyMainWindow meta object code from reading C++ file 'mymainwindow.h'
**
** Created: Wed Aug 1 14:15:59 2001
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
    typedef void(MyMainWindow::*m1_t0)();
    m1_t0 v1_0 = Q_AMPERSAND MyMainWindow::fileQuit;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    slot_tbl[0].name = "fileQuit()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    metaObj = QMetaObject::new_metaobject(
	"MyMainWindow", "KMainWindow",
	slot_tbl, 1,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
