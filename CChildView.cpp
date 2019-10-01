// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "BoxMan.h"
#include "CChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MapSelectDlg.h"
#include "MissionManageDlg.h"
#include "FileRelationDlg.h"

extern UINT MAX_MISSION_NUM;

BoxManClass bm;


/////////////////////////////////////////////////////////////////////////////
// CChildView

UINT ThinkThread(LPVOID pParam)
{
	bm.ThinkTheWay();
//	bm.m_pThread=NULL;
	return 0;
}

CChildView::CChildView()
{
	m_nCurrentMusic=0;
}

CChildView::~CChildView()
{
	
	/*if(bm.m_pThread)
	{
		DWORD dw;
		GetExitCodeThread(bm.m_pThread->m_hThread,&dw);
		TerminateThread(bm.m_pThread->m_hThread,dw);
		bm.m_pThread->Delete();
	}*/
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SELECTMAP, OnSelectmap)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOW_MOVE_WAY, OnShowMoveWay)
	ON_UPDATE_COMMAND_UI(ID_SHOW_MOVE_WAY, OnUpdateShowMoveWay)
	ON_UPDATE_COMMAND_UI(ID_PROMPT, OnUpdatePrompt)
	ON_COMMAND(ID_PROMPT, OnPrompt)
	ON_COMMAND(ID_PRIOR_MAP, OnPriorMap)
	ON_COMMAND(ID_NEXT_MAP, OnNextMap)
	ON_UPDATE_COMMAND_UI(ID_NEXT_MAP, OnUpdateNextMap)
	ON_COMMAND(ID_MUSIC1, OnMusic1)
	ON_UPDATE_COMMAND_UI(ID_MUSIC1, OnUpdateMusic1)
	ON_COMMAND(ID_MUSIC2, OnMusic2)
	ON_UPDATE_COMMAND_UI(ID_MUSIC2, OnUpdateMusic2)
	ON_COMMAND(ID_SOUND, OnSound)
	ON_UPDATE_COMMAND_UI(ID_SOUND, OnUpdateSound)
	ON_COMMAND(ID_MUSIC3, OnMusic3)
	ON_UPDATE_COMMAND_UI(ID_MUSIC3, OnUpdateMusic3)
	ON_COMMAND(ID_MUSIC4, OnMusic4)
	ON_UPDATE_COMMAND_UI(ID_MUSIC4, OnUpdateMusic4)
	ON_COMMAND(ID_MUSIC5, OnMusic5)
	ON_UPDATE_COMMAND_UI(ID_MUSIC5, OnUpdateMusic5)
	ON_COMMAND(ID_MUSIC6, OnMusic6)
	ON_UPDATE_COMMAND_UI(ID_MUSIC6, OnUpdateMusic6)
	ON_COMMAND(ID_MUSIC7, OnMusic7)
	ON_UPDATE_COMMAND_UI(ID_MUSIC7, OnUpdateMusic7)
	ON_COMMAND(ID_MUSIC8, OnMusic8)
	ON_UPDATE_COMMAND_UI(ID_MUSIC8, OnUpdateMusic8)
	ON_COMMAND(ID_MUSIC9, OnMusic9)
	ON_UPDATE_COMMAND_UI(ID_MUSIC9, OnUpdateMusic9)
	ON_COMMAND(ID_GAME_REPLAY, OnGameReplay)
	ON_COMMAND(ID_MORE_MUSIC, OnMoreMusic)
	ON_COMMAND(ID_MUSIC, OnMusic)
	ON_UPDATE_COMMAND_UI(ID_MUSIC, OnUpdateMusic)
	ON_UPDATE_COMMAND_UI(ID_PRIOR_MAP, OnUpdatePriorMap)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_COMMAND(ID_SCENE1, OnScene1)
	ON_UPDATE_COMMAND_UI(ID_SCENE1, OnUpdateScene1)
	ON_COMMAND(ID_SCENE2, OnScene2)
	ON_UPDATE_COMMAND_UI(ID_SCENE2, OnUpdateScene2)
	ON_COMMAND(ID_SCENE3, OnScene3)
	ON_UPDATE_COMMAND_UI(ID_SCENE3, OnUpdateScene3)
	ON_COMMAND(ID_SCENE4, OnScene4)
	ON_UPDATE_COMMAND_UI(ID_SCENE4, OnUpdateScene4)
	ON_COMMAND(ID_LOAD, OnLoad)
	ON_UPDATE_COMMAND_UI(ID_MUSIC1, OnUpdateMusic1)
	ON_COMMAND(ID_SAVE, OnSave)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOL_EDIT_MAP, &CChildView::OnEditMap)
	ON_MESSAGE(MM_MCINOTIFY,OnMciNotify)
	ON_COMMAND(ID_DIFF1, &CChildView::OnDiff1)
	ON_COMMAND(ID_DIFF2, &CChildView::OnDiff2)
	ON_COMMAND(ID_DIFF3, &CChildView::OnDiff3)
	ON_COMMAND(ID_DIFF4, &CChildView::OnDiff4)
	ON_COMMAND(ID_DIFF5, &CChildView::OnDiff5)
	ON_COMMAND(ID_DIFF6, &CChildView::OnDiff6)
	ON_UPDATE_COMMAND_UI(ID_DIFF1, &CChildView::OnUpdateDiff1)
	ON_UPDATE_COMMAND_UI(ID_DIFF2, &CChildView::OnUpdateDiff2)
	ON_UPDATE_COMMAND_UI(ID_DIFF3, &CChildView::OnUpdateDiff3)
	ON_UPDATE_COMMAND_UI(ID_DIFF4, &CChildView::OnUpdateDiff4)
	ON_UPDATE_COMMAND_UI(ID_DIFF5, &CChildView::OnUpdateDiff5)
	ON_UPDATE_COMMAND_UI(ID_DIFF6, &CChildView::OnUpdateDiff6)
	ON_COMMAND(ID_DIFF7, &CChildView::OnDiff7)
	ON_UPDATE_COMMAND_UI(ID_DIFF7, &CChildView::OnUpdateDiff7)
	ON_COMMAND(ID_TOOL_MISSION_MANAGE, &CChildView::OnToolMissionManage)
