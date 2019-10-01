/* ============================================================================================ *\ 
 * Author       :  吴春                                                                         * 
 * Email        :  ghost79@wjedu.net                                                            * 
 * Msn          :  wuchun79@163.com                                                             * 
 * QQ           :  23417690                                                                     * 
 * Version      :  0.2                                                                          * 
 * Created      :  2002/02/01 9:10:13                                                           * 
 * Modified     :  2006/10/24 17:15:46                                                          * 
 * FileName     :  BoxManClass.cpp                                                              * 
 * Description  :  This file is using for declaring the class BoxManClass,and this class is     * 
 *                 using for generating moves,evaluating and searching.                         * 
 *  Warning     :  Copyright (c) ghost79 2004 All rights reserved.                              * 
\* ============================================================================================ */

#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManClass.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define BM_THREAD_BUFFER_SIZE 0x40000

UINT MAX_MISSION_NUM=1;
extern CONST BYTE MAP_GRID_SIZE=30;  //最小方格图片单位的像素大小

/*******************************************************************************************************
结构名 : PathStruct
描  述 : 路径结构
结构体 : 
         char manx : 搬运工的X坐标
		 char many : 搬运工的Y坐标
		 char boxx : 箱子的X坐标
		 char boxy : 箱子的Y坐标
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

struct PathStruct{
	char manx;
	char many;
	char boxx;
	char boxy;
};

extern const char WALLB = 0;        //墙图片在IDB_MAP中的索引
extern const char NULLWALLB = 1;    //墙内通路图片在IDB_MAP中的索引
extern const char NULLB = 2;        //墙外图片在IDB_MAP中的索引
extern const char BOXB = 3;         //不在目的地的BOX在IDB_MAP中的索引
extern const char BOXATPOINTB = 4;  //在目的地的BOX在IDB_MAP中的索引
extern const char POINTB = 5;       //DESTINATION在IDB_MAP中的索引
extern const char MANBD1 = 6;       //MAN向下的图片1在IDB_MAP中的索引
const char MANBD2 = 7;       //MAN向下的图片2在IDB_MAP中的索引
const char MANBU1 = 8;       //MAN向上的图片1在IDB_MAP中的索引
const char MANBU2 = 9;       //MAN向上的图片2在IDB_MAP中的索引
const char MANBL1 = 10;      //MAN向左的图片1在IDB_MAP中的索引
const char MANBL2 = 11;      //MAN向左的图片2在IDB_MAP中的索引
const char MANBR1 = 12;      //MAN向右的图片1在IDB_MAP中的索引
const char MANBR2 = 13;      //MAN向右的图片2在IDB_MAP中的索引
const char MASK   = 14;      //Destination的MASK

const char dx[4] = { 1, 0, -1, 0 };
const char dy[4] = { 0, -1, 0, 1 };
const char pausetimer = 50;

extern const char MAP_WALL='+';
extern const char MAP_OUTSIDE='-';
extern const char MAP_DESTINATION='.';
extern const char MAP_BOX='#';
extern const char MAP_MAN='^';
extern const char MAP_BOX_AT_DESTINATION='@';
extern const char MAP_MAN_AT_DESTINATION='$';
extern const char MAP_ROAD=' ';
const char MAP_CAN_NOT_PUT_BOX='*';

const TCHAR FILE_NAME[7][20]={"kid.bxm","easy.bxm","game.bxm","normal.bxm","veryhard.bxm","impossible.bxm","custom.bxm"};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************************************
函数名 : BoxManClass
描  述 : 类BoxManClass构造函数,主要是初始化变量,以及内存映射地图文件map.dat和演示答案文件MoveWay.dat
参  数 : 无
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

BoxManClass::BoxManClass():midi1("sound\\music[1].mid"),midi2("sound\\music[2].mid"),
                           midi3("sound\\music[3].mid"),midi4("sound\\music[4].mid"),
						   midi5("sound\\music[5].mid"),midi6("sound\\music[6].mid"),
						   midi7("sound\\music[7].mid"),midi8("sound\\music[8].mid"),
						   midi9("sound\\music[9].mid")
{
	_ThreadCommand=BM_COMMAND_STOP_THREAD;
	_ThreadMessage=BM_MESSAGE_THINK_STOPED;
	//m_hStopEvent=NULL;
	//m_pThread=NULL;
	m_bAutoZoom=false;
	m_bAutoSequence=false;
	m_fZoomRate=1;
	m_iDifficulty=1;
	m_bTwain=FALSE;
	m_nKey=VK_DOWN;
	m_nCurrentScene=0;
	m_nTotalStep=0;
	m_ShowPath=NULL;
	m_bBoxMovedToDestination=FALSE;
	m_bEnableSound=TRUE;
	m_CanUndo=false;
	m_pmanmoveway=NULL;
	m_pDrawWnd=NULL;
	m_CanMoveToBadPoint=TRUE;
	m_bIsPause=false;
	m_bCanPaste=false;
	_ThinkingMap=0;

	TCHAR exeFullPath[MAX_PATH]; 
    CString strPath; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH); 
    m_strSysPath=(CString)exeFullPath; 
    int position=m_strSysPath.ReverseFind('\\'); 
    m_strSysPath=m_strSysPath.Left(position+1);

	SetFileName(m_strSysPath+"kid.bxm");

	try
	{
		CFile fway(m_strSysPath+"MoveWay.dat",CFile::modeRead);
		m_wayfilelength=(DWORD)fway.GetLength();
		m_hway=::GlobalAlloc(GHND,m_wayfilelength);
		void *p=(void *)::GlobalLock(m_hway);
		fway.Read(p,m_wayfilelength);
		::GlobalUnlock(m_hway);
		fway.Close();
	}
	catch(CFileException *fe)
	{
		::MessageBeep(MB_ICONEXCLAMATION);
		switch(fe->m_cause)
		{
		case CFileException::fileNotFound:
			::MessageBox(NULL,"没有找到文件\"MvoeWay.dat\",程序不能继续.",fe->m_strFileName,MB_OK|MB_ICONERROR);
			::ExitProcess(1);
		default:
			::MessageBox(NULL,"文件错误,程序不能继续.",fe->m_strFileName,MB_OK|MB_ICONERROR);
			::ExitProcess(2);
		}
	}

	m_pdibPaint=new CDib(CSize(100*MAP_GRID_SIZE,100*MAP_GRID_SIZE),24);

	m_wayfilechanged=false;
	m_nowmap=1;
	m_pmanmoveway=new CPtrArray();
	LoadMaxMissionNum();
}

/*******************************************************************************************************
函数名 : ~BoxManClass
描  述 : 类BoxManClass析构函数,主要是将缓冲区中的数据写入MoveWay.dat文件和释放内存
参  数 : 无
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

BoxManClass::~BoxManClass()
{
	_ThreadCommand = BM_COMMAND_STOP_THREAD;
	if(m_wayfilechanged)
	{
		try
		{
			CFile fway(m_strSysPath+"MoveWay.dat",CFile::modeWrite);
			fway.SetLength(m_wayfilelength);
			fway.SeekToBegin();
			void *p=(void *)::GlobalLock(m_hway);
			fway.Write(p,m_wayfilelength);
			::GlobalUnlock(m_hway);
			fway.Close();
		}
		catch(CFileException *fe)
		{
			switch(fe->m_cause)
			{
			case CFileException::fileNotFound:
				::MessageBox(NULL,"没有找到文件\"MvoeWay.dat\",走法不能纪录.",fe->m_strFileName,MB_OK|MB_ICONERROR);
				::ExitProcess(1);
			default:
				::MessageBox(NULL,"文件错误,走法不能纪录.",fe->m_strFileName,MB_OK|MB_ICONERROR);
				::ExitProcess(2);
			}
		}
	}
	::GlobalFree(m_hway);
	DeleteAllPath(m_path);
	if(m_ShowPath)
	{
		DeleteAllPath(*m_ShowPath);
		delete m_ShowPath;
	}
	delete m_pmanmoveway;
	m_mapB.DeleteObject();
	m_dcMap.SelectObject(m_pOB);
	m_dcMap.DeleteDC();
	delete m_pdibPaint;
	if(m_bCanPaste) DeleteFile(m_strSysPath+"ClipBoard.tmp");
}

/*******************************************************************************************************
函数名 : SetDrawWnd
描  述 : 传递程序主窗口指针给m_pDrawWnd成员变量并创建窗口环境CBitmap m_mpaB
参  数 :
         CWnd *pWnd : 视图窗口指针
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

void BoxManClass::SetDrawWnd(CWnd *pWnd)
{
	m_pDrawWnd=pWnd;
	CClientDC dc(m_pDrawWnd);
	m_dcMap.CreateCompatibleDC(&dc);
	m_mapB.Attach(m_pdibPaint->CreateSection(&dc));
	m_pOB=m_dcMap.SelectObject(&m_mapB);

	/*BITMAPINFO dib={0};
	dib.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	dib.bmiHeader.biWidth=MAP_GRID_SIZE*100;
	dib.bmiHeader.biHeight=MAP_GRID_SIZE*100;
	dib.bmiHeader.biPlanes=1;
	dib.bmiHeader.biBitCount=24;
	dib.bmiHeader.biCompression=BI_RGB;

	LPBYTE *pDib;
	m_mapB.Attach(::CreateDIBSection(dc.GetSafeHdc(),&dib,DIB_RGB_COLORS,(LPVOID *)&pDib,NULL,0));

	m_pOB=m_dcMap.SelectObject(&m_mapB);*/


	AttachMapToMemory();
}

