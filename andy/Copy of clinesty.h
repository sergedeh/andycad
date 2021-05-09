#if !defined(AFX_CLINESTY_H__7CF0EC8C_21B9_43BE_8015_27D43BA93433__INCLUDED_)
#define AFX_CLINESTY_H__7CF0EC8C_21B9_43BE_8015_27D43BA93433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CLineSty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCLineSty dialog

class CCLineSty : public CDialog
{
// Construction
public:
	CImageList m_list;
	CComboBoxEx m_combo;
	CCLineSty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCLineSty)
	enum { IDD = IDD_LDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLineSty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCLineSty)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLINESTY_H__7CF0EC8C_21B9_43BE_8015_27D43BA93433__INCLUDED_)
