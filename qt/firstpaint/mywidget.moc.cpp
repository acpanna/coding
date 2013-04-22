/****************************************************************************
** MyWidget meta object code from reading C++ file 'mywidget.h'
**
** Created: Fri Aug 24 15:23:03 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mywidget.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *MyWidget::className() const
{
    return "MyWidget";
}

QMetaObject *MyWidget::metaObj = 0;

void MyWidget::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("MyWidget","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MyWidget::tr(const char* s)
{
    return qApp->translate( "MyWidget", s, 0 );
}

QString MyWidget::tr(const char* s, const char * c)
{
    return qApp->translate( "MyWidget", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MyWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"MyWidget", "QWidget",
	0, 0,
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
