// MainFrm.cpp : CBoxEditerWnd 类的实现
//

#include "stdafx.h"
#include "BoxEditer.h"
#include "LoadMapDlg.h"
#include "NewMapDlg.h"

#include "BoxEditerWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int MAP_WIDTH; //=                16;
extern int MAP_HEIGHT;  // =             14;
extern int MAP_SMALL_SQUARE_SIZE; // =   20;

// CBoxEditerWnd

IMPLEMENT_DYNAMIC(CBoxEditerWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(CBoxEditerWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_MENU_DRAW_WALL, &CBoxEditerWnd::OnMenuDrawWall)
	ON_COMMAND(ID_MENU_DRAW_DESTINATION, &CBoxEditerWnd::OnMenuDrawDestination)
	ON_COMMAND(ID_MENU_DRAW_BOX, &CBoxEditerWnd::OnMenuDrawBox)
	ON_COMMAND(ID_MENU_DRAW_BOX_AT_DESTINATION, &CBoxEditerWnd::OnMenuDrawBoxAtDestination)
	ON_COMMAND(ID_MENU_DRAW_MAN, &CBoxEditerWnd::OnMenuDrawMan)
	ON_COMMAND(ID_MENU_DRAW_MAN_AT_DESTINATION, &CBoxEditerWnd::OnMenuDrawManAtDestination)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_WALL, &CBoxEditerWnd::OnUpdateMenuDrawWall)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_DESTINATION, &CBoxEditerWnd::OnUpdateMenuDrawDestination)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_BOX, &CBoxEditerWnd::OnUpdateMenuDrawBox)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_BOX_AT_DESTINATION, &CBoxEditerWnd::OnUpdateMenuDrawBoxAtDestination)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_MAN, &CBoxEditerWnd::OnUpdateMenuDrawMan)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_MAN_AT_DESTINATION, &CBoxEditerWnd::OnUpdateMenuDrawManAtDestination)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_DRAW_OUTSIDE, &CBoxEditerWnd::OnMenuDrawOutside)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_OUTSIDE, &CBoxEditerWnd::OnUpdateMenuDrawOutside)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_MENU_NEW_MAP, &CBoxEditerWnd::OnMenuNewMap)
	ON_COMMAND(ID_MENU_LOAD_MAP, &CBoxEditerWnd::OnMenuLoadMap)
	ON_COMMAND(ID_MENU_SAVE_MAP, &CBoxEditerWnd::OnMenuSaveMap)
//	ON_WM_CHAR()
END_MESSAGE_MAP()

// CBoxEditerWnd 构造/析构

CBoxEditerWnd::CBoxEditerWnd()
{
	m_NowSelect=0;
	m_bMouseDown=FALSE;
}

CBoxEditerWnd::~CBoxEditerWnd()
{
}


int CBoxEditerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//创建工具栏	
	if (CreateExToolBar() == -1 )
	{
		MessageBox(_T("创建工具栏失败"));
	}

	return 0;
}

/*******************************************************************************************************
函数名 : CreateExToolBar
描  述 : 创建工具条
参  数 : 无
返回值 : BOOL 返回TRUE表示创建成功,返回FALSE表示创建失败
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月24日 21:11:07
*******************************************************************************************************/

