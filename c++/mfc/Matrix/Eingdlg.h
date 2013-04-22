#if !defined(AFX_EINGDLG_H__28C2B600_63C6_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_EINGDLG_H__28C2B600_63C6_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EingDlg.h : Header-Datei
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEingDlg 

class CEingDlg : public CDialog
{
// Konstruktion
public:
	CEingDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CEingDlg)
	enum { IDD = IDD_EINGABE_DIALOG };
	CEdit	m_Spalten;
	CEdit	m_Zeilen;
	CEdit	m_Name;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CEingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CEingDlg)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EINGDLG_H__28C2B600_63C6_11D3_8D72_002018533DCC__INCLUDED_

extern bool check;