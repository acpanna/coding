// MDIDoc.cpp : Implementierung der Klasse CMDIDoc
//

#include "stdafx.h"
#include "MDI.h"

#include "MDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIDoc

IMPLEMENT_DYNCREATE(CMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDIDoc, CDocument)
	//{{AFX_MSG_MAP(CMDIDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIDoc Konstruktion/Destruktion

CMDIDoc::CMDIDoc()
{
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen

}

CMDIDoc::~CMDIDoc()
{
}

BOOL CMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einf�gen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDIDoc Serialisierung

void CMDIDoc::Serialize(CArchive& ar)
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
// CMDIDoc Diagnose

#ifdef _DEBUG
void CMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIDoc Befehle
