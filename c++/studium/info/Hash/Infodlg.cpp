// InfoDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "Hashfkt.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInfoDlg 

CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	paint = false;
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_info);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)

	ON_WM_PAINT()

END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CInfoDlg 

void CInfoDlg::OnPaint()						 // Ausgabe der Help - Datei
{
	CPaintDC dc(this); 
	
	if (paint == true)
		return;

   	char buffer[256];

	SearchPath(NULL,"hhelp.txt",NULL,256,buffer,NULL);

	ifstream fin;
    
	fin.open(buffer, ios::in | ios::nocreate);

	if(!fin)
	{
		MessageBox("Die Hilfedatei wurde nicht gefunden !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
		
	while(!fin.eof())
	{
		fin.getline(buffer,256,'\n');
		m_info.AddString(buffer);
    }

	paint = true;
}
