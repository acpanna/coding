// InternetCashDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <fstream.h>
#include "InternetCash.h"
#include "InternetCashDlg.h"
#include "tarif.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct nutzung {
	int minuten[250];
	int tag[250];
	int monat[250];
	int jahr[250];
    char wer[250];
}use;

int anzahl;
char check;
double einwahl, minute;
int test = 0;

/////////////////////////////////////////////////////////////////////////////
// CInternetCashDlg Dialogfeld

CInternetCashDlg::CInternetCashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInternetCashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInternetCashDlg)
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
	ifstream fin("c:\\progra~1\\aol\\use.dat");

	if (fin.fail())
		anzahl = 0;

    else 
	{
		fin >> anzahl;
		
		for (int i=0; i<anzahl; i++)
		{
			fin >> use.minuten[i];
			fin >> use.tag[i];
			fin >> use.monat[i];
			fin >> use.jahr[i];
			fin >> use.wer[i];
		}
	}

	fin.close();

	ifstream fin2("C:\\progra~1\\aol\\tar.dat");

	fin2 >> einwahl;
	fin2 >> minute;

	fin2.close();
}

void CInternetCashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInternetCashDlg)
	DDX_Control(pDX, IDC_LIST1, m_Listbox);
	DDX_Control(pDX, IDC_EDIT1, m_Eingabe);
	DDX_Control(pDX, IDC_HEIKO, m_Heiko);
	DDX_Control(pDX, IDC_FRANK, m_Frank);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInternetCashDlg, CDialog)
	//{{AFX_MSG_MAP(CInternetCashDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_FRANK, OnFrank)
	ON_BN_CLICKED(IDC_HEIKO, OnHeiko)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_TARIF, OnTarif)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternetCashDlg Nachrichten-Handler

BOOL CInternetCashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CInternetCashDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

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

	if (test == 1)
		return;
	
	for (int i=0; i < anzahl; i++)
	{
		char str[256];

		if (use.wer[i] == 'h')
			sprintf(str,"%d.%d.%d\t%2d Minute(n)\tHeiko",use.tag[i],use.monat[i],use.jahr[i],use.minuten[i]);
		else
			sprintf(str,"%d.%d.%d\t%2d Minute(n)\tFrank",use.tag[i],use.monat[i],use.jahr[i],use.minuten[i]);

		m_Listbox.AddString(str);
	}

	m_Heiko.SetCheck(1);
	OnHeiko();
	test = 1;
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CInternetCashDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInternetCashDlg::OnClear() 
{
	int i = m_Listbox.GetCurSel(), j;

	if (m_Listbox.GetCurSel() == LB_ERR)
	{
		if( MessageBox("Wollen Sie die gesamte Liste löschen ?","Löschen der Liste",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			i = anzahl;
			anzahl = 0;
			
			for (j=0; j<i ; j++)
				m_Listbox.DeleteString(0);

	        goto save;
		}
	}

    for (j=0; j<=i ; j++)
		m_Listbox.DeleteString(0);

	anzahl = anzahl - i - 1;
	
	for (j = 0; j <= anzahl; j++)
	{
		use.tag[j] = use.tag[i+j+1];
		use.minuten[j] = use.minuten[i+j+1];
	    use.jahr[j] = use.jahr[i+j+1];
		use.monat[j] = use.monat[i+j+1];
		use.wer[j] = use.wer[i+j+1];
	}
	
save:
	
	ofstream fout("c:\\progra~1\\aol\\use.dat");

	fout << anzahl;
	
	for (i=0; i<anzahl; i++)
	{
		fout << " ";
		fout << use.minuten[i];
		fout << " ";
	    fout << use.tag[i];
		fout << " ";
	    fout << use.monat[i];
		fout << " ";
	    fout << use.jahr[i];
		fout << " ";
	    fout << use.wer[i];
	}

	fout.close();
}

void CInternetCashDlg::OnFrank() 
{
	check = 'f';
}

void CInternetCashDlg::OnHeiko() 
{
	check = 'h';
}

void CInternetCashDlg::OnDblclkList1() 
{
	char str[256];
	char str2[256];
	
	int hmin = 0, fmin = 0, hanz = 0, fanz = 0;

	int i = m_Listbox.GetCurSel();

	for (int j=0; j<=i ; j++)
	{
		if (use.wer[j] == 'h')
		{
			hmin += use.minuten[j];
	        hanz++;
		}
		
		else
		{
			fmin += use.minuten[j];
	        fanz++;
		}
	}

	sprintf(str,"Nutzungsdauer (in Minuten)   Heiko :  %d,  Frank :  %d,  Gesamt :  %d\n\nKosten (in DM)   Heiko :  %.2lg,  Frank :  %.2lg,  Gesamt :  %lg",hmin,fmin,hmin+fmin,(hanz*einwahl+hmin*minute)/100.0,(fanz*einwahl+fmin*minute)/100.0,(hanz*einwahl+hmin*minute)/100.0 + (fanz*einwahl+fmin*minute)/100.0);
	sprintf(str2,"Abrechnung einschließlich %d.%d.%d",use.tag[i],use.monat[i],use.jahr[i]);
	
	MessageBox(str,str2,MB_OK|MB_ICONINFORMATION);

		
}

void CInternetCashDlg::OnTarif() 
{
	CTarif dlg;
	dlg.DoModal();
}

void CInternetCashDlg::OnOK() 
{
	char str[10];

    time_t now;

	struct tm *ptr;
	
	time(&now);
	ptr = localtime(&now);	

	m_Eingabe.GetWindowText(str,10);
	
	if (atoi(str) <= 0 || anzahl >= 250)
		exit(1);

	use.minuten[anzahl] = atoi(str);
	use.wer[anzahl] = check;

	strftime(str,10,"%d",ptr);
	use.tag[anzahl] = atoi(str);
    strftime(str,10,"%m",ptr);
	use.monat[anzahl] = atoi(str);
	strftime(str,10,"%Y",ptr);
	use.jahr[anzahl] = atoi(str);	

    anzahl++;

    ofstream fout("c:\\progra~1\\aol\\use.dat");

	fout << anzahl;
	
	for (int i=0; i<anzahl; i++)
	{
		fout << " ";
		fout << use.minuten[i];
		fout << " ";
	    fout << use.tag[i];
		fout << " ";
	    fout << use.monat[i];
		fout << " ";
	    fout << use.jahr[i];
		fout << " ";
	    fout << use.wer[i];
	}

	fout.close();

	CDialog::OnOK();
}


void CInternetCashDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}
