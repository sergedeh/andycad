#if !defined(AFX_SNAPDLG_H__5A57910B_4A4F_4D25_89B4_6FB521B8D91A__INCLUDED_)
#define AFX_SNAPDLG_H__5A57910B_4A4F_4D25_89B4_6FB521B8D91A__INCLUDED_

#include "SnapObject.h"	// Added by ClassView
#include "SnapGridDlg.h"	// Added by ClassView
#include "PolarTrackDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnapDlg dialog

class CSnapDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CSnapDlg)

// Construction
public:
	CSnapDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0); // standard constructor
	CSnapDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0); // standard constructor


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSnapDlg();

protected:

	// Generated message map functions
	//{{AFX_MSG(CSnapDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAPDLG_H__5A57910B_4A4F_4D25_89B4_6FB521B8D91A__INCLUDED_)
