#if !defined(AFX_SUBWND_H__D15B54C6_A27F_4A17_A1D7_B1D4C668E0A5__INCLUDED_)
#define AFX_SUBWND_H__D15B54C6_A27F_4A17_A1D7_B1D4C668E0A5__INCLUDED_

#include "DrawWnd.h"	// Added by ClassView
#include "Ruler1.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubWnd window

class CSubWnd : public CWnd
{
// Construction
public:
	CSubWnd();
	~CSubWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubWnd)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSubWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	protected:
    int m_nViewWidth;   // Workspace width in pixels
    int m_nViewHeight;  // Workspace height in pixels
    int m_nHScrollPos;  // Horizontal scroll position
    int m_nVScrollPos;  // Vertical scroll position
    int m_nHPageSize;   // Horizontal page size
    int m_nVPageSize;   // Vertical page size


	CRect initrec;
	float ratio[2];
	CRect m_wndRect;
	CRuler m_hruler,m_vruler;
	CDrawWnd m_drawwnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBWND_H__D15B54C6_A27F_4A17_A1D7_B1D4C668E0A5__INCLUDED_)
