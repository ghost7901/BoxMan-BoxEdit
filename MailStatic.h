#if !defined(AFX_MAILSTATIC_H__08CE7061_8657_11D3_9C81_9FFB3F2EC6F0__INCLUDED_)
#define AFX_MAILSTATIC_H__08CE7061_8657_11D3_9C81_9FFB3F2EC6F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailStatic window

class CMailStatic : public CStatic
{
// Construction
public:
	CMailStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_bMouseTracking;
	virtual ~CMailStatic();

	// Generated message map functions
protected:
	void OnMouseLeave();
	void OnMouseEnter();
//	HBRUSH m_hBrush;
	COLORREF m_crText;
	CFont m_font;
	HCURSOR m_hCursor;
	LOGFONT m_lf;
	//{{AFX_MSG(CMailStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILSTATIC_H__08CE7061_8657_11D3_9C81_9FFB3F2EC6F0__INCLUDED_)
