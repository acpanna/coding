// SkMultDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matrix.h"
#include "SkMultDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSkMultDlg 


CSkMultDlg::CSkMultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkMultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkMultDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CSkMultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkMultDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Skalar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkMultDlg, CDialog)
	//{{AFX_MSG_MAP(CSkMultDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSkMultDlg 

void CSkMultDlg::OnOK() 
{
	char str[256];

	m_Skalar.GetWindowText(str, 255);
	theApp.matrix[theApp.anzahl - 1] = (*matrix1) * atof(str);

	CDialog::OnOK();
}

void CSkMultDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	m_Skalar.SetFocus();
}
