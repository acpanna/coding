// Tarif.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "InternetCash.h"
#include "InternetCashDlg.h"
#include "Tarif.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTarif 


CTarif::CTarif(CWnd* pParent /*=NULL*/)
	: CDialog(CTarif::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTarif)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CTarif::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTarif)
	DDX_Control(pDX, IDC_EDIT2, m_Minute);
	DDX_Control(pDX, IDC_EDIT1, m_Einwahl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTarif, CDialog)
	//{{AFX_MSG_MAP(CTarif)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CTarif 

void CTarif::OnPaint() 
{
	char str[10];

	CPaintDC dc(this); // device context for painting
	
    sprintf(str,"%4lg",einwahl);
	
	m_Einwahl.SetWindowText(str);

    sprintf(str,"%4lg",minute);
	
	m_Minute.SetWindowText(str);
}

void CTarif::OnOK() 
{
	char str[10], str2[10];

	ofstream fout("C:\\progra~1\\aol\\tar.dat");

	m_Einwahl.GetWindowText(str,10);
    m_Minute.GetWindowText(str2,10);
	
	einwahl = atof(str);
	minute = atof(str2);
	
	fout << einwahl;
	fout << " ";
	fout << minute;

	fout.close();
	
	CDialog::OnOK();
}
