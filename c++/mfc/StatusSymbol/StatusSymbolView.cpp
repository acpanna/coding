// StatusSymbolView.cpp : Implementierung der Klasse CStatusSymbolView
//

#include "stdafx.h"
#include "StatusSymbol.h"

#include "StatusSymbolDoc.h"
#include "StatusSymbolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolView

IMPLEMENT_DYNCREATE(CStatusSymbolView, CView)

BEGIN_MESSAGE_MAP(CStatusSymbolView, CView)
	//{{AFX_MSG_MAP(CStatusSymbolView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolView Konstruktion/Destruktion

CStatusSymbolView::CStatusSymbolView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CStatusSymbolView::~CStatusSymbolView()
{
}

BOOL CStatusSymbolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolView Zeichnen

void CStatusSymbolView::OnDraw(CDC* pDC)
{
	CStatusSymbolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolView Diagnose

#ifdef _DEBUG
void CStatusSymbolView::AssertValid() const
{
	CView::AssertValid();
}

void CStatusSymbolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatusSymbolDoc* CStatusSymbolView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusSymbolDoc)));
	return (CStatusSymbolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolView Nachrichten-Handler
