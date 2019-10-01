// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A8DB6069_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
#define AFX_MAINFRM_H__A8DB6069_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CChildView.h"

class CMainFrame : public CFrameWnd
{	
public:
	CMainFrame();
	void UpdateToolBar(bool bRecalc=true);
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
	BOOL m_bTextTips;  //是否显示工具栏文本标签

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//my
public:
	CStatusBar  m_wndStatusBar;
//end
protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnDropDown(NMHDR* pNotifyStruct,LRESULT* result);
	afx_msg void OnDifficulty();
	afx_msg void OnUpdateDifficulty(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewTexttips();
	afx_msg void OnUpdateViewTexttips(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A8DB6069_6EBD_11D3_9C7F_9D98C5BF25E9__INCLUDED_)
