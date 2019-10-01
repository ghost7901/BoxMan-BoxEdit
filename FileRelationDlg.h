#pragma once

#include "BtnST.h"

// CFileRelationDlg 对话框

class CFileRelationDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileRelationDlg)

public:
	CButtonST m_btnBxs,m_btnBxm,m_btnDelbxs,m_btnDelbxm;
public:
	CFileRelationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileRelationDlg();

// 对话框数据
	enum { IDD = IDD_FILE_RELATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBxsRelation();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelBxsRelation();
public:
	afx_msg void OnBnClickedBxmRelation();
public:
	afx_msg void OnBnClickedDelBxmRelation();
};
