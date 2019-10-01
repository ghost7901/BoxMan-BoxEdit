// BoxEditer.cpp : ����Ӧ�ó��������Ϊ��
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


// CBoxEditerApp ����

CBoxEditerApp::CBoxEditerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBoxEditerApp ����

CBoxEditerApp theApp;


// CBoxEditerApp ��ʼ��

const CString className = _T("BoxManEditer_Class");

BOOL CBoxEditerApp::InitInstance()
{	
	// �����ע�ᴰ��
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
		AfxMessageBox(_T("ע�ᴰ����ʧ��"));
		return FALSE;
	}

	UINT uWidth = MAP_WIDTH*MAP_SMALL_SQUARE_SIZE+10;//��ͼ����+���ұ߿���
	UINT uHeight = MAP_HEIGHT*MAP_SMALL_SQUARE_SIZE+48;//��ͼ����+���±߿���

	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;
	//��������ʾ����
	if ( !m_pBoxManEditerWnd->CreateEx( NULL, className, _T("������_��ͼ�༭��"), 
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL) ) 
	{
		AfxMessageBox(_T("����������ʧ�ܣ�"));
		return FALSE;
	}
	
	m_pBoxManEditerWnd->ShowWindow(SW_NORMAL);

	// �󶨴���Ϊ������
	m_pMainWnd = m_pBoxManEditerWnd;

	return TRUE;
}


// CBoxEditerApp ��Ϣ�������




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CBoxEditerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CBoxEditerApp ��Ϣ�������

