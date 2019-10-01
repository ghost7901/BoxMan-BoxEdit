#if !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)
#define AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>  //GDI ��ͼCDC
#include "..\Ini.h"

#define M_TAB_WIDTH  50   //���򷽿������
#define M_TAB_HEIGHT 30   //���򷽿����߶�

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
    char m_cMap[M_TAB_HEIGHT][M_TAB_WIDTH];  //�������
    CPoint m_ptManPosition;                  
    int m_iMissionNum;  //////ɾ��
//	DWORD m_MapFileLength;  //��ͼ�ļ���С
//	GLOBALHANDLE m_hMap;  //��ͼ�ļ����ڴ��е�ӳ����
	unsigned char m_x;  //��ͼ�����ķ���ͼƬ��
	unsigned char m_y;  //��ͼ�߶���ķ���ͼƬ��
	int m_iMinXPos;  //��ͼ�������ǽ��λ��
	int m_iMaxXPos;  //��ͼ�����ұ�ǽ��λ��
	int m_iMinYPos;  //��ͼ�����ϱ�ǽ��λ��
	int m_iMaxYPos;  //��ͼ�����±�ǽ��λ��
	int m_iNowMissionNum;  //��ǰ�ؿ���
//	CByteArray m_HasGoneWall;  //���Χǽ�պ����м�¼�߹���ǽ
};

#endif // !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)