BOOL CBoxEditerWnd::CreateExToolBar(void)
{
	CImageList img;
	CString str;
	
	if (!m_wndToolBar.CreateEx(this))
	{
		return FALSE;
	}
	
	//设置按钮的宽度和长度
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	//改变属性
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | 
								TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
	//设置按钮数为6
	m_wndToolBar.SetButtons(NULL,7);	

	// 2. 添加图像
	//设置"热/hot"状态的的位图
	img.Create(28, 28, ILC_COLOR8|ILC_MASK,2,2);
	img.SetBkColor(RGB(0, 0, 102));
	//顺序增添按键的图标
	img.Add(AfxGetApp()->LoadIcon(IDI_WALL));
	img.Add(AfxGetApp()->LoadIcon(IDI_DESTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDI_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDI_BOX_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_OUTSIDE));
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();	
	//设置"冷/cold"状态的位图
	img.Create(26, 26, ILC_COLOR8|ILC_MASK, 2,2);
	img.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//顺序增添按键的图标
	img.Add(AfxGetApp()->LoadIcon(IDI_WALL));
	img.Add(AfxGetApp()->LoadIcon(IDI_DESTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDI_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDI_BOX_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_OUTSIDE));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

	//3. 设置文字  
	m_wndToolBar.SetButtonInfo(0, ID_MENU_DRAW_WALL, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, _T("围墙"));	

	m_wndToolBar.SetButtonInfo(1, ID_MENU_DRAW_DESTINATION, TBSTYLE_BUTTON,1);
	m_wndToolBar.SetButtonText(1, _T("目的点"));
	
	m_wndToolBar.SetButtonInfo(2, ID_MENU_DRAW_BOX, TBSTYLE_BUTTON,2);
	m_wndToolBar.SetButtonText(2, _T("箱子"));

	m_wndToolBar.SetButtonInfo(3, ID_MENU_DRAW_BOX_AT_DESTINATION, TBSTYLE_BUTTON,3);
	m_wndToolBar.SetButtonText(3, _T("就位箱"));

	m_wndToolBar.SetButtonInfo(4, ID_MENU_DRAW_MAN, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonText(4, _T("搬运工"));

	m_wndToolBar.SetButtonInfo(5, ID_MENU_DRAW_MAN_AT_DESTINATION, TBSTYLE_BUTTON, 5);
	m_wndToolBar.SetButtonText(5, _T("就位人"));

	m_wndToolBar.SetButtonInfo(6, ID_MENU_DRAW_OUTSIDE, TBSTYLE_BUTTON, 6);
	m_wndToolBar.SetButtonText(6, _T("擦除"));

	CRect rectToolBar;
	//得到按钮的大小
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	//设置按钮的大小
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(26,26));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//允许停靠
	EnableDocking(CBRS_ALIGN_ANY);
	//漂浮停靠
	CPoint pt(GetSystemMetrics(SM_CXSCREEN)/2+100,GetSystemMetrics(SM_CYSCREEN)/3+100);
	FloatControlBar(&m_wndToolBar,pt);

	return TRUE;
}

void CBoxEditerWnd::OnPaint() 
{
	
	CPaintDC dc(this);    // 用以屏幕显示的设备
	CDC dcMemory;  // 内存设备
	
	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	if (!dc.IsPrinting()) 
	{
		// 与dc设备兼容
		if (dcMemory.CreateCompatibleDC(&dc))
		{	
			// 使得bitmap与实际显示的设备兼容
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right, m_rcClient.bottom))
			{
				// 内存设备选择物件－位图
				dcMemory.SelectObject(&bitmap);
				
				//绘制地图		
				m_BoxEdit.DrawMap(&dcMemory);

				//绘制鼠标跟随图标	
				int x = m_MousePoint.x/MAP_SMALL_SQUARE_SIZE;
				int y = m_MousePoint.y/MAP_SMALL_SQUARE_SIZE;
				//if(m_NowSelect)m_BoxEdit.DrawMouseCursor(x,y,m_NowSelect,&dcMemory);
				
				
				// 将内存设备的内容拷贝到实际屏幕显示的设备
				dc.BitBlt(m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom, &dcMemory, 0, 0, SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}	
}
void CBoxEditerWnd::OnMenuDrawWall()
{
	m_NowSelect=MAP_WALL;
	SetCursor(AfxGetApp()->LoadCursor(IDC_OUTSIDE));
}

void CBoxEditerWnd::OnMenuDrawDestination()
{
	m_NowSelect=MAP_DESTINATION;
}

void CBoxEditerWnd::OnMenuDrawBox()
{
	m_NowSelect=MAP_BOX;
}

void CBoxEditerWnd::OnMenuDrawBoxAtDestination()
{
	m_NowSelect=MAP_BOX_AT_DESTINATION;
}

void CBoxEditerWnd::OnMenuDrawMan()
{
	m_NowSelect=MAP_MAN;
}

void CBoxEditerWnd::OnMenuDrawManAtDestination()
{
	m_NowSelect=MAP_MAN_AT_DESTINATION;
}

void CBoxEditerWnd::OnMenuDrawOutside()
{
	m_NowSelect=MAP_OUTSIDE;
}

void CBoxEditerWnd::OnUpdateMenuDrawWall(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_WALL);
}

