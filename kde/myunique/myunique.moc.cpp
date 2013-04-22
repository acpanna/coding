/****************************************************************************
** MyUnique meta object code from reading C++ file 'myunique.h'
**
** Created: Wed Aug 1 13:44:19 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.1.1   edited 2000-03-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MyUnique
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 7
#elif Q_MOC_OUTPUT_REVISION != 7
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "myunique.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MyUnique::className() const
{
    return "MyUnique";
}

QMetaObject *MyUnique::metaObj = 0;

void MyUnique::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(KUniqueApplication::className(), "KUniqueApplication") != 0 )
	badSuperclassWarning("MyUnique","KUniqueApplication");
    (void) staticMetaObject();
}

QString MyUnique::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MyUnique",s);
}

QMetaObject* MyUnique::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KUniqueApplication::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"MyUnique", "KUniqueApplication",
	0, 0,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
