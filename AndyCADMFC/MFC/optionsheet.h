#if !defined(AFX_OPTIONSHEET_H__A3B86A93_AE6E_4521_B74A_7D118C48E8A8__INCLUDED_)
#define AFX_OPTIONSHEET_H__A3B86A93_AE6E_4521_B74A_7D118C48E8A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Optionsheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsheet

class COptionsheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsheet)

// Construction
public:
	COptionsheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptionsheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSHEET_H__A3B86A93_AE6E_4521_B74A_7D118C48E8A8__INCLUDED_)
