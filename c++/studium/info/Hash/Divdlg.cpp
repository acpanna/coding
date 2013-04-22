// DivDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "DivDlg.h"
#include "Hashfkt.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDivDlg 

CDivDlg::CDivDlg(CWnd* pParent)
	: CDialog(CDivDlg::IDD, pParent)
{
}


void CDivDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_DIVREST, m_addressrange);
	DDX_Control(pDX, IDC_STATIC_DIVMIND2, m_mind2);
	DDX_Control(pDX, IDC_STATIC_DIVMIND1, m_mind1);
}


BEGIN_MESSAGE_MAP(CDivDlg, CDialog)
	
	ON_WM_PAINT()
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDivDlg 

void CDivDlg::OnPaint() 
{
	CPaintDC dc(this);

	char str[10];
	
	sprintf(str,"%d",eingabe.getAnzahl());      // Belegung der Textfelder mit sinnvollen
	m_mind1.SetWindowText(str);               

	sprintf(str,"%g",eingabe.getAnzahl()*1.3);  // Werten fuer den Adressbereich
	m_mind2.SetWindowText(str);

    m_addressrange.SetFocus();					// Focus auf Adressbereichs - Eingabefeld
}

void CDivDlg::OnOK() 
{
	char str[10];

	m_addressrange.GetWindowText(str,10);		 // Auslesen des gewuenschten Adressbereichs
	p = atoi(str);
    
    if (p < 1 || p > 2000)
	{
	 MessageBox("Bitte überprüfen Sie Ihre Eingabe !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
     return;
	}

	if (p < eingabe.getAnzahl())
      MessageBox("                  ACHTUNG: eine sinnvolle Zuordnung ist nicht moeglich,\n\nda der Adressraum kleiner als die Maechtigkeit der Schluesselwertmenge ist !","Hinweis...",MB_OK|MB_ICONEXCLAMATION);

	CDialog::OnOK();
	
	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer rechnet!!!");

	divisionsrest(eingabe.getAnzahl());			 // Aufruf der Divisions - Rest - Funktion

	((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");

}
