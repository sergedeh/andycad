#if !defined(AFX_NUMCOPY_H__B5079ED2_598E_4E97_BD56_5F8131EFBFED__INCLUDED_)
#define AFX_NUMCOPY_H__B5079ED2_598E_4E97_BD56_5F8131EFBFED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumCopy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumCopy dialog

class CNumCopy : public CDialog
{
// Construction
public:
	CNumCopy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNumCopy)
	enum { IDD = IDD_NCOPY };
	float	m_offset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumCopy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNumCopy)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMCOPY_H__B5079ED2_598E_4E97_BD56_5F8131EFBFED__INCLUDED_)
