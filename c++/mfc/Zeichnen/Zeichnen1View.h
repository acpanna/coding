// Zeichnen1View.h : Schnittstelle der Klasse CZeichnen1View
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZEICHNEN1VIEW_H__21374F9F_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_ZEICHNEN1VIEW_H__21374F9F_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZeichnen1View : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CZeichnen1View();
	DECLARE_DYNCREATE(CZeichnen1View)

// Attribute
public:
	CZeichnen1Doc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeichnen1View)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZeichnen1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZeichnen1View)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in Zeichnen1View.cpp
inline CZeichnen1Doc* CZeichnen1View::GetDocument()
   { return (CZeichnen1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZEICHNEN1VIEW_H__21374F9F_5348_11D3_8D72_002018533DCC__INCLUDED_)
