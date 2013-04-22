// FraktaleView.h : Schnittstelle der Klasse CFraktaleView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAKTALEVIEW_H__1049348A_6238_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_FRAKTALEVIEW_H__1049348A_6238_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFraktaleView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CFraktaleView();
	DECLARE_DYNCREATE(CFraktaleView)

// Attribute
public:
	CFraktaleDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CFraktaleView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CFraktaleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CFraktaleView)
	afx_msg void OnFraktal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in FraktaleView.cpp
inline CFraktaleDoc* CFraktaleView::GetDocument()
   { return (CFraktaleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_FRAKTALEVIEW_H__1049348A_6238_11D3_8D72_900753C10700__INCLUDED_)
