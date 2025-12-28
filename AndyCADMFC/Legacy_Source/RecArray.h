#if !defined(AFX_RECARRAY_H__B23955F8_8615_484A_8FCB_49C133C7322E__INCLUDED_)
#define AFX_RECARRAY_H__B23955F8_8615_484A_8FCB_49C133C7322E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecArray dialog

class CRecArray : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CRecArray(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecArray)
	enum { IDD = IDD_RECARRAY };
	int		m_cnb;
	int		m_rnb;
	long	m_dx;
	long	m_dy;
	float	m_lspacing;
	int		m_nblevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecArray)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CRecArray)
	afx_msg void OnOffset();
	afx_msg void OnUpdateOffset(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECARRAY_H__B23955F8_8615_484A_8FCB_49C133C7322E__INCLUDED_)