//	ON_WM_SIZING()
ON_WM_SIZE()
ON_WM_ERASEBKGND()
ON_COMMAND(ID_OPTION_AUTO_ZOOM, &CChildView::OnOptionAutoZoom)
ON_UPDATE_COMMAND_UI(ID_OPTION_AUTO_ZOOM, &CChildView::OnUpdateOptionAutoZoom)
ON_COMMAND(ID_OPTION_SEQUENCE, &CChildView::OnOptionSequence)
ON_UPDATE_COMMAND_UI(ID_OPTION_SEQUENCE, &CChildView::OnUpdateOptionSequence)
ON_COMMAND(ID_OPEN_FILE, &CChildView::OnOpenFile)
ON_COMMAND(ID_TOOL_SAVE_SCENE, &CChildView::OnToolSaveScene)
ON_COMMAND(ID_TOOL_FILE_RELATION, &CChildView::OnToolFileRelation)
ON_COMMAND(ID_HELP_AUTHOR, &CChildView::OnHelpAuthor)
ON_COMMAND(ID_HELP_WEB, &CChildView::OnHelpWeb)
ON_COMMAND(ID_TOOL_PRINT, &CChildView::OnToolPrint)
ON_COMMAND(ID_TOOL_COPY, &CChildView::OnToolCopy)
ON_COMMAND(ID_TOOL_PASTE, &CChildView::OnToolPaste)
ON_UPDATE_COMMAND_UI(ID_TOOL_PASTE, &CChildView::OnUpdateToolPaste)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	HCURSOR hCursor=AfxGetApp()->LoadStandardCursor(IDC_HAND);
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		hCursor, HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//上面这句虽然没有用,但一定不能拴掉,I don't know why.

	bm.Paint(NULL);
}

