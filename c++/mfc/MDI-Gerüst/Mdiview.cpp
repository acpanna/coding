// MDIView.cpp : Implementierung der Klasse CMDIView
//

#include "stdafx.h"
#include "MDI.h"

#include "MDIDoc.h"
#include "MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIView

IMPLEMENT_DYNCREATE(CMDIView, CView)

BEGIN_MESSAGE_MAP(CMDIView, CView)
	//{{AFX_MSG_MAP(CMDIView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIView Konstruktion/Destruktion

CMDIView::CMDIView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CMDIView::~CMDIView()
{
}

BOOL CMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIView Zeichnen

void CMDIView::OnDraw(CDC* pDC)
{
	CMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CMDIView Diagnose

#ifdef _DEBUG
void CMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIDoc* CMDIView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIDoc)));
	return (CMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIView Nachrichten-Handler
