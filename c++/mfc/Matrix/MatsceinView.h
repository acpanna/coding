// MatScEinView.h : Schnittstelle der Klasse CMatScEinView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATSCEINVIEW_H__C4C4F8EA_5BF3_11D3_8D72_C06F54C10000__INCLUDED_)
#define AFX_MATSCEINVIEW_H__C4C4F8EA_5BF3_11D3_8D72_C06F54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MatScEinDoc.h"

class CMatScEinView : public CScrollView
{
protected: // Nur aus Serialisierung erzeugen
	CMatScEinView();
	DECLARE_DYNCREATE(CMatScEinView)

// Attribute
public:
	CMatScEinDoc* GetDocument();

// Operationen
public:
	bool chk;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMatScEinView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMatScEinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMatScEinView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in MatScEinView.cpp
inline CMatScEinDoc* CMatScEinView::GetDocument()
   { return (CMatScEinDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MATSCEINVIEW_H__C4C4F8EA_5BF3_11D3_8D72_C06F54C10000__INCLUDED_)

extern CEdit *pEdit;
extern CStatic *pStatic;