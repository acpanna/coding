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
	CListBox	m_ShowList;	//Liste f�r Schl�sselwerte
	CEdit	m_Eingabe;		//Eingabefeld f�r neue Schl�sselwerte

private:
	bool paint;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

// Implementierung
private:
	// Generierte Nachrichtenzuordnungsfunktionen
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnDblclkListEingabe();

    DECLARE_MESSAGE_MAP()
};


