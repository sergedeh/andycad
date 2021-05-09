#if !defined(AFX_INFOBAR_H__5AAF4D52_59C0_4113_AEB2_32D7E2766088__INCLUDED_)
#define AFX_INFOBAR_H__5AAF4D52_59C0_4113_AEB2_32D7E2766088__INCLUDED_

#include "afxmt.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoBar.h : header file

#include "CadView.h"
#include "draw.h"


/////////////////////////////////////////////////////////////////////////////
// CInfoBar dialog

class CInfoBar : public CDialogBar,public CObserver
{
// Construction
public:
	void SendNotify(CString s,void* param[7]);
	void setInterest(CSubject *sub);
	CInfoBar();   // standard constructor
	virtual ~CInfoBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoBar)
	enum { IDD = CG_IDD_MYDIALOGBAR };
	long	m_xv;
	long	m_yv;
	long	m_length;
	long	m_angle;
	long	m_area;
	long	m_zv;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInfoBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_INFOBAR_H__5AAF4D52_59C0_4113_AEB2_32D7E2766088__INCLUDED_)
