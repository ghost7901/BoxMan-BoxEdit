// MapSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BoxMan.h"
#include "MapSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapSelectDlg dialog


MapSelectDlg::MapSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MapSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapSelectDlg)
	m_SelectMap = 0;
	//}}AFX_DATA_INIT
}


void MapSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	extern UINT MAX_MISSION_NUM;
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SelectMap);
	DDV_MinMaxInt(pDX, m_SelectMap, 1, MAX_MISSION_NUM);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_MAX_MISSION_NUM, MAX_MISSION_NUM);
}


BEGIN_MESSAGE_MAP(MapSelectDlg, CDialog)
	//{{AFX_MSG_MAP(MapSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapSelectDlg message handlers

BOOL MapSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_OK.SetIcon(IDI_OK);
	m_OK.AddToolTip(_T("确定"));
	m_OK.SetBtnCursor(IDC_MY_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon(IDI_CANCEL);
	m_Cancel.AddToolTip(_T("取消"));
	m_Cancel.SetBtnCursor(IDC_MY_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
