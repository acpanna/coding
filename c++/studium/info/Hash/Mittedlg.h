// MitteDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMitteDlg 

class CMitteDlg : public CDialog
{
// Konstruktion
public:
	CMitteDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
private:
	enum { IDD = IDD_MITTE_DIALOG };
	CEdit	m_Mitte;

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


