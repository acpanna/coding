// ZinsenDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Zinsen.h"
#include "ZinsenDlg.h"
#include "Zinsenfkt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZinsenDlg Dialogfeld

CZinsenDlg::CZinsenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZinsenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZinsenDlg)
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf ben�tigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZinsenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZinsenDlg)
	DDX_Control(pDX, IDC_EDIT3, m_laufzeit);
	DDX_Control(pDX, IDC_EDIT2, m_zinssatz);
	DDX_Control(pDX, IDC_EDIT1, m_startkapital);
	DDX_Control(pDX, IDC_LIST1, m_Listenfeld);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZinsenDlg, CDialog)
	//{{AFX_MSG_MAP(CZinsenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BN_RECHNEN, OnBnRechnen)
	ON_BN_CLICKED(ID_VERLASSEN, OnVerlassen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZinsenDlg Nachrichten-Handler

BOOL CZinsenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol f�r dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zus�tzliche Initialisierung einf�gen
	
	return TRUE;  // Geben Sie TRUE zur�ck, au�er ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch f�r Sie erledigt.

void CZinsenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger�tekontext f�r Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, w�hrend der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CZinsenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZinsenDlg::OnBnRechnen() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	double startKapital, zinsSatz;
	int laufzeit;
	double Ertrag;
	char str[100];

	m_Listenfeld.ResetContent();

	m_startkapital.GetWindowText(str, 100);
	  startKapital = atof(str);
	m_zinssatz.GetWindowText(str, 100);
	  zinsSatz = atof(str);
	m_laufzeit.GetWindowText(str, 100);
      laufzeit = (int) atof(str);

	  for (int i=0; i<=laufzeit; i++)
	  {
		  Ertrag = ErtragOhneZinsen(startKapital,zinsSatz,i);
		  sprintf(str,"%lf",Ertrag);
		  m_Listenfeld.AddString(str);
	  }
	  m_Listenfeld.SetCurSel(laufzeit);
}
	


void CZinsenDlg::OnVerlassen() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	exit(1);
}
