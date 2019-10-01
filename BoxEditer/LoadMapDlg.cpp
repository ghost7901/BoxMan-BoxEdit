// LoadMapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxEditer.h"
#include "LoadMapDlg.h"


// CLoadMapDlg 对话框

IMPLEMENT_DYNAMIC(CLoadMapDlg, CDialog)

CLoadMapDlg::CLoadMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadMapDlg::IDD, pParent)
	, m_iLoadMapNum(0)
{
	m_iLoadMapNum=1;
}

CLoadMapDlg::~CLoadMapDlg()
{
}

void CLoadMapDlg::DoDataExchange(CDataExchange* pDX)
{
	extern int MAX_MISSION_NUM;
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MAX_NUM, MAX_MISSION_NUM);
	DDX_Text(pDX, IDC_EDIT_LOAD_NUM, m_iLoadMapNum);	
	DDV_MinMaxInt(pDX, m_iLoadMapNum, 1, MAX_MISSION_NUM);
}


BEGIN_MESSAGE_MAP(CLoadMapDlg, CDialog)
END_MESSAGE_MAP()