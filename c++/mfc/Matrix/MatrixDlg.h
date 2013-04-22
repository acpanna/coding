// MatrixDlg.h : Header-Datei
//

#if !defined(AFX_MATRIXDLG_H__A2739C85_63C1_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_MATRIXDLG_H__A2739C85_63C1_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMatrixDlg Dialogfeld

class CMatrixDlg : public CDialog
{
// Konstruktion
public:
	CMatrixDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMatrixDlg)
	enum { IDD = IDD_MATRIX_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMatrixDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMatrixDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEingabe();
	afx_msg void OnAdjung();
	afx_msg void OnLoeschen();
	afx_msg void OnDet();
	afx_msg void OnInvers();
	afx_msg void OnSkmult();
	afx_msg void OnTrans();
	afx_msg void OnMatpot();
	afx_msg void OnEnde();
	afx_msg void OnAusgabe();
	afx_msg void OnLaden();
	afx_msg void OnSave();
	afx_msg void OnMatadd();
	afx_msg void OnMatmult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MATRIXDLG_H__A2739C85_63C1_11D3_8D72_002018533DCC__INCLUDED_)
