// Hello_W3Doc.h : Schnittstelle der Klasse CHello_W3Doc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLO_W3DOC_H__D298C6A8_46BC_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_HELLO_W3DOC_H__D298C6A8_46BC_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHello_W3Doc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CHello_W3Doc();
	DECLARE_DYNCREATE(CHello_W3Doc)

// Attribute
public:
    CString m_sDaten;
// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHello_W3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CHello_W3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CHello_W3Doc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_HELLO_W3DOC_H__D298C6A8_46BC_11D3_8D72_002018533DCC__INCLUDED_)
