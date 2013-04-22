// MaueseDoc.h : Schnittstelle der Klasse CMaueseDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAUESEDOC_H__06074119_622F_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_MAUESEDOC_H__06074119_622F_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMaueseDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CMaueseDoc();
	DECLARE_DYNCREATE(CMaueseDoc)

// Attribute
public:
	CObArray m_Maeuse;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMaueseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMaueseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMaueseDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAUESEDOC_H__06074119_622F_11D3_8D72_900753C10700__INCLUDED_)
