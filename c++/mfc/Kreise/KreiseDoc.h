// KreiseDoc.h : Schnittstelle der Klasse CKreiseDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KREISEDOC_H__06074108_622F_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KREISEDOC_H__06074108_622F_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKreiseDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CKreiseDoc();
	DECLARE_DYNCREATE(CKreiseDoc)

// Attribute
public:

// Operationen
public:
	int m_nZaehler;
	CPoint m_Kreise[100];

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKreiseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CKreiseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CKreiseDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KREISEDOC_H__06074108_622F_11D3_8D72_900753C10700__INCLUDED_)
