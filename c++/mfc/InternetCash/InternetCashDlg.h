// InternetCashDlg.h : Header-Datei
//

#if !defined(AFX_INTERNETCASHDLG_H__81BB7A24_75C9_11D3_A8F2_002018533DCC__INCLUDED_)
#define AFX_INTERNETCASHDLG_H__81BB7A24_75C9_11D3_A8F2_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInternetCashDlg Dialogfeld

class CInternetCashDlg : public CDialog
{
// Konstruktion
public:
	CInternetCashDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CInternetCashDlg)
	enum { IDD = IDD_INTERNETCASH_DIALOG };
	CListBox	m_Listbox;
	CEdit	m_Eingabe;
	CButton m_Heiko;
	CButton m_Frank;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CInternetCashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CInternetCashDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClear();
	afx_msg void OnFrank();
	afx_msg void OnHeiko();
	afx_msg void OnDblclkList1();
	afx_msg void OnTarif();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_INTERNETCASHDLG_H__81BB7A24_75C9_11D3_A8F2_002018533DCC__INCLUDED_)

extern double einwahl, minute;