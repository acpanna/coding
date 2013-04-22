// UpdateMenüView.h : Schnittstelle der Klasse CUpdateMenView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPDATEMENVIEW_H__ABCFEC1B_5E19_11D3_8D72_500C53C10700__INCLUDED_)
#define AFX_UPDATEMENVIEW_H__ABCFEC1B_5E19_11D3_8D72_500C53C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUpdateMenView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CUpdateMenView();
	DECLARE_DYNCREATE(CUpdateMenView)

// Attribute
public:
	CUpdateMenDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CUpdateMenView)
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
	virtual ~CUpdateMenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CUpdateMenView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in UpdateMenüView.cpp
inline CUpdateMenDoc* CUpdateMenView::GetDocument()
   { return (CUpdateMenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_UPDATEMENVIEW_H__ABCFEC1B_5E19_11D3_8D72_500C53C10700__INCLUDED_)
