/* ============================================================================================ *\
 *	Author		:	吴春																		*
 *	Email		:	ghost79@wjedu.net															*
 *	Msn			:	wuchun79@163.com  												        	*
 *	QQ			:	23417690																	*
 *	Version		:	1.0 																		*
 *	Created		:	2006/10/24 21:40:13															*
 *	Modified	:	2006/10/31 17:15:46															*
 *	FileName	: 	BoxEdit.cpp				 									 	     	    *
 *	Description	:	This file is using for declaring the class CBoxEdit,and this class is	    *
 *					using for generating edit boxman map.					                	*
 * 	Warning     : 	Copyright (c) ghost79 2006 All rights reserved.  							*
\* ============================================================================================ */

#include "stdafx.h"
#include "BoxEditer.h"
#include "BoxEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int MAP_WIDTH =                16;
int MAP_HEIGHT   =             14;
int MAP_SMALL_SQUARE_SIZE  =   30;

//地图状态
#define MAP_BACKGROUP  48  //'0'  对应字符'0'
#define MAP_WHITEWALL  49  //'1'
#define MAP_BLUEWALL   50  //'2'
#define MAP_BALL       51  //'3'
#define MAP_YELLOWBOX  52  //'4'
#define MAP_REDBOX     53  //'5'
#define MAP_MANWALL    54  //'6'
#define MAP_MANBALL    55  //'7'

const char BMP_INDEX_WALL=0;
const char BMP_INDEX_ROAD=1;
const char BMP_INDEX_OUTSIDE=2;
const char BMP_INDEX_BOX=3;
const char BMP_INDEX_BOX_AT_DESTINATION=4;
const char BMP_INDEX_DESTINATION=5;
const char BMP_INDEX_MAN=6;
const char BMP_INDEX_MAN_AT_DESTINATION=7;

//方块周围的八个方块X,Y增量
int dx[8]={1,0,-1,0};
int dy[8]={0,1,0,-1};

//假宏定义
int MAX_MISSION_NUM  = 1;
const TCHAR FILENAME[]=".\\custom.bxm";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoxEdit::CBoxEdit()
{	
	ClearMap();
	SetFileName(FILENAME);
	LoadMaxMissionNum();
	m_iNowMissionNum=1;	
}

CBoxEdit::~CBoxEdit()
{
//	::GlobalFree(m_hMap);
}

/*******************************************************************************************************
函数名 : LoadMap
描  述 : 读取地图
参  数 : 
         int iMissionNum : 要读取的关卡号
返回值 : BOOL 返回真值表示读取成功,假值表示读取失败
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月26日 9:54:27
*******************************************************************************************************/

BOOL CBoxEdit::LoadMap(int iMissionNum)
{
	CString strMission;
	strMission.Format("M%d",iMissionNum);
	m_x=GetIntValue(strMission,"Width");
	m_y=GetIntValue(strMission,"Height");
	CString strMap=GetStringValue(strMission,"Map");
	if(m_x==0 || m_y==0 || strMap.IsEmpty()  //无此关地图
		|| m_x>M_TAB_WIDTH || m_y>M_TAB_HEIGHT)  //地图太大
		return false;
	
	int i=0;
	for(int y=0;y<m_y;y++)
	{
		for(int x=0;x<m_x;x++)
		{
			m_cMap[y][x]=strMap[i++];			
		}
	}

	if(m_x>MAP_WIDTH || m_y>MAP_HEIGHT)						
	{
		MAP_WIDTH=m_x;
		MAP_HEIGHT=m_y;
		CWnd *pWnd=AfxGetMainWnd();
		CRect rcWindow;
		pWnd->GetWindowRect(&rcWindow);
		pWnd->SetWindowPos(NULL,rcWindow.top,rcWindow.left,
			MAP_WIDTH*MAP_SMALL_SQUARE_SIZE+10,MAP_HEIGHT*MAP_SMALL_SQUARE_SIZE+48,
			SWP_NOMOVE|SWP_NOZORDER);
	}

	m_iNowMissionNum=iMissionNum;
	AfxGetMainWnd()->Invalidate();
	return true;
}

/*******************************************************************************************************
函数名 : SaveMap
描  述 : 保存地图
参  数 : 无
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月31日 23:12:20
*******************************************************************************************************/

