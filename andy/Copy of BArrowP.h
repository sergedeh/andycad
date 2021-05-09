#if !defined(AFX_BARROWP_H__0F976EDC_9795_4E19_ADCA_56DDD07869FA__INCLUDED_)
#define AFX_BARROWP_H__0F976EDC_9795_4E19_ADCA_56DDD07869FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BArrowP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBArrowP window

class CBArrowP : public CButton
{
// Construction
public:
	CBArrowP();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBArrowP)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setorient(bool b);
	virtual ~CBArrowP();

	// Generated message map functions
protected:
	UINT TM1;
	bool st;
	bool left;
	//{{AFX_MSG(CBArrowP)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARROWP_H__0F976EDC_9795_4E19_ADCA_56DDD07869FA__INCLUDED_)
