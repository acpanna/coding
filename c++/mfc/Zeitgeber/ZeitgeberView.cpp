// ZeitgeberView.cpp : Implementierung der Klasse CZeitgeberView
//

#include "stdafx.h"
#include "Zeitgeber.h"

#include "ZeitgeberDoc.h"
#include "ZeitgeberView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberView

IMPLEMENT_DYNCREATE(CZeitgeberView, CView)

BEGIN_MESSAGE_MAP(CZeitgeberView, CView)
	//{{AFX_MSG_MAP(CZeitgeberView)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberView Konstruktion/Destruktion

CZeitgeberView::CZeitgeberView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CZeitgeberView::~CZeitgeberView()
{
}

BOOL CZeitgeberView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberView Zeichnen

void CZeitgeberView::OnDraw(CDC* pDC)
{
	CZeitgeberDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
    CBrush *pBrush = pDC->SelectObject(new CBrush(0x000000FF));
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	for(int i=0; i<pDoc->m_nSpots; i++)
		pDC->Ellipse(width/2-10, 10+i*height/20, width/2 + 10, 10+i*height/20+10);
	pDC->SelectObject(pBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberView Diagnose

#ifdef _DEBUG
void CZeitgeberView::AssertValid() const
{
	CView::AssertValid();
}

void CZeitgeberView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZeitgeberDoc* CZeitgeberView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZeitgeberDoc)));
	return (CZeitgeberDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberView Nachrichten-Handler

void CZeitgeberView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CZeitgeberDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetTimer(1,50,NULL);
	pDoc->m_nSpots = 0;
	Invalidate();
	UpdateWindow();

	srand((unsigned) time (NULL));
	int wait = (rand() % 7 + 3) * CLOCKS_PER_SEC;
	time_t start = clock();
	while (clock() < start + wait);
	Beep(1000, 100);

	CView::OnRButtonDown(nFlags, point);
}

void CZeitgeberView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
    KillTimer(1);
		
	CView::OnLButtonDown(nFlags, point);
}

void CZeitgeberView::OnTimer(UINT nIDEvent) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CZeitgeberDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_nSpots++;
	Invalidate();
	UpdateWindow();

	CView::OnTimer(nIDEvent);
}
