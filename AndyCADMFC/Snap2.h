#if !defined(AFX_SNAP2_H__80E16588_81DC_4C98_87EC_44957423217D__INCLUDED_)
#define AFX_SNAP2_H__80E16588_81DC_4C98_87EC_44957423217D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Snap2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnap2

class CSnap2 : public CPropertySheet
{
	DECLARE_DYNAMIC(CSnap2)

// Construction
public:
	CSnap2(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSnap2(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnap2)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSnap2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSnap2)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAP2_H__80E16588_81DC_4C98_87EC_44957423217D__INCLUDED_)
