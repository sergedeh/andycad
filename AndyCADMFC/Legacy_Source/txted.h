#if !defined(AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_)
#define AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxtED.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxtED window

class CTxtED : public CRichEditCtrl
{
// Construction
public:
	CTxtED();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxtED)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTxtED();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTxtED)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_)
