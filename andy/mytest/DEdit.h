#if !defined(AFX_DEDIT_H__C6889EF8_1146_422D_A7BA_90B27DF95048__INCLUDED_)
#define AFX_DEDIT_H__C6889EF8_1146_422D_A7BA_90B27DF95048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDEdit window

class CDEdit : public CEdit
{
// Construction
public:
	CDEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEDIT_H__C6889EF8_1146_422D_A7BA_90B27DF95048__INCLUDED_)
