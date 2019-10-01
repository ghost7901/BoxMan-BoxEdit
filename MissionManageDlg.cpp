// MissionManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoxMan.h"
#include "MissionManageDlg.h"

extern CONST BYTE MAP_GRID_SIZE;

PaintStruct g_MapData;

void Paint()
{
	CClientDC dc(g_MapData.pWnd);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap *pOB=memDC.SelectObject(&g_MapData.Bmp);
	
	dc.BitBlt(0,0,g_MapData.Width*MAP_GRID_SIZE,g_MapData.Height*MAP_GRID_SIZE,&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOB);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)        
{        
	HDC hdc;        
    PAINTSTRUCT ps;        
//    RECT rect;        
    switch (message)        
    {
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		return 0;
    case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		
		Paint();
		EndPaint(hwnd,&ps);
		return 0;       
    }
	return DefWindowProc(hwnd,message,wParam,lParam);
}

// CMissionManageDlg �Ի���

IMPLEMENT_DYNAMIC(CMissionManageDlg, CDialog)

CMissionManageDlg::CMissionManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMissionManageDlg::IDD, pParent)
{
	g_MapData.pWnd=NULL;

	m_pMissionChild[0]=new CMissionChildDlg();
	m_pMissionChild[1]=new CMissionChildDlg();
}

CMissionManageDlg::~CMissionManageDlg()
{
	if(g_MapData.pWnd)
	{
		delete g_MapData.pWnd;
		g_MapData.Bmp.DeleteObject();
	}

	delete m_pMissionChild[0];
	delete m_pMissionChild[1];
}

void CMissionManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab[0]);
	DDX_Control(pDX, IDC_TAB2, m_Tab[1]);
	DDX_Control(pDX, IDC_RIGHT, m_btnRight);
	DDX_Control(pDX, IDC_LEFT, m_btnLeft);
	DDX_Control(pDX, IDC_COMPARE, m_btnCompare);
	DDX_Control(pDX, IDC_COMPARE_PROGRESS, m_progCompare);
	DDX_Control(pDX, IDC_RESULT, m_editCompare);
}

BEGIN_MESSAGE_MAP(CMissionManageDlg, CDialog)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_RIGHT, &CMissionManageDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_LEFT, &CMissionManageDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_COMPARE, &CMissionManageDlg::OnBnClickedCompare)
END_MESSAGE_MAP()


// CMissionManageDlg ��Ϣ�������

