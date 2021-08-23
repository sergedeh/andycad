#if !defined(AFX_REGDIALOG_H__8DD279A1_CCE3_11D3_ABCB_D161EFEBDB20__INCLUDED_)
#define AFX_REGDIALOG_H__8DD279A1_CCE3_11D3_ABCB_D161EFEBDB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegDialog.h : header file
//

///////////////////////////////////////////////////////////
//														 //
// 1. Insert CRegDialog class to project                 //
//														 //
// 2. Add to mainApp.cpp :								 //
//														 //	
//		#include "RegDialog.h"							 //
//														 //
// 3. Insert function call in mainApp.cpp				 //
//														 //
//		BOOL CMy123App::InitInstance()					 //
//		{												 //
//		      ...                                        //
//			SetRegistryKey(_T("MyCompany"));             //
//			CRegDialog RegistrationDialog;				 //
//			RegistrationDialog.Check();					 //	
//			  ...										 //
//														 //
//		...}											 //
//														 //
// 4. Set App Specific Data in RegDialog.cpp			 //
//														 //
//														 //
///////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRegDialog dialog
#include <atlbase.h>
#include "resource.h"  
#include "Crypto1.h"

class CRegDialog : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Check();
	CRegDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDialog)
	enum { IDD = IDD_REGDIALOG };
	CButton	m_on;
	CEdit	m_entercode;
	CStatic	m_stat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	CCrypto m_crypto;
//	CStatic Stat1;
	// Generated message map functions
	//{{AFX_MSG(CRegDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAskcode();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDIALOG_H__8DD279A1_CCE3_11D3_ABCB_D161EFEBDB20__INCLUDED_)
