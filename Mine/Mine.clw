; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMineView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Mine.h"
LastPage=0

ClassCount=5
Class1=CMineApp
Class2=CMineDoc
Class3=CMineView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CMineApp]
Type=0
HeaderFile=Mine.h
ImplementationFile=Mine.cpp
Filter=N

[CLS:CMineDoc]
Type=0
HeaderFile=MineDoc.h
ImplementationFile=MineDoc.cpp
Filter=N

[CLS:CMineView]
Type=0
HeaderFile=MineView.h
ImplementationFile=MineView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_RESTART




[CLS:CAboutDlg]
Type=0
HeaderFile=Mine.cpp
ImplementationFile=Mine.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_START
Command2=IDM_RESTART
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