void CBoxEdit::SaveMap(void)
{
	if(IsFinish())
	{
		MAX_MISSION_NUM=LoadMaxMissionNum()+1;

		m_x=m_iMaxXPos-m_iMinXPos+1;
		m_y=m_iMaxYPos-m_iMinYPos+1;

		CString strMission,strTemp;
		strMission.Format("M%d",MAX_MISSION_NUM);

		strTemp.Format("%d",m_x);
		SetValue(strMission,"Width",strTemp);

		strTemp.Format("%d",m_y);
		SetValue(strMission,"Height",strTemp);

		strTemp.Empty();
		for(int y=m_iMinYPos;y<=m_iMaxYPos;y++)
			for(int x=m_iMinXPos;x<=m_iMaxXPos;x++)
			{
				strTemp+=m_cMap[y][x];
			}

		SetValue(strMission,"Map",strTemp);

		strTemp.Format("%d",MAX_MISSION_NUM);
		SetValue("FileInfo","MaxMission",strTemp,false);

		strTemp="已成功保存到关卡\" " + strMission + " \"";
		AfxMessageBox(strTemp);		
	}
}

/*******************************************************************************************************
函数名 : LoadMaxMissionNum
描  述 : 获取地图最大关卡数
参  数 : 无
返回值 : int 返回最大关卡数
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月28日 0:00:55
*******************************************************************************************************/

int CBoxEdit::LoadMaxMissionNum(void)
{
	MAX_MISSION_NUM=GetIntValue("FileInfo","MaxMission");

	return MAX_MISSION_NUM;
}

CPoint CBoxEdit::GetManPosition()
{
    CPoint manPosition(0,0);
    for(int i=0;i<MAP_HEIGHT;i++)
    {
        for(int j=0;j<MAP_WIDTH;j++)
        {
            if (m_cMap[i][j]==MAP_MAN || m_cMap[i][j]==MAP_MAN_AT_DESTINATION)
            {
                manPosition.x=j;
                manPosition.y=i;
            }
        }
    }
    return manPosition;
}

/*******************************************************************************************************
函数名 : DrawMap
描  述 : 画整张地图
参  数 : 
         CDC *pDC : 要画设备环境DC
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月25日 1:45:07
*******************************************************************************************************/

void CBoxEdit::DrawMap(CDC *pDC)
{
    for (int y=0;y<MAP_HEIGHT;y++)
    {
        for(int x=0;x<MAP_WIDTH;x++)
        {
            switch(m_cMap[y][x])
            {
            case MAP_WALL:
                DrawGrid(x,y,pDC,BMP_INDEX_WALL);
                break;
			case MAP_ROAD:
				DrawGrid(x,y,pDC,BMP_INDEX_ROAD);
				break;
            case MAP_DESTINATION:
                DrawGrid(x,y,pDC,BMP_INDEX_DESTINATION);
                break;
			case MAP_BOX:
                DrawGrid(x,y,pDC,BMP_INDEX_BOX);
                break;
            case MAP_MAN:
                DrawGrid(x,y,pDC,BMP_INDEX_MAN);
                break;
            case MAP_MAN_AT_DESTINATION:
                DrawGrid(x,y,pDC,BMP_INDEX_MAN_AT_DESTINATION);
                break;
            case MAP_BOX_AT_DESTINATION:
                DrawGrid(x,y,pDC,BMP_INDEX_BOX_AT_DESTINATION);
                break;
			case MAP_OUTSIDE:
				DrawGrid(x,y,pDC,BMP_INDEX_OUTSIDE);
            }
        }
    }
}

/*******************************************************************************************************
函数名 : DrawGrid
描  述 : 画(x,y)格地图
参  数 : 
         int x : 要画格的X坐标
		 int y : 要画格的Y坐标
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月25日 1:42:45
*******************************************************************************************************/

void CBoxEdit::DrawGrid(int x, int y, CDC* pDC, int index)
{
	CClientDC dc(AfxGetMainWnd());
	CBitmap bmp;
	bmp.LoadBitmap(IDB_MAP);

	CDC mapDC;
	mapDC.CreateCompatibleDC(&dc);
	CBitmap *pOB=mapDC.SelectObject(&bmp);
	pDC->BitBlt(x * MAP_SMALL_SQUARE_SIZE, y * MAP_SMALL_SQUARE_SIZE,
		MAP_SMALL_SQUARE_SIZE, MAP_SMALL_SQUARE_SIZE,
		&mapDC,index * MAP_SMALL_SQUARE_SIZE, 0, SRCCOPY);
	mapDC.SelectObject(pOB);
}

void CBoxEdit::UpdateMap(UINT nChar)
{
    int x1, y1, x2, y2, x3, y3;

    x1 = m_ptManPosition.x;
    y1 = m_ptManPosition.y;

    switch (nChar)
    {
    case VK_UP:
        x2 = x1;
        y2 = y1 - 1;
        x3 = x1;
        y3 = y1 - 2;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_DOWN:
        x2 = x1;
        y2 = y1 + 1;
        x3 = x1;
        y3 = y1 + 2;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_LEFT:
        x2 = x1 - 1;
        y2 = y1;
        x3 = x1 - 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_RIGHT:
        x2 = x1 + 1;
        y2 = y1;
        x3 = x1 + 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case 82:  //R  replay this mission
    case 114: //r  replay this mission
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 113:  //F2  play next mission
        m_iMissionNum = m_iMissionNum + 1;
        if (m_iMissionNum > MAX_MISSION_NUM)
            m_iMissionNum = 1;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 112:  //F1  play forward mission

        m_iMissionNum = m_iMissionNum - 1;
        if (m_iMissionNum < 1)
            m_iMissionNum = MAX_MISSION_NUM;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
    }
}

