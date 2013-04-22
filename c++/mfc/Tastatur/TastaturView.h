// TastaturView.h : Schnittstelle der Klasse CTastaturView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASTATURVIEW_H__21374F8E_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_TASTATURVIEW_H__21374F8E_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTastaturView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CTastaturView();
	DECLARE_DYNCREATE(CTastaturView)

// Attribute
public:
	CTastaturDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTastaturView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CTastaturView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CTastaturView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in TastaturView.cpp
inline CTastaturDoc* CTastaturView::GetDocument()
   { return (CTastaturDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TASTATURVIEW_H__21374F8E_5348_11D3_8D72_002018533DCC__INCLUDED_)
