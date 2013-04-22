// ThreadView.h : Schnittstelle der Klasse CThreadView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADVIEW_H__F62A8B6A_6252_11D3_8D72_D06F54C10000__INCLUDED_)
#define AFX_THREADVIEW_H__F62A8B6A_6252_11D3_8D72_D06F54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThreadView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CThreadView();
	DECLARE_DYNCREATE(CThreadView)

// Attribute
public:
	CThreadDoc* GetDocument();
	CWinThread* m_myThread;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThreadView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CThreadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThreadView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ThreadView.cpp
inline CThreadDoc* CThreadView::GetDocument()
   { return (CThreadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THREADVIEW_H__F62A8B6A_6252_11D3_8D72_D06F54C10000__INCLUDED_)
