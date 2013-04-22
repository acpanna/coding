// MatScEinDoc.h : Schnittstelle der Klasse CMatScEinDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATSCEINDOC_H__C4C4F8E8_5BF3_11D3_8D72_C06F54C10000__INCLUDED_)
#define AFX_MATSCEINDOC_H__C4C4F8E8_5BF3_11D3_8D72_C06F54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMatScEinDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CMatScEinDoc();
	DECLARE_DYNCREATE(CMatScEinDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMatScEinDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMatScEinDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMatScEinDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MATSCEINDOC_H__C4C4F8E8_5BF3_11D3_8D72_C06F54C10000__INCLUDED_)
