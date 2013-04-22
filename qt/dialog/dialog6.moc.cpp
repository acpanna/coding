/****************************************************************************
** AddressDialog meta object code from reading C++ file 'dialog6.h'
**
** Created: Mon Aug 13 15:41:24 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "dialog6.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AddressDialog::className() const
{
    return "AddressDialog";
}

QMetaObject *AddressDialog::metaObj = 0;

void AddressDialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("AddressDialog","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AddressDialog::tr(const char* s)
{
    return qApp->translate( "AddressDialog", s, 0 );
}

QString AddressDialog::tr(const char* s, const char * c)
{
    return qApp->translate( "AddressDialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AddressDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AddressDialog::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &AddressDialog::clear;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "clear()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"AddressDialog", "QDialog",
	slot_tbl, 1,
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
