// InfoDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInfoDlg 

class CInfoDlg : public CDialog
{
// Konstruktion
public:
	CInfoDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_DIALOG_INFO };
	CListBox	m_info;

	bool paint;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

