// DivDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDivDlg 

class CDivDlg : public CDialog
{
// Konstruktion
public:
	CDivDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_DIVREST_DIALOG };
	CEdit	m_addressrange;
	CStatic	m_mind2;
	CStatic	m_mind1;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	
// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	afx_msg void OnPaint();
	virtual void OnOK();
	
	DECLARE_MESSAGE_MAP()
};

