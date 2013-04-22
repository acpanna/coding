// FensteranpassungDoc.cpp : Implementierung der Klasse CFensteranpassungDoc
//

#include "stdafx.h"
#include "Fensteranpassung.h"

#include "FensteranpassungDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungDoc

IMPLEMENT_DYNCREATE(CFensteranpassungDoc, CDocument)

BEGIN_MESSAGE_MAP(CFensteranpassungDoc, CDocument)
	//{{AFX_MSG_MAP(CFensteranpassungDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungDoc Konstruktion/Destruktion

CFensteranpassungDoc::CFensteranpassungDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CFensteranpassungDoc::~CFensteranpassungDoc()
{
}

BOOL CFensteranpassungDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungDoc Serialisierung

void CFensteranpassungDoc::Serialize(CArchive& ar)
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
// CFensteranpassungDoc Diagnose

#ifdef _DEBUG
void CFensteranpassungDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFensteranpassungDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungDoc Befehle
