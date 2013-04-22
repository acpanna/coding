// MitteDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "MitteDlg.h"
#include "Hashfkt.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMitteDlg 

CMitteDlg::CMitteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMitteDlg::IDD, pParent)
{
}


void CMitteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_MITTE, m_Mitte);
}


BEGIN_MESSAGE_MAP(CMitteDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMitteDlg 

void CMitteDlg::OnOK() 
{
	char str[3];
	int i;
	
	m_Mitte.GetWindowText(str,3);				 // Einlesen der herauszugreifenden Stellen
	i = atoi(str);
	
	if (i<1 || i>3)
	{
	 MessageBox("Bitte überprüfen Sie Ihre Eingabe !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
     return;
	}
    
	CDialog::OnOK();

	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer rechnet!!!");

	quadrat(eingabe.getAnzahl(), i);			 // Aufruf der Mitte - des - Quadrats - Funktion

	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");
}

void CMitteDlg::OnPaint() 
{
	CPaintDC dc(this);                         
     
	m_Mitte.SetFocus();
}

