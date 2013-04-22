#include <afx.h>
#include <afxtempl.h>
#include <iostream.h>

CArchive & operator>> (CArchive &ar, CList<WORD,WORD> &lst)
{
	lst.Serialize(ar);
	return ar;
}

void main(void)
{
	CList<WORD,WORD>> myList;
	CFile myFile("myList.dat",CFile::modeRead);
	CArchive ar(&myFile, CArchive::load);
	ar >> myList;
	POSITION pos = myList.GetHeadPosition();
	cout << "Eingelesene Liste: ";
	while (pos)
	{
		int n=myList.GetNext(pos);
		cout << n <<' ';
	}
}
