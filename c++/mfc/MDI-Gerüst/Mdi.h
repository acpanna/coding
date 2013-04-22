// MDI.h : Haupt-Header-Datei für die Anwendung MDI
//

#if !defined(AFX_MDI_H__58E9F602_5D49_11D3_8D72_107B54C10000__INCLUDED_)
#define AFX_MDI_H__58E9F602_5D49_11D3_8D72_107B54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMDIApp:
// Siehe MDI.cpp für die Implementierung dieser Klasse
//

class CMDIApp : public CWinApp
{
public:
	CMDIApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CMDIApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MDI_H__58E9F602_5D49_11D3_8D72_107B54C10000__INCLUDED_)
