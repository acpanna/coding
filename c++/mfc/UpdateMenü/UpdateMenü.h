// UpdateMen�.h : Haupt-Header-Datei f�r die Anwendung UPDATEMEN�
//

#if !defined(AFX_UPDATEMEN_H__ABCFEC13_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_UPDATEMEN_H__ABCFEC13_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CUpdateMenApp:
// Siehe UpdateMen�.cpp f�r die Implementierung dieser Klasse
//

class CUpdateMenApp : public CWinApp
{
public:
	CUpdateMenApp();
	bool m_bCheck;

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CUpdateMenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CUpdateMenApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_UPDATEMEN_H__ABCFEC13_5E19_11D3_8D72_500C53C10700__INCLUDED_)
