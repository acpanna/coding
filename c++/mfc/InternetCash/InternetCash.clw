; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CTarif
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "InternetCash.h"

ClassCount=3
Class1=CInternetCashApp
Class2=CInternetCashDlg

ResourceCount=3
Resource2=IDD_INTERNETCASH_DIALOG
Resource1=IDR_MAINFRAME
Class3=CTarif
Resource3=IDD_DIALOG1

[CLS:CInternetCashApp]
Type=0
HeaderFile=InternetCash.h
ImplementationFile=InternetCash.cpp
Filter=N

[CLS:CInternetCashDlg]
Type=0
HeaderFile=InternetCashDlg.h
ImplementationFile=InternetCashDlg.cpp
Filter=D
LastObject=CInternetCashDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_INTERNETCASH_DIALOG]
Type=1
Class=CInternetCashDlg
ControlCount=11
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST1,listbox,1352728961
Control3=IDC_TARIF,button,1342242816
Control4=IDC_CLEAR,button,1342242816
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_HEIKO,button,1342177289
Control10=IDC_FRANK,button,1342177289
Control11=IDOK,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CTarif
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CTarif]
Type=0
HeaderFile=Tarif.h
ImplementationFile=Tarif.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

