; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BoxMan.h"
LastPage=0

ClassCount=8
Class1=CBoxManApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=5
Resource1=IDD_SELECTMAP
Class2=CChildView
Resource2=IDR_MENU1
Class5=MapSelectDlg
Class6=CMailStatic
Class7=CSplashWnd
Resource3=IDD_LS
Class8=LoadSaveDlg
Resource4=IDD_ABOUTBOX
Resource5=IDR_MAINFRAME

[CLS:CBoxManApp]
Type=0
HeaderFile=BoxMan.h
ImplementationFile=BoxMan.cpp
Filter=N
LastObject=CBoxManApp

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
LastObject=CChildView
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=BoxMan.cpp
ImplementationFile=BoxMan.cpp
Filter=D
LastObject=ID_SAVE
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_MORE,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_MAIL,static,1342308747
Control6=IDC_DYSTATIC,static,1342308352
Control7=IDC_STATIC,static,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_REPLAY
Command2=ID_SELECTMAP
Command3=ID_EDIT_MAP
Command4=ID_LOAD
Command5=ID_SAVE
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_SCENE1
Command9=ID_SCENE2
Command10=ID_SCENE3
Command11=ID_SCENE4
Command12=ID_PROMPT
Command13=ID_SHOW_MOVE_WAY
Command14=ID_MUSIC
Command15=ID_MUSIC1
Command16=ID_MUSIC2
Command17=ID_MUSIC3
Command18=ID_MUSIC4
Command19=ID_MUSIC5
Command20=ID_MUSIC6
Command21=ID_MUSIC7
Command22=ID_MUSIC8
Command23=ID_MUSIC9
Command24=ID_MORE_MUSIC
Command25=ID_PAUSE
Command26=ID_SOUND
Command27=ID_VIEW_TOOLBAR
Command28=ID_VIEW_STATUS_BAR
Command29=ID_HELP_FINDER
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MUSIC1
Command2=ID_SCENE1
Command3=ID_MUSIC2
Command4=ID_SCENE2
Command5=ID_MUSIC3
Command6=ID_SCENE3
Command7=ID_MUSIC4
Command8=ID_SCENE4
Command9=ID_MUSIC5
Command10=ID_MUSIC6
Command11=ID_MUSIC7
Command12=ID_MUSIC8
Command13=ID_MUSIC9
Command14=ID_SOUND
Command15=ID_SELECTMAP
Command16=ID_GAME_REPLAY
Command17=ID_PAUSE
Command18=ID_SHOW_MOVE_WAY
Command19=ID_PROMPT
Command20=ID_HELP
Command21=ID_CONTEXT_HELP
Command22=ID_LOAD
Command23=ID_SAVE
Command24=ID_MUSIC
Command25=ID_PRIOR_MAP
Command26=ID_NEXT_MAP
Command27=ID_EDIT_UNDO
CommandCount=27

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_UNDO
Command2=ID_PRIOR_MAP
Command3=ID_SELECTMAP
Command4=ID_NEXT_MAP
Command5=ID_PROMPT
Command6=ID_SHOW_MOVE_WAY
Command7=ID_SOUND
Command8=ID_MUSIC
Command9=ID_CONTEXT_HELP
Command10=ID_APP_ABOUT
CommandCount=10

[CLS:MapSelectDlg]
Type=0
HeaderFile=MapSelectDlg.h
ImplementationFile=MapSelectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CMailStatic]
Type=0
HeaderFile=MailStatic.h
ImplementationFile=MailStatic.cpp
BaseClass=CStatic
Filter=W
LastObject=CMailStatic
VirtualFilter=WC

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

[DLG:IDD_LS]
Type=1
Class=LoadSaveDlg
ControlCount=6
Control1=IDCANCEL,button,1342275584
Control2=IDC_LS1,button,1342275584
Control3=IDC_LS2,button,1342275584
Control4=IDC_LS3,button,1342275584
Control5=IDC_LS4,button,1342275584
Control6=IDC_LS5,button,1342275584

[DLG:IDD_SELECTMAP]
Type=1
Class=MapSelectDlg
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:LoadSaveDlg]
Type=0
HeaderFile=LoadSaveDlg.h
ImplementationFile=LoadSaveDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MUSIC1
Command2=ID_MUSIC2
Command3=ID_MUSIC3
Command4=ID_MUSIC4
Command5=ID_MUSIC5
Command6=ID_MUSIC6
Command7=ID_MUSIC7
Command8=ID_MUSIC8
Command9=ID_MUSIC9
CommandCount=9

