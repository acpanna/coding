// Men�View.cpp : Implementierung der Klasse CMenView
//

#include "stdafx.h"
#include "Men�.h"

#include "Men�Doc.h"
#include "Men�View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenView

IMPLEMENT_DYNCREATE(CMenView, CView)

BEGIN_MESSAGE_MAP(CMenView, CView)
	//{{AFX_MSG_MAP(CMenView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenView Konstruktion/Destruktion

CMenView::CMenView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

CMenView::~CMenView()
{
}

BOOL CMenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMenView Zeichnen

void CMenView::OnDraw(CDC* pDC)
{
	CMenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der urspr�nglichen Daten hinzuf�gen
}

/////////////////////////////////////////////////////////////////////////////
// CMenView Diagnose

#ifdef _DEBUG
void CMenView::AssertValid() const
{
	CView::AssertValid();
}

void CMenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMenDoc* CMenView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMenDoc)));
	return (CMenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenView Nachrichten-Handler
