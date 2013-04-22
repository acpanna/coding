// TastaturDoc.cpp : Implementierung der Klasse CTastaturDoc
//

#include "stdafx.h"
#include "Tastatur.h"

#include "TastaturDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTastaturDoc

IMPLEMENT_DYNCREATE(CTastaturDoc, CDocument)

BEGIN_MESSAGE_MAP(CTastaturDoc, CDocument)
	//{{AFX_MSG_MAP(CTastaturDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTastaturDoc Konstruktion/Destruktion

CTastaturDoc::CTastaturDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CTastaturDoc::~CTastaturDoc()
{
}

BOOL CTastaturDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTastaturDoc Serialisierung

void CTastaturDoc::Serialize(CArchive& ar)
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
// CTastaturDoc Diagnose

#ifdef _DEBUG
void CTastaturDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTastaturDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTastaturDoc Befehle
