// FileRelationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxMan.h"
#include "FileRelationDlg.h"


// CFileRelationDlg 对话框

IMPLEMENT_DYNAMIC(CFileRelationDlg, CDialog)

CFileRelationDlg::CFileRelationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileRelationDlg::IDD, pParent)
{

}

CFileRelationDlg::~CFileRelationDlg()
{
}

void CFileRelationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_BXS_RELATION,m_btnBxs);
	DDX_Control(pDX,IDC_BXM_RELATION,m_btnBxm);
	DDX_Control(pDX,IDC_DEL_BXS_RELATION,m_btnDelbxs);
	DDX_Control(pDX,IDC_DEL_BXM_RELATION,m_btnDelbxm);
}


BEGIN_MESSAGE_MAP(CFileRelationDlg, CDialog)
	ON_BN_CLICKED(IDC_BXS_RELATION, &CFileRelationDlg::OnBnClickedBxsRelation)
	ON_BN_CLICKED(IDC_DEL_BXS_RELATION, &CFileRelationDlg::OnBnClickedDelBxsRelation)
	ON_BN_CLICKED(IDC_BXM_RELATION, &CFileRelationDlg::OnBnClickedBxmRelation)
	ON_BN_CLICKED(IDC_DEL_BXM_RELATION, &CFileRelationDlg::OnBnClickedDelBxmRelation)
END_MESSAGE_MAP()


// CFileRelationDlg 消息处理程序

void CFileRelationDlg::OnBnClickedBxsRelation()
{
	HKEY hKey=HKEY_CLASSES_ROOT,hSubKey;
	DWORD nbf=0;
	TCHAR value[90]="bxsfile";
	::RegCreateKeyEx(hKey,".bxs\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	::RegSetValueEx(hSubKey,"",0,REG_SZ,(BYTE *)value,sizeof(value));

	::RegCreateKeyEx(hKey,"bxsfile\\shell\\open\\command\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	TCHAR exeFullPath[MAX_PATH]; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH); 
	strcpy_s(value,exeFullPath);
	TCHAR temp[100];
	strcpy_s(temp,value);
	strcat_s(temp," %l");
	::RegSetValueEx(hSubKey,"",0,REG_SZ,(BYTE *)temp,sizeof(temp));

	::RegCreateKeyEx(hKey,"bxsfile\\DefaultIcon\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	strcat_s(value,",0");
	::RegSetValueEx(hSubKey,"",0,REG_SZ,(BYTE *)value,sizeof(value));

		
	::RegCloseKey(hKey);
}

BOOL CFileRelationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnBxs.SetBtnCursor(IDC_MY_HAND);
	m_btnBxs.SetIcon(IDI_RELATION);
	m_btnBxs.AddToolTip("关联到BoxMan.exe");

	m_btnBxm.SetBtnCursor(IDC_MY_HAND);
	m_btnBxm.SetIcon(IDI_RELATION);
	m_btnBxm.AddToolTip("关联到BoxEdit.exe");

	m_btnDelbxs.SetBtnCursor(IDC_MY_HAND);
	m_btnDelbxs.SetIcon(IDI_DELETE,NULL,16,16);

	m_btnDelbxm.SetBtnCursor(IDC_MY_HAND);
	m_btnDelbxm.SetIcon(IDI_DELETE,NULL,16,16);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFileRelationDlg::OnBnClickedDelBxsRelation()
{
	HKEY hKey=HKEY_CLASSES_ROOT;

	RegDeleteKey(hKey,".bxs\\");
	RegDeleteKey(hKey,"bxsfile\\shell\\open\\command\\");
	RegDeleteKey(hKey,"bxsfile\\shell\\open");
	RegDeleteKey(hKey,"bxsfile\\shell\\");
	RegDeleteKey(hKey,"bxsfile\\DefaultIcon\\");
	RegDeleteKey(hKey,"bxsfile\\");
	
	::RegCloseKey(hKey);
}

void CFileRelationDlg::OnBnClickedBxmRelation()
{
	HKEY hKey=HKEY_CLASSES_ROOT,hSubKey;
	DWORD nbf=0;
	TCHAR value[90]="bxmfile";
	::RegCreateKeyEx(hKey,".bxm\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	::RegSetValueEx(hSubKey,"",0,REG_SZ,(BYTE *)value,sizeof(value));

	::RegCreateKeyEx(hKey,"bxmfile\\shell\\open\\command\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	TCHAR exeFullPath[MAX_PATH]; 
    CString strSysPath; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH); 
    strSysPath=(CString)exeFullPath; 
    int position=strSysPath.ReverseFind('\\'); 
    strSysPath=strSysPath.Left(position+1);
	
	CString strValue=strSysPath+"BoxEditer.exe %l";
	BYTE *p=(BYTE *)(LPTSTR)strValue.GetBuffer();
	::RegSetValueEx(hSubKey,"",0,REG_SZ,p,strValue.GetLength()*sizeof(p));
	strValue.ReleaseBuffer();

	::RegCreateKeyEx(hKey,"bxmfile\\DefaultIcon\\",0,"",REG_OPTION_NON_VOLATILE,KEY_READ|KEY_WRITE,NULL,&hSubKey,&nbf);
	strValue=strSysPath+"BoxEditer.exe,0";
	p=(BYTE *)(LPTSTR)strValue.GetBuffer();
	::RegSetValueEx(hSubKey,"",0,REG_SZ,p,strValue.GetLength()*sizeof(p));
	strValue.ReleaseBuffer();

	::RegCloseKey(hKey);
}

void CFileRelationDlg::OnBnClickedDelBxmRelation()
{
	HKEY hKey=HKEY_CLASSES_ROOT;

	RegDeleteKey(hKey,".bxm\\");
	RegDeleteKey(hKey,"bxmfile\\shell\\open\\command\\");
	RegDeleteKey(hKey,"bxmfile\\shell\\open");
	RegDeleteKey(hKey,"bxmfile\\shell\\");
	RegDeleteKey(hKey,"bxmfile\\DefaultIcon\\");
	RegDeleteKey(hKey,"bxmfile\\");
	
	::RegCloseKey(hKey);
}
