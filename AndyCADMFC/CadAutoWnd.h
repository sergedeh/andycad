#if !defined(AFX_CADAUTOWND_H__765CACFD_81FF_49CA_8F4C_A8C6CF75304A__INCLUDED_)
#define AFX_CADAUTOWND_H__765CACFD_81FF_49CA_8F4C_A8C6CF75304A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoWnd.h : header file
//
#include "CadAutoCamera.h"	// Added by ClassView


/////////////////////////////////////////////////////////////////////////////
// CCadAutoWnd command target

class CCadAutoWnd : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoWnd)

	CCadAutoWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual ~CCadAutoWnd();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoWnd)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCadAutoCamera* auto_cam;

	// Generated message map functions
	//{{AFX_MSG(CCadAutoWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCadAutoWnd)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoWnd)
	afx_msg BOOL GetVisible();
	afx_msg void SetVisible(BOOL bNewValue);
	afx_msg LPDISPATCH GetCamera();
	afx_msg void SetCamera(LPDISPATCH newValue);
	afx_msg void Refresh();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOWND_H__765CACFD_81FF_49CA_8F4C_A8C6CF75304A__INCLUDED_)
