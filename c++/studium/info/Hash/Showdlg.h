// ShowDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CShowDlg 

class CShowDlg : public CDialog
{
// Konstruktion
public:
	CShowDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_SHOWMENGE_DIALOG };
	CListBox	m_ShowList;

	bool paint;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
};

