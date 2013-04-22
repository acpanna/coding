// Hash.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "Hash.h"
#include "HashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashApp

BEGIN_MESSAGE_MAP(CHashApp, CWinApp)
	
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashApp Konstruktion

CHashApp::CHashApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CHashApp-Objekt

CHashApp theApp; //Applikation wird global angelegt
    
                                       
/////////////////////////////////////////////////////////////////////////////
// CHashApp Initialisierung

BOOL CHashApp::InitInstance()
{
	AfxEnableControlContainer();				 //ermoeglicht das Einbinden von ActiveX-Elementen 	

	Enable3dControls();						     // Verwendung der MFC in gem. genutzter DLL	

    CHashDlg hdlg;                               // Erzeugung des Haupt - Dialogfelds
	
	m_pMainWnd = &hdlg;							 //Zuweisung der Adresse des Hauptdialogs an member-Variable
	
	int nResponse = hdlg.DoModal();				 //modaler Dialog wird erzeugt

	return FALSE;								 //Nach Beendigung des Dialogs, wird InitInstance mit FALSE beendet
												 //Das bedeutet, dass das Programm beendet wird.
}
