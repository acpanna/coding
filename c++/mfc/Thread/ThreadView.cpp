// ThreadView.cpp : Implementierung der Klasse CThreadView
//

#include "stdafx.h"
#include "Thread.h"
#include "ThreadFkt.h"
#include "ThreadDoc.h"
#include "ThreadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadView

IMPLEMENT_DYNCREATE(CThreadView, CView)

BEGIN_MESSAGE_MAP(CThreadView, CView)
	//{{AFX_MSG_MAP(CThreadView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadView Konstruktion/Destruktion

CThreadView::CThreadView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
    m_myThread = NULL;
}

CThreadView::~CThreadView()
{
	if (m_myThread)
		delete m_myThread;
}

BOOL CThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThreadView Zeichnen

void CThreadView::OnDraw(CDC* pDC)
{
	CThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CThreadView Diagnose

#ifdef _DEBUG
void CThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThreadDoc* CThreadView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadDoc)));
	return (CThreadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThreadView Nachrichten-Handler

void CThreadView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
    DWORD exitcode;
	if(m_myThread)
	{
		g_Exit.SetEvent();
		do GetExitCodeThread(m_myThread->m_hThread, &exitcode);
		while (exitcode == STILL_ACTIVE);
		
		if (exitcode == 0)
			g_Exit.ResetEvent();
		
		Invalidate();
		UpdateWindow();
		
		delete(m_myThread);
		m_myThread = NULL;
	}

	m_myThread = AfxBeginThread(JuliaMenge, this, THREAD_PRIORITY_NORMAL);
	m_myThread->m_bAutoDelete = false;

	CView::OnLButtonDown(nFlags, point);
}

