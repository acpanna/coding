// EingDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matrix.h"
#include "EingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool check;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEingDlg 


CEingDlg::CEingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEingDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CEingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEingDlg)
	DDX_Control(pDX, IDC_EDIT3, m_Spalten);
	DDX_Control(pDX, IDC_EDIT2, m_Zeilen);
	DDX_Control(pDX, IDC_EDIT1, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEingDlg, CDialog)
	//{{AFX_MSG_MAP(CEingDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CEingDlg 

void CEingDlg::OnOK() 
{
	char name[256];
	char zeilen[256];
	char spalten[256];

    m_Name.GetWindowText(name,255);
	m_Zeilen.GetWindowText(zeilen,255);
	m_Spalten.GetWindowText(spalten,255);

    for (int i=0; i < (int) strlen(name); i++)
		if (name[i] != ' ')
			break;

	if (i == (int) strlen(name))
	{
		MessageBox("Die Matrix muß einen gültigen Namen besitzen !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
		m_Name.SetFocus();
		return;
	}

	for (i=0; i < theApp.anzahl ; i++)
		if (!strcmp(name,theApp.matrix[i]->GetName()))
		{
			MessageBox("Es existiert bereits eine Matrix mit diesem Namen !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
            return;
		}

	if (atoi(zeilen) < 1 )
	{
		m_Zeilen.SetFocus();
		return;
	}

	if (atoi(spalten) < 1)
	{
		m_Spalten.SetFocus();
		return;
	}

	theApp.anzahl++;

	theApp.matrix = (CMatrix **) realloc(theApp.matrix, sizeof(CMatrix) * theApp.anzahl);
	
    if (theApp.matrix == 0)
	{
		MessageBox("Zu wenig Speicherplatz !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
	    return;
	}
	
	theApp.matrix[theApp.anzahl - 1] = new CMatrix(name, atoi(zeilen), atoi(spalten));
   
///////////////////////////////////////
	CCommandLineInfo cmd;
	   
    check = 1;

	theApp.ProcessShellCommand(cmd);
///////////////////////////////////////	

	CDialog::OnOK();
}

void CEingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    m_Name.SetFocus();
}
