// MenüDoc.cpp : Implementierung der Klasse CMenDoc
//

#include "stdafx.h"
#include "Menü.h"

#include "MenüDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenDoc

IMPLEMENT_DYNCREATE(CMenDoc, CDocument)

BEGIN_MESSAGE_MAP(CMenDoc, CDocument)
	//{{AFX_MSG_MAP(CMenDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenDoc Konstruktion/Destruktion

CMenDoc::CMenDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CMenDoc::~CMenDoc()
{
}

BOOL CMenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMenDoc Serialisierung

void CMenDoc::Serialize(CArchive& ar)
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
// CMenDoc Diagnose

#ifdef _DEBUG
void CMenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenDoc Befehle
