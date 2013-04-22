// Hello_W3Doc.cpp : Implementierung der Klasse CHello_W3Doc
//

#include "stdafx.h"
#include "Hello_W3.h"

#include "Hello_W3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHello_W3Doc

IMPLEMENT_DYNCREATE(CHello_W3Doc, CDocument)

BEGIN_MESSAGE_MAP(CHello_W3Doc, CDocument)
	//{{AFX_MSG_MAP(CHello_W3Doc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHello_W3Doc Konstruktion/Destruktion

CHello_W3Doc::CHello_W3Doc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CHello_W3Doc::~CHello_W3Doc()
{
}

BOOL CHello_W3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)
    m_sDaten.LoadString(IDS_HELLO);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHello_W3Doc Serialisierung

void CHello_W3Doc::Serialize(CArchive& ar)
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
// CHello_W3Doc Diagnose

#ifdef _DEBUG
void CHello_W3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHello_W3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHello_W3Doc Befehle
