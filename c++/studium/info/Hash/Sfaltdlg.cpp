// SFaltDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "SFaltDlg.h"
#include "Hashfkt.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSFaltDlg 

CSFaltDlg::CSFaltDlg(CWnd* pParent)
	: CDialog(CSFaltDlg::IDD, pParent)
{
}

void CSFaltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LEN, m_len);
	DDX_Control(pDX, IDC_EDIT_SCHFALT, m_sfalt);
}


BEGIN_MESSAGE_MAP(CSFaltDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSFaltDlg 


void CSFaltDlg::OnOK() 
{
	char str[3];
	int i;
	
	m_sfalt.GetWindowText(str,3);				 // Einlesen des Parameters fuer Schiebefaltung
	i = atoi(str);
	
	if (i<1 || i>4)
	{
	 MessageBox("Bitte überprüfen Sie Ihre Eingabe !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
     return;
	}
	
  	CDialog::OnOK();

	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer rechnet!!!");

	schiebefaltung(eingabe.getAnzahl(), i);	     // Aufruf Schiebefaltungsfunktion
	
	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");
}

void CSFaltDlg::OnPaint() 
{	
	CPaintDC dc(this);                           

	char str[10];

	sprintf(str,"%d",p);
	
	m_len.SetWindowText(str);					 // Belegen des Textfelds mit Adressbereichsgroesse	
	m_sfalt.SetFocus();
}
