// SFaltDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSFaltDlg 

class CSFaltDlg : public CDialog
{
// Konstruktion
public:
	CSFaltDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_SCHFALT_DIALOG };
	CStatic	m_len;
	CEdit	m_sfalt;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	
// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	virtual void OnOK();
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
};


