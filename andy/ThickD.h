#if !defined(AFX_THICKD_H__F52F0B53_952C_40B6_BB24_F4BBCF41FFEF__INCLUDED_)
#define AFX_THICKD_H__F52F0B53_952C_40B6_BB24_F4BBCF41FFEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThickD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThickD dialog

class CThickD : public CDialog
{
// Construction
public:
	CThickD(CWnd* pParent = NULL);   // standard constructor
	BOOL ext;
// Dialog Data
	//{{AFX_DATA(CThickD)
	enum { IDD = IDD_DIALOGTHICK };
	CEdit	m_cext;
	CStatic	m_sext;
	float	m_thickness;
	BOOL	m_cbot;
	BOOL	m_ctop;
	float	m_ext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThickD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThickD)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THICKD_H__F52F0B53_952C_40B6_BB24_F4BBCF41FFEF__INCLUDED_)
