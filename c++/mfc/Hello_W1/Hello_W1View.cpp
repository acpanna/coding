// Hello_W1View.cpp : Implementierung der Klasse CHello_W1View
//

#include "stdafx.h"
#include "Hello_W1.h"

#include "Hello_W1Doc.h"
#include "Hello_W1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View

IMPLEMENT_DYNCREATE(CHello_W1View, CView)

BEGIN_MESSAGE_MAP(CHello_W1View, CView)
	//{{AFX_MSG_MAP(CHello_W1View)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View Konstruktion/Destruktion

CHello_W1View::CHello_W1View()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CHello_W1View::~CHello_W1View()
{
}

BOOL CHello_W1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View Zeichnen

void CHello_W1View::OnDraw(CDC* pDC)
{
	CHello_W1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
	pDC->TextOut(30,30,"Hello, World!");
}

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View Drucken

BOOL CHello_W1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CHello_W1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CHello_W1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View Diagnose

#ifdef _DEBUG
void CHello_W1View::AssertValid() const
{
	CView::AssertValid();
}

void CHello_W1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHello_W1Doc* CHello_W1View::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHello_W1Doc)));
	return (CHello_W1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHello_W1View Nachrichten-Handler
