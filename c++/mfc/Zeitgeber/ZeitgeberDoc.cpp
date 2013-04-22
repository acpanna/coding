// ZeitgeberDoc.cpp : Implementierung der Klasse CZeitgeberDoc
//

#include "stdafx.h"
#include "Zeitgeber.h"

#include "ZeitgeberDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberDoc

IMPLEMENT_DYNCREATE(CZeitgeberDoc, CDocument)

BEGIN_MESSAGE_MAP(CZeitgeberDoc, CDocument)
	//{{AFX_MSG_MAP(CZeitgeberDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberDoc Konstruktion/Destruktion

CZeitgeberDoc::CZeitgeberDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
    m_nSpots = 0;
}

CZeitgeberDoc::~CZeitgeberDoc()
{
}

BOOL CZeitgeberDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CZeitgeberDoc Serialisierung

void CZeitgeberDoc::Serialize(CArchive& ar)
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
// CZeitgeberDoc Diagnose

#ifdef _DEBUG
void CZeitgeberDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZeitgeberDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberDoc Befehle
