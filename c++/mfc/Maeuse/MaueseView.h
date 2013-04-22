// MaueseView.h : Schnittstelle der Klasse CMaueseView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAUESEVIEW_H__0607411B_622F_11D3_8D72_900753C10700__INCLUDED_)
#define AFX_MAUESEVIEW_H__0607411B_622F_11D3_8D72_900753C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMaueseView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CMaueseView();
	DECLARE_DYNCREATE(CMaueseView)

// Attribute
public:
	CMaueseDoc* GetDocument();
	double m_Geschwindigkeit;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMaueseView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMaueseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMaueseView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in MaueseView.cpp
inline CMaueseDoc* CMaueseView::GetDocument()
   { return (CMaueseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAUESEVIEW_H__0607411B_622F_11D3_8D72_900753C10700__INCLUDED_)
