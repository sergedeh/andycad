#if !defined(AFX_NSTATUSBAR_H__DA0652C1_5D63_43F5_B9DE_7CBCD6B1A874__INCLUDED_)
#define AFX_NSTATUSBAR_H__DA0652C1_5D63_43F5_B9DE_7CBCD6B1A874__INCLUDED_

#include "PropPage.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNStatusBar dialog

class CNStatusBar : public CDialogBar
{
// Construction
public:
	CNStatusBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNStatusBar)
	enum { IDD = IDD_DBPROPERTY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNStatusBar)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPropPage *prop;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSTATUSBAR_H__DA0652C1_5D63_43F5_B9DE_7CBCD6B1A874__INCLUDED_)
