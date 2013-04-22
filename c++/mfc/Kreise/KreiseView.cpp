// KreiseView.cpp : Implementierung der Klasse CKreiseView
//

#include "stdafx.h"
#include "Kreise.h"

#include "KreiseDoc.h"
#include "KreiseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKreiseView

IMPLEMENT_DYNCREATE(CKreiseView, CView)

BEGIN_MESSAGE_MAP(CKreiseView, CView)
	//{{AFX_MSG_MAP(CKreiseView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKreiseView Konstruktion/Destruktion

CKreiseView::CKreiseView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CKreiseView::~CKreiseView()
{
}

BOOL CKreiseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKreiseView Zeichnen

void CKreiseView::OnDraw(CDC* pDC)
{
	CKreiseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
    for (int i=0; i<pDoc->m_nZaehler; i++)
	{
		int b = (int) (100.0 * rand() / RAND_MAX);
		pDC->Ellipse(pDoc->m_Kreise[i].x-b,pDoc->m_Kreise[i].y-b,
			pDoc->m_Kreise[i].x+b,pDoc->m_Kreise[i].y+b);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CKreiseView Diagnose

#ifdef _DEBUG
void CKreiseView::AssertValid() const
{
	CView::AssertValid();
}

void CKreiseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKreiseDoc* CKreiseView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKreiseDoc)));
	return (CKreiseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKreiseView Nachrichten-Handler

void CKreiseView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
    Invalidate();
	UpdateWindow();

	CKreiseDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CClientDC dc(this);
	int b=(int) (100.0 * rand() / RAND_MAX);
	dc.Ellipse(point.x-b,point.y-b,point.x+b,point.y+b);
    
	if (pDoc->m_nZaehler < 100)
		pDoc->m_nZaehler++;
	pDoc->m_Kreise[pDoc->m_nZaehler - 1] = point;


	CView::OnLButtonDown(nFlags, point);
}
