// Dialog.h : Haupt-Header-Datei f�r die Anwendung DIALOG
//

#if !defined(AFX_DIALOG_H__58E9F615_5D49_11D3_8D72_107B54C10000__INCLUDED_)
#define AFX_DIALOG_H__58E9F615_5D49_11D3_8D72_107B54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDialogApp:
// Siehe Dialog.cpp f�r die Implementierung dieser Klasse
//

class CDialogApp : public CWinApp
{
public:
	CDialogApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDialogApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_DIALOG_H__58E9F615_5D49_11D3_8D72_107B54C10000__INCLUDED_)