/*******************************************************************************************************
函数名 : ReadMap
描  述 : 读取内存映射文件中的地图
参  数 :
         unsigned int index : 关卡号
返回值 : bool 返回false表示读取失败, true表示读取成功
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

bool BoxManClass::ReadMap(unsigned int index)
{
	CString strMission;
	strMission.Format("M%d",index);
	m_x=GetIntValue(strMission,"Width");
	m_y=GetIntValue(strMission,"Height");
	CString strMap=GetStringValue(strMission,"Map");
	if(m_x==0 || m_y==0 || strMap.IsEmpty()  //无此关地图
		|| m_x>MAXMAPSIZEX || m_y>MAXMAPSIZEY
		|| m_x*m_y!=strMap.GetLength())  //地图太大
		return false;

	ExitThinkThreak();

	m_nowmap=index;
	
	int i=0;
	m_NumberOfBox=0;
	for(int y=0;y<m_y;y++)
	{
		for(int x=0;x<m_x;x++)
		{
			m_map[x][y]=strMap[i++];
			switch(m_map[x][y])
			{
			case MAP_BOX_AT_DESTINATION:
				m_map[x][y]=MAP_DESTINATION;
				m_bnm[x][y]=MAP_BOX;
				m_NumberOfBox++;
				break;
			case MAP_MAN_AT_DESTINATION:
				m_map[x][y]=MAP_DESTINATION;
				m_bnm[x][y]=MAP_MAN;
				break;
			case MAP_MAN:
				m_map[x][y]=MAP_ROAD;
				m_bnm[x][y]=MAP_MAN;
				break;
			case MAP_BOX:
				m_map[x][y]=MAP_ROAD;
				m_bnm[x][y]=MAP_BOX;
				m_NumberOfBox++;
				break;
			default:
				m_bnm[x][y]=0;
			}
		}
	}

	m_mapsizex = m_x<12 ? 12 : m_x;					
	m_mapsizey = m_y<8 ? 8 : m_y;

	DeleteAllPath(m_path);
	PrepareThinking(index);
	m_CanUndo=false;
	m_TheShowStep=0;
	//可以开始线程
	if(!m_computerthinkout)
		_ThreadCommand=BM_COMMAND_RUN_THREAD;
	//else
	//	_ThreadMessage = BM_MESSAGE_THINK_OUT;
	//////////
	return true;
}

/*******************************************************************************************************
函数名 : Paint
描  述 : 窗口重画
参  数 : 无
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

void BoxManClass::Paint(CRgn *rgnClip)
{
	CClientDC dc(m_pDrawWnd);
	dc.SelectClipRgn(rgnClip);

	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,
		static_cast <int>(MAP_GRID_SIZE*m_mapsizex*m_fZoomRate),
		static_cast <int>(MAP_GRID_SIZE*m_mapsizey*m_fZoomRate),
		&m_dcMap,0,0,MAP_GRID_SIZE*m_mapsizex,MAP_GRID_SIZE*m_mapsizey,SRCCOPY);
	/*m_pdibPaint->Stretch(&dc,CPoint(0,0),
		CSize(static_cast <int>(MAP_GRID_SIZE*m_mapsizex*m_fZoomRate),
		static_cast <int>(MAP_GRID_SIZE*m_mapsizey*m_fZoomRate)),
		CPoint(0,0),
		CSize(static_cast <int>(MAP_GRID_SIZE*m_mapsizex*m_fZoomRate),
		static_cast <int>(MAP_GRID_SIZE*m_mapsizey*m_fZoomRate)),
		SRCCOPY);*/
}

/*******************************************************************************************************
函数名 : DrawIt
描  述 : 画(x,y)格处图片
参  数 : 
         char x : 要画格的X坐标
		 char y : 要画格的Y坐标
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

void BoxManClass::DrawIt(char x, char y,CDC *pDC)
{
	if((x<0)||(x>=m_x)||(y<0)||(y>=m_y)) return;

	char index=GetDrawIndex(x,y);
	if(index>=MANBD1 && index<=MANBR2 && m_map[x][y]==MAP_DESTINATION)
	{
		DrawMan();
		return;
	}
	
	x+=(m_mapsizex-m_x)/2;
	y+=(m_mapsizey-m_y)/2;

	m_dibMap.Stretch(pDC,
		CPoint(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE),
		CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
		CPoint(index*MAP_GRID_SIZE,0),
		CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
		SRCCOPY);
}

/*******************************************************************************************************
函数名 : DrawAllMap
描  述 : 画整张地图
参  数 : 无
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

void BoxManClass::DrawAllMap()
{
	int xstart=(m_mapsizex-m_x)/2,
		ystart=(m_mapsizey-m_y)/2;
	if (m_mapsizex>m_x||m_mapsizey>m_y)
	{
		for(char y=0;y<=m_mapsizey;y++)
			for(char x=0;x<=m_mapsizex;x++)
			{
				if(x+1>xstart && x+1<xstart+m_x
					&& y+1>ystart && y+1<ystart+m_y)
					continue;

				m_dibMap.Stretch(&m_dcMap,
					CPoint(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE),
					CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
					CPoint(NULLB*MAP_GRID_SIZE,0),
					CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
					SRCCOPY);
			}
	}

	BYTE index;
	int xx,yy;		
	for(char y=0;y<m_y;y++)
		for(char x=0;x<m_x;x++)
		{
			index=GetDrawIndex(x,y);
			
			xx=xstart+x;
			yy=ystart+y;
		
			m_dibMap.Stretch(&m_dcMap,
				CPoint(xx*MAP_GRID_SIZE,yy*MAP_GRID_SIZE),
				CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
				CPoint(index*MAP_GRID_SIZE,0),
				CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
				SRCCOPY);
		}
}

/*******************************************************************************************************
函数名 : MoveTowards
描  述 : 移动搬运工
参  数 : 
        char dx : 搬运工X方向的偏移量
		char dy : 搬运工Y方向的偏移量
返回值 : unsigned char 返回BM_ERROR_CANNOT_MOVE_THERE表示不能移至目的地
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

unsigned char BoxManClass::MoveTowards(char dx, char dy)
{
	unsigned char result=BM_ERROR_CANNOT_MOVE_THERE;
	if (dx==0&&dy==0) return result;
	char tx=m_mx+dx;
	char ty=m_my+dy;
	char ttx=tx+dx;
	char tty=ty+dy;

	if(m_map[tx][ty]!=MAP_WALL)
	{
		switch(m_bnm[tx][ty])
		{
		case 0:
			result=BM_MAN_MOVED;
			PlaySound(result);
			break;
		case MAP_BOX:
			if((m_map[ttx][tty]!=MAP_WALL)&&(m_bnm[ttx][tty]!=MAP_BOX))
			{
				if (m_CanMoveToBadPoint)
					result=BM_BOX_MOVED;
				else if(m_map[ttx][tty]!=MAP_CAN_NOT_PUT_BOX)
					result=BM_BOX_MOVED;
				else result=BM_MOVED_TO_BAD_POINT;
			}
		}
	}
	if((result==BM_MAN_MOVED)||(result==BM_BOX_MOVED))
	{
		if(m_mx<tx)
			m_nKey=VK_RIGHT;
		else if(m_mx>tx)
			m_nKey=VK_LEFT;
		if(m_my<ty)
			m_nKey=VK_DOWN;
		else if(m_my>ty)
			m_nKey=VK_UP;

		CRgn rgnClip,rgnTemp;
		rgnClip.CreateRectRgnIndirect(GetClipRect(m_mx,m_my));
		rgnTemp.CreateRectRgnIndirect(GetClipRect(tx,ty));
		rgnClip.CombineRgn(&rgnClip,&rgnTemp,RGN_OR);
		rgnTemp.DeleteObject();

		m_bnm[m_mx][m_my]=0;
		DrawIt(m_mx,m_my,&m_dcMap);
		m_bnm[tx][ty]=MAP_MAN;
		DrawIt(tx,ty,&m_dcMap);
		m_mx=tx;
		m_my=ty;
		
		if(result==BM_BOX_MOVED)
		{
			m_bnm[ttx][tty]=MAP_BOX;
			DrawIt(ttx,tty,&m_dcMap);
			AddMapToPath(tx-dx,ty-dy,tx,ty);

			rgnTemp.CreateRectRgnIndirect(GetClipRect(ttx,tty));
			rgnClip.CombineRgn(&rgnClip,&rgnTemp,RGN_OR);
		}
		
		Paint(&rgnClip);
	}
	
	for(int j=0; j<m_y; j++)
		for(int i=0;i<m_x;i++)
			if((m_map[i][j]==MAP_DESTINATION)&&(m_bnm[i][j]!=MAP_BOX))
			{
		//		PlaySound(result);
				return result;
			}
	BoxMoveOk(m_path);
	result=BM_MOVED_OK;
//	PlaySound(result);
	return result;
}

/*******************************************************************************************************
函数名 : BoxMoveOk
描  述 : 记录走法
参  数 : 
         CPtrArray &record : 记录所有走法的CPtrArray
返回值 : 无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月4日 16:35:47
*******************************************************************************************************/