BOOL CMissionManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//ע�ᴰ����
	g_MapData.pWnd=new CWnd();
	ASSERT_VALID(g_MapData.pWnd);
	
	TCHAR szClassName[]="Ԥ��";
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	// register the minewnd class
	if (!AfxRegisterClass(&wc))
	{
		AfxMessageBox("ע�ᴰ����ʧ��");
		return FALSE;
	}
	
	//��������
	if (!g_MapData.pWnd->CreateEx(NULL,szClassName,"Ԥ��",
		WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE	| WS_SYSMENU,
		0,0,0,0,
		this->GetSafeHwnd(),NULL))
	{
		AfxMessageBox("����������ʧ�ܣ�");
		return FALSE;
	}

	//��������,����,�Ƚϰ�ť
	m_btnRight.SetIcon(IDI_RIGHT,0,16,16);
	m_btnRight.SetBtnCursor(IDC_MY_HAND);
	m_btnRight.AddToolTip("����");

	m_btnLeft.SetIcon(IDI_LEFT,0,16,16);
	m_btnLeft.SetBtnCursor(IDC_MY_HAND);
	m_btnLeft.AddToolTip("����");

	m_btnCompare.SetIcon(IDI_COMPARE,0,16,16);
	m_btnCompare.SetBtnCursor(IDC_MY_HAND);
	m_btnCompare.AddToolTip("�Ƚ�");

	//����Ԥ������Bitmap
	CClientDC dc(g_MapData.pWnd);
	g_MapData.Bmp.CreateCompatibleBitmap(&dc,50*30,30*30);

	//��ʼ��Tab
	for(int i=0;i<2;i++)
	{
		m_Tab[i].InsertItem(0,"��ͼ�ļ�");
		m_Tab[i].InsertItem(1,"���ļ�");
		m_pMissionChild[i]->Create(IDD_MISSION_CHILD,&m_Tab[i]);
		m_pMissionChild[i]->ShowWindow(SW_SHOW);

		CRect tabRect, itemRect;
		int nX, nY, nXc, nYc;

		m_Tab[i].GetClientRect(&tabRect);
		m_Tab[i].GetItemRect(0, &itemRect);

		nX=itemRect.left;
		nY=itemRect.bottom+1;
		nXc=tabRect.right-itemRect.left-1;
		nYc=tabRect.bottom-nY-1;

		m_pMissionChild[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMissionManageDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	g_MapData.pWnd->SetWindowPos(NULL,
		lpwndpos->x+lpwndpos->cx,
		lpwndpos->y,
		0,
		0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void CMissionManageDlg::OnBnClickedRight()
{	
	if(m_pMissionChild[0]->m_ListMission.GetItemCount()==0)
	{
		MessageBox("���ȴ�Դ�ļ�");
		return;
	}
	else if((m_pMissionChild[0]->m_ListMission.GetNextItem(-1,LVIS_SELECTED))==-1)
	{
		MessageBox("����ѡ��Դ�ؿ�");
		return;
	}
	else if(m_pMissionChild[1]->m_ListMission.GetItemCount()==0)
	{
		MessageBox("���ȴ�Ŀ���ļ�");
		return;
	}

	int iDesSelItem=m_pMissionChild[1]->UnSelectedAll();

	//�����ListCtrl��ѡ�е������������ұ�ListCtrl
	CString tempFild[5];
	int iSelItem;
	while((iSelItem=m_pMissionChild[0]->m_ListMission.GetNextItem(-1,LVIS_SELECTED))!=-1)
	{
		for(int i=0;i<5;i++) tempFild[i]=m_pMissionChild[0]->m_ListMission.GetItemText(iSelItem,i);

		m_pMissionChild[0]->m_ListMission.DeleteItem(iSelItem);

		m_pMissionChild[1]->m_ListMission.InsertItem(iDesSelItem,tempFild[0]);
		for(int i=1;i<5;i++) m_pMissionChild[1]->m_ListMission.SetItemText(iDesSelItem,i,tempFild[i]);
		m_pMissionChild[1]->m_ListMission.SetItemText(iDesSelItem,5,m_pMissionChild[0]->GetFileName());
		
		m_pMissionChild[1]->m_ListMission.SetItemState(iDesSelItem++,LVIS_SELECTED,LVIS_SELECTED);
	}
}

void CMissionManageDlg::OnBnClickedLeft()
{
	if(m_pMissionChild[1]->m_ListMission.GetItemCount()==0)
	{
		MessageBox("���ȴ�Դ�ļ�");
		return;
	}
	else if(m_pMissionChild[1]->m_ListMission.GetNextItem(-1,LVIS_SELECTED)==-1)
	{
		MessageBox("����ѡ��Դ�ؿ�");
		return;
	}
	else if(m_pMissionChild[0]->m_ListMission.GetItemCount()==0)
	{
		MessageBox("���ȴ�Ŀ���ļ�");
		return;
	}

	int iDesSelItem=m_pMissionChild[0]->UnSelectedAll();

	//���ұ�ListCtrl��ѡ�е��������������ListCtrl
	CString tempFild[5];
	int iSelItem;
	while((iSelItem=m_pMissionChild[1]->m_ListMission.GetNextItem(-1,LVIS_SELECTED))!=-1)
	{
		for(int i=0;i<5;i++) tempFild[i]=m_pMissionChild[1]->m_ListMission.GetItemText(iSelItem,i);

		m_pMissionChild[1]->m_ListMission.DeleteItem(iSelItem);

		m_pMissionChild[0]->m_ListMission.InsertItem(iDesSelItem,tempFild[0]);
		for(int i=1;i<5;i++) m_pMissionChild[0]->m_ListMission.SetItemText(iDesSelItem,i,tempFild[i]);
		m_pMissionChild[0]->m_ListMission.SetItemText(iDesSelItem,5,m_pMissionChild[1]->GetFileName());

		m_pMissionChild[0]->m_ListMission.SetItemState(iDesSelItem++,LVIS_SELECTED,LVIS_SELECTED);
	}
}

void CMissionManageDlg::OnBnClickedCompare()
{
	if(m_pMissionChild[0]->m_ListMission.GetItemCount()==0 || m_pMissionChild[1]->m_ListMission.GetItemCount()==0)
	{
		MessageBox("���ȴ�Ҫ�Ƚϵ��ļ�");
		return;
	}

	CIni Ini[2];
	int iMax[2];
	for(int i=0;i<2;i++)
	{
		Ini[i].SetFileName(m_pMissionChild[i]->GetFileName());
		iMax[i]=Ini[i].GetIntValue("FileInfo","MaxMission");
	}
	
	BeginWaitCursor();

	m_progCompare.SetRange(1,iMax[0]*iMax[1]);
	CString strMission,strMap,strResult="�ļ����ȽϽ��:\r\n";
	m_editCompare.SetWindowText(strResult);
	m_editCompare.UpdateWindow();
	int iSameMission=0;

	CStringArray ayMap;
	for(int i=1;i<iMax[1];i++)
	{
		strMission.Format("M%d",i);		
		ayMap.Add(Ini[1].GetStringValue(strMission,"Map"));
	}
	//int aa=0;
	for(int i=1;i<=iMax[0];i++)
	{
		strMission.Format("M%d",i);
		strMap=Ini[0].GetStringValue(strMission,"Map");
		for(int j=0;j<ayMap.GetSize();j++)
		{			
			if(strMap==ayMap.GetAt(j))
			{				
				CString temp;
				temp.Format("M%d",j+1);
				strResult+=strMission+"=="+temp+"\r\n";
				m_editCompare.SetWindowText(strResult);
				m_editCompare.UpdateWindow();
				iSameMission++;
			//	m_pMissionChild[0]->m_ListMission.DeleteItem(i-1-aa++);break;
			}
			
			m_progCompare.SetPos((i-1)*iMax[1]+j);
		}		
	}
	m_progCompare.SetPos(-1);

	EndWaitCursor();

	strResult.Format("��ͬ�Ĺؿ���%d��",iSameMission);
	MessageBox(strResult);
}