void CChildView::Created()
{
	bm.SetDrawWnd(this);

	CString cmdline=AfxGetApp()->m_lpCmdLine;
	if(!cmdline.IsEmpty())
		bm.Load(cmdline);
	else
	{
		bm.ReadMap(bm.m_nowmap);
		bm.ReSetFrame();
		BeginThinkThread();
		bm.SetStatusBar();
	}

	SetTimer(100,500,NULL);
}

void CChildView::OnSelectmap()
{
	SelectMap(false);
}

void CChildView::SelectMap(bool next)
{
	//bm.LoadMaxMissionNum();
	if(next && bm.m_nowmap==MAX_MISSION_NUM) return;
	MapSelectDlg dlg;
	dlg.m_SelectMap=bm.m_nowmap;
	if(next) dlg.m_SelectMap++;
	if(dlg.DoModal()==IDOK && dlg.m_SelectMap!=bm.m_nowmap)
	{
		if(!bm.ReadMap(dlg.m_SelectMap))
		{
			MessageBox("地图数据错误!");
			return;
		}
		bm.SceneSequence();
		bm.ReSetFrame();
		BeginThinkThread();
		bm.m_nTotalStep=0;
		bm.m_bBoxMovedToDestination=FALSE;
		bm.SetStatusBar();
	}
}
/*
void CChildView::OnMouseMove(UINT nFlags,CPoint point)
{
	if(bm.PointAtBox(point)==-1)
	{
		HCURSOR Cursor = AfxGetApp()->LoadStandardCursor( MAKEINTRESOURCE(32649) );
		SetCursor(Cursor);
		SetCapture();
	}
	else
		ReleaseCapture();
	
	MSG message;
	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)){
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}
}
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	unsigned char result=bm.PointAt(point);
	bm.PlaySound(result);
	switch(result){
	case BM_ERROR_PIONT_OUT:
		if(!bm.m_CanMoveToBadPoint)
			MessageBox( "你说笑吗?\r\n\r\n那里是墙外!",
			"ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING );
		break;
	case BM_ERROR_POINT_MAN:
		break;
	case BM_ERROR_POINT_WALL:
		if(!bm.m_CanMoveToBadPoint)
			MessageBox( "对不起,那里是墙.\r\n\r\n我不想撞墙自尽!", 
			"ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING );
		break;
	case BM_MAN_MOVED:
		break;
	case BM_BOX_MOVED:
		bm.m_TheShowStep = 0;
		break;
	case BM_MOVED_OK:
		bm.m_nTotalStep=0;
		//bm.m_bBoxMovedToDestination=FALSE;
	//	bm.SetReg();
		SelectMap( true );
		break;
	case BM_ERROR_CANNOT_MOVE_THERE:
		if(!bm.m_CanMoveToBadPoint)
			MessageBox( "有东西挡着,\r\n\r\n不能移动到那里去!", 
			"ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING );
		break;
	case BM_MOVED_TO_BAD_POINT:
		MessageBox( "这个地方不能推进去,\n进去就出不来了!",
			"ERROR", MB_ICONASTERISK | MB_ICONINFORMATION );
		break;
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	unsigned char result=BM_ERROR_CANNOT_MOVE_THERE;
	switch( nChar )
	{
	case VK_RIGHT:
		bm.m_nKey=VK_RIGHT;
		result=bm.MoveTowards( 1, 0 );
		break;
	case VK_UP:
		bm.m_nKey=VK_UP;
		result=bm.MoveTowards( 0, -1 );
		break;
	case VK_LEFT:
		bm.m_nKey=VK_LEFT;
		result=bm.MoveTowards( -1, 0 );
		break;
	case VK_DOWN:
		bm.m_nKey=VK_DOWN;
		result=bm.MoveTowards( 0, 1 );
		break;
/*	case VK_CONTROL:
		if ( bm.m_CanUndo && !(bool)((nFlags>>14)&0x01) ) bm.Undo();
		break;
	case VK_SPACE:
		bm.ThinkTheWay();
		MessageBox( "Ok" );
*/
	}
	
	bm.PlaySound(result);

	switch (result)
	{
	case BM_MOVED_OK:
		bm.m_nTotalStep=0;
//		bm.SetReg();
		SelectMap(TRUE);
		break;
	case BM_BOX_MOVED:
		bm.m_nTotalStep++;
		bm.m_TheShowStep=0;
		break;
	case BM_MAN_MOVED:
		bm.m_nTotalStep++;
		break;
	case BM_MOVED_TO_BAD_POINT:
		MessageBox( "这个地方不能推进去,\n进去就出不来了!", "PROMPT", MB_ICONASTERISK | MB_ICONINFORMATION );
		break;
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnEditUndo() 
{
	bm.m_nTotalStep=bm.m_nTotalStep+5;
	bm.PlaySound(-1);
	bm.Undo();
	bm.m_TheShowStep=0;
}

void CChildView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bm.m_CanUndo);
}

