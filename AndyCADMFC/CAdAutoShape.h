#if !defined(AFX_CADAUTOSHAPE_H__FA1826A0_DFD5_41E9_A433_F5DEE85F02B1__INCLUDED_)
#define AFX_CADAUTOSHAPE_H__FA1826A0_DFD5_41E9_A433_F5DEE85F02B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CAdAutoShape.h : header file
//
#include "figure.h"


/////////////////////////////////////////////////////////////////////////////
// CCAdAutoShape command target

class CCAdAutoShape : public CCmdTarget
{
	DECLARE_DYNCREATE(CCAdAutoShape)

	CCAdAutoShape();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAdAutoShape)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCAdAutoShape();

	// Generated message map functions
	//{{AFX_MSG(CCAdAutoShape)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCAdAutoShape)
	afx_msg VARIANT GetFigure();
	afx_msg void SetFigure(const VARIANT FAR* newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CFigure* shape;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOSHAPE_H__FA1826A0_DFD5_41E9_A433_F5DEE85F02B1__INCLUDED_)