void BoxManClass::BoxMoveOk(CPtrArray &record)
{
	// the map moved ok
	unsigned int boxmn=record.GetSize();
	char tc1='[';
	char tc2=']';
	if(&record==&m_path){ tc1='{'; tc2='}'; }
	
	//可以停止线程
	//_ThreadCommand = BM_COMMAND_STOP_THREAD;
	//////////
	CString str;
	str.Format("%d",(m_iDifficulty-1)*2000+m_nowmap);
	if(m_noanswerrecoded)
	{
		//在MoveWay.dat的最后记录走法
		int iRecodSize=7+str.GetLength()*sizeof(TCHAR)+boxmn*4*sizeof(TCHAR);
		m_wayfilechanged=true;
		::GlobalReAlloc(m_hway,m_wayfilelength+iRecodSize,GHND);
		char *p=(char *)::GlobalLock(m_hway);
		p+=m_wayfilelength;
		m_wayfilelength+=iRecodSize;
		//记录关卡号
		*p++='M';
		for(char stri=0;stri<str.GetLength();stri++)
			*p++=str.GetAt(stri);
		*p++='\r';
		*p++='\n';
		//记录答案内容('['与']'或'{'与'}'之间为答案内容)
		*p++=tc1;
		for(unsigned int t=0;t<boxmn;t++)
		{
			PathStruct *ps=(PathStruct*)record.GetAt(t);
			*p++=ps->manx;
			*p++=ps->many;
			*p++=ps->boxx;
			*p++=ps->boxy;
		}
		*p++=tc2;
		*p++='\r';
		*p='\n';
		::GlobalUnlock(m_hway);
		m_boxmovestepnumber=boxmn;
	}
	else if(!m_computerthinkout&&(boxmn<m_boxmovestepnumber||tc1=='['))
	{
		//改变已有的纪录,将其放在最后
		m_wayfilechanged=true;
		char *p=(char *)::GlobalLock(m_hway);
		char *MoveBufferEnd=p+m_wayfilelength;
		p+=m_TheMapsMoveWaySavePoint;
		int delta=7+str.GetLength()*sizeof(TCHAR)+m_boxmovestepnumber*4*sizeof(TCHAR);
		for(char *tp=p+delta;tp<MoveBufferEnd;tp++,p++) *p=*tp;
		*p++='M';
		for(char stri=0;stri<str.GetLength();stri++)
			*p++=str.GetAt(stri);
		*p++='\r';
		*p++='\n';
		*p++=tc1;
		for(unsigned int t=0;t<boxmn;t++)
		{
			PathStruct *ps =(PathStruct*)record.GetAt(t);
			*p++=ps->manx;
			*p++=ps->many;
			*p++=ps->boxx;
			*p++=ps->boxy;
		}
		*p++=tc2;
		*p++='\r';
		*p='\n';
		::GlobalUnlock(m_hway);
		//一定是减小内存
		::GlobalReAlloc(m_hway,m_wayfilelength-(m_boxmovestepnumber-boxmn)*4*sizeof(TCHAR),GHND);
		m_wayfilelength-=(m_boxmovestepnumber-boxmn)*4*sizeof(TCHAR);//::GlobalSize( m_hway );
		m_boxmovestepnumber=boxmn;
	}
}

void BoxManClass::AddMapToPath(char manx, char many, char boxx, char boxy)
{
	PathStruct *p = new PathStruct;
	p->manx = manx;
	p->many = many;
	p->boxx = boxx;
	p->boxy = boxy;
	m_path.Add( p );
	m_CanUndo = true;
}

void BoxManClass::DeleteAllPath(CPtrArray &path)
{
	int n = path.GetSize();
	for( int i=0; i<n; i++ ){
		PathStruct *p = (PathStruct*)path.GetAt( i );
		delete p;
	}
	path.RemoveAll();
}

bool BoxManClass::Undo()
{
	if ( !m_CanUndo ) return false;
	int n = m_path.GetSize();
	PathStruct *p = (PathStruct*)m_path.GetAt( n-1 );
	m_path.RemoveAt( n-1 );
	if (n==1) m_CanUndo = false;

	m_bnm[m_mx][m_my] = 0;
	m_bnm[p->boxx][p->boxy] = MAP_BOX;
	m_bnm[p->manx][p->many] = MAP_MAN;
	char tx = 2 * p->boxx - p->manx;
	char ty = 2 * p->boxy - p->many;
	m_bnm[tx][ty] = 0;

	CRgn rgnClip,rgnTemp;	
	rgnClip.CreateRectRgnIndirect(GetClipRect(m_mx,m_my));
	rgnTemp.CreateRectRgnIndirect(GetClipRect(p->boxx,p->boxy));
	rgnClip.CombineRgn(&rgnClip,&rgnTemp,RGN_OR);

	rgnTemp.DeleteObject();
	rgnTemp.CreateRectRgnIndirect(GetClipRect(p->manx,p->many));
	rgnClip.CombineRgn(&rgnClip,&rgnTemp,RGN_OR);

	rgnTemp.DeleteObject();
	rgnTemp.CreateRectRgnIndirect(GetClipRect(tx,ty));
	rgnClip.CombineRgn(&rgnClip,&rgnTemp,RGN_OR);

	DrawIt( m_mx, m_my,&m_dcMap );
	DrawIt( p->boxx, p->boxy,&m_dcMap );
	DrawIt( p->manx, p->many,&m_dcMap );
	DrawIt( tx, ty,&m_dcMap );
	
	Paint(&rgnClip);

	m_mx = p->manx;
	m_my = p->many;

	delete p;
	return true;
}

char BoxManClass::PointAt(CPoint point)
{
	int tx=(m_mapsizex-m_x)/2;
	int ty=(m_mapsizey-m_y)/2;
	if ((point.x>(tx+m_x)*MAP_GRID_SIZE*m_fZoomRate) || (point.x<tx*MAP_GRID_SIZE*m_fZoomRate)
		|| (point.y>(ty+m_y)*MAP_GRID_SIZE*m_fZoomRate) || (point.y<ty*MAP_GRID_SIZE*m_fZoomRate))
		return BM_ERROR_PIONT_OUT;
	int tox=static_cast <int>(point.x/(MAP_GRID_SIZE*m_fZoomRate)-tx);
	int toy=static_cast <int>(point.y/(MAP_GRID_SIZE*m_fZoomRate)-ty);
//#ifdef _DEBUG
//	if(m_map[tox][toy]==MAP_CAN_NOT_PUT_BOX) AfxMessageBox("DEBUG模式,箱子不能推到此处");
//#endif
	if ( m_bnm[tox][toy] == MAP_MAN )
		return BM_ERROR_POINT_MAN;
	if ( m_map[tox][toy] == MAP_WALL )
		return BM_ERROR_POINT_WALL;
	if ( m_map[tox][toy] == MAP_OUTSIDE )
		return BM_ERROR_PIONT_OUT;
	MoveManTo( tox, toy, m_pmanmoveway);
	if ( m_pmanmoveway != NULL )
		return DoManMove();
	return BM_ERROR_CANNOT_MOVE_THERE;
}

void BoxManClass::MoveManTo(char x, char y,CPtrArray *way)
{
	CPtrArray pos;
	CWordArray from;
	CPoint *pn = new CPoint;
	pn->x = x;//注意:这里是倒过来走的
	pn->y = y;
	pos.Add( pn );
	from.Add( 0x7fff );
//	unsigned short head = 0;
	unsigned short now = 0;
	unsigned short end = 0;
	
	while( now <= end ){
		pn = (CPoint*)pos.GetAt( now );
		for ( char d = 0; d<4; d++ ){
			char tx = (char)pn->x + dx[d];
			char ty = (char)pn->y + dy[d];
			if ( (tx == m_mx)&&(ty == m_my) ){
			//	CPtrArray *way = new CPtrArray;
				while( now != 0x7fff ){
					pn = (CPoint*)pos.GetAt( now );
					now = from.GetAt( now );
					CPoint* pe = new CPoint;
					pe->x = pn->x;
					pe->y = pn->y;
					way->Add( pe );
				}
			//	return way;
			}
			if ( (m_map[tx][ty] != MAP_WALL) && (m_bnm[tx][ty] != MAP_BOX) && (m_bnm[tx][ty] != MAP_MAN) ){
				bool have = false;
				for ( unsigned short i=0; !have && (i<=end); i++ ){
					CPoint *tp = (CPoint*)pos.GetAt( i );
					if ( (tp->x == tx)&&(tp->y == ty) ) have = true;
				}
				if (!have){
					CPoint *pe = new CPoint;
					pe->x = tx;
					pe->y = ty;
					pos.Add( pe );
					from.Add( now );
					end++;
				}
			}
		}
		now++;
	}
	end = pos.GetSize();
	for(unsigned short i = 0; i<end; i++ ){
		pn = (CPoint*)pos.GetAt( i );
		delete pn;
	}
	pos.RemoveAll();
	from.RemoveAll();
//	return NULL;
}

unsigned char BoxManClass::DoManMove()
{
	unsigned char result=BM_ERROR_CANNOT_MOVE_THERE;
	for ( int i=0; i<m_pmanmoveway->GetSize(); i++ ){
		CPoint* p =(CPoint*)m_pmanmoveway->GetAt( i );
		char tx = char(p->x - m_mx);
		char ty = char(p->y - m_my);
		delete p;
		result=MoveTowards( tx, ty );
		//PlaySound(result);
		::Sleep(50);
	}
	m_nTotalStep+=m_pmanmoveway->GetSize();
	m_pmanmoveway->RemoveAll();
//	m_pmanmoveway = NULL;
	return result;
}

