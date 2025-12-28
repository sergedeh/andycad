#if !defined(AFX_FILEMACRODLG_H__E4375DBC_C354_4084_9501_B5314AB59FEF__INCLUDED_)
#define AFX_FILEMACRODLG_H__E4375DBC_C354_4084_9501_B5314AB59FEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileMacroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileMacroDlg dialog

class CFileMacroDlg : public CDialog
{
// Construction
public:
	CFileMacroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileMacroDlg)
	enum { IDD = IDD_FILEMACRO };
	CComboBox	m_CMacroCombo;
	//}}AFX_DATA
	CString m_strMacroName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileMacroDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMacrocombo();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEMACRODLG_H__E4375DBC_C354_4084_9501_B5314AB59FEF__INCLUDED_)
