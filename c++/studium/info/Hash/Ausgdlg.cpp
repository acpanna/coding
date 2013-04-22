// AusgDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "AusgDlg.h"
#include "Hashfkt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAusgDlg 

CAusgDlg::CAusgDlg(CWnd* pParent)
	: CDialog(CAusgDlg::IDD, pParent)
{
	paint = false;		//ermöglicht das Hinzufuegen der intern geführten Liste an die angezeigte ListBox
}

void CAusgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_AUSUBL, m_Overflow);
	DDX_Control(pDX, IDC_LIST_AUSSP, m_Speicher);
	DDX_Control(pDX, IDC_STATIC_AUSKOLL, m_Kollision);
}


BEGIN_MESSAGE_MAP(CAusgDlg, CDialog)
	
	ON_WM_PAINT()
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAusgDlg 

void CAusgDlg::OnPaint()					     // Ausgabe nach Anwendung der Transformation
{
	CPaintDC dc(this);

		//Im Konstruktor ist paint auf false gesetzt worden
    if (paint == true)
		return;

	//wird nur einmal direkt nach Konstruktoraufruf aufgerufen
	char str[KEYLENGTH + 7];
	sprintf(str,"%d",kolission);
	
	m_Kollision.SetWindowText(str);				 // Belegen des Textfelds mit Kollisionsanzahl	

   	for (int j = 0; j < p; j++)					 // Ausgabe Speicherbelegungsliste	
	{
		if(arr[j] != -1)
		{
	       sprintf(str,"%d:\t%s",j,eingabe[arr[j]].keystr);
	       m_Speicher.AddString(str);
		}
	}
   
    ueberlauf.output(&m_Overflow);				 // Ausgabe Ueberlaufsliste	
  
    paint = true;

    ueberlauf.remove();
    delete [] arr;
    arr = 0;
}
