// Hello_W3.h : Haupt-Header-Datei f�r die Anwendung HELLO_W3
//

#if !defined(AFX_HELLO_W3_H__D298C6A2_46BC_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_HELLO_W3_H__D298C6A2_46BC_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CHello_W3App:
// Siehe Hello_W3.cpp f�r die Implementierung dieser Klasse
//

class CHello_W3App : public CWinApp
{
public:
	CHello_W3App();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHello_W3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CHello_W3App)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_HELLO_W3_H__D298C6A2_46BC_11D3_8D72_002018533DCC__INCLUDED_)
