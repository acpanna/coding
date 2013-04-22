; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MDI.h"
LastPage=0

ClassCount=9
Class1=CMDIApp
Class2=CMDIDoc
Class3=CMDIView
Class4=CMainFrame
Class7=CChildFrame
Class9=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MDITYPE

[CLS:CMDIApp]
Type=0
HeaderFile=MDI.h
ImplementationFile=MDI.cpp
Filter=N

[CLS:CMDIDoc]
Type=0
HeaderFile=MDIDoc.h
ImplementationFile=MDIDoc.cpp
Filter=N

[CLS:CMDIView]
Type=0
HeaderFile=MDIView.h
ImplementationFile=MDIView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=MDI.cpp
ImplementationFile=MDI.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command9=ID_APP_ABOUT
CommandCount=9

CommandCount=13

[MNU:IDR_MDITYPE]
Type=1
Class=CMDIView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command31=ID_WINDOW_NEW
Command32=ID_WINDOW_CASCADE
Command33=ID_WINDOW_TILE_HORZ
Command34=ID_WINDOW_ARRANGE
Command36=ID_APP_ABOUT
CommandCount=36

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
CommandCount=21


