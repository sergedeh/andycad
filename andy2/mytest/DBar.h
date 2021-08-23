#if !defined(AFX_DBAR_H__661E8465_57D6_4809_8D11_C8248E51060B__INCLUDED_)
#define AFX_DBAR_H__661E8465_57D6_4809_8D11_C8248E51060B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBar.h : header file
//
#include "dedit.h"

/////////////////////////////////////////////////////////////////////////////
// CDBar dialog

class CDBar : public CDialogBar
{
// Construction
public:
	CDBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBar)
	enum { IDD = IDD_DIALOGBAR };
	CDEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBAR_H__661E8465_57D6_4809_8D11_C8248E51060B__INCLUDED_)
