#if !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)
#define AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>  //GDI 绘图CDC
#include "..\Ini.h"

#define M_TAB_WIDTH  50   //横向方块最大宽度
#define M_TAB_HEIGHT 30   //纵向方块最大高度

const char MAP_WALL='+';
const char MAP_OUTSIDE='-';
const char MAP_DESTINATION='.';
const char MAP_BOX='#';
const char MAP_MAN='^';
const char MAP_BOX_AT_DESTINATION='@';
const char MAP_MAN_AT_DESTINATION='$';
const char MAP_ROAD=' ';

class CBoxEdit : public CIni
{
public:
	CBoxEdit(void);
	~CBoxEdit(void);
	BOOL ChangeMissionNum(int iNum);
    void DrawMap(CDC* pDC);
	inline int  GetNowMissionNum(void) {return m_iNowMissionNum;};
	void ChangeMap(int x, int y, int iState);
    BOOL LoadMap(int iMissionNum);
	void ClearMap(void);
	void SaveMap(void);
	bool NewMap(int iWidth,int iHeight);
	int LoadMaxMissionNum(void);
	//inline char GetGridMap(int x,int y){return m_cMap[x][y];};

protected:
    CPoint GetManPosition();
    void DrawGrid(int x, int y, CDC* pDC, int index);
    void UpdateMap(UINT nChar);
    void UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3);
    bool IsFinish(void);
	bool WallIsClose(CPoint p,CPoint start,CSize back);
	bool MissionIsSame();

private:
    char m_cMap[M_TAB_HEIGHT][M_TAB_WIDTH];  //方块矩阵
    CPoint m_ptManPosition;                  
    int m_iMissionNum;  //////删除
//	DWORD m_MapFileLength;  //地图文件大小
//	GLOBALHANDLE m_hMap;  //地图文件在内存中的映射句柄
	unsigned char m_x;  //地图宽度里的方格图片数
	unsigned char m_y;  //地图高度里的方格图片数
	int m_iMinXPos;  //地图中最左边墙的位置
	int m_iMaxXPos;  //地图中最右边墙的位置
	int m_iMinYPos;  //地图中最上边墙的位置
	int m_iMaxYPos;  //地图中最下边墙的位置
	int m_iNowMissionNum;  //当前关卡数
//	CByteArray m_HasGoneWall;  //检查围墙闭合性中记录走过的墙
};

#endif // !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)