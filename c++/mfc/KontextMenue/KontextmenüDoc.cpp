// Kontextmen�Doc.cpp : Implementierung der Klasse CKontextmenDoc
//

#include "stdafx.h"
#include "Kontextmen�.h"

#include "Kontextmen�Doc.h"

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
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc Konstruktion/Destruktion

CKontextmenDoc::CKontextmenDoc()
{
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen

}

CKontextmenDoc::~CKontextmenDoc()
{
}

BOOL CKontextmenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einf�gen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKontextmenDoc Serialisierung

void CKontextmenDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einf�gen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einf�gen
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
