// MatScEinView.cpp : Implementierung der Klasse CMatScEinView
//

#include "stdafx.h"
#include "MatScEinDoc.h"
#include "MatScEinView.h"
#include "EingDlg.h"
#include "Matrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEdit *pEdit = 0;
CStatic *pStatic = 0;

/////////////////////////////////////////////////////////////////////////////
// CMatScEinView

IMPLEMENT_DYNCREATE(CMatScEinView, CScrollView)

BEGIN_MESSAGE_MAP(CMatScEinView, CScrollView)
	//{{AFX_MSG_MAP(CMatScEinView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatScEinView Konstruktion/Destruktion

CMatScEinView::CMatScEinView()
{
	if (check == 1)
	{
		pEdit = new CEdit[(theApp.matrix[theApp.anzahl - 1]->GetZeilen()) * (theApp.matrix[theApp.anzahl - 1]->GetSpalten())];
		
		if (pEdit == NULL)
		{
			MessageBox("Zu wenig Speicher für Editfelder !","Programmabbruch...",MB_OK|MB_ICONEXCLAMATION);
			exit(1);
		}
	}
			
	else
	{
		pStatic = new CStatic[(matrix1->GetZeilen()) * (matrix1->GetSpalten())];
    
		if (pStatic == NULL)
		{
			MessageBox("Zu wenig Speicher für Textfelder !","Programmabbruch...",MB_OK|MB_ICONEXCLAMATION);
            exit(1);
		}
	}

	chk = 0;
}

CMatScEinView::~CMatScEinView()
{
	if (check == 1)
	{
		for (int i=0; i<((theApp.matrix[theApp.anzahl - 1]->GetZeilen()) * (theApp.matrix[theApp.anzahl - 1]->GetSpalten()));i++)
			pEdit[i].DestroyWindow();
	    	
		delete [] pEdit;
		pEdit = 0;
	}
	else
	{
		for (int i=0; i<((matrix1->GetZeilen()) * (matrix1->GetSpalten()));i++)
		    pStatic[i].DestroyWindow();
		
		delete [] pStatic;
		pStatic = 0;
	}

	matrix1 = 0;
}

BOOL CMatScEinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMatScEinView Zeichnen

void CMatScEinView::OnDraw(CDC* pDC)
{
	int i, j;

	CMatScEinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (chk == 1)
		return;

    if (check == 1)
	{
		pDoc->SetTitle("  - Eingabe der Matrizen");
		for (i=0; i<theApp.matrix[theApp.anzahl - 1]->GetZeilen(); i++)
			for (j=0; j<theApp.matrix[theApp.anzahl - 1]->GetSpalten(); j++)
				pEdit[i * (theApp.matrix[theApp.anzahl - 1]->GetSpalten()) + j].Create(WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL, CRect(10+40*j,10+20*i,50+40*j,30+20*i), this, 0);
	}

	else
	{
		char str[10];

		pDoc->SetTitle("  - Ausgabe der Matrizen");
		for (i=0; i<matrix1->GetZeilen(); i++)
			for (j=0; j<matrix1->GetSpalten(); j++)
			{
				sprintf(str,"%4lg",matrix1->GetEintrag(i, j));
		        pStatic[i * matrix1->GetSpalten() + j].Create(str, WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL, CRect(10+40*j,10+20*i,50+40*j,30+20*i), this, 0);
			}
	}

	chk = 1;
}

void CMatScEinView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;
	
	if (check == 1)
	{
		sizeTotal.cx = theApp.matrix[theApp.anzahl - 1]->GetSpalten() * 45;
	    sizeTotal.cy = theApp.matrix[theApp.anzahl - 1]->GetZeilen() * 25;
	}

	else
	{
		sizeTotal.cx = matrix1->GetSpalten() * 45;
	    sizeTotal.cy = matrix1->GetZeilen() * 25;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMatScEinView Diagnose

#ifdef _DEBUG
void CMatScEinView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMatScEinView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMatScEinDoc* CMatScEinView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatScEinDoc)));
	return (CMatScEinDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatScEinView Nachrichten-Handler
