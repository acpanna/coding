// StatusSymbol.h : Haupt-Header-Datei f�r die Anwendung STATUSSYMBOL
//

#if !defined(AFX_STATUSSYMBOL_H__21374F74_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_STATUSSYMBOL_H__21374F74_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CStatusSymbolApp:
// Siehe StatusSymbol.cpp f�r die Implementierung dieser Klasse
//

class CStatusSymbolApp : public CWinApp
{
public:
	CStatusSymbolApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStatusSymbolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CStatusSymbolApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_STATUSSYMBOL_H__21374F74_5348_11D3_8D72_002018533DCC__INCLUDED_)
