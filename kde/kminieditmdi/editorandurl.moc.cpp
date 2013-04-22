/****************************************************************************
** EditorAndURL meta object code from reading C++ file 'editorandurl.h'
**
** Created: Fri Aug 10 16:08:10 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "editorandurl.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *EditorAndURL::className() const
{
    return "EditorAndURL";
}

QMetaObject *EditorAndURL::metaObj = 0;

void EditorAndURL::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QMultiLineEdit::className(), "QMultiLineEdit") != 0 )
	badSuperclassWarning("EditorAndURL","QMultiLineEdit");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString EditorAndURL::tr(const char* s)
{
    return qApp->translate( "EditorAndURL", s, 0 );
}

QString EditorAndURL::tr(const char* s, const char * c)
{
    return qApp->translate( "EditorAndURL", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* EditorAndURL::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QMultiLineEdit::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (EditorAndURL::*m1_t0)(bool);
    typedef void (QObject::*om1_t0)(bool);
    typedef void (EditorAndURL::*m1_t1)(bool);
    typedef void (QObject::*om1_t1)(bool);
    typedef void (EditorAndURL::*m1_t2)(bool);
    typedef void (QObject::*om1_t2)(bool);
    m1_t0 v1_0 = &EditorAndURL::updateUndo;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &EditorAndURL::updateRedo;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &EditorAndURL::updateCopy;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "updateUndo(bool)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "updateRedo(bool)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "updateCopy(bool)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    typedef void (EditorAndURL::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    typedef void (EditorAndURL::*m2_t1)(const KURL&);
    typedef void (QObject::*om2_t1)(const KURL&);
    m2_t0 v2_0 = &EditorAndURL::barsChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &EditorAndURL::newURLused;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "barsChanged()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "newURLused(const KURL&)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"EditorAndURL", "QMultiLineEdit",
	slot_tbl, 3,
	signal_tbl, 2,
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

// SIGNAL barsChanged
void EditorAndURL::barsChanged()
{
    activate_signal( "barsChanged()" );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL newURLused
void EditorAndURL::newURLused( const KURL& t0 )
{
    // No builtin function for signal parameter type const KURL&
    QConnectionList *clist = receivers("newURLused(const KURL&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const KURL&);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}
