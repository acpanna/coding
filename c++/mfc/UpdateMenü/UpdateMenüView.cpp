// UpdateMen�View.cpp : Implementierung der Klasse CUpdateMenView
//

#include "stdafx.h"
#include "UpdateMen�.h"

#include "UpdateMen�Doc.h"
#include "UpdateMen�View.h"

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
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
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
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

CUpdateMenView::~CUpdateMenView()
{
}

BOOL CUpdateMenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Zeichnen

void CUpdateMenView::OnDraw(CDC* pDC)
{
	CUpdateMenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der urspr�nglichen Daten hinzuf�gen
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
	// ZU ERLEDIGEN: Zus�tzliche Initialisierung vor dem Drucken hier einf�gen
}

void CUpdateMenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einf�gen
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

CUpdateMenDoc* CUpdateMenView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUpdateMenDoc)));
	return (CUpdateMenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenView Nachrichten-Handler
