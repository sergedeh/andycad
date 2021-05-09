#if !defined(AFX_ARCPROP_H__B8BF6A84_5CDF_4F5C_970A_136BC611706B__INCLUDED_)
#define AFX_ARCPROP_H__B8BF6A84_5CDF_4F5C_970A_136BC611706B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArcProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArcProp dialog

class CArcProp : public CDialog
{
// Construction
public:
	CArcProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArcProp)
	enum { IDD = IDD_ARCPROP};
	double	m_arcRadius;
	BOOL	m_swaprad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArcProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArcProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCPROP_H__B8BF6A84_5CDF_4F5C_970A_136BC611706B__INCLUDED_)
