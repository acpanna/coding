// TastaturDoc.h : Schnittstelle der Klasse CTastaturDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASTATURDOC_H__21374F8C_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_TASTATURDOC_H__21374F8C_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTastaturDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CTastaturDoc();
	DECLARE_DYNCREATE(CTastaturDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTastaturDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CTastaturDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CTastaturDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TASTATURDOC_H__21374F8C_5348_11D3_8D72_002018533DCC__INCLUDED_)
