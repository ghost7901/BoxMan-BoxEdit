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
// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
	
	CWinApp::InitInstance();
	
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("������-����湤����"));
	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ش�������Դ�Ŀ��
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_MAXIMIZE);
	pFrame->UpdateWindow();
	// �������ں�׺ʱ�ŵ��� DragAcceptFiles��
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����	

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
	m_OK.AddToolTip(_T("ȷ��"));
	m_OK.SetBtnCursor(IDC_MY_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_More.SetIcon(IDI_MORE);
	m_More.AddToolTip(_T("�����..."));
	m_More.SetBtnCursor(IDC_MY_HAND);
	m_More.SetActiveFgColor(RGB(0,0,255));

	m_bMax = false;
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom -= LENGTH;
	MoveWindow(&rc);

	TCHAR *pArrCredit={
		_T("BoxMan\t|"
		"1.2��|"
		"(2002.1-2006.10)||"
		"����\r|����ʡ�����"
		"|����湤����|"
		"��   ��||"
		"����\r"
		"|�������������������"
		"|���������⿽��"
		"|�����κ��������"
		"|����ҷ��ʼ�"
		"|E-mail:  wuchun79@163.com"
		"|����������Һ���Ҫ!"
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
		m_More.SetWindowText(_T("�����"));
		m_More.AddToolTip(_T("�����..."));
		
	}
	else
	{
		SizeWindow();
		m_More.SetWindowText(_T("����"));
		m_More.AddToolTip(_T("����"));
		
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