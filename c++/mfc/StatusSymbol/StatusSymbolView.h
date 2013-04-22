// StatusSymbolView.h : Schnittstelle der Klasse CStatusSymbolView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSSYMBOLVIEW_H__21374F7C_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_STATUSSYMBOLVIEW_H__21374F7C_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusSymbolView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CStatusSymbolView();
	DECLARE_DYNCREATE(CStatusSymbolView)

// Attribute
public:
	CStatusSymbolDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStatusSymbolView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CStatusSymbolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CStatusSymbolView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in StatusSymbolView.cpp
inline CStatusSymbolDoc* CStatusSymbolView::GetDocument()
   { return (CStatusSymbolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STATUSSYMBOLVIEW_H__21374F7C_5348_11D3_8D72_002018533DCC__INCLUDED_)
