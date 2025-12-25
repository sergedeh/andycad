#if !defined(AFX_LCOMBOBOX_H__C397CFCF_9182_430B_B5E0_7505F052BF57__INCLUDED_)
#define AFX_LCOMBOBOX_H__C397CFCF_9182_430B_B5E0_7505F052BF57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLComboBox window

class CLComboBox : public CComboBoxEx
{
// Construction
public:
	CLComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLComboBox)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLComboBox();

	// Generated message map functions
protected:
	COMBOBOXEXITEM ps;

	//{{AFX_MSG(CLComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LCOMBOBOX_H__C397CFCF_9182_430B_B5E0_7505F052BF57__INCLUDED_)