void CChildView::OnShowMoveWay() 
{
	bm.ShowMoveWay();
	bm.m_nTotalStep=0;
}

void CChildView::OnUpdateShowMoveWay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !bm.m_noanswerrecoded );
}

void CChildView::OnUpdatePrompt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( !bm.m_CanMoveToBadPoint );
	bm.SetStatusBar();
}

void CChildView::OnPrompt() 
{
	bm.m_CanMoveToBadPoint = !bm.m_CanMoveToBadPoint;
}

void CChildView::BeginThinkThread()
{
	//my
	//bm.m_pThread=AfxBeginThread( ThinkThread, 0, THREAD_PRIORITY_BELOW_NORMAL/*THREAD_PRIORITY_TIME_CRITICAL*/ );
	AfxBeginThread(ThinkThread,0,THREAD_PRIORITY_BELOW_NORMAL/*THREAD_PRIORITY_TIME_CRITICAL*/);
//	if(bm.m_pThread) bm.m_hStopEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	//end
}

void CChildView::OnPriorMap() 
{
	int i=bm.m_nowmap;
	while(!bm.ReadMap(--i) && i>0);
	if(i>0)
	{
		bm.SceneSequence();
		bm.ReSetFrame();
		BeginThinkThread();
		bm.SetStatusBar();
		bm.m_nTotalStep=0;
		bm.m_bBoxMovedToDestination=FALSE;
	}
	else
		MessageBox("没有你选择的这副地图.","ERROR",MB_ICONEXCLAMATION|MB_ICONWARNING);
}

void CChildView::OnNextMap() 
{
	UINT i=bm.m_nowmap;
	while(!bm.ReadMap(++i) && i<=MAX_MISSION_NUM);
	if(i<=MAX_MISSION_NUM)
	{
		bm.SceneSequence();
		bm.ReSetFrame();
		BeginThinkThread();
		bm.SetStatusBar();
		bm.m_nTotalStep=0;
		bm.m_bBoxMovedToDestination=FALSE;
	}
	else
		MessageBox("没有你选择的这副地图.","ERROR",MB_ICONEXCLAMATION|MB_ICONWARNING);
}

void CChildView::OnUpdatePriorMap(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( bm.m_nowmap > 1);
}

void CChildView::OnUpdateNextMap(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( bm.m_nowmap < MAX_MISSION_NUM);
}

void CChildView::OnMusic1() 
{
	if(m_nCurrentMusic!=1)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=1;
		if(!bm.midi1.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		
		SetTimer(m_nCurrentMusic,(2*60+0)*1000,NULL);
	}
	else
	{
		KillTimer(1);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnMusic2() 
{
	if(m_nCurrentMusic!=2)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=2;
		if(!bm.midi2.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(1*60+35)*1000,NULL);	
	}
	else
	{
		KillTimer(2);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==1);
}

void CChildView::OnUpdateMusic2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==2);	
}

void CChildView::OnPause() 
{
	bm.m_bIsPause=!bm.m_bIsPause;
	if(bm.m_bIsPause)
		bm.midi1.PauseMIDI();
	else
		bm.midi1.ResumeMIDI();
}

void CChildView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	if(bm.midi1.IsPlaying())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(bm.m_bIsPause);
}

void CChildView::OnSound() 
{
	bm.m_bEnableSound=!bm.m_bEnableSound;
}

