// Coder.h : Haupt-Header-Datei f�r die Anwendung CODER
//

#if !defined(AFX_CODER_H__A1C5BD42_93B9_11D3_A8F2_E04252C10000__INCLUDED_)
#define AFX_CODER_H__A1C5BD42_93B9_11D3_A8F2_E04252C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CCoderApp:
// Siehe Coder.cpp f�r die Implementierung dieser Klasse
//

class CCoderApp : public CWinApp
{
public:
	CCoderApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCoderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CCoderApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_CODER_H__A1C5BD42_93B9_11D3_A8F2_E04252C10000__INCLUDED_)
