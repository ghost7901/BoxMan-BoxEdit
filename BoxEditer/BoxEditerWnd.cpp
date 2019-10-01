// MainFrm.cpp : CBoxEditerWnd ���ʵ��
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

// CBoxEditerWnd ����/����

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

	//����������	
	if (CreateExToolBar() == -1 )
	{
		MessageBox(_T("����������ʧ��"));
	}

	return 0;
}

/*******************************************************************************************************
������ : CreateExToolBar
��  �� : ����������
��  �� : ��
����ֵ : BOOL ����TRUE��ʾ�����ɹ�,����FALSE��ʾ����ʧ��
��  �� : 0.1.0.0
��  �� : �ⴺ
ʱ  �� : 2006��10��24�� 21:11:07
*******************************************************************************************************/

BOOL CBoxEditerWnd::CreateExToolBar(void)
{
	CImageList img;
	CString str;
	
	if (!m_wndToolBar.CreateEx(this))
	{
		return FALSE;
	}
	
	//���ð�ť�Ŀ�Ⱥͳ���
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	//�ı�����
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | 
								TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
	//���ð�ť��Ϊ6
	m_wndToolBar.SetButtons(NULL,7);	

	// 2. ���ͼ��
	//����"��/hot"״̬�ĵ�λͼ
	img.Create(28, 28, ILC_COLOR8|ILC_MASK,2,2);
	img.SetBkColor(RGB(0, 0, 102));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDI_WALL));
	img.Add(AfxGetApp()->LoadIcon(IDI_DESTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDI_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDI_BOX_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_OUTSIDE));
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();	
	//����"��/cold"״̬��λͼ
	img.Create(26, 26, ILC_COLOR8|ILC_MASK, 2,2);
	img.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDI_WALL));
	img.Add(AfxGetApp()->LoadIcon(IDI_DESTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDI_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDI_BOX_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDI_MAN_AT_DESTINATION));
	img.Add(AfxGetApp()->LoadIcon(IDI_OUTSIDE));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

	//3. ��������  
	m_wndToolBar.SetButtonInfo(0, ID_MENU_DRAW_WALL, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, _T("Χǽ"));	

	m_wndToolBar.SetButtonInfo(1, ID_MENU_DRAW_DESTINATION, TBSTYLE_BUTTON,1);
	m_wndToolBar.SetButtonText(1, _T("Ŀ�ĵ�"));
	
	m_wndToolBar.SetButtonInfo(2, ID_MENU_DRAW_BOX, TBSTYLE_BUTTON,2);
	m_wndToolBar.SetButtonText(2, _T("����"));

	m_wndToolBar.SetButtonInfo(3, ID_MENU_DRAW_BOX_AT_DESTINATION, TBSTYLE_BUTTON,3);
	m_wndToolBar.SetButtonText(3, _T("��λ��"));

	m_wndToolBar.SetButtonInfo(4, ID_MENU_DRAW_MAN, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonText(4, _T("���˹�"));

	m_wndToolBar.SetButtonInfo(5, ID_MENU_DRAW_MAN_AT_DESTINATION, TBSTYLE_BUTTON, 5);
	m_wndToolBar.SetButtonText(5, _T("��λ��"));

	m_wndToolBar.SetButtonInfo(6, ID_MENU_DRAW_OUTSIDE, TBSTYLE_BUTTON, 6);
	m_wndToolBar.SetButtonText(6, _T("����"));

	CRect rectToolBar;
	//�õ���ť�Ĵ�С
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	//���ð�ť�Ĵ�С
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(26,26));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//����ͣ��
	EnableDocking(CBRS_ALIGN_ANY);
	//Ư��ͣ��
	CPoint pt(GetSystemMetrics(SM_CXSCREEN)/2+100,GetSystemMetrics(SM_CYSCREEN)/3+100);
	FloatControlBar(&m_wndToolBar,pt);

	return TRUE;
}

void CBoxEditerWnd::OnPaint() 
{
	
	CPaintDC dc(this);    // ������Ļ��ʾ���豸
	CDC dcMemory;  // �ڴ��豸
	
	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	if (!dc.IsPrinting()) 
	{
		// ��dc�豸����
		if (dcMemory.CreateCompatibleDC(&dc))
		{	
			// ʹ��bitmap��ʵ����ʾ���豸����
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right, m_rcClient.bottom))
			{
				// �ڴ��豸ѡ�������λͼ
				dcMemory.SelectObject(&bitmap);
				
				//���Ƶ�ͼ		
				m_BoxEdit.DrawMap(&dcMemory);

				//����������ͼ��	
				int x = m_MousePoint.x/MAP_SMALL_SQUARE_SIZE;
				int y = m_MousePoint.y/MAP_SMALL_SQUARE_SIZE;
				//if(m_NowSelect)m_BoxEdit.DrawMouseCursor(x,y,m_NowSelect,&dcMemory);
				
				
				// ���ڴ��豸�����ݿ�����ʵ����Ļ��ʾ���豸
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
	//��ʶ��걻����
	m_bMouseDown = TRUE;
	//�������
	SetCapture();
	//��ȡ����λ�ò�������ڵ�ͼ��Ӧ�ķ���λ��
	m_MousePoint = point;
	x = static_cast<int>(point.x / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);
	y = static_cast<int>(point.y / static_cast<double>(MAP_SMALL_SQUARE_SIZE) + 0.5);

	//�޸ĵ�ͼ��Ӧλ�õ�״̬
	m_BoxEdit.ChangeMap(x,y,m_NowSelect);
	//֪ͨ�����ػ�
	Invalidate(FALSE);

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CBoxEditerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	//��¼��ǰ�����λ�ã��Ա�������Ч����ʵ��
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
	//��¼���״̬Ϊ�ͷ�״̬
	m_bMouseDown = FALSE;
	//�ͷ���겶��
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
		MessageBox(_T("�����ͼʧ�ܣ�"),_T("����"),MB_OK|MB_ICONERROR);
}

void CBoxEditerWnd::OnMenuSaveMap()
{
	m_BoxEdit.SaveMap();
}