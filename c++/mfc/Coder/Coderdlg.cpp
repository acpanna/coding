// CoderDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Coder.h"
#include "CoderDlg.h"
#include <string.h>
#include <fstream.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MATRANG 10

/////////////////////////////////////////////////////////////////////////////
// CCoderDlg Dialogfeld

CCoderDlg::CCoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoderDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoderDlg)
	DDX_Control(pDX, IDC_EDIT1, m_codegrad);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCoderDlg, CDialog)
	//{{AFX_MSG_MAP(CCoderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CODER, OnCoder)
	ON_BN_CLICKED(IDC_DECODE, OnDecode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoderDlg Nachrichten-Handler

BOOL CCoderDlg::OnInitDialog()
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

void CCoderDlg::OnPaint() 
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
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CCoderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCoderDlg::OnCoder() 
{
	char text;

	char *str;
    char str2[4];
	
	double *ascii;
	double *ascii2;
	
	int count = 0;
    int codegrad;

	long i = 1;
	long k = 0;

	long matrix[MATRANG][MATRANG]={ -1, 2, 3, -4, 2, 1, -2, 0, -1, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 3, 0, -3, 5, 0, 0, 1, -6, -1, 0, 0, 0, 1, -1, 0, -5, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, -3, 1, 0, 5, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, -1, 0, 0, 1, 4, 0, 5, 1, -2, 0, 0, 1, -3, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 3, 0, -2, 0, 1, 0, 2, 0, 0, 2, 0 };

	m_codegrad.GetWindowText(str2,3);
	
    codegrad = atoi(str2);

	if (codegrad <= 0)
		codegrad = 1;
	if (codegrad > 12)
	    codegrad = 12;
    if ((codegrad % 2) == 0)
		codegrad++;

	CFileDialog dlg(1);

	dlg.m_ofn.lpstrInitialDir="c:\\";
	
	if(dlg.DoModal() == IDCANCEL)
		return;

	ifstream fin(dlg.m_ofn.lpstrFile);

    str = (char *) malloc(sizeof(char));

	if (str == 0)
		exit(1);

	while(!fin.eof())
	{		
		fin.get(text);
		str = (char *) realloc(str, i * sizeof(char));
		
		if (str == 0)
			exit(1);

		str[i-1] = text;
		i++;
	}

	fin.close();

  	i = i - 2;
   
   	str[i]='\0';

	for (long j=i; j>=0; j--)
		if (str[j] != '\0' && str[j] != ' ')
		{
			i = j + 1;
			break;
		}

	count = MATRANG - (i % MATRANG);
	
    ascii = (double *) malloc((i+count) * sizeof(double));
    ascii2 = (double *) malloc((i+count) * sizeof(double));
  
	if (ascii == 0 || ascii2 == 0)
		exit(1);

	for (j=0; j<i; j++)
		ascii[j] = str[j];

    for (j=i; j<i+count;j++)
		ascii[j] = 0;
	
  	for (j=0; j<i+count; j++)
		ascii2[j] = ascii[j];

	for (j=0; j<i+count; j++)
	{
		double temp = 0.0;

		for (long p=0; p<MATRANG; p++)
		    temp += matrix[j%MATRANG][p] * ascii2[k+p];
		
		if ( (j+1) % MATRANG == 0)
		    k = k + MATRANG;

		ascii[j] = temp;
	}

    for (int a=1; a<=codegrad; a++)
	{
		if ((a % 2) != 0)
		{
			for (j=0; j<(i+count)/2; j++)
        		ascii[j] = ascii[j] + ascii[i+count-1-j];
		}

		else
		{
			for (j=0; j<(i+count)/2; j++)
        		ascii[i+count-1-j] = ascii[i+count-1-j] + ascii[j];
		}
	}
	
	ofstream fout(dlg.m_ofn.lpstrFile);

	fout << i+count;

	fout << " ";
	
	for (j=0; j<i+count; j++)
	{
		fout << ascii[j];
	   
		fout << " ";
	}

	fout.close();

	free(str);
	free(ascii);
	free(ascii2);
}

void CCoderDlg::OnDecode() 
{
    int codegrad;

	long k = 0;
	long zahl;
	long i;

	double *zahlen;
	double *zahlen2;

	char str2[4];
	long matrix[MATRANG][MATRANG]={ -1344, -5784, -1456, -672, -1792, 1792, 5772, 336, 3860, 504, 448, -2552, -1008, 224, -896, 896, 4796, -112, -540, -168, -3360, -3220, 280, -560, 2240, 4480, -3990, -1960, 11270, -4060, 0, 640, 0, 0, 0, 0, 960, 0, -960, 0, -2688, -5008, -672, -1344, 896, 3584, 1224, -1568, 9080, -2352, 9072, 9982, 28, 1736, -4704, -9856, 5649, 4732, -28665, 9898, 0, 1920, 0, 0, 0, 0, -3840, 0, -640, 0, -9072, -9982, -28, -1736, 9184, 9856, -5649, -4732, 33145, -9898, -8624, -12854, -1036, -1512, 3808, 10752, -1333, -4844, 28605, -7826, 0, 640, 0, 0, 0, 0, -1280, 0, 1280, 0 };
	
	m_codegrad.GetWindowText(str2,3);
	
    codegrad = atoi(str2);

	if (codegrad <= 0)
		codegrad = 1;
	if (codegrad > 12)
	    codegrad = 12;
	if ((codegrad % 2) == 0)
		codegrad++;

	CFileDialog dlg(1);

	dlg.m_ofn.lpstrInitialDir="c:\\";

	if(dlg.DoModal() == IDCANCEL)
		return;

	ifstream fin(dlg.m_ofn.lpstrFile);
	
    zahlen = (double *) malloc(sizeof(double));

	if (zahlen == 0)
		exit(1);

	fin >> i;
	
	for (long j=0; j<i; j++)
	{		
		fin >> zahl;
		zahlen = (double *) realloc(zahlen, i * sizeof(double));
		
		if (zahlen == 0)
			exit(1);

		zahlen[j] = (double) zahl;
	}

   	fin.close();

   	zahlen2 = (double *) malloc(i * sizeof(double)); 
	
	if (zahlen2 == 0)
		exit(1);
   
    for (int a=1; a<=codegrad; a++)
	{
		if ((a % 2) == 0)
		{
			for (long j=0; j<i/2; j++)
        		zahlen[i-1-j] = zahlen[i-1-j] - zahlen[j];
		}

		else
		{
			for (long j=0; j<i/2; j++)
        		zahlen[j] = zahlen[j] - zahlen[i-1-j];
		}
	}
	
	for (j=0; j<i; j++)
	    zahlen2[j] = zahlen[j];
		
    for (j=0; j<i; j++)
	{
	    double temp = 0.0;

	    for (long p=0; p<MATRANG; p++)
		   temp += matrix[j%MATRANG][p] * zahlen2[k+p]; 
		 
  	    if ( (j+1) % MATRANG == 0)
		    k = k + MATRANG;

	    zahlen[j] = temp;
	}
      
	ofstream fout(dlg.m_ofn.lpstrFile);

	for (j=0; j<i; j++)
	{
		zahlen[j] *= 1.0/4480.0; // Multiplikation mit Kehrbruch der Determinante 
		
		if (zahlen[j] - (int) zahlen[j] >= 0.5)
			zahlen[j] += 1.0;
		
		char temp = (int) zahlen[j];
		
	  	fout << temp;
	}

	fout.close();

	free(zahlen);
	free(zahlen2);
}