void CBoxEdit::UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
    switch (m_cMap[y2][x2])
    {
    case MAP_BACKGROUP:           //wrong map
        AfxMessageBox("wrong map");
        break;
    case MAP_WHITEWALL:          //do nothing
        
        break;
    case MAP_BLUEWALL:           //can go
        m_cMap[y2][x2] = MAP_MANWALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;

        break;

    case MAP_BALL:               //can go
        m_cMap[y2][x2] = MAP_MANBALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;        
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;

        break;

    case MAP_YELLOWBOX:          //under judge
        if (m_cMap[y3][x3] == MAP_BALL)   // can go
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) //can go
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        break;

    case MAP_REDBOX:             //under judge
        if (m_cMap[y3][x3] == MAP_BALL)   // can go
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) //can go
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }        
        break;

    case MAP_MANWALL:            //wrong map
        AfxMessageBox("wrong map");
        break;

    case MAP_MANBALL:            //wrong map
        AfxMessageBox("wrong map");
        break;
    }
}

/*******************************************************************************************************
函数名 : WallIsClose
描  述 : 判断围墙是否闭合
参  数 : 
         CPoint p     : 当前点
		 CPoint start : 开始判断的围墙起点                    ++++                 +++++
		 CSize back   : 回到上一点的增量                      +   +  ——没有闭合  +   +  ——闭合
返回值 : bool 返回真值表示围墙闭合,返回假值表示围墙没有闭合   +++++                +++++
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月29日 20:26:30
*******************************************************************************************************/

bool CBoxEdit::WallIsClose(CPoint p,CPoint start,CSize back=CSize(9,9))
{
	CPoint next;
	CSize prev;
	for(int i=0;i<4;i++)
	{
		next=p+CSize(dx[i],dy[i]);
		
		if(next.x<0 || next.x>=MAP_WIDTH || next.y<0 || next.y>=MAP_HEIGHT  //越界
			|| m_cMap[next.y][next.x]!=MAP_WALL  //不是墙
			|| CSize(dx[i],dy[i])==back)  //回了老路
			continue;
		
		prev=p-next;

		if(next==start)
			return true;
		else if(WallIsClose(next,start,prev))
			return true;
		
	}
	return false;
}

/*******************************************************************************************************
函数名 : MissionIsSame
描  述 : 当前编辑的关卡地图中是否已经存在
参  数 : 无
返回值 : bool 返回真值表示存在,返回假值表示没有
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月31日 12:08:57
*******************************************************************************************************/

bool CBoxEdit::MissionIsSame()
{
    bool bResult=false;  //函数返回值

	CString EditingMission;  //当前编辑的关卡地图
	for(int y=m_iMinYPos;y<=m_iMaxYPos;y++)
		for(int x=m_iMinXPos;x<=m_iMaxXPos;x++)
			EditingMission+=m_cMap[y][x];

	CString strMission;
	LoadMaxMissionNum();
	for(int i=1;i<=MAX_MISSION_NUM;i++)
	{
		strMission.Format("M%d",i);
		if(EditingMission==GetStringValue(strMission,"Map")) return true;
	}

	return false;
}

/*******************************************************************************************************
函数名 : IsFinish
描  述 : 检查搬运工是否有且只有一个
         检查箱子数和目的点数是否相同
		 检查围墙是否闭合
		 检查地图中是否有此关卡
参  数 : 无
返回值 : BOOL 返回真值表示完成,假值表示没有完成
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年10月28日 19:34:18
*******************************************************************************************************/

