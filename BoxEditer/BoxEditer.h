// BoxEditer.h : BoxEditer 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CBoxEditerApp:
// 有关此类的实现，请参阅 BoxEditer.cpp
//

class CBoxEditerApp : public CWinApp
{
public:
	CBoxEditerApp();


// 重写
public:
	virtual BOOL InitInstance();

	CWnd *	m_pBoxManEditerWnd;

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBoxEditerApp theApp;