void CBoxEditerWnd::OnUpdateMenuDrawDestination(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_DESTINATION);
}

void CBoxEditerWnd::OnUpdateMenuDrawBox(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_BOX);
}

void CBoxEditerWnd::OnUpdateMenuDrawBoxAtDestination(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_BOX_AT_DESTINATION);
}

void CBoxEditerWnd::OnUpdateMenuDrawMan(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_MAN);
}

void CBoxEditerWnd::OnUpdateMenuDrawManAtDestination(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_MAN_AT_DESTINATION);
}

void CBoxEditerWnd::OnUpdateMenuDrawOutside(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_NowSelect==MAP_OUTSIDE);
}

void CBoxEditerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_NowSelect==0) return;
	int x,y;
	//标识鼠标被按下
	m_bMouseDown = TRUE;
	//捕获鼠标
	SetCapture();
	//获取鼠标的位置并计算出在地图相应的方块位置
	m_MousePoint = point;
	x = static_cast<int>(point.x / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);
	y = static_cast<int>(point.y / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);

	//修改地图相应位置的状态
	m_BoxEdit.ChangeMap(x,y,m_NowSelect);
	//通知窗口重绘
	Invalidate(FALSE);

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CBoxEditerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	//记录当前的鼠标位置，以便鼠标跟随效果的实现
	m_MousePoint = point;
	
	if( m_bMouseDown )
	{
		int x, y;
		
		x = static_cast<int>(point.x / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);
		y = static_cast<int>(point.y / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);
		
		m_BoxEdit.ChangeMap(x,y,m_NowSelect);
		Invalidate(FALSE);
	}
	
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CBoxEditerWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	//记录鼠标状态为释放状态
	m_bMouseDown = FALSE;
	//释放鼠标捕获
	ReleaseCapture();

	CFrameWnd::OnLButtonUp(nFlags, point);
}

BOOL CBoxEditerWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	
	CPoint CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(&CursorPos);

	if(rcClient.PtInRect(CursorPos))
	{
		switch(m_NowSelect)
		{
		case 0:
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			break;
		case MAP_WALL:
			SetCursor(AfxGetApp()->LoadCursor(IDC_WALL));
			break;
		case MAP_DESTINATION:
			SetCursor(AfxGetApp()->LoadCursor(IDC_DESTINATION));
			break;
		case MAP_MAN:
			SetCursor(AfxGetApp()->LoadCursor(IDC_MAN));
			break;
		case MAP_MAN_AT_DESTINATION:
			SetCursor(AfxGetApp()->LoadCursor(IDC_MAN_AT_DESTINATION));
			break;
		case MAP_BOX:
			SetCursor(AfxGetApp()->LoadCursor(IDC_BOX));
			break;
		case MAP_BOX_AT_DESTINATION:
			SetCursor(AfxGetApp()->LoadCursor(IDC_BOX_AT_DESTINATION));
			break;
		case MAP_OUTSIDE:
			SetCursor(AfxGetApp()->LoadCursor(IDC_OUTSIDE));
			break;
		}
	}

	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CBoxEditerWnd::OnMenuNewMap()
{
	CNewMapDlg dlg;
	dlg.m_iMapWidth=MAP_WIDTH;
	dlg.m_iMapHeight=MAP_HEIGHT;
	if(dlg.DoModal()==IDOK)	m_BoxEdit.NewMap(dlg.m_iMapWidth,dlg.m_iMapHeight);
}

void CBoxEditerWnd::OnMenuLoadMap()
{
	CLoadMapDlg dlg;
	dlg.m_iLoadMapNum=m_BoxEdit.GetNowMissionNum();
	if(dlg.DoModal()==IDOK && !m_BoxEdit.LoadMap(dlg.m_iLoadMapNum))
		MessageBox(_T("载入地图失败！"),_T("错误"),MB_OK|MB_ICONERROR);
}

void CBoxEditerWnd::OnMenuSaveMap()
{
	m_BoxEdit.SaveMap();
}