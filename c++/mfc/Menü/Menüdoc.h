// Men�Doc.h : Schnittstelle der Klasse CMenDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENDOC_H__21374FAE_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_MENDOC_H__21374FAE_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMenDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CMenDoc();
	DECLARE_DYNCREATE(CMenDoc)

// Attribute
public:

// Operationen
public:

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMenDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MENDOC_H__21374FAE_5348_11D3_8D72_002018533DCC__INCLUDED_)
