/////////////////////////////////////////////////////////////////////////////
// CMemDC.h : main header file for the CMEMDC application
//
// Written by Kelly Ward
// of Microsoft Product Support Services, Languages Developer Support
// Copyright (c) 1996 Microsoft Corporation. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCMemDCApp:
// See CMemDC.cpp for the implementation of this class
//

class CCMemDCApp : public CWinApp
{
public:
	CCMemDCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCMemDCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCMemDCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
