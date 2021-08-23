#if !defined(AFX_CUSTOMWIDTH_H__3B5CB148_68F2_4EB2_B6A9_2DAEA5B3F1E8__INCLUDED_)
#define AFX_CUSTOMWIDTH_H__3B5CB148_68F2_4EB2_B6A9_2DAEA5B3F1E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomWidth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomWidth dialog

class CCustomWidth : public CDialog
{
// Construction
public:
	CCustomWidth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomWidth)
	enum { IDD = IDD_DIALOG3 };
	double	m_cwidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomWidth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomWidth)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMWIDTH_H__3B5CB148_68F2_4EB2_B6A9_2DAEA5B3F1E8__INCLUDED_)
