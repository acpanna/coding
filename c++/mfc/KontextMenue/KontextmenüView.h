// KontextmenüView.h : Schnittstelle der Klasse CKontextmenView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KONTEXTMENVIEW_H__28066D0A_6228_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_KONTEXTMENVIEW_H__28066D0A_6228_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKontextmenView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CKontextmenView();
	DECLARE_DYNCREATE(CKontextmenView)

// Attribute
public:
	CKontextmenDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CKontextmenView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CKontextmenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CKontextmenView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in KontextmenüView.cpp
inline CKontextmenDoc* CKontextmenView::GetDocument()
   { return (CKontextmenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_KONTEXTMENVIEW_H__28066D0A_6228_11D3_8D72_900753C10700__INCLUDED_)
