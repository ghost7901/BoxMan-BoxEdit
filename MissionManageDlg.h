#ifndef _MISSION_MANAGE_DLG_H
#define _MISSION_MANAGE_DLG_H

#pragma once

#include "afxcmn.h"
#include "MissionChildDlg.h"
#include "BtnST.h"
#include "afxwin.h"

struct PaintStruct
{
	CWnd *pWnd;
	int Width;
	int Height;
	CString strMap;
	CBitmap Bmp;
};

// CMissionManageDlg �Ի���

class CMissionManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMissionManageDlg)

public:
	CMissionManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMissionManageDlg();

// �Ի�������
	enum { IDD = IDD_MISSION_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CMissionChildDlg *m_pMissionChild[2];
	CTabCtrl m_Tab[2];
	CButtonST m_btnRight,m_btnLeft,m_btnCompare;
	CProgressCtrl m_progCompare;
	CEdit m_editCompare;
public:
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedCompare();
public:
	
};

#endif