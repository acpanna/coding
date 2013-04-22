// ThreadDoc.cpp : Implementierung der Klasse CThreadDoc
//

#include "stdafx.h"
#include "Thread.h"

#include "ThreadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadDoc

IMPLEMENT_DYNCREATE(CThreadDoc, CDocument)

BEGIN_MESSAGE_MAP(CThreadDoc, CDocument)
	//{{AFX_MSG_MAP(CThreadDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadDoc Konstruktion/Destruktion

CThreadDoc::CThreadDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CThreadDoc::~CThreadDoc()
{
}

BOOL CThreadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CThreadDoc Serialisierung

void CThreadDoc::Serialize(CArchive& ar)
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
// CThreadDoc Diagnose

#ifdef _DEBUG
void CThreadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThreadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThreadDoc Befehle
