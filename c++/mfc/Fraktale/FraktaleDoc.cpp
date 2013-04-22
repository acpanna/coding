// FraktaleDoc.cpp : Implementierung der Klasse CFraktaleDoc
//

#include "stdafx.h"
#include "Fraktale.h"

#include "FraktaleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFraktaleDoc

IMPLEMENT_DYNCREATE(CFraktaleDoc, CDocument)

BEGIN_MESSAGE_MAP(CFraktaleDoc, CDocument)
	//{{AFX_MSG_MAP(CFraktaleDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFraktaleDoc Konstruktion/Destruktion

CFraktaleDoc::CFraktaleDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CFraktaleDoc::~CFraktaleDoc()
{
}

BOOL CFraktaleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFraktaleDoc Serialisierung

void CFraktaleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFraktaleDoc Diagnose

#ifdef _DEBUG
void CFraktaleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFraktaleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFraktaleDoc Befehle
