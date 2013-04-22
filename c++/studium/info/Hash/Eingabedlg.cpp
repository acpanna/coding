// EingabeDlg.cpp: Implementierungsdatei	
//

#include "stdafx.h"
#include "Hash.h"
#include "HashDlg.h"
#include "EingabeDlg.h"
#include "Hashfkt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEingabeDlg 

CEingabeDlg::CEingabeDlg(CWnd* pParent)
	: CDialog(CEingabeDlg::IDD, pParent)
{
	paint = false;		//ermöglicht das Hinzufuegen der intern geführten Liste an die angezeigte ListBox
}


void CEingabeDlg::DoDataExchange(CDataExchange* pDX)	//Datenaustausch zwischen Dialogfeldelementen und Membervariablen wird ermoeglicht
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_EINGABE, m_ShowList);		
	DDX_Control(pDX, IDC_EDIT_EINGABE, m_Eingabe);
}

BEGIN_MESSAGE_MAP(CEingabeDlg, CDialog)
	
	ON_WM_PAINT()
	ON_LBN_DBLCLK(IDC_LIST_EINGABE, OnDblclkListEingabe)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CEingabeDlg 

void CEingabeDlg::OnOK() 
{
	unsigned int i, j = 0;
	
	char *str;
	char str2[KEYLENGTH + 1];

	i = m_Eingabe.GetWindowTextLength();         // Auslesen der Laenge des eingegebenen Strings

	if (i > KEYLENGTH)						     // Beschraenkung auf max. Schluesselwert - String - Lange	
	{
		MessageBox("Schlüsselwert wurde auf zulässige Länge verkürzt!!!","Achtung...",MB_ICONINFORMATION);
		i = KEYLENGTH;
	}
	
	str = (char *) malloc( (i+1) * sizeof(char) );//Speicherallocation

	if (str == 0)								 //Test, ob genügend Speicher vorhanden
		speicher();
	
	m_Eingabe.GetWindowText(str,i+1);			 // Auslesen des eingegebenen Strings
	
	str[i] = '\0';

	while(str[j] != '\0' && str[j] == ' ')	     // zum ersten Zeichen im String ungleich <space>		
		j++;
    
	if (str[j] == '\0')
	{
		MessageBox("Der eingegebene Schlüsselwert muß mind. ein Zeichen enthalten !","Eingabefehler...",MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	
    i = j;

	for(j = strlen(str);str[j] == '\0'||str[j] == ' ';j--); // zum letzten Zeichen im String ungleich <space>

	str[j+1] = '\0';							 // sprich: fuehrende und nachfolgende Leerstellen werden uebergangen

    j = m_ShowList.FindStringExact(-1, str + i); // Ueberpruefung ob eingegebener Schluesselwert schon vorhanden

	if (j == LB_ERR)							 // Schluesselwert noch nicht vorhanden
	{
		m_ShowList.AddString(str + i);		     // Hinzufuegen des Schluesselwerts an
	    C_xstrlong tmp(str + i);                 // angezeigte CListBox und intern gefuehrte
		eingabe.append(tmp);                     // C_list eingabe
    }
	else								
	{
		m_ShowList.GetText(j, str2);
			
		if (!strcmp(str2, str + i))				 // falls Schluesselwert schon vorhanden (Gross-/Kleinschreibung relevant)
			MessageBox("Schlüsselwert bereits vorhanden !","Achtung...",MB_OK|MB_ICONEXCLAMATION);
		
		else									 // Schluesselwert noch nicht vorhanden (z.B. Unterschied in Gross-/Kleinschreibung)
		{
			m_ShowList.AddString(str + i);		 // Hinzufuegen des Schluesselwerts
	        C_xstrlong tmp(str + i); 
		    eingabe.append(tmp);
		}
	}

	m_Eingabe.SetWindowText("");				 // Loeschen des Eingabefelds
	m_Eingabe.SetFocus();						 // Focus auf Eingabefeld
		
	free(str);
}


void CEingabeDlg::OnPaint() 
{
	CPaintDC dc(this);    
	
	//Im Konstruktor ist paint auf false gesetzt worden
	if (paint == true)
		return;
	//wird nur einmal direkt nach Konstruktoraufruf aufgerufen
	eingabe.output(&m_ShowList);			     //  Hinzufuegen der intern gefuehrten C_list zur angezeigten CListBox
	
    m_Eingabe.SetFocus();						//Eingabefeld erhält den Focus (d.h. Cursor befindet sich im Eingabefeld)

	paint = true;
}


void CEingabeDlg::OnDblclkListEingabe() 
{
    char str[KEYLENGTH + 1];
	int i = m_ShowList.GetCurSel();              // Bei Doppelklick auf Listenelement:
												 // a) Entfernen des Listenelements
	m_ShowList.GetText(i,str);				     // b) Belegung des Eingabefelds mit entferntem Element		
    C_xstrlong it(str);

    if (str[0] != '\0')
	{
		m_ShowList.DeleteString(i);
		eingabe.remove(it);
		m_Eingabe.SetWindowText(str);
	}
}
