// Fraktale.h : Haupt-Header-Datei f�r die Anwendung FRAKTALE
//

#if !defined(AFX_FRAKTALE_H__10493482_6238_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_FRAKTALE_H__10493482_6238_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CFraktaleApp:
// Siehe Fraktale.cpp f�r die Implementierung dieser Klasse
//

class CFraktaleApp : public CWinApp
{
public:
	CFraktaleApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CFraktaleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CFraktaleApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_FRAKTALE_H__10493482_6238_11D3_8D72_900753C10700__INCLUDED_)
