// MDIDoc.h : Schnittstelle der Klasse CMDIDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIDOC_H__58E9F60A_5D49_11D3_8D72_107B54C10000__INCLUDED_)
#define AFX_MDIDOC_H__58E9F60A_5D49_11D3_8D72_107B54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMDIDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CMDIDoc();
	DECLARE_DYNCREATE(CMDIDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMDIDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MDIDOC_H__58E9F60A_5D49_11D3_8D72_107B54C10000__INCLUDED_)
