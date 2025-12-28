#if !defined(AFX_PROPPAGE_H__3F299427_657E_44AD_9C8E_A9A1D682E36F__INCLUDED_)
#define AFX_PROPPAGE_H__3F299427_657E_44AD_9C8E_A9A1D682E36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPage.h : header file
//
#include "PageCircle.h"
#include "LineProp.h"
#include "SplineProp.h"
//	CPropertyPage Object;
/////////////////////////////////////////////////////////////////////////////
// CPropPage

class CPropPage : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropPage)

// Construction
public:
	CPropPage(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropPage(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropPage)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropPage();

	// Generated message map functions
protected:
	CPageCircle Circle;
	CLineProp Line;
//	CPropertyPage arc;
	CSplineProp spline;
//	CPropertyPage Object;
	//{{AFX_MSG(CPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE_H__3F299427_657E_44AD_9C8E_A9A1D682E36F__INCLUDED_)
