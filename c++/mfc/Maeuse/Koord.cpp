#include "stdafx.h"
#include "Koord.h"

IMPLEMENT_SERIAL(CKoord, CObject, 1)

CKoord::CKoord()
{
	x=1;
	y=1;
}
CKoord::CKoord(int x_koord, int y_koord)
{
	x=x_koord;
	y=y_koord;
}
void CKoord::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << x << y;
	}
	else
	{
		ar >> x >> y;
	}
}