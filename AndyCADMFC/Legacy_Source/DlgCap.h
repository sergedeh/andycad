#if !defined(AFX_DLGCAP_H__6BD455C6_FA47_4B0E_AE56_94AF680BB9E6__INCLUDED_)
#define AFX_DLGCAP_H__6BD455C6_FA47_4B0E_AE56_94AF680BB9E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCap dialog

class CDlgCap : public CDialog
{
// Construction
public:
	CDlgCap(CWnd* pParent = NULL);   // standard constructor
    BOOL m_style;
// Dialog Data
	//{{AFX_DATA(CDlgCap)
	enum { IDD = IDD_DIALOG_CAP };
	BOOL	m_cbot;
	BOOL	m_ctop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCap)
	afx_msg void OnRadioGrid();
	afx_msg void OnRadioPoly();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCAP_H__6BD455C6_FA47_4B0E_AE56_94AF680BB9E6__INCLUDED_)
