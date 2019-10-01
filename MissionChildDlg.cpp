// CMissionChildDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxMan.h"
#include "MissionChildDlg.h"
#include "MissionManageDlg.h"

extern CONST BYTE MAP_GRID_SIZE;

extern const char MAP_WALL;
extern const char MAP_OUTSIDE;
extern const char MAP_DESTINATION;
extern const char MAP_BOX;
extern const char MAP_MAN;
extern const char MAP_BOX_AT_DESTINATION;
extern const char MAP_MAN_AT_DESTINATION;
extern const char MAP_ROAD;

extern const char WALLB;        //墙图片在IDB_MAP中的索引
extern const char NULLWALLB;    //墙内通路图片在IDB_MAP中的索引
extern const char NULLB;        //墙外图片在IDB_MAP中的索引
extern const char BOXB;         //不在目的地的BOX在IDB_MAP中的索引
extern const char BOXATPOINTB;  //在目的地的BOX在IDB_MAP中的索引
extern const char POINTB;       //DESTINATION在IDB_MAP中的索引
extern const char MANBD1;       //MAN向下的图片1在IDB_MAP中的索引

extern struct PaintStruct g_MapData;

// CMissionChildDlg 对话框

IMPLEMENT_DYNAMIC(CMissionChildDlg, CDialog)

CMissionChildDlg::CMissionChildDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMissionChildDlg::IDD, pParent)
{
}

CMissionChildDlg::~CMissionChildDlg()
{
}

void CMissionChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MISSION, m_ListMission);
	DDX_Control(pDX, IDC_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_PREVIEW, m_btnPreview);
	DDX_Control(pDX, IDC_UP, m_btnUp);
	DDX_Control(pDX, IDC_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_MAP_PATH, m_MapPath);
}

BEGIN_MESSAGE_MAP(CMissionChildDlg, CDialog)
	ON_BN_CLICKED(IDC_OPEN, &CMissionChildDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_PREVIEW, &CMissionChildDlg::OnBnClickedPreview)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MISSION, &CMissionChildDlg::OnNMDblclkListMission)
	ON_BN_CLICKED(IDC_DELETE, &CMissionChildDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SAVE, &CMissionChildDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_UP, &CMissionChildDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_DOWN, &CMissionChildDlg::OnBnClickedDown)
END_MESSAGE_MAP()

// CMissionChildDlg 消息处理程序

