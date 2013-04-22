// KreiseDoc.cpp : Implementierung der Klasse CKreiseDoc
//

#include "stdafx.h"
#include "Kreise.h"

#include "KreiseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKreiseDoc

IMPLEMENT_DYNCREATE(CKreiseDoc, CDocument)

BEGIN_MESSAGE_MAP(CKreiseDoc, CDocument)
	//{{AFX_MSG_MAP(CKreiseDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKreiseDoc Konstruktion/Destruktion

CKreiseDoc::CKreiseDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
    m_nZaehler = 0;
}

CKreiseDoc::~CKreiseDoc()
{
}

BOOL CKreiseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKreiseDoc Serialisierung

void CKreiseDoc::Serialize(CArchive& ar)
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
// CKreiseDoc Diagnose

#ifdef _DEBUG
void CKreiseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKreiseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKreiseDoc Befehle
