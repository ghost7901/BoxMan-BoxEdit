// BoxEditer.h : BoxEditer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBoxEditerApp:
// �йش����ʵ�֣������ BoxEditer.cpp
//

class CBoxEditerApp : public CWinApp
{
public:
	CBoxEditerApp();


// ��д
public:
	virtual BOOL InitInstance();

	CWnd *	m_pBoxManEditerWnd;

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBoxEditerApp theApp;