BOOL CMissionChildDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ListMission.InsertColumn(0,"关卡");
	m_ListMission.InsertColumn(1,"宽度");
	m_ListMission.InsertColumn(2,"高度");
	m_ListMission.InsertColumn(3,"箱子数");
	m_ListMission.InsertColumn(4,"未到位箱子");
	m_ListMission.InsertColumn(5,"");

	m_ListMission.SetColumnWidth(0,36);
	m_ListMission.SetColumnWidth(1,36);
	m_ListMission.SetColumnWidth(2,36);
	m_ListMission.SetColumnWidth(3,48);
	m_ListMission.SetColumnWidth(4,72);
	m_ListMission.SetColumnWidth(5,0);

	//给列表加上表格
	LONG lStyle = m_ListMission.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
    lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
    m_ListMission.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,(LPARAM)lStyle);

	//设置按钮图标,提示,指针
	m_btnOpen.SetIcon(IDI_OPEN,0,16,16);
	m_btnOpen.SetBtnCursor(IDC_MY_HAND);
	m_btnOpen.AddToolTip("打开");

	m_btnDelete.SetIcon(IDI_DELETE,0,16,16);
	m_btnDelete.SetBtnCursor(IDC_MY_HAND);
	m_btnDelete.AddToolTip("删除");

	m_btnSave.SetIcon(IDI_SAVE,0,16,16);
	m_btnSave.SetBtnCursor(IDC_MY_HAND);
	m_btnSave.AddToolTip("保存");

	m_btnPreview.SetIcon(IDI_PREVIEW,0,16,16);
	m_btnPreview.SetBtnCursor(IDC_MY_HAND);
	m_btnPreview.AddToolTip("预览");

	m_btnUp.SetIcon(IDI_UP,0,16,16);
	m_btnUp.SetBtnCursor(IDC_MY_HAND);
	m_btnUp.AddToolTip("上移");

	m_btnDown.SetIcon(IDI_DOWN,0,16,16);
	m_btnDown.SetBtnCursor(IDC_MY_HAND);
	m_btnDown.AddToolTip("下移");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CMissionChildDlg::ReadMission(CString Name)
{
	SetFileName(Name);
	int iMaxMission=GetIntValue("FileInfo","MaxMission");
	if(iMaxMission==0) return FALSE;

	m_ListMission.SetRedraw(FALSE);
    
	m_ListMission.DeleteAllItems();

	CString strMission,strTemp;
	for(int i=0;i<iMaxMission;i++)
	{
		MSG msg;
		while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		strMission.Format("%d",i+1);
		m_ListMission.InsertItem(i,strMission);

		strMission="M"+strMission;

		strTemp=GetStringValue(strMission,"Width");
		m_ListMission.SetItemText(i,1,strTemp);

		strTemp=GetStringValue(strMission,"Height");
		m_ListMission.SetItemText(i,2,strTemp);

		strTemp=GetStringValue(strMission,"Map");
		int iNumberOfAtDestinationBox=0,iNumberOfNotAtDestinationBox=0;
		for(int j=0;j<strTemp.GetLength();j++)
		{
			if(strTemp[j]==MAP_BOX)
				iNumberOfNotAtDestinationBox++;		
			else if(strTemp[j]==MAP_BOX_AT_DESTINATION)
				iNumberOfAtDestinationBox++;
		}
		strTemp.Format("%d",iNumberOfNotAtDestinationBox+iNumberOfAtDestinationBox);
		m_ListMission.SetItemText(i,3,strTemp);
		strTemp.Format("%d",iNumberOfNotAtDestinationBox);
		m_ListMission.SetItemText(i,4,strTemp);
	}

	m_ListMission.SetRedraw(TRUE);
	m_ListMission.Invalidate();
	m_ListMission.UpdateWindow();

	return TRUE;
}

void CMissionChildDlg::OnBnClickedOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,"BoxMan地图文件(*.bxm)|*bxm||");
	dlg.m_ofn.lpstrTitle="打开地图文件";
	if(dlg.DoModal()==IDOK)
	{
		if(!ReadMission(dlg.GetPathName()))
			MessageBox("读取地图出错,请打开BoxMan地图文件!","错误",MB_ICONERROR|MB_OK);
		else
			m_MapPath.SetWindowText(dlg.GetPathName());
	}
}

