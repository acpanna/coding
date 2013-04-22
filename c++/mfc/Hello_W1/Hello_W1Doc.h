// Hello_W1Doc.h : Schnittstelle der Klasse CHello_W1Doc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLO_W1DOC_H__FD59CF48_4691_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_HELLO_W1DOC_H__FD59CF48_4691_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHello_W1Doc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CHello_W1Doc();
	DECLARE_DYNCREATE(CHello_W1Doc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHello_W1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CHello_W1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CHello_W1Doc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_HELLO_W1DOC_H__FD59CF48_4691_11D3_8D72_002018533DCC__INCLUDED_)
