// MainFrm.h : CBoxEditerWnd ��Ľӿ�
//
#include "BoxEdit.h"

#pragma once

class CBoxEditerWnd : public CFrameWnd
{
	
public:
	CBoxEditerWnd();
protected: 
	DECLARE_DYNAMIC(CBoxEditerWnd)

// ����
private:
	char m_NowSelect;
protected:
	CBoxEdit m_BoxEdit;    // BoxEditʵ��
	CDC *m_pWindowDC;      // windows�豸����
	CPoint m_MousePoint;   // ��������λ��
	BOOL m_bMouseDown;     // �Ƿ�����ѱ�����

public:

// ����
public:
	BOOL CreateExToolBar(void);

// ��д
public:

// ʵ��
public:
	virtual ~CBoxEditerWnd();

protected:  // �ؼ���Ƕ���Ա
	CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
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