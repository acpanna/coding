// Kreise.h : Haupt-Header-Datei für die Anwendung KREISE
//

#if !defined(AFX_KREISE_H__06074102_622F_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KREISE_H__06074102_622F_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CKreiseApp:
// Siehe Kreise.cpp für die Implementierung dieser Klasse
//

class CKreiseApp : public CWinApp
{
public:
	CKreiseApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKreiseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CKreiseApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KREISE_H__06074102_622F_11D3_8D72_900753C10700__INCLUDED_)
