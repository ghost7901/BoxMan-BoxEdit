// BoxManClass.h: interface for the BoxManClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOXMANCLASS_H__A8DB6093_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
#define AFX_BOXMANCLASS_H__A8DB6093_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_

#define BM_MOVED_TO_BAD_POINT 0
#define BM_ERROR_POINT_MAN 1
#define BM_ERROR_CANNOT_MOVE_THERE 2
#define BM_ERROR_POINT_WALL 3
#define BM_ERROR_PIONT_OUT 4
#define BM_MOVED_OK 5
#define BM_BOX_MOVED 6
#define BM_MAN_MOVED 7

#define BM_MESSAGE_THINK_STOPED 100
#define BM_MESSAGE_THINKING 101
#define BM_MESSAGE_NO_ANSWER 102
#define BM_MESSAGE_BUFFER_FULL 103
#define BM_MESSAGE_THINK_OUT 104

#define BM_COMMAND_RUN_THREAD 200
#define BM_COMMAND_STOP_THREAD 201

#include "mymidi.h"
#include "Ini.h"
#include "Dib.h"

const char MAXMAPSIZEX = 50;
const char MAXMAPSIZEY = 50;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BoxManClass : public CIni
{
protected:
	//BOOL SaveWnd(LPTSTR szFile,CWnd *pWnd,CPoint ptStart,CSize szWnd);
	HANDLE DDBToDIB(CBitmap &bitmap,DWORD dwCompression,CPalette *pPal);
	BOOL WriteDIB(LPTSTR szFile,HANDLE hDIB);
public:
	BoxManClass();
	virtual ~BoxManClass();
	void DrawMan(bool bPaint=false);
	void SceneSequence();
	void ThinkTheWay();
	void ShowMoveWay();
	bool PrepareThinking( unsigned int index );
	unsigned char DoManMove();
	void MoveManTo(char x, char y,CPtrArray *way);
	char PointAt(CPoint point);
	bool Undo();
	void DeleteAllPath(CPtrArray &path);
	void AddMapToPath( char manx, char many, char boxx, char boxy );
	void BoxMoveOk(CPtrArray &record);
	unsigned char MoveTowards(char dx, char dy);
	void DrawAllMap();
	void DrawIt(char x,char y,CDC *pDC);
	void Paint(CRgn *rgnClip);
	bool ReadMap( unsigned int index );
	void SetDrawWnd( CWnd* pWnd );
	UINT LoadMaxMissionNum();
	BOOL Save(CString name) const;
	BOOL Load(CString name);
	void ExitThinkThreak();
	bool SelectDifficulty(int iDifficulty);
	void ReSetFrame();CBitmap m_mapB;
	void SetStatusBar();
	CString GetDifficultyString();
	double ChangeRate(int cx,int cy);
	CRect GetClipRect(int x,int y);
	BOOL LoadMapFile(CString name);
	BYTE GetDrawIndex(int x,int y);
	BYTE GetManIndex();
	void AttachMapToMemory();
	BOOL SaveScene(LPTSTR szFile);
	BOOL PlaySound(int iState);
	void UpdateToolBar(bool bRecalc=true);
	BOOL PrintScene();
	POINT GetSceneBitmap(CBitmap &bmp);
	void Temp();

// Implementation
public:	
	CDib m_dibMap,*m_pdibPaint;
	BOOL m_bTwain;  //用于搬运工动画中两个画面的切换
	UINT m_nKey;    //搬运工面朝的方向 ( VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN )	
	UINT m_nCurrentScene;    //当前场景画面 ( 0,1,2,3 )
	BOOL m_bBoxMovedToDestination;   //箱子是否移至目的地
	int m_nTotalStep;  //搬运工走的总步数
	BOOL m_bEnableSound;  //是否允许音效播放
	MyMIDI midi1,midi2,midi3,midi4,midi5,midi6,midi7,midi8,midi9;  //MIDI播放对象
	BOOL m_bIsPause;   //MIDI是否处于暂停状态
	unsigned int _ThreadMessage;  //思考线程当前状态
	unsigned int m_nowmap;  //当前使用的地图
	int m_RemainShewStep;  //演示所剩的步数
	unsigned char m_NumberOfBox;  //箱子数	
	bool m_CanMoveToBadPoint;  //是否有移至坏点处的提示
	int m_TheShowStep;  //当前要演示的步数序号,m_ShowPath索引
	int m_TheMapsMoveWaySavePoint;  //关卡在MoveWay.dat中的存盘点
	
	unsigned char m_mapsizex;  //画面窗口宽度(方格数)
	unsigned char m_mapsizey;  //画面窗口高度(方格数)
	unsigned char m_x;  //地图宽度里的方格图片数
	unsigned char m_y;  //地图高度里的方格图片数
	unsigned int m_boxmovestepnumber;  //答案中箱子移动的次数
	bool m_noanswerrecoded;  //答案中是否没有关卡记录
//	bool m_BoxMoveOk;
	BOOL m_CanUndo;  //当前状态能否撤销
	int m_iDifficulty;  //游戏难度等级
	CString m_strSysPath;  //程序的绝对路径	
	double m_fZoomRate;  //图像缩放比率
	bool m_bAutoZoom;  //界面是否自动缩放
	bool m_bAutoSequence;  //是否自动切换场景
	bool m_bCanPaste;  //是否可以粘贴当前状态

// Attributes
protected:
	bool m_computerthinkout;  //MoveWay.dat中是否有电脑思考得到的答案
	CPtrArray m_path,  //记录每步中搬运工的坐标和箱子的坐标
		*m_ShowPath;
	CWnd *m_pDrawWnd;  //程序视图窗口指针
//	unsigned char m_stepnumber;
	unsigned char m_mx;   //MAN当前在地图中的X坐标
	unsigned char m_my;   //MAN当前在地图中的Y坐标
	unsigned char m_map[MAXMAPSIZEX][MAXMAPSIZEY];  //地图中不可移动的信息 Box,Destination,Wall,Road
	unsigned char m_bnm[MAXMAPSIZEX][MAXMAPSIZEY];  //地图中可移动的信息 Man,Box
//	bool m_manmoving;
	bool m_wayfilechanged;  //是否改写过答案的内存映射文件
	CPtrArray *m_pmanmoveway;
//	GLOBALHANDLE m_hmap;  //地图文件在内存中的映射句柄
	GLOBALHANDLE m_hway;  //答案文件在内存中的映射句柄
	DWORD m_wayfilelength;  //答案文件大小
	//DWORD m_MapFileLength;  //地图文件大小
	CDC m_dcMap;  //窗口重画DC
	CBitmap //m_mapB,  //窗口重画用CBitmap
		*m_pOB;
	//HBITMAP hBitmap;
private:
	inline void _PackData();
	inline bool _AlreadyHave();
	inline bool _IsOk(unsigned char *p);
	inline void _UnpackData(unsigned char *p);
	void _OutputToFile();
	bool _ThinkIt();
	void _InitData();
	unsigned int _ThreadCommand;
	unsigned int _ThinkingMap;
	unsigned char *_now, *_head, *_end;
	unsigned char _x, _x2;
	unsigned char _y, _y2;
	unsigned char _structSize;
	char _con[MAXMAPSIZEX][MAXMAPSIZEY];
};

#endif // !defined(AFX_BOXMANCLASS_H__A8DB6093_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
