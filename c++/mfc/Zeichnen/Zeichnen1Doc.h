// Zeichnen1Doc.h : Schnittstelle der Klasse CZeichnen1Doc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZEICHNEN1DOC_H__21374F9D_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_ZEICHNEN1DOC_H__21374F9D_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZeichnen1Doc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CZeichnen1Doc();
	DECLARE_DYNCREATE(CZeichnen1Doc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeichnen1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZeichnen1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZeichnen1Doc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZEICHNEN1DOC_H__21374F9D_5348_11D3_8D72_002018533DCC__INCLUDED_)
