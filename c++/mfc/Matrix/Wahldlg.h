#if !defined(AFX_WAHLDLG_H__28C2B601_63C6_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_WAHLDLG_H__28C2B601_63C6_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WahlDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CWahlDlg 

class CWahlDlg : public CDialog
{
// Konstruktion
public:
	CWahlDlg(CWnd* pParent = NULL);   // Standardkonstruktor
    
// Dialogfelddaten
	//{{AFX_DATA(CWahlDlg)
	enum { IDD = IDD_AUSWAHL_DIALOG };
	CListBox	m_Liste;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CWahlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

private: 
    bool checker;

// Implementierung
protected:
    
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CWahlDlg)
	virtual void OnOK();
	afx_msg void OnDblclkListMatrix();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_WAHLDLG_H__28C2B601_63C6_11D3_8D72_002018533DCC__INCLUDED_
