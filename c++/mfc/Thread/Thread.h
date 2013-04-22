// Thread.h : Haupt-Header-Datei für die Anwendung THREAD
//

#if !defined(AFX_THREAD_H__F62A8B62_6252_11D3_8D72_D06F54C10000__INCLUDED_)
#define AFX_THREAD_H__F62A8B62_6252_11D3_8D72_D06F54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CThreadApp:
// Siehe Thread.cpp für die Implementierung dieser Klasse
//

class CThreadApp : public CWinApp
{
public:
	CThreadApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThreadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CThreadApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THREAD_H__F62A8B62_6252_11D3_8D72_D06F54C10000__INCLUDED_)