/*******************************************************************************************************
函数名 : PrepareThinking
描  述 : 优化地图,将箱子不可到的死方格标记为 MAP_CAN_NOT_PUT_BOX
         检查MoveWay.dat中是否有index关卡的答案
参  数 : 
         unsigned int index : 关卡号
返回值 : bool 返回真值表示MoveWay.dat中有此关卡的答案,假值表示无
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2002年1月3日 12:45:07
*******************************************************************************************************/

bool BoxManClass::PrepareThinking(unsigned int index)
{
	                                                      ////////////////////////////////
	//去掉四周的墙                                        //         d 1   d01          //  
	char y=m_y-1;                                         //        (i,j)  d 0          //
	char x=m_x-1;                                         //         d 3   d03          //
	                                                      ////////////////////////////////
	                                       		                                                      
	/*****************************************************************************************************
	* I.(i,j) 是通路, d01-d0-d03 一线是墙,如果 d1-(i,j)-d3 一线是通路,并且没有目的地,则 (i,j) 不能放箱子 *
	*                                                                                                    *
	* II.(i,j) 是通路, 与其相邻的四个方向中有两个相邻的方向是墙,则 (i,j) 不能放箱子 ( 如 d0 和 d1是墙 )  *
	*****************************************************************************************************/
	for(char j=1;j<y;j++)
	{
		for(char i=1;i<x;i++)  //判断(i,j)位置是否可以放box
		{
			if(m_map[i][j]==MAP_ROAD)  //(i,j)位置是通路
			{
				int u=0;  //与(i,j)位置相邻的四个方向( 右、上、左、下--记作 d0 d1 d2 d3 ) 有几面相邻的墙
				for(int d=0;d<4;d++)
				{
					if(m_map[i+dx[d]][j+dy[d]]==MAP_WALL)  //(i,j)位置的 当前 d 方向是墙( 记作 d0 )
					{
						u++;
						bool canputbox=false;
						int td=(d+3)%4;  //d0方逆时针转第三个方向( 记作 d3 )
						int tx=i;
						int ty=j;
						while(!canputbox)
						{
							tx+=dx[td];
							ty+=dy[td];
							if(m_map[tx][ty]==MAP_WALL) break;  //d3位置是墙
							if(m_map[tx][ty]==MAP_DESTINATION)  //d3位置是目的地
								canputbox=true;
							else if(m_map[tx+dx[d]][ty+dy[d]]!=MAP_WALL)  //d3 是通路 且 d03 不是墙
								canputbox=true;
						}
						td=(d+1)%4;  //d方向逆时针转第一个方向( 记作 d1 )
						tx=i;
						ty=j;
						while(!canputbox)
						{
							tx+=dx[td];
							ty+=dy[td];
							if(m_map[tx][ty]==MAP_WALL) break;  //d1位置是墙
							if(m_map[tx][ty]==MAP_DESTINATION)  //d1位置是目的地
								canputbox=true;
							else if(m_map[tx+dx[d]][ty+dy[d]]!=MAP_WALL)  //d1 是通路 且 d01 不是墙
								canputbox=true;
						}
						if(!canputbox) m_map[i][j]=MAP_CAN_NOT_PUT_BOX;  //I.
					}
					else  //(i,j)位置的d方向上不是墙
					{//endof if '+'
						if(u>1) m_map[i][j]=MAP_CAN_NOT_PUT_BOX;  //II.
						u=0;
					}
				}//endof for (d~4)
				if((u>1)||((u>0)&&(m_map[i+dx[0]][j+dy[0]]==MAP_WALL)))  //II.( d2 d3 是墙 )||( d0 d3 是墙 )
					m_map[i][j]=MAP_CAN_NOT_PUT_BOX;  
			}//endof if map == ' '
		}//endof for (i , j)
	}

	//分析moveway.dat文件
	char *p=(char *)::GlobalLock(m_hway);
	char str[256];
	bool ism=false;
	char i=0;
	m_noanswerrecoded=false;
	for(DWORD n=0;n<m_wayfilelength;n++,p++)
	{
		if(ism)
		{
			if(*p!='\r')
				str[i++]=*p;
			else
			{
				str[i]=0;
				unsigned int value=atoi(str)-(m_iDifficulty-1)*2000;
				if (value==index)
				{
					//find the map way
					p+=2;
					m_computerthinkout = (*p=='[') ? true : false;
					char *tp;
					for(tp=p;(*tp!=']')&&(*tp!='}');tp++);//注:无循环体
					m_boxmovestepnumber=(tp-p)/(4*sizeof(TCHAR));
					::GlobalUnlock(m_hway);
					return true;
				}
				i=0;
				m_TheMapsMoveWaySavePoint=-1;
				ism=false;
			}
		}
		else if(*p=='M')
		{
			ism=true;
			m_TheMapsMoveWaySavePoint=n;
		}
	}
	::GlobalUnlock(m_hway);
	m_noanswerrecoded=true;
	m_computerthinkout=false;
	return false;
}

void BoxManClass::ShowMoveWay()
{
	static int TotalStep=0;
	
	if ( m_TheShowStep == 0 ){
		if(!m_ShowPath)
			m_ShowPath=new CPtrArray;
		else
			DeleteAllPath(*m_ShowPath);			
		
		TotalStep=0;
		if (m_CanUndo) {
			while(m_CanUndo) Undo();
			//::MessageBox( m_pDrawWnd->m_hWnd, "开始演示", "Message", 0 );
			PathStruct *ps1 = new PathStruct;
			ps1->manx = m_mx;
			ps1->many = m_my;
			ps1->boxx = m_mx;
			ps1->boxy = m_my;
			m_ShowPath->Add( ps1 );
			TotalStep++;
		}
		char* p = (char*)::GlobalLock( m_hway );
		for ( p+=m_TheMapsMoveWaySavePoint; (*p!='{')&&(*p!='['); p++ );//no body
		p++;
		//TRACE( "%d\t", m_ShowPath->GetSize() );
		for ( unsigned int i=0; i<m_boxmovestepnumber; i++ ){
			PathStruct *ps = new PathStruct;
			ps->manx = *p++;
			ps->many = *p++;
			ps->boxx = *p++;
			ps->boxy = *p++;
			m_ShowPath->Add( ps );
			TotalStep++;
		}
		//TRACE( "%d\n", m_ShowPath->GetSize() );
		::GlobalUnlock( m_hway );
	}
	PathStruct* ps = (PathStruct*)m_ShowPath->GetAt( m_TheShowStep );
	if ( (m_mx != ps->manx) || (m_my != ps->many) ){
		MoveManTo( ps->manx, ps->many, m_pmanmoveway);
		if ( m_pmanmoveway != NULL ) DoManMove();
	}
	::Sleep(50);
	MoveTowards( ps->boxx-ps->manx, ps->boxy-ps->many );
	::Sleep(50);
	m_RemainShewStep = TotalStep - ++m_TheShowStep;
	if ( m_ShowPath->GetSize() == m_TheShowStep ){
		DeleteAllPath(*m_ShowPath);
		m_TheShowStep = m_RemainShewStep = 0;
		::MessageBox( m_pDrawWnd->m_hWnd, "演示完毕!", "Message", MB_ICONASTERISK | MB_ICONINFORMATION );
	}
}

void BoxManClass::ThinkTheWay()
{
	if ( _ThreadCommand == BM_COMMAND_STOP_THREAD ) {
		_ThreadMessage = BM_MESSAGE_THINK_OUT;
		return;
	}
	_ThreadMessage = BM_MESSAGE_THINKING;
	unsigned char i, j;
	if ( _ThinkingMap == m_nowmap ) return;
	else _ThinkingMap = m_nowmap;
	_x = m_x-1;
	_y = m_y-1;
	_x2 = m_x-2;
	_y2 = m_y-2;
	_structSize = ( m_NumberOfBox + 1 ) + 4;
	for ( j=0; j<m_y; j++ ) for ( i=0; i<m_x; i++ ) _con[i][j]=m_bnm[i][j];
	//there must use 0 to m_x, can't use 1 to _x, but i don't know why.
	//TRACE("
	_InitData();
	bool tb = _ThinkIt();

	::GlobalFree( _head );
	if( _ThreadMessage == BM_MESSAGE_THINKING ) _ThreadMessage = 0;
}

void BoxManClass::_InitData()
{
	unsigned char *p, **ap;
	unsigned char i, j;
	//定义一个计算用的内存
	p = (unsigned char*)GlobalAlloc( GPTR, _structSize * BM_THREAD_BUFFER_SIZE );
	_head = _now = p;
	_end = p+_structSize;
	ap = (unsigned char**)(_end-4);
	*ap = NULL;

	for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
		if ( _con[i][j] == '#' ){
			//*p++ = i;
			//*p++ = j;
			*p++ = (j-1) * _x2 + (i-1);
		}
	}
	//用'^'着色
	bool havechange;
	do{
		havechange = false;
		for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
			if ( m_map[i][j]!=MAP_WALL && _con[i][j]==0 &&
				( _con[i+1][j]=='^' || _con[i-1][j]=='^' || _con[i][j+1]=='^' || _con[i][j-1]=='^' ) ){
				_con[i][j] = '^';
				havechange = true;
			}
		}
		if ( !havechange ) break;
		havechange = false;
		for ( i=_x-1; i>0; i-- ) for ( j=_y-1; j>0; j-- ){
			if ( m_map[i][j]!=MAP_WALL && _con[i][j]==0 &&
				( _con[i+1][j]=='^' || _con[i-1][j]=='^' || _con[i][j+1]=='^' || _con[i][j-1]=='^' ) ){
				_con[i][j] = '^';
				havechange = true;
			}
		}
	}while ( havechange );
	//纪录人的位置
	for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
		if ( _con[i][j] == '^' ){
			//*p++ = i;
			//*p = j;
			*p = (j-1) * _x2 + ( i-1 );
			return;
		}
	}
	return;
}

