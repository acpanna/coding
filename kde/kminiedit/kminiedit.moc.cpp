/****************************************************************************
** KMiniEdit meta object code from reading C++ file 'kminiedit.h'
**
** Created: Fri Aug 10 15:38:03 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "kminiedit.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *KMiniEdit::className() const
{
    return "KMiniEdit";
}

QMetaObject *KMiniEdit::metaObj = 0;

void KMiniEdit::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(KMainWindow::className(), "KMainWindow") != 0 )
	badSuperclassWarning("KMiniEdit","KMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString KMiniEdit::tr(const char* s)
{
    return qApp->translate( "KMiniEdit", s, 0 );
}

QString KMiniEdit::tr(const char* s, const char * c)
{
    return qApp->translate( "KMiniEdit", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* KMiniEdit::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (KMiniEdit::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (KMiniEdit::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (KMiniEdit::*m1_t2)(const KURL&);
    typedef void (QObject::*om1_t2)(const KURL&);
    typedef void (KMiniEdit::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (KMiniEdit::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (KMiniEdit::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (KMiniEdit::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (KMiniEdit::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    m1_t0 v1_0 = &KMiniEdit::fileNew;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &KMiniEdit::fileOpen;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &KMiniEdit::fileOpenRecent;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &KMiniEdit::fileSave;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &KMiniEdit::fileSaveAs;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &KMiniEdit::fileQuit;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &KMiniEdit::checkClipboard;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &KMiniEdit::checkEdited;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    QMetaData *slot_tbl = QMetaObject::new_metadata(8);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(8);
    slot_tbl[0].name = "fileNew()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "fileOpen()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "fileOpenRecent(const KURL&)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "fileSave()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "fileSaveAs()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Private;
    slot_tbl[5].name = "fileQuit()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Private;
    slot_tbl[6].name = "checkClipboard()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Private;
    slot_tbl[7].name = "checkEdited()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"KMiniEdit", "KMainWindow",
	slot_tbl, 8,
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
