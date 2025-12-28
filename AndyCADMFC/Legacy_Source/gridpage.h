#if !defined(AFX_GRIDPAGE_H__67AB2F69_B509_4E6C_8454_1D593DD3A6F6__INCLUDED_)
#define AFX_GRIDPAGE_H__67AB2F69_B509_4E6C_8454_1D593DD3A6F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridPage

class CGridPage : public CPropertySheet
{
	DECLARE_DYNAMIC(CGridPage)

// Construction
public:
	CGridPage(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGridPage(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridPage)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGridPage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDPAGE_H__67AB2F69_B509_4E6C_8454_1D593DD3A6F6__INCLUDED_)
