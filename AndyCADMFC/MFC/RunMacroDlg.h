#if !defined(AFX_RUNMACRODLG_H__C387E889_2FAE_487E_B651_CE85C4774572__INCLUDED_)
#define AFX_RUNMACRODLG_H__C387E889_2FAE_487E_B651_CE85C4774572__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RunMacroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRunMacroDlg dialog

class CRunMacroDlg : public CDialog
{
// Construction
public:
	CRunMacroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRunMacroDlg)
	enum { IDD = IDD_RUNMACRO };
	CListBox	m_CMacroList;
	//}}AFX_DATA
	CString m_strMacroName;
	CString m_strFile;
	CString m_strText;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRunMacroDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeMacrolist();
	afx_msg void OnEditRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNMACRODLG_H__C387E889_2FAE_487E_B651_CE85C4774572__INCLUDED_)