inline void BoxManClass::_UnpackData(unsigned char *p)
{
	unsigned char i, j;

	//注意:这里一定是MAXMAPSIZEY*(_x-1)
	::memset( MAXMAPSIZEY+(char*)_con, 0, MAXMAPSIZEY*(_x-1) );
	//for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ) _con[i][j] = 0;
	for ( i=0; i<m_NumberOfBox; i++, p++ ){
		_con[ *p % _x2 + 1 ][ *p / _x2 + 1 ] = '#';//放'#'
	}
	//放'^'
	_con[ *p % _x2 + 1 ][ *p / _x2 + 1 ] = '^';
	//用'^'着色
	bool havechange;
	do{
		havechange = false;
		for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
			if ( m_map[i][j]!=MAP_WALL && _con[i][j]==0 &&
				( _con[i+1][j] == '^' || _con[i-1][j]=='^' || _con[i][j+1]=='^' || _con[i][j-1]=='^' ) ){
				_con[i][j] = '^';
				havechange = true;
			}
		}
		if ( !havechange ) break;
		havechange = false;
		for ( i=_x-1; i>0; i-- ) for ( j=_y-1; j>0; j-- ){
			if ( m_map[i][j]!=MAP_WALL && _con[i][j]==0 &&
				( _con[i+1][j]=='^' || _con[i-1][j]=='^' || _con[i][j+1]=='^' || _con[i][j-1]=='^'  ) ){
				_con[i][j] = '^';
				havechange = true;
			}
		}
	}while ( havechange );
}

inline bool BoxManClass::_IsOk(unsigned char *p)
{
	bool ok=true;
	for ( int i=0; ok && (i<m_NumberOfBox); i++ , p++ ){
		ok = (m_map[ *p % _x2 + 1 ][ *p / _x2 + 1 ] == MAP_DESTINATION);
	}
	return ok;
}

bool BoxManClass::_ThinkIt()
{
	unsigned char *np, nx, ny, fx, fy, bx, by, k, d;
	int numberofnode=0;
	bool conChanged;
	bool Ok;

	Ok = _IsOk( _end - _structSize );
	if ( Ok ){
		//MsgBox( "ERROR", "The Map needn't think." );
		_ThreadMessage = BM_MESSAGE_THINK_OUT;
		::MessageBeep( MB_OK );
		return true;
	}
	//DWORD dwReturn;
	while ( _now != _end && _ThreadCommand != BM_COMMAND_STOP_THREAD ){
		_UnpackData( _now );
		conChanged = false;
		//move
		np = _now;
		for ( k=0; k<m_NumberOfBox; k++, np++ ){
			//nx = *np++;
			//ny = *np++;
			nx = *np % _x2 + 1;
			ny = *np / _x2 + 1;
			for ( d=0; d<4; d++ ){
				fx = nx + dx[d];
				fy = ny + dy[d];
				bx = nx - dx[d];
				by = ny - dy[d];
				if (_ThreadCommand == BM_COMMAND_STOP_THREAD ){
					_ThreadMessage = BM_MESSAGE_THINK_STOPED;
					return false;
				}
				if ( conChanged ) { _UnpackData( _now ); conChanged = false; }
				if ( m_map[fx][fy]!=MAP_WALL && m_map[fx][fy]!=MAP_CAN_NOT_PUT_BOX && _con[fx][fy]!='#' && _con[bx][by]=='^' ){
					_con[fx][fy] = '#';
					_con[nx][ny] = '%';//移动后的人
					_con[bx][by] = '%';
					conChanged = true;
					_PackData();
					if ( !_AlreadyHave() ) {
						Ok = _IsOk( _end );
						_end += _structSize;
						if ( BM_THREAD_BUFFER_SIZE < ++numberofnode) {
							_ThreadMessage = BM_MESSAGE_BUFFER_FULL;
							::MessageBeep( MB_ICONHAND );
							return false;
						}
						if ( Ok ) {
							_OutputToFile();
							//char s[40];
							//wsprintf(s,"OK! 共产生了%d个节点",numberofnode);
							//MsgBox( "OK", s );
							_ThreadMessage = BM_MESSAGE_THINK_OUT;
							::MessageBeep( MB_OK );
							return true;
						}
					}
				}//endof can move
			}//endof for d<4
		}//endof for k<m_NumberOfBox
		_now += _structSize;
	}//endof while !IsOk
	//UnpackData( head );
	//char s[40];
	//wsprintf(s,"No Answer! 共产生了%d个节点",numberofnode);
	//MsgBox( "ERROR", s );
	if ( _now == _end  ){
		_ThreadMessage = BM_MESSAGE_NO_ANSWER;
		::MessageBeep( MB_ICONQUESTION );
	} else _ThreadMessage = BM_MESSAGE_THINK_STOPED;
	return false;
}

void BoxManClass::_OutputToFile()
{
	unsigned char *tp, **ap, *p;
	//将链表的方向颠倒
	p = _end - _structSize;
	tp = NULL;
	while ( p != _head ) {
		unsigned char *np = p;
		ap = (unsigned char**)(p+_structSize-4);
		p = *ap;
		*ap = tp;
		tp = np;
	}
	ap = (unsigned char**)(p+_structSize-4);
	*ap = tp;
	_now = _head;
	//将路径记入way中
	char pcon[MAXMAPSIZEX][MAXMAPSIZEY];
	unsigned char i, j;
	CPtrArray way;

	_UnpackData( _now );
	for ( j=1; j<_y; j++ ) for ( i=0; i<_x; i++ ) pcon[i][j]=_con[i][j];
//	char **
	ap = (unsigned char**)(_now+_structSize-4);
	_now = *ap;
	while ( _now != NULL ){
		_UnpackData( _now );
		PathStruct *ps = new PathStruct;
		for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
			if (_con[i][j]=='^' && pcon[i][j]=='#'){
				ps->boxx=i;
				ps->boxy=j;
			}
		}
		for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
			if (_con[i][j]=='#' && pcon[i][j]!='#'){
				ps->manx = ps->boxx * 2 - i;
				ps->many = ps->boxy * 2 - j;
			}
		}
		way.Add( ps );
		for ( j=1; j<_y; j++ ) for ( i=0; i<_x; i++ ) pcon[i][j]=_con[i][j];
//		char **
		ap = (unsigned char**)(_now+_structSize-4);
		_now = *ap;
	}
	//纪录入内存中
	BoxMoveOk( way );
	//清除way;
	for( i=0; i<way.GetSize(); i++ ){
		PathStruct *ps = (PathStruct*)way.GetAt( i );
		delete ps;
	}
	way.RemoveAll();
	PrepareThinking( m_nowmap );
}

inline bool BoxManClass::_AlreadyHave()
{
	unsigned char *p = _head , *nextp, *temp, *ep;
	bool equal = false;

	while ( !equal && (p != _end) ){
		nextp = p+_structSize;
		temp = nextp-4;
		equal = true;
		for ( ep=_end; equal && ( p<temp ); p++, ep++ )
			equal = ( *p == *ep );
		p = nextp;
	}
	return equal;
}

inline void BoxManClass::_PackData()
{
	//用'%'着色
	char i, j;
	bool havechange;

	do{
		havechange = false;
		for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
			if ( m_map[i][j]!=MAP_WALL && ( _con[i][j]==0 || _con[i][j]=='^' ) &&
				( _con[i+1][j]=='%' || _con[i-1][j]=='%' || _con[i][j+1]=='%' || _con[i][j-1]=='%' ) ){
				_con[i][j] = '%';
				havechange = true;
			}
		}
		if ( !havechange ) break;
		havechange = false;
		for ( i=_x-1; i>0; i-- ) for ( j=_y-1; j>0; j-- ){
			if ( m_map[i][j]!=MAP_WALL && ( _con[i][j]==0 || _con[i][j]=='^' ) &&
				( _con[i+1][j]=='%' || _con[i-1][j]=='%' || _con[i][j+1]=='%' || _con[i][j-1]=='%' ) ){
				_con[i][j] = '%';
				havechange = true;
			}
		}
	}while ( havechange );
	//endof 用'%'着色
	
	//加入新节点
	unsigned char *p = _end, **ap;
	//char manY, manX=0;
	unsigned char manXY;
	
	for ( j=1; j<_y; j++ ) for ( i=1; i<_x; i++ ){
		if ( _con[i][j] == '#' ){
			//*p++ = i;
			//*p++ = j;
			*p++ = (j-1) * _x2 + (i-1);
		} else if ( _con[i][j] == '%' ){
			//manX = i;
			//manY = j;
			manXY = (j-1) * _x2 + (i-1);
		}
	}
	*p++ = manXY;
	//*p++ = manY;
	ap = (unsigned char**)p;
	*ap = _now;
}

void BoxManClass::SceneSequence()
{
	if(!m_bAutoSequence) return;
	if(m_nCurrentScene<3)
		m_nCurrentScene++;
	else
		m_nCurrentScene=0;

	AttachMapToMemory();
}

