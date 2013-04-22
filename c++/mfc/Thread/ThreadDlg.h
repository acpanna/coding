// ThreadDoc.h : Schnittstelle der Klasse CThreadDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADDOC_H__F62A8B68_6252_11D3_8D72_D06F54C10000__INCLUDED_)
#define AFX_THREADDOC_H__F62A8B68_6252_11D3_8D72_D06F54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThreadDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CThreadDoc();
	DECLARE_DYNCREATE(CThreadDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThreadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CThreadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThreadDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THREADDOC_H__F62A8B68_6252_11D3_8D72_D06F54C10000__INCLUDED_)
