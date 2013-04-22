// MatrixDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Matrix.h"
#include "MatrixDlg.h"
#include "EingDlg.h"
#include "WahlDlg.h"
#include "NameDlg.h"
#include "SkMultDlg.h"
#include "PotDlg.h"
#include "MainFrm.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixDlg Dialogfeld

CMatrixDlg::CMatrixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMatrixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatrixDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatrixDlg)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMatrixDlg, CDialog)
	//{{AFX_MSG_MAP(CMatrixDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EINGABE, OnEingabe)
	ON_BN_CLICKED(IDC_ADJUNG, OnAdjung)
	ON_BN_CLICKED(IDC_LOESCHEN, OnLoeschen)
	ON_BN_CLICKED(IDC_DET, OnDet)
	ON_BN_CLICKED(IDC_INVERS, OnInvers)
	ON_BN_CLICKED(IDC_SKMULT, OnSkmult)
	ON_BN_CLICKED(IDC_TRANS, OnTrans)
	ON_BN_CLICKED(IDC_MATPOT, OnMatpot)
	ON_BN_CLICKED(IDC_ENDE, OnEnde)
	ON_BN_CLICKED(IDC_AUSGABE, OnAusgabe)
	ON_BN_CLICKED(IDC_LADEN, OnLaden)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_MATADD, OnMatadd)
	ON_BN_CLICKED(IDC_MATMULT, OnMatmult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixDlg Nachrichten-Handler

BOOL CMatrixDlg::OnInitDialog()
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

void CMatrixDlg::OnPaint() 
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
HCURSOR CMatrixDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMatrixDlg::OnEingabe() 
{
	if (active)
		return;

	CEingDlg dlg;
	dlg.DoModal();
}

void CMatrixDlg::OnAdjung() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CNameDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
		   theApp.matrix[theApp.anzahl - 1] = matrix1->Adj();
		   theApp.matrix[theApp.anzahl - 1]->SetName(name);
		}
	}

	matrix1 = 0;
}

void CMatrixDlg::OnLoeschen() 
{
	if (active)
		return;
	
	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		for (int i=0; i<theApp.anzahl; i++)
			if(!strcmp(matrix1->GetName(),theApp.matrix[i]->GetName()))
				break;

		delete matrix1;
		matrix1 = 0;

		theApp.matrix[i] = theApp.matrix[theApp.anzahl - 1];
		theApp.anzahl--;
	}

	matrix1 = 0;
}

void CMatrixDlg::OnDet()
{
	if (active)
		return;

   	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		char str[256];
		
		if (matrix1->GetSpalten() != matrix1->GetZeilen())
		{
			MessageBox("Spalten- und Zeilenanzahl der Matrix stimmen nicht überein !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
			return;
		}

		sprintf(str,"Die Determinante der Matrix beträgt :  %lg",matrix1->Det());

		MessageBox(str,"Determinantenberechnung...",MB_OK|MB_ICONINFORMATION);
	}

	matrix1 = 0;
}

void CMatrixDlg::OnInvers() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		if (matrix1->GetSpalten() != matrix1->GetZeilen())
		{
			MessageBox("Spalten- und Zeilenanzahl der Matrix stimmen nicht überein !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		
		if(!matrix1->Det())
		{
			MessageBox("Die Matrix kann nicht invertiert werden (Determinate ist 0) !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
			return;
		}

		CNameDlg dlg2;
	    if (dlg2.DoModal() == IDOK)
		{
			theApp.matrix[theApp.anzahl - 1] = matrix1->Adj();
	        matrix1 = *(theApp.matrix[theApp.anzahl - 1]) * (1.0 / matrix1->Det());
	        
			delete theApp.matrix[theApp.anzahl - 1];
			
			theApp.matrix[theApp.anzahl - 1] = matrix1;
			theApp.matrix[theApp.anzahl - 1]->SetName(name);		
		}
	}

	matrix1 = 0;
}


void CMatrixDlg::OnSkmult() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CNameDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
			CSkMultDlg dlg3;
			dlg3.DoModal();

			theApp.matrix[theApp.anzahl - 1]->SetName(name);
		}
	}

	matrix1 = 0;
}

void CMatrixDlg::OnTrans() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CNameDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
		   theApp.matrix[theApp.anzahl - 1] = matrix1->Trans();
		   theApp.matrix[theApp.anzahl - 1]->SetName(name);
		}
	}

	matrix1 = 0;
}

void CMatrixDlg::OnMatpot() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (matrix1->GetSpalten() != matrix1->GetZeilen())
		{
			MessageBox("Spalten- und Zeilenanzahl der Matrix stimmen nicht überein !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
			return;
		}

		CNameDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
		   	CPotDlg dlg3;
			dlg3.DoModal();

			theApp.matrix[theApp.anzahl - 1]->SetName(name);
		}
	}

	matrix1 = 0;
}

void CMatrixDlg::OnEnde() 
{
	if (active)
		return;

	if (MessageBox("Wollen Sie das Programm wirklich verlassen ?","Programmende...",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		delete matrix1;
        delete matrix2;
		matrix1 = 0;
		matrix2 = 0;
		exit(0);
	}
}

void CMatrixDlg::OnAusgabe() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		///////////////////////////////////////
		CCommandLineInfo cmd;
	   
        check = 0;

	    theApp.ProcessShellCommand(cmd);
		///////////////////////////////////////
	}
}

