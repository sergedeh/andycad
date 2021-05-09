#if !defined(AFX_LAYERAD_H__BBDD6293_B9EF_11D8_A4A5_AACF179A7E1A__INCLUDED_)
#define AFX_LAYERAD_H__BBDD6293_B9EF_11D8_A4A5_AACF179A7E1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Layerad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayerad dialog

class CLayerad : public CDialog
{
// Construction
public:
	CLayerad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLayerad)
	enum { IDD = IDD_LAYADD };
	CString	m_layadd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayerad)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERAD_H__BBDD6293_B9EF_11D8_A4A5_AACF179A7E1A__INCLUDED_)
