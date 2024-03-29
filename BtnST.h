#ifndef _BTNST_H
#define _BTNST_H

#if _MSC_VER>=1000
#pragma once
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonST window

#define ST_LIKEIE

// Comment this if you don't want to use CMemDC class
//#define ST_USE_MEMDC

/////////////////////////////////////////////////////////////////////////////
// CButtonST window

class CButtonST : public CButton
{
// Construction
public:
    CButtonST();
	~CButtonST();
    enum {ST_ALIGN_HORIZ, ST_ALIGN_VERT};

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CButtonST)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void AddToolTip ( const CString &strTip );
	BOOL SetBtnCursor(int nCursorId = -1);

	void SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint = FALSE);
	BOOL GetFlatFocus();

	void SetDefaultActiveFgColor(BOOL bRepaint = FALSE);
	void SetActiveFgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetActiveFgColor();
	
	void SetDefaultActiveBgColor(BOOL bRepaint = FALSE);
	void SetActiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetActiveBgColor();
	
	void SetDefaultInactiveFgColor(BOOL bRepaint = FALSE);
	void SetInactiveFgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetInactiveFgColor();

	void SetDefaultInactiveBgColor(BOOL bRepaint = FALSE);
	void SetInactiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetInactiveBgColor();

	void SetShowText(BOOL bShow = TRUE);
	BOOL GetShowText();

	void SetAlign(int nAlign);
	int GetAlign();

	void SetFlat(BOOL bState = TRUE);
	BOOL GetFlat();

	void DrawBorder(BOOL bEnable = TRUE);
	void SetIcon(int nIconInId, int nIconOutId = NULL, 
		unsigned char cx = 32, unsigned char cy = 32);

	static const short GetVersionI();
	static const char* GetVersionC();

protected:
	CString m_strToolTip;
	CToolTipCtrl m_ctrlToolTip;
    //{{AFX_MSG(CButtonST)
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void DrawTheIcon(CDC* pDC, CString* title, RECT* rcItem, CRect* captionRect, BOOL IsPressed, BOOL IsDisabled);

	int m_nAlign;
	BOOL m_bShowText;
	BOOL m_bDrawBorder;
	BOOL m_bIsFlat;
	BOOL m_MouseOnButton;
	BOOL m_bDrawFlatFocus;

	HCURSOR m_hCursor;

	HICON m_hIconIn;
	HICON m_hIconOut;
	BYTE m_cyIcon;
	BYTE m_cxIcon;

	COLORREF  m_crInactiveBg;
    COLORREF  m_crInactiveFg;
    COLORREF  m_crActiveBg;
    COLORREF  m_crActiveFg;
};


#ifdef ST_USE_MEMDC
//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//           25 feb 98 - fixed minor assertion bug
//
// This class implements a memory Device Context

class CMemDC : public CDC
{
public:

    // constructor sets up the memory DC
    CMemDC(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
              
        if (m_bMemDC)    // Create a Memory DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    // Destructor copies the contents of the mem DC to the original DC
    ~CMemDC()
    {
        if (m_bMemDC) 
        {    
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // Allow usage as a pointer
    CMemDC* operator->() {return this;}
        
    // Allow usage as a pointer
    operator CMemDC*() {return this;}

private:
    CBitmap  m_bitmap;      // Offscreen bitmap
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC
    CDC*     m_pDC;         // Saves CDC passed in constructor
    CRect    m_rect;        // Rectangle of drawing area.
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};

#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
