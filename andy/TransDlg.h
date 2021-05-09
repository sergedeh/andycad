#if !defined(AFX_TRANSDLG_H__29AD9410_60D2_4A45_BDEA_8983386CE761__INCLUDED_)
#define AFX_TRANSDLG_H__29AD9410_60D2_4A45_BDEA_8983386CE761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransDlg.h : header file
//
#include "subject.h"
/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog

class CTransDlg : public CDialog,public CSubject
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTransDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransDlg)
	enum { IDD = IDD_TRANSDIALOG };
	CEdit	m_edit;
	CSliderCtrl	m_slidec;
	int		m_value;
	int		m_slidev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(CTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSDLG_H__29AD9410_60D2_4A45_BDEA_8983386CE761__INCLUDED_)
