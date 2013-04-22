/****************************************************************************
** KMiniEdit meta object code from reading C++ file 'kminiedit.h'
**
** Created: Sun Aug 5 16:40:24 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.1.1   edited 2000-03-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_KMiniEdit
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 7
#elif Q_MOC_OUTPUT_REVISION != 7
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "kminiedit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *KMiniEdit::className() const
{
    return "KMiniEdit";
}

QMetaObject *KMiniEdit::metaObj = 0;

void KMiniEdit::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(KMainWindow::className(), "KMainWindow") != 0 )
	badSuperclassWarning("KMiniEdit","KMainWindow");
    (void) staticMetaObject();
}

QString KMiniEdit::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("KMiniEdit",s);
}

QMetaObject* KMiniEdit::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KMainWindow::staticMetaObject();
    typedef void(KMiniEdit::*m1_t0)();
    typedef void(KMiniEdit::*m1_t1)();
    typedef void(KMiniEdit::*m1_t2)(const KURL&);
    typedef void(KMiniEdit::*m1_t3)();
    typedef void(KMiniEdit::*m1_t4)();
    typedef void(KMiniEdit::*m1_t5)();
    typedef void(KMiniEdit::*m1_t6)();
    typedef void(KMiniEdit::*m1_t7)();
    m1_t0 v1_0 = Q_AMPERSAND KMiniEdit::fileNew;
    m1_t1 v1_1 = Q_AMPERSAND KMiniEdit::fileOpen;
    m1_t2 v1_2 = Q_AMPERSAND KMiniEdit::fileOpenRecent;
    m1_t3 v1_3 = Q_AMPERSAND KMiniEdit::fileSave;
    m1_t4 v1_4 = Q_AMPERSAND KMiniEdit::fileSaveAs;
    m1_t5 v1_5 = Q_AMPERSAND KMiniEdit::fileClose;
    m1_t6 v1_6 = Q_AMPERSAND KMiniEdit::checkClipboard;
    m1_t7 v1_7 = Q_AMPERSAND KMiniEdit::checkEdited;
    QMetaData *slot_tbl = QMetaObject::new_metadata(8);
    slot_tbl[0].name = "fileNew()";
    slot_tbl[1].name = "fileOpen()";
    slot_tbl[2].name = "fileOpenRecent(const KURL&)";
    slot_tbl[3].name = "fileSave()";
    slot_tbl[4].name = "fileSaveAs()";
    slot_tbl[5].name = "fileClose()";
    slot_tbl[6].name = "checkClipboard()";
    slot_tbl[7].name = "checkEdited()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl[5].ptr = *((QMember*)&v1_5);
    slot_tbl[6].ptr = *((QMember*)&v1_6);
    slot_tbl[7].ptr = *((QMember*)&v1_7);
    metaObj = QMetaObject::new_metaobject(
	"KMiniEdit", "KMainWindow",
	slot_tbl, 8,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
