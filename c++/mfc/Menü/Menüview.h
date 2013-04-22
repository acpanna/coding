// Men�View.h : Schnittstelle der Klasse CMenView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENVIEW_H__21374FB0_5348_11D3_8D72_002018533DCC__INCLUDED_)
#define AFX_MENVIEW_H__21374FB0_5348_11D3_8D72_002018533DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMenView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CMenView();
	DECLARE_DYNCREATE(CMenView)

// Attribute
public:
	CMenDoc* GetDocument();

// Operationen
public:

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMenView)
	public:
	virtual void OnDraw(CDC* pDC);  // �berladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMenView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in Men�View.cpp
inline CMenDoc* CMenView::GetDocument()
   { return (CMenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MENVIEW_H__21374FB0_5348_11D3_8D72_002018533DCC__INCLUDED_)
