#if !defined(AFX_TABOPTION_H__71275D8B_6D28_4414_946F_B1CAB509C727__INCLUDED_)
#define AFX_TABOPTION_H__71275D8B_6D28_4414_946F_B1CAB509C727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabOption window

class CTabOption : public CTabCtrl
{
// Construction
public:
	CTabOption();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabOption)
	//}}AFX_VIRTUAL

// Implementation
public:
	CTabCtrl mtab1;
	virtual ~CTabOption();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabOption)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABOPTION_H__71275D8B_6D28_4414_946F_B1CAB509C727__INCLUDED_)
