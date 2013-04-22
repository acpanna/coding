#include "stdafx.h"
#include "ThreadFkt.h"
#include <complex>

using namespace std;

CEvent g_Exit;

UINT JuliaMenge(LPVOID hWnd)
{	
	CClientDC dc((CWnd *)hWnd);
	RECT rect;
	((CWnd *)hWnd)->GetClientRect(&rect);
       	
	complex<double> c(-0.012, 0.74);
	for(int i=rect.left; i<rect.right; i++)
		for(int j=rect.top; j<rect.bottom; j++)
		{
			if(WaitForSingleObject(g_Exit,0) == WAIT_OBJECT_0)
				return 1;

			complex<double> x(0.0001*i, 0.0001*j);
			for (int n=0; n<100;n++)
			{
				if(abs(x)>100)
					break;
				x=pow(x,2)+c;
			}
			if(abs(x)<1)
				dc.SetPixel(i,j,RGB(0,0,0));
			else
				dc.SetPixel(i,j,RGB(2*abs(x),abs(x),abs(x)/2));
		}

    AfxEndThread(0);  //nötig wegen m_bAutoDelete = false
	return 0;
}