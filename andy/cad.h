// cad.h : main header file for the CAD application
//

#if !defined(AFX_CAD_H__ABCB4AAF_1197_49DE_822E_53DCED2A3E11__INCLUDED_)
#define AFX_CAD_H__ABCB4AAF_1197_49DE_822E_53DCED2A3E11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'pch.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "Cad_i.h"
#include "cadaddin.h"


/////////////////////////////////////////////////////////////////////////////
// CCadApp:
// See cad.cpp for the implementation of this class
//

class CCadApp : public CWinApp
{
	DECLARE_DYNCREATE(CCadApp)

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CCadApp();
//	static CAddinManager m_AddinManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
//	COleTemplateServer m_server;
	//{{AFX_MSG(CCadApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnNotifyStatus(LPTSTR strStatus);
  
private:
	void ShowTipAtStartup(void);
private:
	COleTemplateServer m_server;
	BOOL m_bATLInited;
	BOOL InitATL();
	void ShowTipOfTheDay(void);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAD_H__ABCB4AAF_1197_49DE_822E_53DCED2A3E11__INCLUDED_)
