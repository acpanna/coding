// FraktaleView.cpp : Implementierung der Klasse CFraktaleView
//

#include "stdafx.h"
#include "Fraktale.h"

#include "FraktaleDoc.h"
#include "FraktaleView.h"
#include <complex>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFraktaleView

IMPLEMENT_DYNCREATE(CFraktaleView, CView)

BEGIN_MESSAGE_MAP(CFraktaleView, CView)
	//{{AFX_MSG_MAP(CFraktaleView)
	ON_COMMAND(ID_FRAKTAL, OnFraktal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFraktaleView Konstruktion/Destruktion

CFraktaleView::CFraktaleView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CFraktaleView::~CFraktaleView()
{
}

BOOL CFraktaleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFraktaleView Zeichnen

void CFraktaleView::OnDraw(CDC* pDC)
{
	CFraktaleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CFraktaleView Diagnose

#ifdef _DEBUG
void CFraktaleView::AssertValid() const
{
	CView::AssertValid();
}

void CFraktaleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFraktaleDoc* CFraktaleView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFraktaleDoc)));
	return (CFraktaleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFraktaleView Nachrichten-Handler

void CFraktaleView::OnFraktal() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CClientDC dc(this);
	RECT rect;
	GetClientRect(&rect);

	complex<double> c(-0.012, 0.74);
	for(int i=rect.left; i<rect.right; i++)
		for(int j=rect.top; j<rect.bottom; j++)
		{
			complex<double> x(0.0001*i, 0.0001*j);
			for (int n=0; n<100;n++)
			{
				if(abs(x)>100)
					break;
				x=pow(x,2)+c;
			}
			if(abs(x)<1)
				dc.SetPixel(i,j,RGB(0,0,0));
			else
				dc.SetPixel(i,j,RGB(2*abs(x),abs(x),abs(x)/2));
		}
}


