; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMatScEinDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "matrix.h"
LastPage=0

ClassCount=10
Class1=CEingDlg
Class2=CMainFrame
Class3=CMatrixApp
Class4=CMatrixDlg
Class5=CMatScEinDoc
Class6=CMatScEinView
Class7=CNameDlg
Class8=CPotDlg
Class9=CSkMultDlg
Class10=CWahlDlg

ResourceCount=7
Resource1=IDD_ERGEBNIS_NAME
Resource2=IDD_SKMULT
Resource3=IDD_EINGABE_DIALOG
Resource4=IDD_AUSWAHL_DIALOG
Resource5=IDD_MATRIX_DIALOG
Resource6=IDD_POTENZ
Resource7=IDR_MAINFRAME

[CLS:CEingDlg]
Type=0
BaseClass=CDialog
HeaderFile=EingDlg.h
ImplementationFile=EingDlg.cpp
LastObject=CEingDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMatrixApp]
Type=0
BaseClass=CWinApp
HeaderFile=Matrix.h
ImplementationFile=Matrix.cpp

[CLS:CMatrixDlg]
Type=0
BaseClass=CDialog
HeaderFile=MatrixDlg.h
ImplementationFile=MatrixDlg.cpp

[CLS:CMatScEinDoc]
Type=0
BaseClass=CDocument
HeaderFile=MatScEinDoc.h
ImplementationFile=MatScEinDoc.cpp
LastObject=CMatScEinDoc

[CLS:CMatScEinView]
Type=0
BaseClass=CScrollView
HeaderFile=MatScEinView.h
ImplementationFile=MatScEinView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMatScEinView

[CLS:CNameDlg]
Type=0
BaseClass=CDialog
HeaderFile=NameDlg.h
ImplementationFile=NameDlg.cpp

[CLS:CPotDlg]
Type=0
BaseClass=CDialog
HeaderFile=PotDlg.h
ImplementationFile=PotDlg.cpp

[CLS:CSkMultDlg]
Type=0
BaseClass=CDialog
HeaderFile=SkMultDlg.h
ImplementationFile=SkMultDlg.cpp

[CLS:CWahlDlg]
Type=0
BaseClass=CDialog
HeaderFile=WahlDlg.h
ImplementationFile=WahlDlg.cpp

[DLG:IDD_EINGABE_DIALOG]
Type=1
Class=CEingDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552

[DLG:IDD_MATRIX_DIALOG]
Type=1
Class=CMatrixDlg
ControlCount=14
Control1=IDC_EINGABE,button,1342242816
Control2=IDC_INVERS,button,1342242816
Control3=IDC_ADJUNG,button,1342242816
Control4=IDC_TRANS,button,1342242816
Control5=IDC_SKMULT,button,1342242816
Control6=IDC_DET,button,1342242816
Control7=IDC_MATPOT,button,1342242816
Control8=IDC_MATADD,button,1342242816
Control9=IDC_MATMULT,button,1342242816
Control10=IDC_LADEN,button,1342242816
Control11=IDC_SAVE,button,1342242816
Control12=IDC_AUSGABE,button,1342242816
Control13=IDC_ENDE,button,1342242816
Control14=IDC_LOESCHEN,button,1342242816

[DLG:IDD_ERGEBNIS_NAME]
Type=1
Class=CNameDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[DLG:IDD_POTENZ]
Type=1
Class=CPotDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552

[DLG:IDD_SKMULT]
Type=1
Class=CSkMultDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552

[DLG:IDD_AUSWAHL_DIALOG]
Type=1
Class=CWahlDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST_MATRIX,listbox,1352728835

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_OK
CommandCount=1

