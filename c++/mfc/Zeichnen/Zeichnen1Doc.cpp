// Zeichnen1Doc.cpp : Implementierung der Klasse CZeichnen1Doc
//

#include "stdafx.h"
#include "Zeichnen1.h"

#include "Zeichnen1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1Doc

IMPLEMENT_DYNCREATE(CZeichnen1Doc, CDocument)

BEGIN_MESSAGE_MAP(CZeichnen1Doc, CDocument)
	//{{AFX_MSG_MAP(CZeichnen1Doc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1Doc Konstruktion/Destruktion

CZeichnen1Doc::CZeichnen1Doc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CZeichnen1Doc::~CZeichnen1Doc()
{
}

BOOL CZeichnen1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CZeichnen1Doc Serialisierung

void CZeichnen1Doc::Serialize(CArchive& ar)
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
// CZeichnen1Doc Diagnose

#ifdef _DEBUG
void CZeichnen1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZeichnen1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1Doc Befehle
