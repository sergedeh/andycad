#if !defined(AFX_NEWTEXT_H__33F5BDD4_16F4_40B5_9377_14AF0ADBAB69__INCLUDED_)
#define AFX_NEWTEXT_H__33F5BDD4_16F4_40B5_9377_14AF0ADBAB69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewText dialog

class CNewText : public CDialog
{
// Construction
public:
	CNewText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewText)
	enum { IDD = IDD_DIALOG4 };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
CToolBar bar;
	// Generated message map functions
	//{{AFX_MSG(CNewText)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTEXT_H__33F5BDD4_16F4_40B5_9377_14AF0ADBAB69__INCLUDED_)
