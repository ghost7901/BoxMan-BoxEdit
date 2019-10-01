#pragma once


// CLoadMapDlg 对话框

class CLoadMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadMapDlg)

public:
	CLoadMapDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadMapDlg();

// 对话框数据
	enum { IDD = DD_DIALOAG_LOAD_NMU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLoadMapNum;
};
