#if !defined(AFX_MAPSELECTDLG_H__63033781_790C_11D3_9C80_E69E36DF64FC__INCLUDED_)
#define AFX_MAPSELECTDLG_H__63033781_790C_11D3_9C80_E69E36DF64FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BtnST.h"
// MapSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapSelectDlg dialog

class MapSelectDlg : public CDialog
{
// Construction
public:
	MapSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapSelectDlg)
	enum { IDD = IDD_SELECTMAP };
	int		m_SelectMap;
	CButtonST m_OK;
	CButtonST m_Cancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapSelectDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPSELECTDLG_H__63033781_790C_11D3_9C80_E69E36DF64FC__INCLUDED_)
