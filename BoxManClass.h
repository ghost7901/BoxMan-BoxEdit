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
	BOOL m_bTwain;  //���ڰ��˹�����������������л�
	UINT m_nKey;    //���˹��泯�ķ��� ( VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN )	
	UINT m_nCurrentScene;    //��ǰ�������� ( 0,1,2,3 )
	BOOL m_bBoxMovedToDestination;   //�����Ƿ�����Ŀ�ĵ�
	int m_nTotalStep;  //���˹��ߵ��ܲ���
	BOOL m_bEnableSound;  //�Ƿ�������Ч����
	MyMIDI midi1,midi2,midi3,midi4,midi5,midi6,midi7,midi8,midi9;  //MIDI���Ŷ���
	BOOL m_bIsPause;   //MIDI�Ƿ�����ͣ״̬
	unsigned int _ThreadMessage;  //˼���̵߳�ǰ״̬
	unsigned int m_nowmap;  //��ǰʹ�õĵ�ͼ
	int m_RemainShewStep;  //��ʾ��ʣ�Ĳ���
	unsigned char m_NumberOfBox;  //������	
	bool m_CanMoveToBadPoint;  //�Ƿ����������㴦����ʾ
	int m_TheShowStep;  //��ǰҪ��ʾ�Ĳ������,m_ShowPath����
	int m_TheMapsMoveWaySavePoint;  //�ؿ���MoveWay.dat�еĴ��̵�
	
	unsigned char m_mapsizex;  //���洰�ڿ��(������)
	unsigned char m_mapsizey;  //���洰�ڸ߶�(������)
	unsigned char m_x;  //��ͼ�����ķ���ͼƬ��
	unsigned char m_y;  //��ͼ�߶���ķ���ͼƬ��
	unsigned int m_boxmovestepnumber;  //���������ƶ��Ĵ���
	bool m_noanswerrecoded;  //�����Ƿ�û�йؿ���¼
//	bool m_BoxMoveOk;
	BOOL m_CanUndo;  //��ǰ״̬�ܷ���
	int m_iDifficulty;  //��Ϸ�Ѷȵȼ�
	CString m_strSysPath;  //����ľ���·��	
	double m_fZoomRate;  //ͼ�����ű���
	bool m_bAutoZoom;  //�����Ƿ��Զ�����
	bool m_bAutoSequence;  //�Ƿ��Զ��л�����
	bool m_bCanPaste;  //�Ƿ����ճ����ǰ״̬

// Attributes
protected:
	bool m_computerthinkout;  //MoveWay.dat���Ƿ��е���˼���õ��Ĵ�
	CPtrArray m_path,  //��¼ÿ���а��˹�����������ӵ�����
		*m_ShowPath;
	CWnd *m_pDrawWnd;  //������ͼ����ָ��
//	unsigned char m_stepnumber;
	unsigned char m_mx;   //MAN��ǰ�ڵ�ͼ�е�X����
	unsigned char m_my;   //MAN��ǰ�ڵ�ͼ�е�Y����
	unsigned char m_map[MAXMAPSIZEX][MAXMAPSIZEY];  //��ͼ�в����ƶ�����Ϣ Box,Destination,Wall,Road
	unsigned char m_bnm[MAXMAPSIZEX][MAXMAPSIZEY];  //��ͼ�п��ƶ�����Ϣ Man,Box
//	bool m_manmoving;
	bool m_wayfilechanged;  //�Ƿ��д���𰸵��ڴ�ӳ���ļ�
	CPtrArray *m_pmanmoveway;
//	GLOBALHANDLE m_hmap;  //��ͼ�ļ����ڴ��е�ӳ����
	GLOBALHANDLE m_hway;  //���ļ����ڴ��е�ӳ����
	DWORD m_wayfilelength;  //���ļ���С
	//DWORD m_MapFileLength;  //��ͼ�ļ���С
	CDC m_dcMap;  //�����ػ�DC
	CBitmap //m_mapB,  //�����ػ���CBitmap
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
