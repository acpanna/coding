// AusgDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAusgDlg 

class CAusgDlg : public CDialog
{
// Konstruktion
public:
	CAusgDlg(CWnd* pParent = NULL);   // Standardkonstruktor
   
// Dialogfelddaten
private:
	enum { IDD = IDD_AUSGABE_DIALOG };

	CListBox	m_Overflow;
	CListBox	m_Speicher;
	CStatic  	m_Kollision;

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

