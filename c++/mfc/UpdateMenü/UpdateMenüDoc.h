// UpdateMen�Doc.h : Schnittstelle der Klasse CUpdateMenDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPDATEMENDOC_H__ABCFEC19_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_UPDATEMENDOC_H__ABCFEC19_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUpdateMenDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CUpdateMenDoc();
	DECLARE_DYNCREATE(CUpdateMenDoc)

// Attribute
public:

// Operationen
public:

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CUpdateMenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CUpdateMenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CUpdateMenDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_UPDATEMENDOC_H__ABCFEC19_5E19_11D3_8D72_500C53C10700__INCLUDED_)
