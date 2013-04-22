#if !defined(AFX_TARIF_H__81BB7A2D_75C9_11D3_A8F2_002018533DCC__INCLUDED_)
#define AFX_TARIF_H__81BB7A2D_75C9_11D3_A8F2_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tarif.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTarif 

class CTarif : public CDialog
{
// Konstruktion
public:
	CTarif(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CTarif)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_Minute;
	CEdit	m_Einwahl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CTarif)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CTarif)
	afx_msg void OnPaint();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_TARIF_H__81BB7A2D_75C9_11D3_A8F2_002018533DCC__INCLUDED_
