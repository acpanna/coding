// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "MainFrm.h"
#include "Matrix.h"
#include "EingDlg.h"
#include "MatScEinView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool active = 0;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
	active = 1;
}

CMainFrame::~CMainFrame()
{
	active = 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler

void CMainFrame::OnOk() 
{
	char str[10];
		
	if (check == 1)
	{
		for (int i=0; i<theApp.matrix[theApp.anzahl - 1]->GetZeilen(); i++)
			for (int j=0; j<theApp.matrix[theApp.anzahl - 1]->GetSpalten(); j++)
			{
				pEdit[i * (theApp.matrix[theApp.anzahl - 1]->GetSpalten()) + j].GetWindowText(str,10);
			    theApp.matrix[theApp.anzahl - 1]->SetEintrag(i, j, atof(str));
			}
	}

    theApp.m_pDocManager->CloseAllDocuments(1);
}
