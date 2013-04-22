// MaueseView.cpp : Implementierung der Klasse CMaueseView
//

#include "stdafx.h"
#include "Mauese.h"
#include "Koord.h"
#include "MaueseDoc.h"
#include "MaueseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaueseView

IMPLEMENT_DYNCREATE(CMaueseView, CView)

BEGIN_MESSAGE_MAP(CMaueseView, CView)
	//{{AFX_MSG_MAP(CMaueseView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaueseView Konstruktion/Destruktion

CMaueseView::CMaueseView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
    m_Geschwindigkeit = 0.1;  
}

CMaueseView::~CMaueseView()
{
}

BOOL CMaueseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMaueseView Zeichnen

void CMaueseView::OnDraw(CDC* pDC)
{
	CMaueseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
    CObArray maeuse;
	CKoord *pAktMaus, *pNextMaus;
	int loop2;

	for (int loop=0; loop<pDoc->m_Maeuse.GetSize(); loop++)
	{
		CKoord *pKoord = new CKoord;
		pKoord->x = ((CKoord *) pDoc->m_Maeuse[loop])->x;
        pKoord->y = ((CKoord *) pDoc->m_Maeuse[loop])->y;
		maeuse.Add(pKoord);
		pDC->Ellipse(pKoord->x - 10, pKoord->y - 10, pKoord->x + 10, pKoord->y + 10);
	}
	for (int loop1=1; loop1<= 30; loop1++)
	{
		for(loop2=0; loop2<maeuse.GetSize();loop2++)
		{
			pAktMaus = (CKoord *) maeuse[loop2];
			pDC->MoveTo(pAktMaus->x,pAktMaus->y);
			pNextMaus = (CKoord *) maeuse[(loop2+1)%(maeuse.GetSize())];
			pDC->LineTo(pNextMaus->x,pNextMaus->y);
		}

		for (loop2=0; loop2<maeuse.GetSize()-1; loop2++)
		{
			pAktMaus = (CKoord*) maeuse[loop2];
			pNextMaus=(CKoord *) maeuse[loop2 +1];
			pAktMaus->x += (pNextMaus->x-pAktMaus->x)*m_Geschwindigkeit;
	        pAktMaus->y += (pNextMaus->y-pAktMaus->y)*m_Geschwindigkeit;
		}
		pAktMaus = (CKoord *) maeuse[maeuse.GetSize()-1];
		pNextMaus=(CKoord *) maeuse[0];
		pAktMaus->x += (pNextMaus->x-pAktMaus->x)*m_Geschwindigkeit;
        pAktMaus->y += (pNextMaus->y-pAktMaus->y)*m_Geschwindigkeit;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMaueseView Diagnose

#ifdef _DEBUG
void CMaueseView::AssertValid() const
{
	CView::AssertValid();
}

void CMaueseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMaueseDoc* CMaueseView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaueseDoc)));
	return (CMaueseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaueseView Nachrichten-Handler
