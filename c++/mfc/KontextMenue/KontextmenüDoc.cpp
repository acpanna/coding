// KontextmenüDoc.cpp : Implementierung der Klasse CKontextmenDoc
//

#include "stdafx.h"
#include "Kontextmenü.h"

#include "KontextmenüDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc

IMPLEMENT_DYNCREATE(CKontextmenDoc, CDocument)

BEGIN_MESSAGE_MAP(CKontextmenDoc, CDocument)
	//{{AFX_MSG_MAP(CKontextmenDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc Konstruktion/Destruktion

CKontextmenDoc::CKontextmenDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CKontextmenDoc::~CKontextmenDoc()
{
}

BOOL CKontextmenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc Serialisierung

void CKontextmenDoc::Serialize(CArchive& ar)
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
// CKontextmenDoc Diagnose

#ifdef _DEBUG
void CKontextmenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKontextmenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc Befehle
