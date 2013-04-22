// InternetCash.h : Haupt-Header-Datei für die Anwendung INTERNETCASH
//

#if !defined(AFX_INTERNETCASH_H__81BB7A22_75C9_11D3_A8F2_002018533DCC__INCLUDED_)
#define AFX_INTERNETCASH_H__81BB7A22_75C9_11D3_A8F2_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CInternetCashApp:
// Siehe InternetCash.cpp für die Implementierung dieser Klasse
//

class CInternetCashApp : public CWinApp
{
public:
	CInternetCashApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CInternetCashApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CInternetCashApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_INTERNETCASH_H__81BB7A22_75C9_11D3_A8F2_002018533DCC__INCLUDED_)
