// UpdateMenüView.cpp : Implementierung der Klasse CUpdateMenView
//

#include "stdafx.h"
#include "UpdateMenü.h"

#include "UpdateMenüDoc.h"
#include "UpdateMenüView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView

IMPLEMENT_DYNCREATE(CUpdateMenView, CView)

BEGIN_MESSAGE_MAP(CUpdateMenView, CView)
	//{{AFX_MSG_MAP(CUpdateMenView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Konstruktion/Destruktion

CUpdateMenView::CUpdateMenView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CUpdateMenView::~CUpdateMenView()
{
}

BOOL CUpdateMenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Zeichnen

void CUpdateMenView::OnDraw(CDC* pDC)
{
	CUpdateMenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Drucken

BOOL CUpdateMenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CUpdateMenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CUpdateMenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Diagnose

#ifdef _DEBUG
void CUpdateMenView::AssertValid() const
{
	CView::AssertValid();
}

void CUpdateMenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUpdateMenDoc* CUpdateMenView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUpdateMenDoc)));
	return (CUpdateMenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Nachrichten-Handler
