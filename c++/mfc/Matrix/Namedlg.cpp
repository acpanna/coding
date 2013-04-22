// NameDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matrix.h"
#include "NameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CNameDlg 


CNameDlg::CNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNameDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNameDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialog)
	//{{AFX_MSG_MAP(CNameDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CNameDlg 


void CNameDlg::OnOK() 
{
	m_Name.GetWindowText(name,255);

	for (int i=0; i<theApp.anzahl ; i++)
		if (!strcmp(name,theApp.matrix[i]->GetName()))
		{
			MessageBox("Es existiert bereits eine Matrix mit diesem Namen !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
            return;
		}

	theApp.anzahl++;

	theApp.matrix = (CMatrix **) realloc(theApp.matrix, sizeof(CMatrix) * theApp.anzahl);
	
    if (theApp.matrix == 0)
	{
		MessageBox("Zu wenig Speicherplatz !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
    CDialog::OnOK();
}

void CNameDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    m_Name.SetFocus();
}
