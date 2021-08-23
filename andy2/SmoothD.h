#if !defined(AFX_SMOOTHD_H__92CEF17D_917E_4624_8247_0B069B0D1EF2__INCLUDED_)
#define AFX_SMOOTHD_H__92CEF17D_917E_4624_8247_0B069B0D1EF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmoothD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmoothD dialog

class CSmoothD : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CSmoothD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmoothD)
	enum { IDD = IDD_DIALOG_SMOOTH };
	int		m_us;
	int		m_vs;
	int		m_ws;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmoothD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CSmoothD)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMOOTHD_H__92CEF17D_917E_4624_8247_0B069B0D1EF2__INCLUDED_)
