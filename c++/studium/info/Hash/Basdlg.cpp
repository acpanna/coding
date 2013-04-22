// BasDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "BasDlg.h"
#include "Hashfkt.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CBasDlg 

CBasDlg::CBasDlg(CWnd* pParent)
	: CDialog(CBasDlg::IDD, pParent)
{
}


void CBasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_BASTRANS, m_bastrans);
	DDX_Control(pDX, IDC_STATIC_LEN, m_len);
}


BEGIN_MESSAGE_MAP(CBasDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CBasDlg 

void CBasDlg::OnPaint() 
{
	CPaintDC dc(this);

	char str[10];

	sprintf(str,"%d",p);
	
	m_len.SetWindowText(str);					 // Anzeigen der Groesse des Adressbereichs im Textfeld
	m_bastrans.SetFocus();						 // Focus auf Feld zur Basis - Eingabe
}

void CBasDlg::OnOK() 
{
	char str[4];
	int i;
	
	m_bastrans.GetWindowText(str,4);            // Auslesen der gew. Basis im Eingabefeld
	i = atoi(str);

	if (i<1 || i>20)
	{
	 MessageBox("Bitte überprüfen Sie Ihre Eingabe !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
     return;
	}
	CDialog::OnOK();
   
  
	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer rechnet!!!");

	transform(eingabe.getAnzahl(), i);			 // Aufruf der Basis - Trans. - Funktion

    ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");
}
