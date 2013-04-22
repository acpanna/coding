// MaueseDoc.cpp : Implementierung der Klasse CMaueseDoc
//

#include "stdafx.h"
#include "Mauese.h"
#include "Koord.h"
#include "MaueseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaueseDoc

IMPLEMENT_DYNCREATE(CMaueseDoc, CDocument)

BEGIN_MESSAGE_MAP(CMaueseDoc, CDocument)
	//{{AFX_MSG_MAP(CMaueseDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaueseDoc Konstruktion/Destruktion

CMaueseDoc::CMaueseDoc()
{
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen
    m_Maeuse.Add(new CKoord(20,20));
	m_Maeuse.Add(new CKoord(70,150));
	m_Maeuse.Add(new CKoord(300,100));
	m_Maeuse.Add(new CKoord(200,200));
	m_Maeuse.Add(new CKoord(400,30));
	
}

CMaueseDoc::~CMaueseDoc()
{
}

BOOL CMaueseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einf�gen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMaueseDoc Serialisierung

void CMaueseDoc::Serialize(CArchive& ar)
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
// CMaueseDoc Diagnose

#ifdef _DEBUG
void CMaueseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMaueseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaueseDoc Befehle
