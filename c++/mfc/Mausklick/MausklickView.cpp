// MausklickView.cpp : Implementierung der Klasse CMausklickView
//

#include "stdafx.h"
#include "Mausklick.h"

#include "MausklickDoc.h"
#include "MausklickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMausklickView

IMPLEMENT_DYNCREATE(CMausklickView, CView)

BEGIN_MESSAGE_MAP(CMausklickView, CView)
	//{{AFX_MSG_MAP(CMausklickView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMausklickView Konstruktion/Destruktion

CMausklickView::CMausklickView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

CMausklickView::~CMausklickView()
{
}

BOOL CMausklickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMausklickView Zeichnen

void CMausklickView::OnDraw(CDC* pDC)
{
	CMausklickDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der urspr�nglichen Daten hinzuf�gen
    pDC->Ellipse(50,50,70,70);
}

/////////////////////////////////////////////////////////////////////////////
// CMausklickView Diagnose

#ifdef _DEBUG
void CMausklickView::AssertValid() const
{
	CView::AssertValid();
}

void CMausklickView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMausklickDoc* CMausklickView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMausklickDoc)));
	return (CMausklickDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMausklickView Nachrichten-Handler

void CMausklickView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen und/oder Standard aufrufen
	CClientDC dc(this);
	dc.Ellipse(point.x-20,point.y-20,point.x+20,point.y+20);


	CView::OnLButtonDown(nFlags, point);
}
