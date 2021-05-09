#if !defined(AFX_NEWMACRODLG_H__FF77C42F_0D39_435D_94DB_2B65E59BA3E1__INCLUDED_)
#define AFX_NEWMACRODLG_H__FF77C42F_0D39_435D_94DB_2B65E59BA3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewMacroDlg.h : header file
//
#include "FilenameEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CNewMacroDlg dialog

class CNewMacroDlg : public CDialog
{
// Construction
public:
	CFilenameEdit m_CName;
	CNewMacroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewMacroDlg)
	enum { IDD = IDD_NEWMACRO };
//	CFileNameEdit	m_CName;
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewMacroDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWMACRODLG_H__FF77C42F_0D39_435D_94DB_2B65E59BA3E1__INCLUDED_)
