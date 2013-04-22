// UpdateMenüDoc.cpp : Implementierung der Klasse CUpdateMenDoc
//

#include "stdafx.h"
#include "UpdateMenü.h"

#include "UpdateMenüDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenDoc

IMPLEMENT_DYNCREATE(CUpdateMenDoc, CDocument)

BEGIN_MESSAGE_MAP(CUpdateMenDoc, CDocument)
	//{{AFX_MSG_MAP(CUpdateMenDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenDoc Konstruktion/Destruktion

CUpdateMenDoc::CUpdateMenDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CUpdateMenDoc::~CUpdateMenDoc()
{
}

BOOL CUpdateMenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUpdateMenDoc Serialisierung

void CUpdateMenDoc::Serialize(CArchive& ar)
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
// CUpdateMenDoc Diagnose

#ifdef _DEBUG
void CUpdateMenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUpdateMenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenDoc Befehle
