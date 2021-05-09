#if !defined(AFX_SNAPGRIDDLG_H__11BC4F87_2FD3_428B_A402_3FFB80DB485D__INCLUDED_)
#define AFX_SNAPGRIDDLG_H__11BC4F87_2FD3_428B_A402_3FFB80DB485D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnapGridDlg.h : header file
//
#include "property.h"
/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg dialog

class CSnapGridDlg : public CPropertyPage, public CProperty
{
// Construction
public:
	CSnapGridDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnapGridDlg)
	enum { IDD = IDD_PROPPAGE_SNAP };
	BOOL	m_gridon;
	BOOL	m_snapon;
	float	m_angle;
	float	m_gridxspacing;
	float	m_gridyspacing;
	float	m_polardistance;
	float	m_xbase;
	float	m_ybase;
	float	m_snapxspacing;
	float	m_snapyspacing;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSnapGridDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAPGRIDDLG_H__11BC4F87_2FD3_428B_A402_3FFB80DB485D__INCLUDED_)