void CMissionChildDlg::OnBnClickedPreview()
{	
	//得到选择的ListCtrl行索引
	int iSelCol=static_cast<int>(m_ListMission.SendMessage(LVM_GETNEXTITEM,(WPARAM)-1,MAKELPARAM(LVNI_ALL|LVNI_SELECTED,0)));
	if(iSelCol==-1) 
	{
		MessageBox("请先打开文件并选中一行!");
		return;
	}

	//读取地图信息
	CIni srcINI;
	CString strSrcFile=m_ListMission.GetItemText(iSelCol,5);
	if(strSrcFile.IsEmpty())
		srcINI.SetFileName(GetFileName());
	else
		srcINI.SetFileName(strSrcFile);

	CString strMission=m_ListMission.GetItemText(iSelCol,0);
	CString strTemp="M"+strMission;

	g_MapData.strMap=srcINI.GetStringValue(strTemp,"Map");
	g_MapData.Width=srcINI.GetIntValue(strTemp,"Width");
	g_MapData.Height=srcINI.GetIntValue(strTemp,"Height");


	//将地图信息绘入CBitmap
	CClientDC dc(g_MapData.pWnd);
	CDC mapDC;
	mapDC.CreateCompatibleDC(&dc);
	CBitmap tB;
	tB.LoadBitmap(IDB_MAP1);
	CBitmap *pOB1=mapDC.SelectObject(&tB);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap *pOB2=memDC.SelectObject(&g_MapData.Bmp);

	int i=0,index;
	for(int y=0;y<g_MapData.Height;y++)
		for(int x=0;x<g_MapData.Width;x++)
		{
			if(g_MapData.strMap[i]==MAP_WALL)
				index=WALLB;
			else if(g_MapData.strMap[i]==MAP_ROAD)
				index=NULLWALLB;
			else if(g_MapData.strMap[i]==MAP_OUTSIDE)
				index=NULLB;
			else if(g_MapData.strMap[i]==MAP_DESTINATION)
				index=POINTB;
			else if(g_MapData.strMap[i]==MAP_BOX)
				index=BOXB;
			else if(g_MapData.strMap[i]==MAP_MAN)
				index=MANBD1;
			else if(g_MapData.strMap[i]==MAP_BOX_AT_DESTINATION)
				index=BOXATPOINTB;
			else if(g_MapData.strMap[i]==MAP_MAN_AT_DESTINATION)
				index=7;
			else
				g_MapData.pWnd->MessageBox("地图格式错误!","错误",MB_ICONERROR | MB_OK);

			memDC.BitBlt(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE,MAP_GRID_SIZE,MAP_GRID_SIZE,&mapDC,index*MAP_GRID_SIZE,0,SRCCOPY);

			i++;
		}

	dc.BitBlt(0,0,g_MapData.Width*MAP_GRID_SIZE,g_MapData.Height*MAP_GRID_SIZE,&memDC,0,0,SRCCOPY);

	mapDC.SelectObject(pOB1);
	memDC.SelectObject(pOB2);


	//重置窗口大小并显示
	strTemp="预览( Round - "+strMission+" )";
	g_MapData.pWnd->SetWindowText(strTemp);
	CRect rcWindow;
	GetParent()->GetParent()->GetWindowRect(&rcWindow);
	g_MapData.pWnd->SetWindowPos(NULL,
		rcWindow.right,
		rcWindow.top,
		30*g_MapData.Width+GetSystemMetrics(SM_CXBORDER)*2,
		30*g_MapData.Height+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYBORDER)*2,
		NULL);
	g_MapData.pWnd->ShowWindow(SW_SHOW);
	g_MapData.pWnd->UpdateWindow();

	SetFocus();
}

void CMissionChildDlg::OnNMDblclkListMission(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedPreview();
	*pResult = 0;
}

void CMissionChildDlg::OnBnClickedDelete()
{
	int iSelCol;
	while((iSelCol=m_ListMission.GetNextItem(-1,LVIS_SELECTED))!=-1)
		m_ListMission.DeleteItem(iSelCol);
}

void CMissionChildDlg::OnBnClickedSave()
{		
	int iMaxMission=m_ListMission.GetItemCount();
	if(iMaxMission==-1) return;
	
	CStdioFile file(GetFileName()+".tmp",CStdioFile::modeCreate);
	file.Close();
	CIni SrcINI,DesINI;//temp;
	DesINI.SetFileName(GetFileName()+".tmp");
	
	TCHAR cbMax[10];
	::wsprintf(cbMax,"%d",iMaxMission);
	DesINI.SetValue("FileInfo","MaxMission",cbMax);

	CString strOldMission,strNewMission,strSrcFile;
	for(int i=0;i<iMaxMission;i++)
	{
		strSrcFile=m_ListMission.GetItemText(i,5);
		if(strSrcFile.IsEmpty())
			SrcINI.SetFileName(GetFileName());
		else
			SrcINI.SetFileName(strSrcFile);

		strOldMission="M"+m_ListMission.GetItemText(i,0);
		strNewMission.Format("M%d",i+1);

		DesINI.SetValue(strNewMission,"Width",SrcINI.GetStringValue(strOldMission,"Width"));
		DesINI.SetValue(strNewMission,"Height",SrcINI.GetStringValue(strOldMission,"Height"));
		DesINI.SetValue(strNewMission,"Map",SrcINI.GetStringValue(strOldMission,"Map"));
	}

	DeleteFile(GetFileName());
	rename(DesINI.GetFileName(),GetFileName());

	ReadMission(GetFileName());
}

