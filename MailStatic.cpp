// MailStatic.cpp : implementation file
//

#include "stdafx.h"
#include "BoxMan.h"
#include "MailStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailStatic

CMailStatic::CMailStatic()
{
	//my
	m_crText = RGB(0,0,255);

	::GetObject( (HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(m_lf), &m_lf);
//	m_lf.lfWeight = FW_BOLD;
//	m_lf.lfUnderline = false;
	int creatOk = m_font.CreateFontIndirect(&m_lf);
	ASSERT( creatOk );

	m_hCursor = AfxGetApp()->LoadStandardCursor( MAKEINTRESOURCE(32649) );
//	m_hBrush = ::CreateSolidBrush( GetSysColor(COLOR_3DFACE) );

	m_bMouseTracking = false;
	//end
}

CMailStatic::~CMailStatic()
{
	//my
	m_font.DeleteObject();
//	::DeleteObject(m_hBrush);
	//end
}


BEGIN_MESSAGE_MAP(CMailStatic, CStatic)
	//{{AFX_MSG_MAP(CMailStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailStatic message handlers

BOOL CMailStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	//my
	if (m_hCursor) {
		::SetCursor(m_hCursor);
		return TRUE;
	}
	//end
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

HBRUSH CMailStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	//my
	if (CTLCOLOR_STATIC == nCtlColor) {
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(GetSysColor(COLOR_3DFACE)); //RGB( 128,128,128) );
	}
	//end
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	//my
	return /*m_hBrush;*/(HBRUSH)GetStockObject(NULL_BRUSH);
	//end
}

void CMailStatic::OnClicked() 
{
	// TODO: Add your control notification handler code here
	//my
	CString strLink;

	GetWindowText(strLink);
	strLink = "mailto:" + strLink;
	::ShellExecute(NULL,"open",strLink,NULL,NULL,SW_SHOWNORMAL);
	//end
}

void CMailStatic::OnMouseEnter()
{
	//my
	m_bMouseTracking = true;

//	m_lf.lfWeight = FW_BOLD;
//	m_lf.lfItalic = true;
	m_lf.lfUnderline = true;
	m_font.DeleteObject();
	int creatOk = m_font.CreateFontIndirect(&m_lf);
	ASSERT( creatOk );

	SetCapture();
	Invalidate();
	UpdateWindow();
	//end
}

void CMailStatic::OnMouseLeave()
{
	//my
	m_bMouseTracking = false;

//	m_lf.lfWeight = FW_NORMAL;
//	m_lf.lfItalic = false;
	m_lf.lfUnderline = false;
	m_font.DeleteObject();
	int creatOk = m_font.CreateFontIndirect(&m_lf);
	ASSERT( creatOk );

	Invalidate();
	UpdateWindow();
	ReleaseCapture();
	//end
}

void CMailStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//my
	if( !m_bMouseTracking || GetCapture() != this ){
		OnMouseEnter();
	}else{
		CRect rc;
		GetClientRect(&rc);
		if(!rc.PtInRect(point))	// The mouse cursor is no longer above this button
			OnMouseLeave();
	}
	//end
	CStatic::OnMouseMove(nFlags, point);
}
