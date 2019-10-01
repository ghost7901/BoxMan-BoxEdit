// MainFrm.h : CBoxEditerWnd 类的接口
//
#include "BoxEdit.h"

#pragma once

class CBoxEditerWnd : public CFrameWnd
{
	
public:
	CBoxEditerWnd();
protected: 
	DECLARE_DYNAMIC(CBoxEditerWnd)

// 属性
private:
	char m_NowSelect;
protected:
	CBoxEdit m_BoxEdit;    // BoxEdit实体
	CDC *m_pWindowDC;      // windows设备环境
	CPoint m_MousePoint;   // 鼠标的坐标位置
	BOOL m_bMouseDown;     // 是否鼠标已被按下

public:

// 操作
public:
	BOOL CreateExToolBar(void);

// 重写
public:

// 实现
public:
	virtual ~CBoxEditerWnd();

protected:  // 控件条嵌入成员
	CToolBar    m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuDrawWall();
	afx_msg void OnMenuDrawDestination();
	afx_msg void OnMenuDrawBox();
	afx_msg void OnMenuDrawBoxAtDestination();
	afx_msg void OnMenuDrawMan();
	afx_msg void OnMenuDrawManAtDestination();
	afx_msg void OnUpdateMenuDrawWall(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawDestination(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawBox(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawBoxAtDestination(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawMan(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawManAtDestination(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuDrawOutside();
	afx_msg void OnUpdateMenuDrawOutside(CCmdUI *pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMenuNewMap();
	afx_msg void OnMenuLoadMap();
	afx_msg void OnMenuSaveMap();
};