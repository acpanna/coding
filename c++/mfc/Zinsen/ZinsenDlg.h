// ZinsenDlg.h : Header-Datei
//

#if !defined(AFX_ZINSENDLG_H__2FDB9464_4694_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_ZINSENDLG_H__2FDB9464_4694_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZinsenDlg Dialogfeld

class CZinsenDlg : public CDialog
{
// Konstruktion
public:
	CZinsenDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CZinsenDlg)
	enum { IDD = IDD_ZINSEN_DIALOG };
	CEdit	m_laufzeit;
	CEdit	m_zinssatz;
	CEdit	m_startkapital;
	CListBox	m_Listenfeld;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZinsenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CZinsenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnRechnen();
	afx_msg void OnVerlassen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZINSENDLG_H__2FDB9464_4694_11D3_8D72_002018533DCC__INCLUDED_)
