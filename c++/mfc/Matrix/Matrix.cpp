// Matrix.cpp : Legt das Klassenverhalten f�r die Anwendung fest.
//

#include "stdafx.h"
#include "Matrix.h"
#include "MatrixDlg.h"
#include "MatScEinDoc.h"
#include "MainFrm.h"
#include "MatScEinView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char name[256] = { '\0' };

CMatrix *matrix1 = 0;
CMatrix *matrix2 = 0;

/////////////////////////////////////////////////////////////////////////////
// CMatrixApp

BEGIN_MESSAGE_MAP(CMatrixApp, CWinApp)
	//{{AFX_MSG_MAP(CMatrixApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixApp Konstruktion/Destruktion

CMatrixApp::CMatrixApp()
{
	anzahl = 0;
}

CMatrixApp::~CMatrixApp()
{
	for (int i=0; i<anzahl; i++)
		delete matrix[i];
	
	delete [] matrix;
	matrix = 0;
	anzahl = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMatrixApp-Objekt

CMatrixApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMatrixApp Initialisierung

BOOL CMatrixApp::InitInstance()
{
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Gr��e Ihrer fertigen 
	//  ausf�hrbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht ben�tigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMatScEinDoc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster f�r Ein-/Ausgabe
		RUNTIME_CLASS(CMatScEinView));
	AddDocTemplate(pDocTemplate);
	
	CMatrixDlg dlg;
    m_pMainWnd = new CFrameWnd;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
