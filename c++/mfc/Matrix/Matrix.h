// Matrix.h : Haupt-Header-Datei f�r die Anwendung MATRIX
//

#if !defined(AFX_MATRIX_H__A2739C83_63C1_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_MATRIX_H__A2739C83_63C1_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "MatrixFkt.h"

/////////////////////////////////////////////////////////////////////////////
// CMatrixApp:
// Siehe Matrix.cpp f�r die Implementierung dieser Klasse
//

class CMatrixApp : public CWinApp
{
public:
	CMatrixApp();
	~CMatrixApp();

	int anzahl;
	CMatrix **matrix;

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMatrixApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMatrixApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MATRIX_H__A2739C83_63C1_11D3_8D72_002018533DCC__INCLUDED_)

extern CMatrixApp theApp;
extern char name[256];

extern CMatrix *matrix1;
extern CMatrix *matrix2;
