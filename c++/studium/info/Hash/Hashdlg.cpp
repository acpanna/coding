// HashDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Hash.h"
#include "HashDlg.h"
#include "ShowDlg.h"
#include "EingabeDlg.h"
#include "DivDlg.h"
#include "MitteDlg.h"
#include "SFaltDlg.h"
#include "GFaltDlg.h"
#include "BasDlg.h"
#include "InfoDlg.h"
#include "Hashfkt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashDlg Dialogfeld

CHashDlg::CHashDlg(CWnd* pParent)
	: CDialog(CHashDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);   
}                                                // Einlesen des Hash - Icons

void CHashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);                // Funktion zum Datenaustausch zwischen 
    DDX_Control(pDX, IDC_STATUS, m_status);

}											     // Dialogfeldern und Membervariablen							

BEGIN_MESSAGE_MAP(CHashDlg, CDialog)             // Message - Schleife, zur Reaktion auf
												 // verschiedenen Events	
	ON_WM_PAINT()	//Neuzeichnungsmethode
	//Bei Buttonklick werden die angegebenen Methoden aufgerufen
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_KEYMENGE, OnKeymenge)
	ON_BN_CLICKED(IDC_KEYEINGABE, OnKeyeingabe)
	ON_BN_CLICKED(IDC_KEYEINLESEN, OnKeyeinlesen)
	ON_BN_CLICKED(IDC_KEYCLEAR, OnKeyclear)
	ON_BN_CLICKED(IDC_BASISTRANS, OnBasistrans)
	ON_BN_CLICKED(IDC_DIVREST, OnDivrest)
	ON_BN_CLICKED(IDC_FALTGRENZEN, OnFaltgrenzen)
	ON_BN_CLICKED(IDC_MITTEQUAD, OnMittequad)
	ON_BN_CLICKED(IDC_SCHIEBEFALT, OnSchiebefalt)
	ON_BN_CLICKED(IDC_KEYSAVE, OnKeysave)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHashDlg Nachrichten-Handler

BOOL CHashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, FALSE);		             // Kleines Symbol verwenden
	
	return TRUE;						         // Rueckgabe von TRUE --> Focus auf Dialogfeld
}

void CHashDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON); //Breite des Icons wird bestimmt
		int cyIcon = GetSystemMetrics(SM_CYICON); //Hoehe des Icons wird bestimmt
		CRect rect;
		GetClientRect(&rect);
		//rect==Dialogbereich
		int x = (rect.Width() - cxIcon + 1) / 2;	//x/y-Kordinaten der linken oberen Ecke des Icons 
													//werden so gewaehlt, dass das Icon im Dialogbereich zentriert ist
		int y = (rect.Height() - cyIcon + 1) / 2;	

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CHashDlg::OnExit() //Beim Klick auf Programmende-Icon/Button wird folgende MessageBox erzeugt
{
	if(MessageBox("      Sind Sie sicher ?", "Programm beenden...", MB_YESNO|MB_ICONQUESTION) == IDYES)
		exit(0);
}

void CHashDlg::OnKeymenge() 
{
	if(Empty())								     // Falls Liste leer, mache nichts, Mitteilung an den User in der Empty()-Methode
		return;

	CShowDlg sdlg;								 // Zeige Liste im ShowDialog an	
    sdlg.DoModal();
}

void CHashDlg::OnKeyeingabe() 
{
   	CEingabeDlg dlg;                             // Erzeugung und Anzeigen des Eingabedialogs 
	dlg.DoModal();
}

