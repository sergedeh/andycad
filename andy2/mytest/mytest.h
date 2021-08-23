// mytest.h : main header file for the MYTEST application
//

#if !defined(AFX_MYTEST_H__615841FE_5499_4DE3_867F_B2C40A3C58A9__INCLUDED_)
#define AFX_MYTEST_H__615841FE_5499_4DE3_867F_B2C40A3C58A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMytestApp:
// See mytest.cpp for the implementation of this class
//

class CMytestApp : public CWinApp
{
public:
	CMytestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMytestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMytestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTEST_H__615841FE_5499_4DE3_867F_B2C40A3C58A9__INCLUDED_)
