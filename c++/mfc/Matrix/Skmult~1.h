#if !defined(AFX_SKMULTDLG_H__D55E5240_63E7_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_SKMULTDLG_H__D55E5240_63E7_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkMultDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSkMultDlg 

class CSkMultDlg : public CDialog
{
// Konstruktion
public:
	CSkMultDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSkMultDlg)
	enum { IDD = IDD_SKMULT };
	CEdit	m_Skalar;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSkMultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSkMultDlg)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SKMULTDLG_H__D55E5240_63E7_11D3_8D72_002018533DCC__INCLUDED_