void CMissionChildDlg::OnBnClickedUp()
{
	int iSelCol=m_ListMission.GetNextItem(-1,LVIS_SELECTED);
	if(m_ListMission.GetItemCount()==0)
	{
		MessageBox("请先打开文件!");
		return;
	}
	else if(iSelCol==-1)
	{
		MessageBox("请先选中一行");
		return;
	}
	else if(iSelCol==0)
	{
		MessageBox("已经位于第一行!");
		return;
	}

	CString tempFild[5];
	for(int i=0;i<5;i++) tempFild[i]=m_ListMission.GetItemText(iSelCol,i);

	m_ListMission.DeleteItem(iSelCol);
	m_ListMission.InsertItem(iSelCol-1,tempFild[0]);
	for(int i=1;i<5;i++) m_ListMission.SetItemText(iSelCol-1,i,tempFild[i]);

	UINT flag=LVIS_SELECTED | LVIS_FOCUSED;
	m_ListMission.SetItemState(iSelCol-1,flag,flag);
}

void CMissionChildDlg::OnBnClickedDown()
{
	int iSelCol=m_ListMission.GetNextItem(-1,LVIS_SELECTED);
	if(m_ListMission.GetItemCount()==0)
	{
		MessageBox("请先打开文件!");
		return;
	}
	else if(iSelCol==-1)
	{
		MessageBox("请先选中一行");
		return;
	}
	else if(iSelCol==m_ListMission.GetItemCount()-1)
	{
		MessageBox("已经位于最后一行!");
		return;
	}

	CString tempFild[5];
	for(int i=0;i<5;i++) tempFild[i]=m_ListMission.GetItemText(iSelCol,i);

	m_ListMission.DeleteItem(iSelCol);
	m_ListMission.InsertItem(iSelCol+1,tempFild[0]);
	for(int i=1;i<5;i++) m_ListMission.SetItemText(iSelCol+1,i,tempFild[i]);

	UINT flag=LVIS_SELECTED | LVIS_FOCUSED;
	m_ListMission.SetItemState(iSelCol+1,flag,flag);
}

void CMissionChildDlg::OnOK()
{
}

void CMissionChildDlg::OnCancel()
{
}

int CMissionChildDlg::UnSelectedAll()
{
	//记录选中的第一行
	int iResult=m_ListMission.GetNextItem(-1,LVIS_SELECTED);
	if(iResult==-1) iResult=m_ListMission.GetItemCount();

	//取消所有选中的行
	POSITION pos=m_ListMission.GetFirstSelectedItemPosition();
	while(pos!=NULL)
	{
		int iSel=m_ListMission.GetNextSelectedItem(pos);
		m_ListMission.SetItemState(iSel,0,LVIS_SELECTED);
	}

	return iResult;
}

//CMyHeaderCtrl 类实现
const int HIDE_COLUMN=5;

BEGIN_MESSAGE_MAP(CMyHeaderCtrl,CHeaderCtrl)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

CMyHeaderCtrl::CMyHeaderCtrl()
{
}

CMyHeaderCtrl::~CMyHeaderCtrl()
{
}

BOOL CMyHeaderCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	NMHDR *pnmh=(NMHDR *)lParam;
	if(pnmh->code==HDN_BEGINTRACKA || pnmh->code==HDN_BEGINTRACKW) 
		return *pLResult=TRUE;

	return CHeaderCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

BOOL CMyHeaderCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return TRUE;
}

void CMyHeaderCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CHeaderCtrl::OnLButtonDblClk(nFlags, point);
}

//CMyListCtrl 类实现
CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}

void CMyListCtrl::PreSubclassWindow()
{
	ASSERT(GetStyle() & LVS_REPORT);
	
	CListCtrl::PreSubclassWindow();
	VERIFY(m_ctlHeader.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd()));
}
