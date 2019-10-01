#pragma once

#include "afxcmn.h"
#include "Ini.h"
#include "BtnST.h"
#include "afxwin.h"

// CHeaderCtrl 派生类
class CMyHeaderCtrl : public CHeaderCtrl
{
public:
	CMyHeaderCtrl();
	~CMyHeaderCtrl();
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
protected:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

class CMyListCtrl : public CListCtrl
{
public:
	CMyListCtrl();
	~CMyListCtrl();
protected:	
	CMyHeaderCtrl m_ctlHeader;
	virtual void PreSubclassWindow();
};

// CMissionChildDlg 对话框

class CMissionChildDlg : public CDialog, public CIni
{
	DECLARE_DYNAMIC(CMissionChildDlg)

public:
	CMissionChildDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMissionChildDlg();

// 对话框数据
	enum { IDD = IDD_MISSION_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListMission;
	CButtonST m_btnOpen,
		      m_btnDelete,
			  m_btnSave,
			  m_btnPreview,
			  m_btnUp,
			  m_btnDown;
	CEdit m_MapPath;
public:
	virtual BOOL OnInitDialog();
	BOOL ReadMission(CString Name);
	int UnSelectedAll();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnNMDblclkListMission(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
