#pragma once


// CNewMapDlg �Ի���

class CNewMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewMapDlg)

public:
	CNewMapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewMapDlg();

// �Ի�������
	enum { IDD = IDD_NEW_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iMapWidth;
	int m_iMapHeight;
};