void BoxManClass::DrawMan(bool bPaint)
{
	int x=m_mx;
	int y=m_my;
	
	x+=(m_mapsizex - m_x)/2;
	y+=(m_mapsizey - m_y)/2;

	m_bTwain=!m_bTwain;
	char index=GetManIndex();	

	m_dibMap.Stretch(&m_dcMap,
		CPoint(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE),
		CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
		CPoint(index*MAP_GRID_SIZE,0),
		CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
		SRCCOPY);

	if(m_map[m_mx][m_my]==MAP_DESTINATION)
	{
		CClientDC dc(m_pDrawWnd);
		CDC dcDestination;
		dcDestination.CreateCompatibleDC(&dc);

		CBitmap bmpDestination;
		bmpDestination.CreateCompatibleBitmap(&dc,MAP_GRID_SIZE,MAP_GRID_SIZE);
		CBitmap *pDestination=dcDestination.SelectObject(&bmpDestination);
		/*
		CDib dibDestination(CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),8);
		CBitmap bmp;
		bmp.Attach(dibDestination.CreateSection(&dc));
		CBitmap *pDestination=dcDestination.SelectObject(&bmp);*/


		m_dibMap.Stretch(&dcDestination,
			CPoint(0,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			CPoint(POINTB*MAP_GRID_SIZE,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			SRCCOPY);

		m_dibMap.Stretch(&dcDestination,  //处理精灵图片
			CPoint(0,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			CPoint(MASK*MAP_GRID_SIZE,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			MERGEPAINT);

		////////////////////////
		//   Alpha 混合
		///////////////////////
		CDC dcMask;
		dcMask.CreateCompatibleDC(&dc);
		CBitmap bmpMask;
		bmpMask.CreateCompatibleBitmap(&dc,MAP_GRID_SIZE,MAP_GRID_SIZE);
		CBitmap *pMask=dcMask.SelectObject(&bmpMask);
		m_dibMap.Stretch(&dcMask,
			CPoint(0,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			CPoint(MASK*MAP_GRID_SIZE,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			SRCCOPY);
		int Alpha=130;
		COLORREF pixel1,pixel2,newPixelR,newPixelG,newPixelB;
		for(int i=0;i<MAP_GRID_SIZE;i++)
			for(int j=0;j<MAP_GRID_SIZE;j++)
			{
				if(dcMask.GetPixel(i,j)==RGB(0,0,0)) continue;
				pixel1=dcDestination.GetPixel(i,j);
				pixel2=m_dcMap.GetPixel(x*MAP_GRID_SIZE+i,y*MAP_GRID_SIZE+j);
				newPixelR=(GetRValue(pixel1)*(255-Alpha)+GetRValue(pixel2)*Alpha)/255;
				newPixelG=(GetGValue(pixel1)*(255-Alpha)+GetGValue(pixel2)*Alpha)/255;
				newPixelB=(GetBValue(pixel1)*(255-Alpha)+GetBValue(pixel2)*Alpha)/255;
				dcDestination.SetPixel(i,j,RGB(newPixelR,newPixelG,newPixelB));
			}
		dcMask.SelectObject(pMask);

		m_dibMap.Stretch(&m_dcMap,    //处理背景图片
			CPoint(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			CPoint(MASK*MAP_GRID_SIZE,0),
			CSize(MAP_GRID_SIZE,MAP_GRID_SIZE),
			NOTSRCERASE);

		m_dcMap.StretchBlt(x*MAP_GRID_SIZE,y*MAP_GRID_SIZE,
			MAP_GRID_SIZE,MAP_GRID_SIZE,
			&dcDestination,0,0,MAP_GRID_SIZE,MAP_GRID_SIZE,SRCINVERT);  //将处理过的精灵图片与背景"异或"起来

		dcDestination.SelectObject(pDestination);
		bmpDestination.DeleteObject();
	}

	if(bPaint)
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect(GetClipRect(m_mx,m_my));
		Paint(&rgn);
	}
}

UINT BoxManClass::LoadMaxMissionNum()
{
	MAX_MISSION_NUM=GetIntValue("FileInfo","MaxMission");
	return MAX_MISSION_NUM;
}

BOOL BoxManClass::Save(CString name) const
{
	CFile file(name,CFile::modeCreate|CFile::modeReadWrite|CFile::shareExclusive);
	file.Write(&m_iDifficulty,sizeof(m_iDifficulty));
	file.Write(&m_nowmap,sizeof(m_nowmap));
	file.Write(&m_x,sizeof(m_x));
	file.Write(&m_y,sizeof(m_y));
	file.Write(&m_NumberOfBox,sizeof(m_NumberOfBox));
	file.Write(&m_mapsizex,sizeof(m_mapsizex));
	file.Write(&m_mapsizey,sizeof(m_mapsizey));
	for(int x=0;x<m_x;x++)
	{		
		file.Write(m_map[x],m_y*sizeof(unsigned char));
		file.Write(m_bnm[x],m_y*sizeof(unsigned char));
	}

	WCHAR n=m_path.GetSize();
	file.Write(&n,sizeof(n));
	PathStruct *path;
	for(int i=0;i<n;i++)
	{		
		path=(PathStruct *)m_path.GetAt(i);
		file.Write(&path->boxx,sizeof(path->boxx));
		file.Write(&path->boxy,sizeof(path->boxy));
		file.Write(&path->manx,sizeof(path->manx));
		file.Write(&path->many,sizeof(path->many));
	}
	
	file.Close();	

	return TRUE;
}

BOOL BoxManClass::Load(CString name)
{
	CFile file(name,CFile::modeRead|CFile::shareDenyWrite);
	file.Read(&m_iDifficulty,sizeof(m_iDifficulty));
	file.Read(&m_nowmap,sizeof(m_nowmap));
	file.Read(&m_x,sizeof(m_x));
	file.Read(&m_y,sizeof(m_y));
	file.Read(&m_NumberOfBox,sizeof(m_NumberOfBox));
	file.Read(&m_mapsizex,sizeof(m_mapsizex));
	file.Read(&m_mapsizey,sizeof(m_mapsizey));
	for(int x=0;x<m_x;x++)
	{
		file.Read(m_map[x],m_y*sizeof(unsigned char));
		file.Read(m_bnm[x],m_y*sizeof(unsigned char));
	}

	DeleteAllPath(m_path);

	WCHAR n;
	file.Read(&n,sizeof(n));
	char boxx,boxy,manx,many;
	for(int i=0;i<n;i++)
	{		
		file.Read(&boxx,sizeof(boxx));
		file.Read(&boxy,sizeof(boxy));
		file.Read(&manx,sizeof(manx));
		file.Read(&many,sizeof(many));
		AddMapToPath(manx,many,boxx,boxy);
	}

	file.Close();

	SetFileName(m_strSysPath+FILE_NAME[m_iDifficulty-1]);
	m_CanUndo=n;
	PrepareThinking(m_nowmap);
	m_TheShowStep=0;
	m_nTotalStep=0;
	m_bBoxMovedToDestination=FALSE;

	ExitThinkThreak();
	ReSetFrame();
	SetStatusBar();

	return TRUE;
}

void BoxManClass::ExitThinkThreak()
{
	_ThreadCommand = BM_COMMAND_STOP_THREAD;
	for(int tt=0;tt<100&&_ThreadMessage==BM_MESSAGE_THINKING;tt++)::Sleep(1);
	//while ( _ThreadMessage == BM_MESSAGE_THINKING ) ::Sleep(2);
}

void BoxManClass::Temp()
{
	CStdioFile file(".\\impossible.txt",CStdioFile::modeCreate | CStdioFile::modeWrite);

	CIni src;
	src.SetFileName(".\\impossible.bxm");

	int iMission=1;
	CString strMission,strMapData,strTemp;
	while(1)
	{		
		strMission.Format("Level %d",iMission);
		strMapData=src.GetStringValue(strMission,"MapData");
		if(strMapData.IsEmpty()) break;

		strTemp.Format("[M%d]\n",iMission);
		file.WriteString(strTemp);

		strTemp.Format("Width=%d\n",src.GetIntValue(strMission,"MapWidth"));
		file.WriteString(strTemp);

		strTemp.Format("Height=%d\n",src.GetIntValue(strMission,"MapHeight"));
		file.WriteString(strTemp);

		strMapData.Replace('0',MAP_OUTSIDE);
		strMapData.Replace('1',MAP_WALL);
		strMapData.Replace('2',MAP_ROAD);
		strMapData.Replace('3',MAP_DESTINATION);
		strMapData.Replace('4',MAP_BOX);
		strMapData.Replace('5',MAP_BOX_AT_DESTINATION);
		strMapData.Replace('6',MAP_MAN);
		strMapData.Replace('7',MAP_MAN_AT_DESTINATION);
		file.WriteString("Map="+strMapData+"\n");

		iMission++;
	}

	file.Close();
}

bool BoxManClass::SelectDifficulty(int iDifficulty)
{
	if(iDifficulty==m_iDifficulty) return false;
	m_iDifficulty=iDifficulty;
	SetFileName(m_strSysPath+FILE_NAME[iDifficulty-1]);
	LoadMaxMissionNum();
	ReadMap(1);
	if(m_bAutoSequence) SceneSequence();
	ReSetFrame();
	SetStatusBar();
	
	m_nTotalStep=0;
	m_bBoxMovedToDestination=FALSE;	

	return true;
}

void BoxManClass::ReSetFrame()
{
	CRect rcClient;
	m_pDrawWnd->GetClientRect(&rcClient);
	ChangeRate(rcClient.Width(),rcClient.Height());
	CRect reWindow;
	CWnd *pWnd=AfxGetMainWnd();
	/*pWnd->GetWindowRect( &reWindow );
	pWnd->SetWindowPos( NULL, reWindow.top, reWindow.left,
		m_mapsizex * MAP_GRID_SIZE + 11, m_mapsizey * MAP_GRID_SIZE + 94,
		SWP_NOMOVE | SWP_NOZORDER );*/
	//parent->MoveWindow( reWindow.top, reWindow.left,
	//	bm.m_mapsizex * bm.MAP_GRID_SIZE + 11, bm.m_mapsizey * bm.MAP_GRID_SIZE + 94 );
	char s[80];
	::wsprintf(s,"BoxMan [%s] — Round %d",GetDifficultyString(),m_nowmap);
	pWnd->SetWindowText(s);
	DrawAllMap();
	Paint(NULL);
}

void BoxManClass::SetStatusBar()
{
	CString strTemp;
	strTemp.Format("步数：%d",m_nTotalStep);
	CStatusBar *pStatus=(CStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	pStatus->SetPaneText(1,strTemp);

	if ( m_RemainShewStep == 0 ) {
		switch(_ThreadMessage){
		case BM_MESSAGE_THINKING:
			strTemp.Format( "电脑正在想解法" );
			break;
		case BM_MESSAGE_NO_ANSWER:
			strTemp.Format( "没有解法" );
			break;
		case BM_MESSAGE_BUFFER_FULL:
			strTemp.Format( "太难了" );
			break;
		case BM_MESSAGE_THINK_OUT:
			strTemp.Format( "已知道解法" );
			break;
		case BM_MESSAGE_THINK_STOPED:
			strTemp.Format( "Copyright Hunter" );
			break;
		default:
			strTemp.Format( "I am Hunter!" );
			break;
		}
	}else{
		strTemp.Format( "还有:%d步", m_RemainShewStep );
	}

	pStatus->SetPaneText(2,strTemp);
}

CString BoxManClass::GetDifficultyString()
{
	CString strResult;
	switch(m_iDifficulty)
	{
	case 1:
		strResult="儿童级";
		break;
	case 2:
		strResult="入门级";
		break;
	case 3:
		strResult="趣味级";
		break;
	case 4:
		strResult="脑力级";
		break;
	case 5:
		strResult="体力级";
		break;
	case 6:
		strResult="恐怖级";
		break;
	case 7:
		strResult="自定义";
		break;
	default:
		strResult="额外的";
		break;
	}
	return strResult;
}

double BoxManClass::ChangeRate(int cx,int cy)
{
	if(cy==0 || cx==0) return 0;
	double xRate=(cx+1)/static_cast <double>(m_x*MAP_GRID_SIZE),
		   yRate=(cy+1)/static_cast <double>(m_y*MAP_GRID_SIZE);

	m_fZoomRate=min(xRate,yRate);
	if(m_fZoomRate<.000000001) m_fZoomRate=.000001;
	if(!m_bAutoZoom && m_fZoomRate>1) m_fZoomRate=1;

	m_mapsizex=static_cast <BYTE>(ceil((cx+1)/(MAP_GRID_SIZE*m_fZoomRate)));
	m_mapsizey=static_cast <BYTE>(ceil((cy+1)/(MAP_GRID_SIZE*m_fZoomRate)));
	if(m_mapsizex>100) m_mapsizex=100;
	if(m_mapsizey>100) m_mapsizey=100;
	return m_fZoomRate;
}

CRect BoxManClass::GetClipRect(int x,int y)
{
	int xstart=(m_mapsizex-m_x)/2,
		ystart=(m_mapsizey-m_y)/2,
		left=(xstart+x)*MAP_GRID_SIZE,
		top=(ystart+y)*MAP_GRID_SIZE,
		right=left+MAP_GRID_SIZE,
		bottom=top+MAP_GRID_SIZE;

	return CRect(static_cast <int>(left*m_fZoomRate),static_cast <int>(top*m_fZoomRate),
		static_cast <int>(right*m_fZoomRate),static_cast <int>(bottom*m_fZoomRate));	
}

BOOL BoxManClass::LoadMapFile(CString name)
{
	SetFileName(name);
	m_iDifficulty=GetIntValue("FileInfo","Difficulty");

	if(m_iDifficulty==0) m_iDifficulty=-1;

	LoadMaxMissionNum();
	ReadMap(1);	
	if(m_bAutoSequence) SceneSequence();
	ReSetFrame();
	SetStatusBar();

	m_nTotalStep=0;
	m_bBoxMovedToDestination=FALSE;	

	return TRUE;
}

/*******************************************************************************************************
函数名 : GetDrawIndex
描  述 : 获得要画窗格的图片索引
参  数 : 
         int x : 要画窗格的x坐标
		 int y : 要画窗格的y坐标
返回值 : BYTE 返回图片索引号
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年11月24日 15:34:48
*******************************************************************************************************/

BYTE BoxManClass::GetDrawIndex(int x,int y)
{
	BYTE index;
	switch(m_map[x][y])
	{
	case MAP_WALL:
		index=WALLB;
		break;
	case MAP_OUTSIDE:
		index=NULLB;
		break;
	case MAP_ROAD:
		{
			switch(m_bnm[x][y])
			{
			case 0:
				index=NULLWALLB;
				break;
			case MAP_MAN:
				m_mx=x;
				m_my=y;
				index=GetManIndex();
				break;
			case MAP_BOX:
				index=BOXB;
			}
		}
		break;
	case MAP_CAN_NOT_PUT_BOX:
		{
			switch(m_bnm[x][y])
			{
			case 0:
				index=NULLWALLB;
				break;
			case MAP_MAN:
				m_mx=x;
				m_my=y;
				index=GetManIndex();
				break;
			case MAP_BOX:
				index=BOXB;
			}
		}
		break;
	case MAP_DESTINATION:
		{
			switch(m_bnm[x][y])
			{
			case 0:
				index=POINTB;
				break;
			case MAP_MAN:
				m_mx=x;
				m_my=y;
				index=GetManIndex();
				break;
			case MAP_BOX:
				index=BOXATPOINTB;
				if(m_bEnableSound)
					m_bBoxMovedToDestination=TRUE;
			}
		}
		break;
	default:
		m_pDrawWnd->MessageBox(_T("地图记录错误！"),_T("错误"),MB_OK|MB_ICONERROR);
		index=0;
		break;
	}

	return index;
}

/*******************************************************************************************************
函数名 : GetManIndex
描  述 : 得到搬运工动画当前帧在IDB中的索引
参  数 : 无
返回值 : BYTE 返回索引号
版  本 : 0.1.0.0
作  者 : 吴春
时  间 : 2006年11月24日 15:32:27
*******************************************************************************************************/

BYTE BoxManClass::GetManIndex()
{
	BYTE index;
	switch(m_nKey)
	{
	case VK_DOWN:
		if(m_bTwain)
			index=MANBD1;
		else
			index=MANBD2;
		break;
	case VK_UP:
		if(m_bTwain)
			index=MANBU1;
		else
			index=MANBU2;
		break;
	case VK_LEFT:
		if(m_bTwain)
			index=MANBL1;
		else
			index=MANBL2;
		break;
	case VK_RIGHT:
		if(m_bTwain)
			index=MANBR1;
		else
			index=MANBR2;
		break;
	}

	return index;
}

// WriteDIB - Writes a DIB to file 
// Returns - TRUE on success 
// szFile - Name of file to write to 
// hDIB - Handle of the DIB 
BOOL BoxManClass::WriteDIB(LPTSTR szFile,HANDLE hDIB)
{ 
	BITMAPFILEHEADER hdr; 
	LPBITMAPINFOHEADER lpbi; 

	if(!hDIB) return FALSE; 

	CFile file; 
	if(!file.Open(szFile,CFile::modeWrite|CFile::modeCreate)) return FALSE;

	lpbi=(LPBITMAPINFOHEADER)hDIB; 

	int nColors=1<<lpbi->biBitCount; 

	// Fill in the fields of the file header
	hdr.bfType=((WORD)('M'<<8)|'B'); // is always "BM"
	hdr.bfSize=GlobalSize(hDIB)+sizeof(hdr);
	hdr.bfReserved1=0;
	hdr.bfReserved2=0;
	hdr.bfOffBits=(DWORD)(sizeof(hdr)+lpbi->biSize+nColors*sizeof(RGBQUAD));
	// Write the file header
	file.Write(&hdr,sizeof(hdr));
	// Write the DIB header and the bits
	file.Write(lpbi,GlobalSize(hDIB));

	return TRUE;
}

void BoxManClass::AttachMapToMemory()
{
	LPVOID lpvResource=(LPVOID)::LoadResource(NULL,::FindResource(NULL,MAKEINTRESOURCE(IDB_MAP1+m_nCurrentScene),RT_BITMAP));
	m_dibMap.AttachMemory(lpvResource);
}

HANDLE BoxManClass::DDBToDIB(CBitmap &bitmap,DWORD dwCompression,CPalette *pPal)
{  
	BITMAP                bm;
	BITMAPINFOHEADER      bi;   
	LPBITMAPINFOHEADER    lpbi;
	DWORD                 dwLen;
	HANDLE                hDIB;
	HANDLE                handle;
	HDC                   hDC;
	HPALETTE              hPal;
	
	ASSERT(bitmap.GetSafeHandle());
    
	//The function has no arg for bitfields
	if(dwCompression==BI_BITFIELDS) return NULL;
	//If a palette has not been supplied,use default palette
	hPal=(HPALETTE)pPal->GetSafeHandle();
	if(hPal==NULL) hPal=(HPALETTE)GetStockObject(DEFAULT_PALETTE); 
	//Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	//Initialize the bitmap infoheader
	bi.biSize           = sizeof(BITMAPINFOHEADER);
	bi.biWidth          = bm.bmWidth;
	bi.biHeight         = bm.bmHeight;
	bi.biPlanes         = 1;
	bi.biBitCount       = bm.bmPlanes*bm.bmBitsPixel;
	//bm.bmPlanes*bm.bmBitsPixel;
	bi.biCompression    = dwCompression;
	bi.biSizeImage      = 0;
	bi.biXPelsPerMeter  = 0;
	bi.biYPelsPerMeter  = 0;
	bi.biClrUsed        = 0;
	bi.biClrImportant   = 0;

	//Compute the size of the infoheader and the color table
	int nColors=(1<<bi.biBitCount);
	if(nColors>256) nColors=0;
	dwLen=bi.biSize+nColors*sizeof(RGBQUAD);

	//We need a device context to get the DIB from
	hDC=::GetDC(NULL);
	hPal=SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	//Allocate enough memory to hold bitmap infoheader and
	//color table
	hDIB=GlobalAlloc(GMEM_FIXED,dwLen);

	if(!hDIB)
	{
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi=(LPBITMAPINFOHEADER)hDIB;

	*lpbi=bi;

	//Call GetDIBits with a NULL lpBits param,so the device
	//driver will calculate the biSizeImage field
	GetDIBits(hDC,(HBITMAP)bitmap.GetSafeHandle(),0L,
		(DWORD)bi.biHeight,
		(LPBYTE)NULL,(LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);   

	bi=*lpbi; 
	//If the driver did not fill in the biSizeImage field,then
	//compute it
	//Each scan line of the image is aligned on a DWORD(32bit)
	//boundary
	if(bi.biSizeImage==0)
	{
		bi.biSizeImage=((((bi.biWidth*bi.biBitCount)+31)&~31)/8)*bi.biHeight;
		//If a compression scheme is used,the result may in fact
		//be larger
		//Increase the size to account for this.
		if(dwCompression!=BI_RGB)
			bi.biSizeImage=(bi.biSizeImage*3)/2;
	}
	//Realloc the buffer so that it can hold all the bits
	dwLen+=bi.biSizeImage;
	if(handle=GlobalReAlloc(hDIB,dwLen,GMEM_MOVEABLE))
		hDIB=handle;
	else
	{
		GlobalFree(hDIB);
		//Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}   
	//Get the bitmap bits
	lpbi=(LPBITMAPINFOHEADER)hDIB;
	//FINALLY get the DIB
	BOOL bGotBits=GetDIBits(hDC,(HBITMAP)bitmap.GetSafeHandle(),
		0L,                                                 //Start scan line
		(DWORD)bi.biHeight,                 //#of scan lines
			  (LPBYTE)lpbi                  //address for bitmap bits
			  +(bi.biSize+nColors*sizeof(RGBQUAD)),
			  (LPBITMAPINFO)lpbi,           //address of bitmapinfo
			  (DWORD)DIB_RGB_COLORS);       //Use RGB for color table

	if(!bGotBits)
	{
		GlobalFree(hDIB);
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);

	return   hDIB;
}  

//BOOL BoxManClass::SaveWnd(LPTSTR szFile,CWnd *pWnd,CPoint ptStart,CSize szWnd)
//{
//	CBitmap 	bitmap;
//	CWindowDC	dc(pWnd);
//	CDC 		memDC;
//	CRect		rect;
//
//	memDC.CreateCompatibleDC(&dc);
//	bitmap.CreateCompatibleBitmap(&dc,szWnd.cx,szWnd.cy);
//	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
//	memDC.BitBlt(0,0,szWnd.cx,szWnd.cy,&dc,ptStart.x,ptStart.y,SRCCOPY);
//
//	//Create logical palette if device support a palette
//	CPalette pal;
//	if(dc.GetDeviceCaps(RASTERCAPS)&RC_PALETTE)
//	{
//		UINT nSize=sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)*256);
//		LOGPALETTE *pLP=(LOGPALETTE *)new BYTE[nSize];
//		pLP->palVersion=0x300;
//		pLP->palNumEntries=GetSystemPaletteEntries(dc,0,255,pLP->palPalEntry);
//
//		//Create the palette
//		pal.CreatePalette(pLP);
//
//		delete[] pLP;
//	}
//
//	memDC.SelectObject(pOldBitmap);
//
//	//Convert the bitmap to a DIB
//	HANDLE hDIB=DDBToDIB(bitmap,BI_RGB,&pal);
//
//	if(hDIB==NULL) return FALSE;
//
//	//Write it to file
//	WriteDIB(szFile,hDIB);
//
//	//Free the memory allocated by DDBToDIB for the DIB
//	GlobalFree(hDIB);
//
//	return TRUE;
//}

BOOL BoxManClass::SaveScene(LPTSTR szFile)
{
	CBitmap bmp;
	GetSceneBitmap(bmp);
	//Create logical palette if device support a palette
	CClientDC dc(m_pDrawWnd);
	CPalette pal;
	if(dc.GetDeviceCaps(RASTERCAPS)&RC_PALETTE)
	{
		UINT nSize=sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)*256);
		LOGPALETTE *pLP=(LOGPALETTE *)new BYTE[nSize];
		pLP->palVersion=0x300;
		pLP->palNumEntries=GetSystemPaletteEntries(dc,0,255,pLP->palPalEntry);

		//Create the palette
		pal.CreatePalette(pLP);

		delete[] pLP;
	}

	HANDLE hDIB=DDBToDIB(bmp,BI_RGB,&pal);

	if(hDIB==NULL) return FALSE;

	//Write it to file
	WriteDIB(szFile,hDIB);

	//Free the memory allocated by DDBToDIB for the DIB
	GlobalFree(hDIB);
	//return SaveWnd(szFile,m_pDrawWnd,CPoint(xstart,ystart),CSize(iWidth,iHeight));
	return TRUE;
}

BOOL BoxManClass::PlaySound(int iState)
{
	if(!m_bEnableSound) return FALSE;
	bool bNoStop=FALSE;
	TCHAR szSound[30]="";
	switch(iState)
	{
	case BM_ERROR_PIONT_OUT:
	case BM_ERROR_POINT_MAN:
	case BM_ERROR_POINT_WALL:
	case BM_ERROR_CANNOT_MOVE_THERE:
		strcpy_s(szSound,"sound\\block.wav");
		break;
	case BM_MAN_MOVED:
		strcpy_s(szSound,"sound\\manmove.wav");
		bNoStop=TRUE;
		break;
	case BM_BOX_MOVED:
		if(m_bBoxMovedToDestination)
		{
			strcpy_s(szSound,"sound\\boxgoal.wav");
			m_bBoxMovedToDestination=FALSE;
		}
		else
			strcpy_s(szSound,"sound\\boxmove.wav");
		break;
	case BM_MOVED_OK:
		strcpy_s(szSound,"sound\\boxwin.wav");
		break;
	case -1:
		strcpy_s(szSound,"sound\\boxundo.wav");
		break;
	default:
		ASSERT(FALSE);
	}
	if(strcmp(szSound,"")) CMIDI::m_funcPlaySound(szSound,bNoStop);
	return TRUE;
}

BOOL BoxManClass::PrintScene()
{
	CDC printDC;
	CPrintDialog printDlg(FALSE);
	DOCINFO docInfo;

	if(printDlg.DoModal()==IDOK)
	{
		HDC hDC;
		hDC=printDlg.GetPrinterDC();
		if(!printDC.Attach(hDC)) return FALSE;
	}
	else
	{
		printDC.Detach();
		return FALSE;
	}

	memset(&docInfo,0,sizeof(docInfo));
	docInfo.cbSize=sizeof(DOCINFO);
	docInfo.lpszDocName="打印场景图";
	if(printDC.StartDoc(&docInfo)<=0)
	{
#ifdef _DEBUG
		AfxMessageBox("Start Doc Failed");
#endif
		printDC.Detach();
		return FALSE;
	}
	printDC.StartPage();
	printDC.SetMapMode(MM_TEXT);
	CClientDC dc(m_pDrawWnd);
	CBitmap bmp;
	POINT pp=GetSceneBitmap(bmp);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap *pOB=memDC.SelectObject(&bmp);
	printDC.StretchBlt(0,0,pp.x,pp.y,&memDC,0,0,pp.x,pp.y,SRCCOPY);
	printDC.EndPage();
	printDC.EndDoc();

	printDC.Detach();
	return TRUE;
}

POINT BoxManClass::GetSceneBitmap(CBitmap &bmp)
{
	int iWidth=m_x*MAP_GRID_SIZE,
		iHeight=m_y*MAP_GRID_SIZE;

	int iDesWidth=static_cast <int>(iWidth*m_fZoomRate),
		iDesHeight=static_cast <int>(iHeight*m_fZoomRate);

	int xstart=(m_mapsizex-m_x)/2*MAP_GRID_SIZE,
		ystart=(m_mapsizey-m_y)/2*MAP_GRID_SIZE;

	CClientDC dc(m_pDrawWnd);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc,iDesWidth,iDesHeight);
	CBitmap *pOB=memDC.SelectObject(&bmp);
	memDC.SetStretchBltMode(COLORONCOLOR);
	memDC.StretchBlt(0,0,iDesWidth,iDesHeight,
		&m_dcMap,xstart,ystart,iWidth,iHeight,SRCCOPY);
	memDC.SelectObject(pOB);
	POINT ptResult={iDesWidth,iDesHeight};
	return ptResult;
}