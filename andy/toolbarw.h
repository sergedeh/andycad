#if !defined(AFX_TOOLBARW_H__4C4F52DD_9CDA_441A_B39E_4A26650F717C__INCLUDED_)
#define AFX_TOOLBARW_H__4C4F52DD_9CDA_441A_B39E_4A26650F717C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarW window

class CToolBarW : public CToolBar
{
// Construction
public:
	CToolBarW();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarW)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarW();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarW)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARW_H__4C4F52DD_9CDA_441A_B39E_4A26650F717C__INCLUDED_)
