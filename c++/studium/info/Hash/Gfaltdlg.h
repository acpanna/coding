// GFaltDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGFaltDlg 

class CGFaltDlg : public CDialog
{
// Konstruktion
public:
	CGFaltDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_GRFALT_DIALOG };
	CStatic	m_len;
	CEdit	m_grfalt;

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


