; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CFraktaleView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Fraktale.h"
LastPage=0

ClassCount=5
Class1=CFraktaleApp
Class2=CFraktaleDoc
Class3=CFraktaleView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CFraktaleApp]
Type=0
HeaderFile=Fraktale.h
ImplementationFile=Fraktale.cpp
Filter=N

[CLS:CFraktaleDoc]
Type=0
HeaderFile=FraktaleDoc.h
ImplementationFile=FraktaleDoc.cpp
Filter=N

[CLS:CFraktaleView]
Type=0
HeaderFile=FraktaleView.h
ImplementationFile=FraktaleView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_FRAKTAL


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Fraktale.cpp
ImplementationFile=Fraktale.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FRAKTAL
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