void CChildView::OnUpdateSound(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bm.m_bEnableSound);
	bm.SetStatusBar();	
}

void CChildView::OnMusic3() 
{
	if(m_nCurrentMusic!=3)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=3;
		if(!bm.midi3.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(1*60+58)*1000,NULL);
	}
	else
	{
		KillTimer(3);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==3);
}

void CChildView::OnMusic4() 
{
	if(m_nCurrentMusic!=4)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=4;
		if(!bm.midi4.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(3*60+23)*1000,NULL);
	}
	else
	{	
		KillTimer(4);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==4);	
}

void CChildView::OnMusic5() 
{
	if(m_nCurrentMusic!=5)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=5;
		if(!bm.midi5.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(1*60+26)*1000,NULL);
	}
	else
	{
		KillTimer(5);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic5(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==5);
}

void CChildView::OnMusic6() 
{
	if(m_nCurrentMusic!=6)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=6;
		if(!bm.midi6.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(4*60+32)*1000,NULL);
	}
	else if(m_nCurrentMusic==6)
	{	
		KillTimer(6);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic6(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==6);
}

void CChildView::OnMusic7() 
{
	if(m_nCurrentMusic!=7)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=7;
		if(!bm.midi7.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件",ERROR);
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(1*60+23)*1000,NULL);
	}
	else if(m_nCurrentMusic==7)
	{
		KillTimer(7);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic7(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==7);
}

void CChildView::OnMusic8() 
{
	if(m_nCurrentMusic!=8)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=8;
		if(!bm.midi8.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(1*60+2)*1000,NULL);
	}
	else if(m_nCurrentMusic==8)
	{	
		KillTimer(8);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic8(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==8);
}

void CChildView::OnMusic9() 
{
	if(m_nCurrentMusic!=9)
	{
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=9;
		if(!bm.midi9.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件","ERROR");
			m_nCurrentMusic=0;
			return;
		}
		SetTimer(m_nCurrentMusic,(4*60+22)*1000,NULL);
	}
	else if(m_nCurrentMusic==9)
	{
		KillTimer(9);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic9(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nCurrentMusic==9);
}

void CChildView::OnGameReplay() 
{
	UINT i=bm.m_nowmap;
	while ( !bm.ReadMap( i ) && i<=MAX_MISSION_NUM );
	if ( i<=MAX_MISSION_NUM ) {
		bm.ReSetFrame();
		BeginThinkThread();
		bm.SetStatusBar();
		bm.m_nTotalStep=0;
		bm.m_bBoxMovedToDestination=FALSE;
	}	
}

void CChildView::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
		OnMusic2();
		break;
	case 2:
		OnMusic3();
		break;
	case 3:
		OnMusic4();
		break;
	case 4:
		OnMusic5();
		break;
	case 5:
		OnMusic6();
		break;
	case 6:
		OnMusic7();
		break;
	case 7:
		OnMusic8();
		break;
	case 8:
		OnMusic9();
		break;
	case 9:
		OnMusic1();
		break;
	case 100:
		bm.DrawMan(true);
	}
}

void CChildView::OnMoreMusic() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,"MIDI文件(*.mid)|*.mid||");
	dlg.m_ofn.lpstrTitle="打开MIDI文件";
	if(dlg.DoModal()==IDOK)
	{
		CString str=dlg.GetPathName();
		str.Replace("\\","\\\\");
		CMIDI midi(str);
		if(!midi.PlayMIDI(this->GetSafeHwnd()))
		{
			MessageBox("无法播放MIDI文件",ERROR);
			return;
		}
		KillTimer(m_nCurrentMusic);
		m_nCurrentMusic=10;
	}	
}

void CChildView::OnMusic() 
{//bm.Save("map.sav");
//bm.Load("map.sav");
//ReSetFrame();
//	const BYTE aa=3;
//	if(!bm.SetReg(&aa))MessageBox("aa");
//	if(!bm.CreateReg())MessageBox("bb");
	if(!m_nCurrentMusic)
		OnMusic1();
	else
	{
		KillTimer(m_nCurrentMusic);
		MyMIDI::StopAllMIDI();
		m_nCurrentMusic=0;
	}
}

