/****************************************************************************
** Counter meta object code from reading C++ file 'counter2.h'
**
** Created: Mon Jul 30 20:59:36 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.1.1   edited 2000-03-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_Counter
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 7
#elif Q_MOC_OUTPUT_REVISION != 7
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "counter2.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *Counter::className() const
{
    return "Counter";
}

QMetaObject *Counter::metaObj = 0;

void Counter::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QLabel::className(), "QLabel") != 0 )
	badSuperclassWarning("Counter","QLabel");
    (void) staticMetaObject();
}

QString Counter::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("Counter",s);
}

QMetaObject* Counter::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QLabel::staticMetaObject();
    typedef void(Counter::*m1_t0)();
    m1_t0 v1_0 = Q_AMPERSAND Counter::countUp;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    slot_tbl[0].name = "countUp()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    metaObj = QMetaObject::new_metaobject(
	"Counter", "QLabel",
	slot_tbl, 1,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
