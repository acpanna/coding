// BasDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CBasDlg 

class CBasDlg : public CDialog
{
// Konstruktion
public:
	CBasDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_BASTRANS_DIALOG };
	CEdit	m_bastrans;
	CStatic	m_len;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	
// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	afx_msg void OnPaint();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};


