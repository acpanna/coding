// MatScEinDoc.cpp : Implementierung der Klasse CMatScEinDoc
//

#include "stdafx.h"
#include "MatScEinDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatScEinDoc

IMPLEMENT_DYNCREATE(CMatScEinDoc, CDocument)

BEGIN_MESSAGE_MAP(CMatScEinDoc, CDocument)
	//{{AFX_MSG_MAP(CMatScEinDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatScEinDoc Konstruktion/Destruktion

CMatScEinDoc::CMatScEinDoc()
{
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen
}

CMatScEinDoc::~CMatScEinDoc()
{
}

BOOL CMatScEinDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einf�gen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMatScEinDoc Serialisierung

void CMatScEinDoc::Serialize(CArchive& ar)
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
// CMatScEinDoc Diagnose

#ifdef _DEBUG
void CMatScEinDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMatScEinDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatScEinDoc Befehle
