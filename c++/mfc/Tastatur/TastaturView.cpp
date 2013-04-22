// TastaturView.cpp : Implementierung der Klasse CTastaturView
//

#include "stdafx.h"
#include "Tastatur.h"

#include "TastaturDoc.h"
#include "TastaturView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTastaturView

IMPLEMENT_DYNCREATE(CTastaturView, CView)

BEGIN_MESSAGE_MAP(CTastaturView, CView)
	//{{AFX_MSG_MAP(CTastaturView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTastaturView Konstruktion/Destruktion

CTastaturView::CTastaturView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CTastaturView::~CTastaturView()
{
}

BOOL CTastaturView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTastaturView Zeichnen

void CTastaturView::OnDraw(CDC* pDC)
{
	CTastaturDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CTastaturView Diagnose

#ifdef _DEBUG
void CTastaturView::AssertValid() const
{
	CView::AssertValid();
}

void CTastaturView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTastaturDoc* CTastaturView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTastaturDoc)));
	return (CTastaturDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTastaturView Nachrichten-Handler

void CTastaturView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (nChar == 'M')
		MessageBox("DieTaste 'm' wurde gedrückt","Tastaturereignis",MB_OK|MB_ICONINFORMATION);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
