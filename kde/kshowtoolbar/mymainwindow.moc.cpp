/****************************************************************************
** MyMainWindow meta object code from reading C++ file 'mymainwindow.h'
**
** Created: Fri Aug 10 15:48:20 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mymainwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *MyMainWindow::className() const
{
    return "MyMainWindow";
}

QMetaObject *MyMainWindow::metaObj = 0;

void MyMainWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(KMainWindow::className(), "KMainWindow") != 0 )
	badSuperclassWarning("MyMainWindow","KMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MyMainWindow::tr(const char* s)
{
    return qApp->translate( "MyMainWindow", s, 0 );
}

QString MyMainWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "MyMainWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MyMainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MyMainWindow::*m1_t0)(bool);
    typedef void (QObject::*om1_t0)(bool);
    typedef void (MyMainWindow::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (MyMainWindow::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &MyMainWindow::toggleToolBar;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MyMainWindow::fileQuit;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MyMainWindow::fileClear;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "toggleToolBar(bool)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "fileQuit()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "fileClear()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"MyMainWindow", "KMainWindow",
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
