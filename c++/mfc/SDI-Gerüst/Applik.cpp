#include "applik.h"

CMyApp Anwendung;

CAnsicht::CAnsicht(CFrameWnd *parent)
{
	Create(0,"Check",WS_CHILD | WS_VISIBLE , CRect(100,100,200,200), parent,0);
}

CAnsicht::~CAnsicht()
{
}

void CAnsicht::OnDraw(class CDC *dc)
{
	RECT rect;
	TEXTMETRIC tm;
	GetClientRect(&rect);
	dc->GetTextMetrics(&tm);
	dc->TextOut(10,(rect.bottom-tm.tmHeight)/2,"Dies ist die Ansichtsklasse !");
  
}

CRahmenfenster::CRahmenfenster()
{
	Create(0,"Rahmen mit View", WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL, rectDefault);
    new CAnsicht(this);
}	

BOOL CMyApp::InitInstance()
{
	CRahmenfenster *pMainWnd = new CRahmenfenster;

	m_pMainWnd = pMainWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CRahmenfenster::~CRahmenfenster()
{
}
