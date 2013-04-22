// Zeichnen1.h : Haupt-Header-Datei für die Anwendung ZEICHNEN1
//

#if !defined(AFX_ZEICHNEN1_H__21374F97_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_ZEICHNEN1_H__21374F97_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CZeichnen1App:
// Siehe Zeichnen1.cpp für die Implementierung dieser Klasse
//

class CZeichnen1App : public CWinApp
{
public:
	CZeichnen1App();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeichnen1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CZeichnen1App)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZEICHNEN1_H__21374F97_5348_11D3_8D72_002018533DCC__INCLUDED_)
