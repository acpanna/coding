// MausklickView.h : Schnittstelle der Klasse CMausklickView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAUSKLICKVIEW_H__2554467C_4B60_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_MAUSKLICKVIEW_H__2554467C_4B60_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMausklickView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CMausklickView();
	DECLARE_DYNCREATE(CMausklickView)

// Attribute
public:
	CMausklickDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMausklickView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMausklickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMausklickView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in MausklickView.cpp
inline CMausklickDoc* CMausklickView::GetDocument()
   { return (CMausklickDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAUSKLICKVIEW_H__2554467C_4B60_11D3_8D72_002018533DCC__INCLUDED_)
