// StatusSymbolDoc.cpp : Implementierung der Klasse CStatusSymbolDoc
//

#include "stdafx.h"
#include "StatusSymbol.h"

#include "StatusSymbolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolDoc

IMPLEMENT_DYNCREATE(CStatusSymbolDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusSymbolDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusSymbolDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolDoc Konstruktion/Destruktion

CStatusSymbolDoc::CStatusSymbolDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CStatusSymbolDoc::~CStatusSymbolDoc()
{
}

BOOL CStatusSymbolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolDoc Serialisierung

void CStatusSymbolDoc::Serialize(CArchive& ar)
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
// CStatusSymbolDoc Diagnose

#ifdef _DEBUG
void CStatusSymbolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusSymbolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolDoc Befehle
