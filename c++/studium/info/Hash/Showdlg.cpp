// ShowDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "ShowDlg.h"
#include "Hashfkt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CShowDlg 

CShowDlg::CShowDlg(CWnd* pParent)
	: CDialog(CShowDlg::IDD, pParent)
{
	paint = false;	//ermöglicht das Hinzufuegen der intern geführten Liste an die angezeigte ListBox
}


void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SHOWMENGE, m_ShowList);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CShowDlg 

void CShowDlg::OnPaint() 
{
	CPaintDC dc(this);                        
	
	//Im Konstruktor ist paint auf false gesetzt worden
	if (paint == true)
		return;
	//wird nur einmal direkt nach Konstruktoraufruf aufgerufen
	eingabe.output(&m_ShowList);                 // Anzeigen der momentanen Schluesselwertmenge

    paint = true;
}