void CChildView::OnUpdateMusic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nCurrentMusic!=0);	
}

void CChildView::OnScene1() 
{
	if(bm.m_nCurrentScene==0) return;
	bm.m_nCurrentScene=0;
	bm.AttachMapToMemory();
	bm.ReSetFrame();
}

void CChildView::OnUpdateScene1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(bm.m_nCurrentScene==0);
}

void CChildView::OnScene2() 
{
	if(bm.m_nCurrentScene==1) return;
	bm.m_nCurrentScene=1;
	bm.AttachMapToMemory();
	bm.ReSetFrame();	
}

void CChildView::OnUpdateScene2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(bm.m_nCurrentScene==1);
}

void CChildView::OnScene3() 
{
	if(bm.m_nCurrentScene==2) return;
	bm.m_nCurrentScene=2;
	bm.AttachMapToMemory();
	bm.ReSetFrame();
}

void CChildView::OnUpdateScene3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(bm.m_nCurrentScene==2);
}

void CChildView::OnScene4() 
{
	if(bm.m_nCurrentScene==3) return;
	bm.m_nCurrentScene=3;
	bm.AttachMapToMemory();
	bm.ReSetFrame();
}

void CChildView::OnUpdateScene4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(bm.m_nCurrentScene==3);
}

void CChildView::OnLoad() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,"BoxMan关卡存档(*.bxs)|*bxs||");
	dlg.m_ofn.lpstrTitle="载入进度";
	if(dlg.DoModal() == IDOK)
	{
		bm.Load(dlg.GetPathName());
		
		//BeginThinkThread();
	}
}

void CChildView::OnSave() 
{	
	//bm.Temp();
	CString s,strFile;
	s.Format(bm.GetDifficultyString()+"_Round_%d",bm.m_nowmap);
	CFileDialog dlg(false,"bxs",s,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,"BoxMan关卡存档(*.bxs)|*.bxs||");
	dlg.m_ofn.lpstrTitle="存储进度";
	if(dlg.DoModal()==IDOK)	bm.Save(dlg.GetPathName());
}

void CChildView::OnDestroy()
{
	CWnd::OnDestroy();
	
	bm.ExitThinkThreak();
}

void CChildView::OnEditMap()
{
	WinExec("BoxEditer.exe",1);
}

LONG CChildView::OnMciNotify(UINT wFlags,LONG lDevId)
{
	/*switch(lDevId)   
	{
    case MCI_NOTIFY_SUCCESSFUL:
		if(++m_nCurrentMusic>9) m_nCurrentMusic=1;
		switch(m_nCurrentMusic)
		{
		case 0:
			bm.midi1.PlayMIDI(this->GetSafeHwnd());
			break;
		case 1:
			bm.midi2.PlayMIDI(this->GetSafeHwnd());
			break;
		case 2:
			bm.midi3.PlayMIDI(this->GetSafeHwnd());
			break;
		case 3:
			bm.midi4.PlayMIDI(this->GetSafeHwnd());
			break;
		case 4:
			bm.midi5.PlayMIDI(this->GetSafeHwnd());
			break;
		case 5:
			bm.midi6.PlayMIDI(this->GetSafeHwnd());
			break;
		case 6:
			bm.midi7.PlayMIDI(this->GetSafeHwnd());
			break;
		case 7:
			bm.midi8.PlayMIDI(this->GetSafeHwnd());
			break;
		case 8:
			bm.midi9.PlayMIDI(this->GetSafeHwnd());
			break;
		}
		break;       
    case MCI_NOTIFY_FAILURE:
		break;       
    case MCI_NOTIFY_SUPERSEDED:
		break;       
    }*/   

	return 1;
}

void CChildView::OnDiff1()
{
	if(!bm.SelectDifficulty(1)) return;
	BeginThinkThread();
}

void CChildView::OnDiff2()
{
	if(!bm.SelectDifficulty(2)) return;
	BeginThinkThread();
}

