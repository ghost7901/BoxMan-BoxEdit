#pragma once


// CLoadMapDlg �Ի���

class CLoadMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadMapDlg)

public:
	CLoadMapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadMapDlg();

// �Ի�������
	enum { IDD = DD_DIALOAG_LOAD_NMU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iLoadMapNum;
};
