// ZeitgeberDoc.h : Schnittstelle der Klasse CZeitgeberDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZEITGEBERDOC_H__ABCFEC08_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_ZEITGEBERDOC_H__ABCFEC08_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZeitgeberDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CZeitgeberDoc();
	DECLARE_DYNCREATE(CZeitgeberDoc)

// Attribute
public:
	int m_nSpots;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeitgeberDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZeitgeberDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZeitgeberDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZEITGEBERDOC_H__ABCFEC08_5E19_11D3_8D72_500C53C10700__INCLUDED_)
