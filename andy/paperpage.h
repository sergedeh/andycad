#if !defined(AFX_PAPERPAGE_H__BA319750_F63E_4764_8743_90EB4A936A93__INCLUDED_)
#define AFX_PAPERPAGE_H__BA319750_F63E_4764_8743_90EB4A936A93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaperPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaperPage

class CPaperPage : public CPropertySheet
{
	DECLARE_DYNAMIC(CPaperPage)

// Construction
public:
	CPaperPage(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPaperPage(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaperPage)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaperPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPaperPage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPERPAGE_H__BA319750_F63E_4764_8743_90EB4A936A93__INCLUDED_)
