// Kontextmenü.h : Haupt-Header-Datei für die Anwendung KONTEXTMENÜ
//

#if !defined(AFX_KONTEXTMEN_H__28066D02_6228_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KONTEXTMEN_H__28066D02_6228_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CKontextmenApp:
// Siehe Kontextmenü.cpp für die Implementierung dieser Klasse
//

class CKontextmenApp : public CWinApp
{
public:
	CKontextmenApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKontextmenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CKontextmenApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KONTEXTMEN_H__28066D02_6228_11D3_8D72_900753C10700__INCLUDED_)
