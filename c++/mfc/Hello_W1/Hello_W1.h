// Hello_W1.h : Haupt-Header-Datei f�r die Anwendung HELLO_W1
//

#if !defined(AFX_HELLO_W1_H__FD59CF42_4691_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_HELLO_W1_H__FD59CF42_4691_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CHello_W1App:
// Siehe Hello_W1.cpp f�r die Implementierung dieser Klasse
//

class CHello_W1App : public CWinApp
{
public:
	CHello_W1App();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHello_W1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CHello_W1App)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_HELLO_W1_H__FD59CF42_4691_11D3_8D72_002018533DCC__INCLUDED_)
