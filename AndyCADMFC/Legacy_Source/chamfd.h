#if !defined(AFX_CHAMFD_H__0A9ADE33_6507_47D9_BEF4_E9AF919A0E49__INCLUDED_)
#define AFX_CHAMFD_H__0A9ADE33_6507_47D9_BEF4_E9AF919A0E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChamfD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChamfD dialog

class CChamfD : public CDialog
{
// Construction
public:
	CChamfD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChamfD)
	enum { IDD = IDD_CHAMF };
	long	m_chlgth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChamfD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChamfD)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAMFD_H__0A9ADE33_6507_47D9_BEF4_E9AF919A0E49__INCLUDED_)
