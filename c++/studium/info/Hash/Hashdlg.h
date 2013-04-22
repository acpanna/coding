// HashDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// CHashDlg Dialogfeld

class CHashDlg : public CDialog
{
// Konstruktion
public:
	CHashDlg(CWnd* pParent = NULL);	// Standard-Konstruktor, kein Parent-Fenster vorhanden
   
// Dialogfelddaten
	enum { IDD = IDD_HASH_DIALOG };	//Zuweisung der IDD
	
	void setStatus(char * text) { m_status.SetWindowText(text); }
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
private:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung

// Implementierung
private:
	HICON m_hIcon;
	bool Empty();
	CStatic m_status;

	virtual BOOL OnInitDialog();

//Reaktionsfunktionen auf verschiedene Nachrichten (z.B. Buttonklick)	
	afx_msg void OnPaint();		//neuzeichnen		
	afx_msg void OnExit();		//beenden
	//Buttons
	afx_msg void OnKeymenge();	
	afx_msg void OnKeyeingabe();
	afx_msg void OnKeyeinlesen();
	afx_msg void OnKeyclear();
	afx_msg void OnBasistrans();
	afx_msg void OnDivrest();
	afx_msg void OnFaltgrenzen();
	afx_msg void OnMittequad();
	afx_msg void OnSchiebefalt();
	afx_msg void OnKeysave();
	afx_msg void OnInfo();

	DECLARE_MESSAGE_MAP()
};



