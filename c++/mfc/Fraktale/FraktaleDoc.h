// FraktaleDoc.h : Schnittstelle der Klasse CFraktaleDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAKTALEDOC_H__10493488_6238_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_FRAKTALEDOC_H__10493488_6238_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFraktaleDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CFraktaleDoc();
	DECLARE_DYNCREATE(CFraktaleDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CFraktaleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CFraktaleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CFraktaleDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_FRAKTALEDOC_H__10493488_6238_11D3_8D72_900753C10700__INCLUDED_)
