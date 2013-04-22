// KreiseView.h : Schnittstelle der Klasse CKreiseView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KREISEVIEW_H__0607410A_622F_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KREISEVIEW_H__0607410A_622F_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKreiseView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CKreiseView();
	DECLARE_DYNCREATE(CKreiseView)

// Attribute
public:
	CKreiseDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKreiseView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CKreiseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CKreiseView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in KreiseView.cpp
inline CKreiseDoc* CKreiseView::GetDocument()
   { return (CKreiseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KREISEVIEW_H__0607410A_622F_11D3_8D72_900753C10700__INCLUDED_)
