// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BoxMan.h"

#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CONST BYTE MAP_GRID_SIZE;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_DIFFICULTY, CMainFrame::OnDifficulty)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULTY, CMainFrame::OnUpdateDifficulty)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)	
	ON_NOTIFY(TBN_DROPDOWN,AFX_IDW_TOOLBAR,OnDropDown)
	ON_COMMAND(ID_VIEW_TEXTTIPS, &CMainFrame::OnViewTexttips)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TEXTTIPS, &CMainFrame::OnUpdateViewTexttips)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bTextTips=AfxGetApp()->GetProfileInt("Setting","m_bTextTips",1);
}

CMainFrame::~CMainFrame()
{
	AfxGetApp()->WriteProfileInt("Setting","m_bTextTips",m_bTextTips);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CSplashWnd::ShowSplashScreen(this);
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(0,0,0,160);
	m_wndStatusBar.SetPaneInfo(1,0,0,60);
	m_wndStatusBar.SetPaneInfo(2,0,SBPS_STRETCH,100);
	
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	int i=m_wndToolBar.CommandToIndex(ID_MUSIC);
	DWORD dwStyle = m_wndToolBar.GetButtonStyle(i);
	dwStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonStyle(i, dwStyle);

	//i=m_wndToolBar.CommandToIndex(ID_EDIT_UNDO);
	//dwStyle = m_wndToolBar.GetButtonStyle(i);
	//dwStyle |= TBSTYLE_DROPDOWN;
	//m_wndToolBar.SetButtonStyle(i, dwStyle);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//my
//	m_wndStatusBar.SetPaneText(1,"Thinking...");
	m_wndView.Created();
	//Load icon resource.
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ASSERT(hIcon);
	//Specify new iconfor window .
	SendMessage(WM_SETICON, TRUE, (LPARAM)hIcon);
	CenterWindow();

	//end

	// CG: The following line was added by the Splash Screen component.
	UpdateToolBar();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPEDWINDOW;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
//	cs.dwExStyle =WS_EX_TOPMOST;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::OnDropDown(NMHDR* pNotifyStruct,LRESULT* result)
{
	NMTOOLBAR *pnmtb=(NMTOOLBAR *)pNotifyStruct;
	UINT nID;
	switch(pnmtb->iItem)
	{
	case ID_MUSIC:
		nID=IDR_MENU1;
		break;
	/*case ID_EDIT_UNDO:
		nID=IDR_MENU2;
		break;*/
	default:
		return;
	}

	CRect rc;
	m_wndToolBar.SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	m_wndToolBar.ClientToScreen(&rc);

	CMenu menu;
	VERIFY(menu.LoadMenu(nID));
	CMenu *pPopup=menu.GetSubMenu(0);
	ASSERT(pPopup!=NULL);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL, rc.left, rc.bottom,
						this);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnDifficulty()
{
	CMenu mnuTop;
	mnuTop.LoadMenu(IDR_MENU2);//装入菜单资源
	CMenu *pPopup=mnuTop.GetSubMenu(0);//得到第一个菜单项的指针
	ASSERT_VALID(pPopup);
	CRect rc;
	int nIndex=m_wndToolBar.CommandToIndex(ID_DIFFICULTY);//得到新增按钮的索引
	ASSERT(nIndex>= 0); 

	m_wndToolBar.GetItemRect(nIndex,&rc);//取得按钮的矩形位置
	m_wndToolBar.ClientToScreen(&rc);//将客户区坐标转变为屏幕坐标
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,
		rc.left, rc.bottom,
		this, NULL );//显示弹出式菜单
}

void CMainFrame::OnUpdateDifficulty(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(false);
}

void CMainFrame::UpdateToolBar(bool bRecalc)
{
	for(int i = 0; i < m_wndToolBar.GetCount(); i++)
	{
		UINT id = m_wndToolBar.GetItemID(i);
		CString s;
		if(!s.LoadString(id)) continue;
		int j = s.Find(_T('\n'));
		if(j < 0) continue;
		s = s.Right(s.GetLength() - j - 1);
		m_wndToolBar.SetButtonText(i,s);
	}// Adjust sizes to include text
	CRect rect;
	m_wndToolBar.GetItemRect(0,&rect);
	CSize sizeButton=rect.Size();
	if(!m_bTextTips) sizeButton=CSize(28,24);
	m_wndToolBar.SetSizes(sizeButton,CSize(21,18));
}

void CMainFrame::OnViewTexttips()
{
	m_bTextTips=!m_bTextTips;
	UpdateToolBar();
	ShowControlBar(&m_wndToolBar,TRUE,FALSE);
}

void CMainFrame::OnUpdateViewTexttips(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bTextTips);
}
