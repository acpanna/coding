// KontextmenüDoc.h : Schnittstelle der Klasse CKontextmenDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KONTEXTMENDOC_H__28066D08_6228_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KONTEXTMENDOC_H__28066D08_6228_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKontextmenDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CKontextmenDoc();
	DECLARE_DYNCREATE(CKontextmenDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKontextmenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CKontextmenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CKontextmenDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KONTEXTMENDOC_H__28066D08_6228_11D3_8D72_900753C10700__INCLUDED_)
