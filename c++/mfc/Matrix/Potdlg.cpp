// PotDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matrix.h"
#include "PotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPotDlg 


CPotDlg::CPotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPotDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPotDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CPotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPotDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Potenz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPotDlg, CDialog)
	//{{AFX_MSG_MAP(CPotDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPotDlg 

void CPotDlg::OnOK() 
{
	char str[256];

	m_Potenz.GetWindowText(str, 255);

	if (atoi(str) < 1)
		return;

	theApp.matrix[theApp.anzahl - 1] = (*matrix1)^atoi(str);
	
	CDialog::OnOK();
}

void CPotDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	m_Potenz.SetFocus();
}
