// Hash.h : Haupt-Header-Datei f�r die Anwendung HASH
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
//Abbruch, falls stdafx.h nicht eingebunden wurde!!!

#endif

#include "resource.h"		// Hauptsymbole, werden eingebunden

/////////////////////////////////////////////////////////////////////////////
// CHashApp:
// Siehe Hash.cpp f�r die Implementierung dieser Klasse
//

class CHashApp : public CWinApp //allgemeine Applikationsklasse
{
public:
	CHashApp();
    
// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()	//Nachrichtenschleife wird vordefiniert
};

extern CHashApp theApp;

