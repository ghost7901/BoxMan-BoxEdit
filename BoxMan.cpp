// BoxMan.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BoxMan.h"

#include "MainFrm.h"
//my
#include "BoxManClass.h"
#include "MailStatic.h"
#include "Splash.h"
#include "BtnST.h"
#include "CreditStatic.h"
//end
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char LENGTH=54;

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp

BEGIN_MESSAGE_MAP(CBoxManApp, CWinApp)
	//{{AFX_MSG_MAP(CBoxManApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp construction

CBoxManApp::CBoxManApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBoxManApp object
CBoxManApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp initialization

BOOL CBoxManApp::InitInstance()
{
		// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();
	
	CWinApp::InitInstance();
	
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("推箱子-菜青虫工作室"));
	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载带有其资源的框架
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_MAXIMIZE);
	pFrame->UpdateWindow();
	// 仅当存在后缀时才调用 DragAcceptFiles，
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp message handlers





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	void SizeWindow();
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CCreditStatic	m_DyStatic;
	CButtonST 	m_More;
	CButtonST	m_OK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	HCURSOR m_holdCursor;
	CMailStatic m_MailStatic;
	bool m_bMax;
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_DYSTATIC, m_DyStatic);
	DDX_Control(pDX, IDC_MORE, m_More);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_STATIC_MAIL, m_MailStatic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	//}}AFX_MSG_MAP
//	ON_WM_CHAR()
END_MESSAGE_MAP()

// App command to run the dialog
void CBoxManApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	m_OK.SetIcon(IDI_OK);
	m_OK.AddToolTip(_T("确定"));
	m_OK.SetBtnCursor(IDC_MY_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_More.SetIcon(IDI_MORE);
	m_More.AddToolTip(_T("更多的..."));
	m_More.SetBtnCursor(IDC_MY_HAND);
	m_More.SetActiveFgColor(RGB(0,0,255));

	m_bMax = false;
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom -= LENGTH;
	MoveWindow(&rc);

	TCHAR *pArrCredit={
		_T("BoxMan\t|"
		"1.2版|"
		"(2002.1-2006.10)||"
		"作者\r|江苏省武进市"
		"|菜青虫工作室|"
		"吴   春||"
		"声明\r"
		"|本软件属于自由免费软件"
		"|您可以任意拷贝"
		"|如有任何意见或建议"
		"|请给我发邮件"
		"|E-mail:  wuchun79@163.com"
		"|您的意见对我很重要!"
		"|||||")};

	//m_DyStatic.SetBkImage(IDB_MAP2);
	m_DyStatic.SubclassDlgItem(IDD_ABOUTBOX,this);
	m_DyStatic.SetCredits(pArrCredit,'|');
	m_DyStatic.SetSpeed(2);
	m_DyStatic.SetColor(BACKGROUND_COLOR, RGB(0,255,200));
	m_DyStatic.SetTransparent();
	m_DyStatic.SetGradient(GRADIENT_RIGHT_DARK);
	m_DyStatic.StartScrolling();


	CRect rect;
	GetWindowRect(&rect);
	rect.bottom-=LENGTH;
	MoveWindow(&rect);
	m_bMax=FALSE;

	//end
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CBoxManApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

void CAboutDlg::OnMore() 
{
	m_More.EnableWindow(FALSE);
	if(m_bMax)
	{
		SizeWindow();
		m_More.SetWindowText(_T("更多的"));
		m_More.AddToolTip(_T("更多的..."));
		
	}
	else
	{
		SizeWindow();
		m_More.SetWindowText(_T("隐藏"));
		m_More.AddToolTip(_T("隐藏"));
		
	}

	m_More.EnableWindow(TRUE);
	m_bMax=!m_bMax;	
}

void CAboutDlg::SizeWindow()
{
	CRect rect;
	GetWindowRect(&rect);
	for(int i=0;i<LENGTH;i++)
	{
		if(m_bMax)
		{
			rect.top+=1;
			rect.bottom-=1;
		}
		else
		{
			rect.top-=1;
			rect.bottom+=1;
		}
		MoveWindow(&rect);
	}
}