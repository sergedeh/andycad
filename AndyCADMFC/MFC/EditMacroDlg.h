#if !defined(AFX_EDITMACRODLG_H__AF28ED1F_7DCC_42B6_B08A_4D9DE4A77134__INCLUDED_)
#define AFX_EDITMACRODLG_H__AF28ED1F_7DCC_42B6_B08A_4D9DE4A77134__INCLUDED_

#include "FilenameEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditMacroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditMacroDlg dialog

class CEditMacroDlg : public CDialog
{
// Construction
public:
	CEditMacroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditMacroDlg)
	enum { IDD = IDD_EDITMACRO };
	CString	m_strMacroName;
	CString	m_strText;
	//}}AFX_DATA
	CString m_strFile;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditMacroDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateTextedit();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITMACRODLG_H__AF28ED1F_7DCC_42B6_B08A_4D9DE4A77134__INCLUDED_)
