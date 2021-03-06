; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHIGHSCORE
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SaoLei.h"
LastPage=0

ClassCount=8
Class1=CSaoLeiApp
Class2=CSaoLeiDoc
Class3=CSaoLeiView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CHIGHSCORE
Resource3=IDD_SIZE
Class7=GAMESIZE
Resource4=IDD_HIGHSCORE
Class8=SETNAME
Resource5=IDD_SETNAME

[CLS:CSaoLeiApp]
Type=0
HeaderFile=SaoLei.h
ImplementationFile=SaoLei.cpp
Filter=N

[CLS:CSaoLeiDoc]
Type=0
HeaderFile=SaoLeiDoc.h
ImplementationFile=SaoLeiDoc.cpp
Filter=N

[CLS:CSaoLeiView]
Type=0
HeaderFile=SaoLeiView.h
ImplementationFile=SaoLeiView.cpp
Filter=C
LastObject=AFX_ID_GAOFEN
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=AFX_ID_GAOFEN




[CLS:CAboutDlg]
Type=0
HeaderFile=SaoLei.cpp
ImplementationFile=SaoLei.cpp
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
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
Command3=AFX_ID_GAOFEN
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_HIGHSCORE]
Type=1
Class=CHIGHSCORE
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FIRST_TIME,static,1342308352
Control6=IDC_FIRST_NAME,static,1342308352
Control7=IDC_STATIC_RANK,static,1342308352
Control8=IDC_SECOND_NAME,static,1342308352
Control9=IDC_SECOND_TIME,static,1342308352
Control10=IDC_THIRD_NAME,static,1342308352
Control11=IDC_THIRD_TIME,static,1342308352

[CLS:CHIGHSCORE]
Type=0
HeaderFile=HIGHSCORE.h
ImplementationFile=HIGHSCORE.cpp
BaseClass=CDialog
Filter=D
LastObject=AFX_ID_GAOFEN
VirtualFilter=dWC

[DLG:IDD_SIZE]
Type=1
Class=GAMESIZE
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_L,edit,1350631552
Control4=IDC_W,edit,1350631552
Control5=IDC_N,edit,1350631552
Control6=IDC_LENGTH,static,1342308352
Control7=IDC_WIDTH,static,1342308352
Control8=IDC_MINE,static,1342308352

[CLS:GAMESIZE]
Type=0
HeaderFile=GAMESIZE.h
ImplementationFile=GAMESIZE.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_GAOFEN

[DLG:IDD_SETNAME]
Type=1
Class=SETNAME
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_WORD,static,1342308352
Control3=IDC_NAME,edit,1350631552

[CLS:SETNAME]
Type=0
HeaderFile=SETNAME.h
ImplementationFile=SETNAME.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

