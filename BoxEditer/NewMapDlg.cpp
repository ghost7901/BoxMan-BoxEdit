// NewMapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxEditer.h"
#include "NewMapDlg.h"


// CNewMapDlg 对话框

IMPLEMENT_DYNAMIC(CNewMapDlg, CDialog)

CNewMapDlg::CNewMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewMapDlg::IDD, pParent)
	, m_iMapWidth(0)
	, m_iMapHeight(0)
{

}

CNewMapDlg::~CNewMapDlg()
{
}

void CNewMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAP_WIDTH, m_iMapWidth);
	DDV_MinMaxInt(pDX, m_iMapWidth, 3, 50);
	DDX_Text(pDX, IDC_MAP_HEIGHT, m_iMapHeight);
	DDV_MinMaxInt(pDX, m_iMapHeight, 3, 30);
}


BEGIN_MESSAGE_MAP(CNewMapDlg, CDialog)
END_MESSAGE_MAP()


// CNewMapDlg 消息处理程序
