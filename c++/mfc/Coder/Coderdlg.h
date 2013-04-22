// CoderDlg.h : Header-Datei
//

#if !defined(AFX_CODERDLG_H__A1C5BD44_93B9_11D3_A8F2_E04252C10000__INCLUDED_)
#define AFX_CODERDLG_H__A1C5BD44_93B9_11D3_A8F2_E04252C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCoderDlg Dialogfeld

class CCoderDlg : public CDialog
{
// Konstruktion
public:
	CCoderDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CCoderDlg)
	enum { IDD = IDD_CODER_DIALOG };
	CEdit	m_codegrad;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CCoderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCoder();
	afx_msg void OnDecode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CODERDLG_H__A1C5BD44_93B9_11D3_A8F2_E04252C10000__INCLUDED_)
