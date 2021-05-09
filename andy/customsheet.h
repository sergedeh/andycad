#if !defined(AFX_CUSTOMSHEET_H__EBBE1F10_663B_4B9D_AA65_72174D3BE6C6__INCLUDED_)
#define AFX_CUSTOMSHEET_H__EBBE1F10_663B_4B9D_AA65_72174D3BE6C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomSheet.h : header file
//
#include "paperpag.h"
#include "gridpag.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomSheet

class CCustomSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCustomSheet)

// Construction
public:
	CCustomSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCustomSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CGridPag  m_custgrid;
	CPaperPag m_custpaper;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMSHEET_H__EBBE1F10_663B_4B9D_AA65_72174D3BE6C6__INCLUDED_)