void CChildView::OnDiff3()
{
	if(!bm.SelectDifficulty(3)) return;
	BeginThinkThread();
}

void CChildView::OnDiff4()
{
	if(!bm.SelectDifficulty(4)) return;
	BeginThinkThread();
}

void CChildView::OnDiff5()
{
	if(!bm.SelectDifficulty(5)) return;
	BeginThinkThread();
}

void CChildView::OnDiff6()
{
	if(!bm.SelectDifficulty(6)) return;
	BeginThinkThread();
}

void CChildView::OnDiff7()
{
	if(!bm.SelectDifficulty(7)) return;
	BeginThinkThread();
}

void CChildView::OnUpdateDiff1(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==1);
}

void CChildView::OnUpdateDiff2(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==2);
}

void CChildView::OnUpdateDiff3(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==3);
}

void CChildView::OnUpdateDiff4(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==4);
}

void CChildView::OnUpdateDiff5(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==5);
}

void CChildView::OnUpdateDiff6(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==6);
}

void CChildView::OnUpdateDiff7(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(bm.m_iDifficulty==7);
}

void CChildView::OnToolMissionManage()
{
	CMissionManageDlg dlg;
	dlg.DoModal();
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	double rate=bm.m_fZoomRate;
	int	mapsizex=bm.m_mapsizex,
		mapsizey=bm.m_mapsizey;
	if(bm.ChangeRate(cx,cy)<.000000000001) return;
	
	if(rate!=bm.m_fZoomRate || mapsizex!=bm.m_mapsizex || mapsizey!=bm.m_mapsizey) bm.DrawAllMap();	
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	//return CWnd::OnEraseBkgnd(pDC);
}

void CChildView::OnOptionAutoZoom()
{
	bm.m_bAutoZoom=!bm.m_bAutoZoom;
	bm.ReSetFrame();
}

void CChildView::OnUpdateOptionAutoZoom(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(bm.m_bAutoZoom);
}

void CChildView::OnOptionSequence()
{
	bm.m_bAutoSequence=!bm.m_bAutoSequence;
}

void CChildView::OnUpdateOptionSequence(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(bm.m_bAutoSequence);
}

void CChildView::OnOpenFile()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,"BoxMan地图文件(*.bxm)|*bxm||");
	dlg.m_ofn.lpstrTitle="打开地图";
	if(dlg.DoModal() == IDOK)
	{
		bm.LoadMapFile(dlg.GetPathName());
		BeginThinkThread();
	}
}

void CChildView::OnToolSaveScene()
{
	CString s,strFile;
	s.Format(bm.GetDifficultyString()+"_Round_%d",bm.m_nowmap);

	CFileDialog dlg(FALSE,"bmp",s,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,"位图文件(*.bmp)|*bmp||",this);
	dlg.m_ofn.lpstrTitle="保存场景";
	//dlg.m_ofn.FlagsEx=OFN_EX_NOPLACESBAR;
	if(dlg.DoModal() == IDOK)
	{
		CString strName=dlg.GetPathName();
		bm.SaveScene((LPTSTR)strName.GetBuffer());
		strName.ReleaseBuffer();
	}
}

void CChildView::OnToolFileRelation()
{
	CFileRelationDlg dlg;
	dlg.DoModal();
}

void CChildView::OnHelpAuthor()
{
	ShellExecute(0,NULL,"mailto:ghost79@126.com",NULL,NULL,SW_SHOWNORMAL);
}

void CChildView::OnHelpWeb()
{
	ShellExecute(0,NULL,"http://www.jzxx.net/myvc/",NULL,NULL,SW_SHOWNORMAL);
}

void CChildView::OnToolPrint()
{
	bm.PrintScene();
}

void CChildView::OnToolCopy()
{
	bm.Save(bm.m_strSysPath+"ClipBoard.tmp");
	bm.m_bCanPaste=true;
}

void CChildView::OnToolPaste()
{
	bm.Load(bm.m_strSysPath+"ClipBoard.tmp");
}

void CChildView::OnUpdateToolPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(bm.m_bCanPaste);
}
