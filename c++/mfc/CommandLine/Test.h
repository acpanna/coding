// Test.h : Haupt-Header-Datei f�r die Anwendung TEST
//

#if !defined(AFX_TEST_H__25544662_4B60_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_TEST_H__25544662_4B60_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// Siehe Test.cpp f�r die Implementierung dieser Klasse
//

class My_CCommandLineInfo : public CCommandLineInfo
{
public:
	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
};

class CTestApp : public CWinApp
{
public:
	CTestApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_TEST_H__25544662_4B60_11D3_8D72_002018533DCC__INCLUDED_)
