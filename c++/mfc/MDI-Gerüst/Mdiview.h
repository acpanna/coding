// MDIView.h : Schnittstelle der Klasse CMDIView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIVIEW_H__58E9F60C_5D49_11D3_8D72_107B54C10000__INCLUDED_)
#define AFX_MDIVIEW_H__58E9F60C_5D49_11D3_8D72_107B54C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMDIView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CMDIView();
	DECLARE_DYNCREATE(CMDIView)

// Attribute
public:
	CMDIDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMDIView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in MDIView.cpp
inline CMDIDoc* CMDIView::GetDocument()
   { return (CMDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MDIVIEW_H__58E9F60C_5D49_11D3_8D72_107B54C10000__INCLUDED_)
