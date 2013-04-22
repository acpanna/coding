// Hello_W1View.h : Schnittstelle der Klasse CHello_W1View
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLO_W1VIEW_H__FD59CF4A_4691_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_HELLO_W1VIEW_H__FD59CF4A_4691_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHello_W1View : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CHello_W1View();
	DECLARE_DYNCREATE(CHello_W1View)

// Attribute
public:
	CHello_W1Doc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHello_W1View)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CHello_W1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CHello_W1View)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in Hello_W1View.cpp
inline CHello_W1Doc* CHello_W1View::GetDocument()
   { return (CHello_W1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_HELLO_W1VIEW_H__FD59CF4A_4691_11D3_8D72_002018533DCC__INCLUDED_)
