// Zeitgeber.h : Haupt-Header-Datei f�r die Anwendung ZEITGEBER
//

#if !defined(AFX_ZEITGEBER_H__ABCFEC02_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_ZEITGEBER_H__ABCFEC02_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CZeitgeberApp:
// Siehe Zeitgeber.cpp f�r die Implementierung dieser Klasse
//

class CZeitgeberApp : public CWinApp
{
public:
	CZeitgeberApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeitgeberApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CZeitgeberApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_ZEITGEBER_H__ABCFEC02_5E19_11D3_8D72_500C53C10700__INCLUDED_)
