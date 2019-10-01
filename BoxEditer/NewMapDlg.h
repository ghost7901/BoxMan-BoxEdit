#pragma once


// CNewMapDlg 对话框

class CNewMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewMapDlg)

public:
	CNewMapDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewMapDlg();

// 对话框数据
	enum { IDD = IDD_NEW_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iMapWidth;
	int m_iMapHeight;
};
