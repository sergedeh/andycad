#if !defined(AFX_EDITPARSE_H__9F69B790_CBE0_4588_87D3_96AB330E2F92__INCLUDED_)
#define AFX_EDITPARSE_H__9F69B790_CBE0_4588_87D3_96AB330E2F92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditParse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditParse window

class CEditParse : public CEdit
{
// Construction
public:
	CEditParse();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditParse)
	public:
	protected:
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditParse();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditParse)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITPARSE_H__9F69B790_CBE0_4588_87D3_96AB330E2F92__INCLUDED_)
