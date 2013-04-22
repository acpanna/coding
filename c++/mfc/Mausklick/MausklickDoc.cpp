// MausklickDoc.cpp : Implementierung der Klasse CMausklickDoc
//

#include "stdafx.h"
#include "Mausklick.h"

#include "MausklickDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMausklickDoc

IMPLEMENT_DYNCREATE(CMausklickDoc, CDocument)

BEGIN_MESSAGE_MAP(CMausklickDoc, CDocument)
	//{{AFX_MSG_MAP(CMausklickDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMausklickDoc Konstruktion/Destruktion

CMausklickDoc::CMausklickDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CMausklickDoc::~CMausklickDoc()
{
}

BOOL CMausklickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMausklickDoc Serialisierung

void CMausklickDoc::Serialize(CArchive& ar)
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
// CMausklickDoc Diagnose

#ifdef _DEBUG
void CMausklickDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMausklickDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMausklickDoc Befehle
