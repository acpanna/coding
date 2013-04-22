// FensteranpassungView.cpp : Implementierung der Klasse CFensteranpassungView
//

#include "stdafx.h"
#include "Fensteranpassung.h"

#include "FensteranpassungDoc.h"
#include "FensteranpassungView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungView

IMPLEMENT_DYNCREATE(CFensteranpassungView, CView)

BEGIN_MESSAGE_MAP(CFensteranpassungView, CView)
	//{{AFX_MSG_MAP(CFensteranpassungView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungView Konstruktion/Destruktion

CFensteranpassungView::CFensteranpassungView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CFensteranpassungView::~CFensteranpassungView()
{
}

BOOL CFensteranpassungView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungView Zeichnen

void CFensteranpassungView::OnDraw(CDC* pDC)
{
	CFensteranpassungDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungView Diagnose

#ifdef _DEBUG
void CFensteranpassungView::AssertValid() const
{
	CView::AssertValid();
}

void CFensteranpassungView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFensteranpassungDoc* CFensteranpassungView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFensteranpassungDoc)));
	return (CFensteranpassungDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFensteranpassungView Nachrichten-Handler
