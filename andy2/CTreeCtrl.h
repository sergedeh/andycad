#if !defined(AFX_CTREECTRL_H__69637F48_BC55_11D8_A4A5_B6FF981E7C1A__INCLUDED_)
#define AFX_CTREECTRL_H__69637F48_BC55_11D8_A4A5_B6FF981E7C1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCTreeCtrl window

class CCTreeCtrl : public CListCtrl
{
// Construction
public:
	CCTreeCtrl();

// Attributes
public:
	CImageList libimlist;
	CTreeCtrl m_libtree;
	CHeaderCtrl hlist;
private:
	bool drag;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTreeCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTREECTRL_H__69637F48_BC55_11D8_A4A5_B6FF981E7C1A__INCLUDED_)
