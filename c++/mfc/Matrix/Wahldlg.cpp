// WahlDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matrix.h"
#include "WahlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CWahlDlg 


CWahlDlg::CWahlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWahlDlg::IDD, pParent)
{
	checker = 0;
	
	//{{AFX_DATA_INIT(CWahlDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CWahlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWahlDlg)
	DDX_Control(pDX, IDC_LIST_MATRIX, m_Liste);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWahlDlg, CDialog)
	//{{AFX_MSG_MAP(CWahlDlg)
	ON_LBN_DBLCLK(IDC_LIST_MATRIX, OnDblclkListMatrix)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CWahlDlg 

void CWahlDlg::OnOK() 
{
	int i;
	char str[256];

	i = m_Liste.GetCurSel();

	if (i == LB_ERR)
		return;

    m_Liste.GetText(i, str);

    for (i=0; i<theApp.anzahl; i++)
		if(!strcmp(str,theApp.matrix[i]->GetName()))
			break;

	matrix1 = theApp.matrix[i];

	CDialog::OnOK();
}

void CWahlDlg::OnDblclkListMatrix() 
{
    OnOK();
}

void CWahlDlg::OnPaint() 
{
	CPaintDC dc(this);

    if (checker == 1)
		return;
	
	for (int i=0; i<theApp.anzahl; i++)
		m_Liste.AddString(theApp.matrix[i]->GetName());

	checker = 1;
}