bool CBoxEdit::IsFinish()
{
	CPoint p(-1,-1);

	int *pMinX=new int[MAP_HEIGHT],
		*pMaxX=new int[MAP_HEIGHT],
		*pMinY=new int[MAP_WIDTH],
		*pMaxY=new int[MAP_WIDTH];
		
	m_iMinXPos=MAP_WIDTH;
	m_iMaxXPos=-1;
	m_iMinYPos=MAP_HEIGHT;
	m_iMaxYPos=-1;

	for(int i=0;i<MAP_HEIGHT;i++)
		pMinX[i]=pMaxX[i]=-1;
	for(int i=0;i<MAP_WIDTH;i++)
		pMinY[i]=pMaxY[i]=-1;

	int NumberOfMan=0,
		NumberOfBox=0,
		NumberOfDestination=0;
    for(int y=0;y<MAP_HEIGHT;y++)
    {
        for(int x=0;x<MAP_WIDTH;x++)
        {
			switch(m_cMap[y][x])
			{
			case MAP_MAN:
				NumberOfMan++;
				break;
			case MAP_BOX:
				NumberOfBox++;
				break;
			case MAP_BOX_AT_DESTINATION:
				NumberOfBox++;
				NumberOfDestination++;
				break;
			case MAP_DESTINATION:
				NumberOfDestination++;
				break;
			case MAP_MAN_AT_DESTINATION:
				NumberOfMan++;
				NumberOfDestination++;
				break;
			case MAP_WALL:
				if(pMinX[y]==-1) pMinX[y]=x;
				pMaxX[y]=x;
				if(pMinY[x]==-1) pMinY[x]=y;
				pMaxY[x]=y;

				if(p==CPoint(-1,-1))p=CPoint(x,y);
				break;
			}			
        }
    }

	CString err;
	if(NumberOfMan!=1) err+="搬运工有且只能有一个！\n";
	if(NumberOfBox==0) err+="不能没有箱子！\n";
	if(NumberOfDestination==0) err+="不能没有目的点！\n";
	if(NumberOfBox!=NumberOfDestination) err+="箱子数与目的点数不相等！\n";
	
	for(int i=0;i<MAP_HEIGHT;i++)
	{
		if(pMinX[i]==-1 || pMaxX[i]==-1) continue;
		if(pMinX[i]<m_iMinXPos)	m_iMinXPos=pMinX[i];
		if(pMaxX[i]>m_iMaxXPos)	m_iMaxXPos=pMaxX[i];
	}

	for(int i=0;i<MAP_WIDTH;i++)
	{
		if(pMinY[i]==-1 || pMaxY[i]==-1) continue;
		if(pMinY[i]<m_iMinYPos)	m_iMinYPos=pMinY[i];
		if(pMaxY[i]>m_iMaxYPos)	m_iMaxYPos=pMaxY[i];
	}
	
	if(p==CPoint(-1,-1))
		err+="四周要有围墙！";
	//else if(!WallIsClose(p,p))
	//	err+="围墙没有闭合！";
	else
	{
		for(int y=m_iMinYPos+1;y<m_iMaxYPos;y++)
		{
			for(int x=m_iMinXPos+1;x<m_iMaxXPos;x++)
			{
				if(y>pMinY[x] && y<pMaxY[x] && x>pMinX[y] && x<pMaxX[y]  //在围墙内
				&& m_cMap[y][x]==MAP_OUTSIDE)  //围墙内通道是OUTSIDE
					m_cMap[y][x]=MAP_ROAD;  //改为通道
			}
		}
		AfxGetMainWnd()->Invalidate();  //更新窗口
	}

	if(MissionIsSame())
		err+="地图中已有相同关卡！";

	delete[] pMinX;
	delete[] pMaxX;
	delete[] pMinY;
	delete[] pMaxY;

	if(!err.IsEmpty())
	{
		AfxGetMainWnd()->MessageBox(err,"提示",MB_ICONASTERISK | MB_ICONINFORMATION);
		return false;
	}
	return true;
}

BOOL CBoxEdit::ChangeMissionNum(int iNum)
{
	if((iNum>MAX_MISSION_NUM)||(iNum<1))
	{
		return FALSE;
	}
	else
	{
        m_iMissionNum = iNum;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
		return TRUE;
	}
}

void CBoxEdit::ChangeMap(int x, int y, int iState)
{
    m_cMap[y][x] = iState;
}

void CBoxEdit::ClearMap(void)
{
	for(int x=0;x<MAP_WIDTH;x++)
		for(int y=0;y<MAP_HEIGHT;y++)
		{
            m_cMap[y][x]=MAP_OUTSIDE;
		}
}

bool CBoxEdit::NewMap(int iWidth,int iHeight)
{
	if(iWidth>M_TAB_WIDTH || iHeight>M_TAB_HEIGHT) return false;

	MAP_WIDTH=iWidth;
	MAP_HEIGHT=iHeight;

	CWnd *pWnd=AfxGetMainWnd();
	CRect rcWindow;
	pWnd->GetWindowRect(&rcWindow);
	pWnd->SetWindowPos(NULL,rcWindow.top,rcWindow.left,
		iWidth*MAP_SMALL_SQUARE_SIZE+10,iHeight*MAP_SMALL_SQUARE_SIZE+48,
		SWP_NOMOVE|SWP_NOZORDER);

	ClearMap();
	pWnd->Invalidate();
	return true;
}