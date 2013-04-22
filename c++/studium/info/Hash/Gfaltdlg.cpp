// GFaltDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "GFaltDlg.h"
#include "Hashfkt.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGFaltDlg 

CGFaltDlg::CGFaltDlg(CWnd* pParent) 
	: CDialog(CGFaltDlg::IDD, pParent)
{
}


void CGFaltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LEN, m_len);
	DDX_Control(pDX, IDC_EDIT_GRFALT, m_grfalt);
}


BEGIN_MESSAGE_MAP(CGFaltDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGFaltDlg 

void CGFaltDlg::OnPaint() 
{
	CPaintDC dc(this);

	char str[10];

	sprintf(str,"%d",p);
	
	m_len.SetWindowText(str);
	m_grfalt.SetFocus();
}

void CGFaltDlg::OnOK() 
{
	char str[3];
	int i;
	
	m_grfalt.GetWindowText(str,3);				 // Einlesen des Parameters fuer Faltung - an - den - Grenzen
	i = atoi(str);

	if (i<1 || i>4)
	{
	 MessageBox("Bitte überprüfen Sie Ihre Eingabe !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
     return;
	}

	CDialog::OnOK();	
    
	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer rechnet!!!");

	grenzfaltung(eingabe.getAnzahl(), i);		 // Aufruf der Faltung - an - den - Grenzen - Funktion

    ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");

}
