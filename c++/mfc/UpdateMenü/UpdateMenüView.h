// UpdateMen�View.h : Schnittstelle der Klasse CUpdateMenView
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

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CUpdateMenView)
	public:
	virtual void OnDraw(CDC* pDC);  // �berladen zum Zeichnen dieser Ansicht
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
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in UpdateMen�View.cpp
inline CUpdateMenDoc* CUpdateMenView::GetDocument()
   { return (CUpdateMenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_UPDATEMENVIEW_H__ABCFEC1B_5E19_11D3_8D72_500C53C10700__INCLUDED_)
