// ZeitgeberView.h : Schnittstelle der Klasse CZeitgeberView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZEITGEBERVIEW_H__ABCFEC0A_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_ZEITGEBERVIEW_H__ABCFEC0A_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZeitgeberView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CZeitgeberView();
	DECLARE_DYNCREATE(CZeitgeberView)

// Attribute
public:
	CZeitgeberDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZeitgeberView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZeitgeberView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZeitgeberView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ZeitgeberView.cpp
inline CZeitgeberDoc* CZeitgeberView::GetDocument()
   { return (CZeitgeberDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZEITGEBERVIEW_H__ABCFEC0A_5E19_11D3_8D72_500C53C10700__INCLUDED_)
