// Zeichnen1View.cpp : Implementierung der Klasse CZeichnen1View
//

#include "stdafx.h"
#include "Zeichnen1.h"

#include "Zeichnen1Doc.h"
#include "Zeichnen1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1View

IMPLEMENT_DYNCREATE(CZeichnen1View, CView)

BEGIN_MESSAGE_MAP(CZeichnen1View, CView)
	//{{AFX_MSG_MAP(CZeichnen1View)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1View Konstruktion/Destruktion

CZeichnen1View::CZeichnen1View()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CZeichnen1View::~CZeichnen1View()
{
}

BOOL CZeichnen1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1View Zeichnen

void CZeichnen1View::OnDraw(CDC* pDC)
{
	CZeichnen1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
    pDC->Ellipse(50,50,70,70);
}

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1View Diagnose

#ifdef _DEBUG
void CZeichnen1View::AssertValid() const
{
	CView::AssertValid();
}

void CZeichnen1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZeichnen1Doc* CZeichnen1View::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZeichnen1Doc)));
	return (CZeichnen1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1View Nachrichten-Handler
