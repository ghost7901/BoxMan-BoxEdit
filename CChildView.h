// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__A8DB606B_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
#define AFX_CHILDVIEW_H__A8DB606B_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "midi.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_nCurrentMusic;
	void BeginThinkThread();
	void SelectMap(bool next);
	void Created();
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelectmap();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowMoveWay();
	afx_msg void OnUpdateShowMoveWay(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrompt(CCmdUI* pCmdUI);
	afx_msg void OnPrompt();
	afx_msg void OnPriorMap();
	afx_msg void OnNextMap();
	afx_msg void OnUpdateNextMap(CCmdUI* pCmdUI);
	afx_msg void OnMusic1();
	afx_msg void OnUpdateMusic1(CCmdUI* pCmdUI);
	afx_msg void OnMusic2();
	afx_msg void OnUpdateMusic2(CCmdUI* pCmdUI);
	afx_msg void OnSound();
	afx_msg void OnUpdateSound(CCmdUI* pCmdUI);
	afx_msg void OnMusic3();
	afx_msg void OnUpdateMusic3(CCmdUI* pCmdUI);
	afx_msg void OnMusic4();
	afx_msg void OnUpdateMusic4(CCmdUI* pCmdUI);
	afx_msg void OnMusic5();
	afx_msg void OnUpdateMusic5(CCmdUI* pCmdUI);
	afx_msg void OnMusic6();
	afx_msg void OnUpdateMusic6(CCmdUI* pCmdUI);
	afx_msg void OnMusic7();
	afx_msg void OnUpdateMusic7(CCmdUI* pCmdUI);
	afx_msg void OnMusic8();
	afx_msg void OnUpdateMusic8(CCmdUI* pCmdUI);
	afx_msg void OnMusic9();
	afx_msg void OnUpdateMusic9(CCmdUI* pCmdUI);
	afx_msg void OnGameReplay();
	afx_msg void OnMoreMusic();
	afx_msg void OnMusic();
	afx_msg void OnUpdateMusic(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePriorMap(CCmdUI* pCmdUI);
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnScene1();
	afx_msg void OnUpdateScene1(CCmdUI* pCmdUI);
	afx_msg void OnScene2();
	afx_msg void OnUpdateScene2(CCmdUI* pCmdUI);
	afx_msg void OnScene3();
	afx_msg void OnUpdateScene3(CCmdUI* pCmdUI);
	afx_msg void OnScene4();
	afx_msg void OnUpdateScene4(CCmdUI* pCmdUI);
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg LONG OnMciNotify(UINT wFlags,LONG lDevId);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnEditMap();
	afx_msg void OnDiff1();
	afx_msg void OnDiff2();
	afx_msg void OnDiff3();
	afx_msg void OnDiff4();
	afx_msg void OnDiff5();
	afx_msg void OnDiff6();
	afx_msg void OnDiff7();
	afx_msg void OnUpdateDiff1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff5(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff6(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDiff7(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDifficulty(CCmdUI *pCmdUI);
	afx_msg void OnToolMissionManage();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOptionAutoZoom();
	afx_msg void OnUpdateOptionAutoZoom(CCmdUI *pCmdUI);
	afx_msg void OnOptionSequence();
	afx_msg void OnUpdateOptionSequence(CCmdUI *pCmdUI);
	afx_msg void OnOpenFile();
	afx_msg void OnToolSaveScene();
	afx_msg void OnToolFileRelation();
	afx_msg void OnHelpAuthor();
	afx_msg void OnHelpWeb();
	afx_msg void OnToolPrint();
	afx_msg void OnToolCopy();
	afx_msg void OnToolPaste();
	afx_msg void OnUpdateToolPaste(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__A8DB606B_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
