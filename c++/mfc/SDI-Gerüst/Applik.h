#include <afxwin.h>

class CAnsicht : public CView {

public:
	CAnsicht() {}
	~CAnsicht();
	CAnsicht(CFrameWnd *parent);

protected:
	afx_msg void OnDraw (class CDC *);
};

class CRahmenfenster : public CFrameWnd {

public:
	CRahmenfenster();
	~CRahmenfenster();
};

class CMyApp : public CWinApp {

public:
	virtual BOOL InitInstance();
};