void CHashDlg::OnKeyeinlesen()					 // FileDialog zum Einlesen der Schluesselwerte aus Datei				 		
{
	char *filename;
	
	CFileDialog fdlg(1,0,0,OFN_HIDEREADONLY,0,0);	//Erzeugen eines Read-Filedialogs

    fdlg.m_ofn.lpstrInitialDir="c:\\";				//Setzen des Startdirectorys auf c:
	fdlg.m_ofn.lpstrFilter="HashDateien (*.hsh)\0*.hsh\0Alle Dateien (*.*)\0*.*\0"; //Setzen des Filters 
	
	if (fdlg.DoModal() == IDOK) //falls Filedialog mit OK beendet wird
    {
		filename = (char *) malloc( (strlen(fdlg.m_ofn.lpstrFile) + 1) * sizeof(char) );//Speicher fuer Filename wird allociert

		if (filename == 0)	//Test auf Null, ob Speicherplatz frei ist
			speicher();		//Falls nicht Mitteilung an den User, dass kein Speicher frei ist

		strcpy(filename,fdlg.m_ofn.lpstrFile);
        
		((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer lädt!!!");

		read_file(filename);					 // Aufruf der bereits programmierten Einlese - Funktion
	    
		((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Computer bereit!!!");
	}
}

void CHashDlg::OnKeyclear() 
{
	if( MessageBox("            Sind Sie sicher ?", "Aktuelle Schlüsselwertmenge löschen...", MB_YESNO|MB_ICONQUESTION) == IDYES)
		eingabe.remove();	//loeschen der Schluesselmenge
}

void CHashDlg::OnBasistrans() 
{
	if(Empty())		//Test ob Schluesselmenge leer ist
		return;

	CBasDlg dlg;
	dlg.DoModal();	//Falls nicht leer,erzeugen des Basistransformationsdialogs
}

void CHashDlg::OnDivrest() 
{
    if(Empty())	//Test ob Schluesselmenge leer ist
		return;

	CDivDlg dlg;	//Falls nicht leer,erzeugen des Divisionsrestdialogs
	dlg.DoModal();
}

void CHashDlg::OnFaltgrenzen() 
{
	if(Empty())//Test ob Schluesselmenge leer ist
		return;

	CGFaltDlg dlg;	//Falls nicht leer,erzeugen des Faltung-an-den-Grenzen-Dialogs
	dlg.DoModal();
}

void CHashDlg::OnMittequad() 
{
	if(Empty())	//Test ob Schluesselmenge leer ist
		return;

	CMitteDlg dlg;	//Falls nicht leer,erzeugen des Mitte-des-Quadrats-Dialogs
	dlg.DoModal();
}

void CHashDlg::OnSchiebefalt() 
{
	if(Empty()) //Test ob Schluesselmenge leer ist
		return;

	CSFaltDlg dlg;	//Falls nicht leer,erzeugen des Schiebe-Faltung-Dialogs
	dlg.DoModal();
}

void CHashDlg::OnKeysave() 						 // FileDialog zum Speichern der Schluesselwerte in Datei	
{
	char *filename;
	
	if(Empty()) //Test ob Schluesselmenge leer ist
		return;
	
	CFileDialog fdlg(0,0,0,OFN_HIDEREADONLY,0,0);

	fdlg.m_ofn.lpstrInitialDir="c:\\";
	fdlg.m_ofn.lpstrFilter="HashDateien (*.hsh)\0*.hsh\0Alle Dateien (*.*)\0*.*\0";
	
	if (fdlg.DoModal() == IDOK)
    {
		int i;
		filename = (char *) malloc( (strlen(fdlg.m_ofn.lpstrFile) + 5) * sizeof(char) );

		if (filename == 0)
			speicher();

		strcpy(filename,fdlg.m_ofn.lpstrFile);
        for(i=0;i<strlen(filename)&&filename[i]!='.';i++);	//durchsucht filename nach Punkt
		filename[i]='\0';
		strcat(filename,".hsh");				  //Anhaengen der Endung an den Filenamen
      	save_file(filename);					 // Aufruf der Speichern - Funktion
	}

}

void CHashDlg::OnInfo()		//Info-Dialog
{
	CInfoDlg dlg;
	dlg.DoModal();
}

bool CHashDlg::Empty()		//Überprüft, ob Schlüsselmenge leer ist
{
	if (eingabe.empty() == 1)
	{
		MessageBox("Die aktuelle Schlüsselwertmenge ist leer !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
        return 1;
	}

	return 0;
}
