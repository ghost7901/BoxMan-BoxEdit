// BoxEditer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "BoxEditer.h"
#include "BoxEditerWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int MAP_SMALL_SQUARE_SIZE;

// CBoxEditerApp

BEGIN_MESSAGE_MAP(CBoxEditerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CBoxEditerApp::OnAppAbout)
END_MESSAGE_MAP()


// CBoxEditerApp 构造

CBoxEditerApp::CBoxEditerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBoxEditerApp 对象

CBoxEditerApp theApp;


// CBoxEditerApp 初始化

const CString className = _T("BoxManEditer_Class");

BOOL CBoxEditerApp::InitInstance()
{	
	// 定义和注册窗口
	m_pBoxManEditerWnd = new CBoxEditerWnd();
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hbrBackground = NULL;
	wc.hCursor = NULL;//LoadStandardCursor(IDC_ARROW);
	wc.hIcon = LoadIcon(IDR_MAINFRAME);
	wc.lpszClassName = className;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
	// register the minewnd class
	if (!AfxRegisterClass(&wc)) 
	{
		AfxMessageBox(_T("注册窗口类失败"));
		return FALSE;
	}

	UINT uWidth = MAP_WIDTH*MAP_SMALL_SQUARE_SIZE+10;//地图区域+左右边框宽度
	UINT uHeight = MAP_HEIGHT*MAP_SMALL_SQUARE_SIZE+48;//地图区域+上下边框宽度

	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;
	//创建，显示窗口
	if ( !m_pBoxManEditerWnd->CreateEx( NULL, className, _T("推箱子_地图编辑器"), 
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL) ) 
	{
		AfxMessageBox(_T("创建主窗口失败！"));
		return FALSE;
	}
	
	m_pBoxManEditerWnd->ShowWindow(SW_NORMAL);

	// 绑定窗口为主窗口
	m_pMainWnd = m_pBoxManEditerWnd;

	return TRUE;
}


// CBoxEditerApp 消息处理程序




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CBoxEditerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CBoxEditerApp 消息处理程序