void CMatrixDlg::OnLaden() 
{
	if (active)
		return;

	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY,NULL,NULL);
	
	dlg.m_ofn.lpstrInitialDir = "c:\\";
	dlg.m_ofn.lpstrFilter = "MatrizenFiles (*.mtx)\0*.mtx\0Alle Dateien (*.*)\0*.*\0";
	
	if (dlg.DoModal() == IDOK)
	{
		char *filename;
		bool test = 0;
		
		filename = (char *) malloc( (strlen(dlg.m_ofn.lpstrFile) + 1) * sizeof(char) );
	    
		if (filename == 0)
		{
			MessageBox("Zu wenig Speicherplatz !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
	        return;
		}

		strcpy(filename,dlg.m_ofn.lpstrFile);
	    
		for (int i=0; i<theApp.anzahl; i++)
			if (!strcmp(dlg.m_ofn.lpstrFileTitle,theApp.matrix[i]->GetName()))
				test = 1;
			
		if (test == 1)
		{
			CNameDlg dlg2;
			dlg2.DoModal();

			theApp.matrix[theApp.anzahl - 1] = new CMatrix(name, 1);
		}

		else
		{
			theApp.anzahl++;
	        theApp.matrix = (CMatrix **) realloc(theApp.matrix, sizeof(CMatrix) * theApp.anzahl);
            
			if (theApp.matrix == 0)
			{
				MessageBox("Zu wenig Speicherplatz !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
	            return;
			}

	        theApp.matrix[theApp.anzahl - 1] = new CMatrix(dlg.m_ofn.lpstrFileTitle, 1);
		}

		ifstream fin(filename); 
		fin >> *(theApp.matrix[theApp.anzahl - 1]);
		fin.close();
	}
}

void CMatrixDlg::OnSave() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg1;
	if (dlg1.DoModal() == IDCANCEL)
		return;
	
	CFileDialog dlg(false,NULL,matrix1->GetName(),OFN_HIDEREADONLY,NULL,NULL);
	
	dlg.m_ofn.lpstrInitialDir = "c:\\";
	dlg.m_ofn.lpstrFilter = "MatrizenFiles (*.mtx)\0*.mtx\0Alle Dateien (*.*)\0*.*\0";
	
	if (dlg.DoModal() == IDOK)
	{
		char *filename;
		filename = (char *) malloc( (strlen(dlg.m_ofn.lpstrFile) + 4) * sizeof(char) );
	    
		if (filename == 0)
		{
			MessageBox("Zu wenig Speicherplatz !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
	        return;
		}
		
		strcpy(filename,dlg.m_ofn.lpstrFile);
		
		if (strlen(filename) < 4)
			strcat(filename,".mtx");

		else if (filename[strlen(filename)-4] != '.')
			strcat(filename,".mtx");

		else if (filename[strlen(filename)-3] != 'm' || filename[strlen(filename)-2] != 't' || filename[strlen(filename)-1] != 'x')
		{
			filename[strlen(filename)-3] = 'm';
			filename[strlen(filename)-2] = 't';
			filename[strlen(filename)-1] = 'x';
		}
			    
		ofstream fout(filename); 
		fout << *matrix1;
		fout.close();
	}

	matrix1 = 0;
}

void CMatrixDlg::OnMatadd() 
{
	if (active)
		return;

	if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		matrix2 = matrix1;
		
		CWahlDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
			if (matrix2->GetSpalten() != matrix1->GetSpalten() || matrix2->GetZeilen() != matrix1->GetZeilen())
			{
				MessageBox("Spalten- bzw. Zeilenanzahl der Matrizen stimmen nicht überein !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
			    matrix1 = 0;
				matrix2 = 0;
				return;
			}
			
			CNameDlg dlg3;
			if (dlg3.DoModal() == IDOK)
			{
				theApp.matrix[theApp.anzahl - 1] = (*matrix2) + (*matrix1);
		        theApp.matrix[theApp.anzahl - 1]->SetName(name);
			}
		}
	}

	matrix1 = 0;
	matrix2 = 0;
}

void CMatrixDlg::OnMatmult() 
{
	if (active)
		return;

    if (theApp.anzahl == 0)
		return;

	CWahlDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		matrix2 = matrix1;
		
		CWahlDlg dlg2;
		if (dlg2.DoModal() == IDOK)
		{
			if (matrix2->GetSpalten() != matrix1->GetZeilen())
			{
				MessageBox("Spalten- bzw. Zeilenanzahl der Matrizen stimmen nicht überein !","Fehler...",MB_OK|MB_ICONEXCLAMATION);
			    matrix1 = 0;
				matrix2 = 0;
				return;
			}
			
			CNameDlg dlg3;
			if (dlg3.DoModal() == IDOK)
			{
				theApp.matrix[theApp.anzahl - 1] = (*matrix2) * (*matrix1);
		        theApp.matrix[theApp.anzahl - 1]->SetName(name);
			}
		}
	}

	matrix1 = 0;
	matrix2 = 0;
}
