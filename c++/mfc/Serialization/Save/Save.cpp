#include <afx.h>
#include <afxtempl.h>
#include <iostream.h>

CArchive & operator<< (CArchive &ar, CList<WORD,WORD> &lst)
{
	lst.Serialize(ar);
	return ar;
}

void main(void)
{
	CList<WORD,WORD>> myList;
	cout<<"Liste wird angelegt: ";
	for (int i=0; i<10; i++)
	{
		int n=rand();
		cout <<n<<' ';
		myList.AddTail(n);
	}
	CFile myFile("myList.dat",CFile::modeCreate|CFile::modeWrite);
	CArchive ar(&myFile,CArchive::store);
	ar << myList;
}