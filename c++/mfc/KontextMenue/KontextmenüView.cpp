// Kontextmen�View.cpp : Implementierung der Klasse CKontextmenView
//

#include "stdafx.h"
#include "Kontextmen�.h"

#include "Kontextmen�Doc.h"
#include "Kontextmen�View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKontextmenView

IMPLEMENT_DYNCREATE(CKontextmenView, CView)

BEGIN_MESSAGE_MAP(CKontextmenView, CView)
	//{{AFX_MSG_MAP(CKontextmenView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKontextmenView Konstruktion/Destruktion

CKontextmenView::CKontextmenView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

CKontextmenView::~CKontextmenView()
{
}

BOOL CKontextmenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKontextmenView Zeichnen

void CKontextmenView::OnDraw(CDC* pDC)
{
	CKontextmenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der urspr�nglichen Daten hinzuf�gen
}

/////////////////////////////////////////////////////////////////////////////
// CKontextmenView Diagnose

#ifdef _DEBUG
void CKontextmenView::AssertValid() const
{
	CView::AssertValid();
}

void CKontextmenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKontextmenDoc* CKontextmenView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKontextmenDoc)));
	return (CKontextmenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKontextmenView Nachrichten-Handler

void CKontextmenView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

}
