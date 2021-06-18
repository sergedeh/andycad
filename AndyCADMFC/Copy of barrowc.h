#if !defined(AFX_BARROWC_H__510F95DF_BE6D_4329_855A_4ABA0A951E00__INCLUDED_)
#define AFX_BARROWC_H__510F95DF_BE6D_4329_855A_4ABA0A951E00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BArrowC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBArrowC window

class CBArrowC : public CButton
{
// Construction
public:
	CBArrowC();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBArrowC)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void setorient(bool b);
	virtual ~CBArrowC();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBArrowC)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	bool left;
	bool st;
	UINT TM1;


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARROWC_H__510F95DF_BE6D_4329_855A_4ABA0A951E00__INCLUDED_)
