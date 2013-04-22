// EingabeDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEingabeDlg 

class CEingabeDlg : public CDialog
{
// Konstruktion
public:
	CEingabeDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
private:
	enum { IDD = IDD_EINGABE_DIALOG };
	CListBox	m_ShowList;	//Liste für Schlüsselwerte
	CEdit	m_Eingabe;		//Eingabefeld für neue Schlüsselwerte

private:
	bool paint;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnDblclkListEingabe();

    DECLARE_MESSAGE_MAP()
};


