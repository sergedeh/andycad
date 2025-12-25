#if !defined(AFX_SNAPOBJECTDLG_H__8A4156C6_DE0B_4DE1_9C33_F8FA51DC6A62__INCLUDED_)
#define AFX_SNAPOBJECTDLG_H__8A4156C6_DE0B_4DE1_9C33_F8FA51DC6A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnapObjectDlg.h : header file
//
#include "property.h"
/////////////////////////////////////////////////////////////////////////////
// CSnapObject dialog

class CSnapObjectDlg : public CPropertyPage, public CProperty
{
// Construction
public:
	void getValue(vector<CProperty*>& val);
	CSnapObjectDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnapObject)
	enum { IDD = IDD_PROPPAGE_OBJECTSNAP };
	BOOL	m_appint;
	BOOL	m_center;
	BOOL	m_endpoint;
	BOOL	m_exten;
	BOOL	m_inter;
	BOOL	m_midpoint;
	BOOL	m_nearest;
	BOOL	m_para;
	BOOL	m_perp;
	BOOL	m_snapon;
	BOOL	m_tangent;
	BOOL	m_trackingon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSnapObject)
	afx_msg void OnButtonselectall();
	afx_msg void OnButtoncancelall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAPOBJECTDlG_H__8A4156C6_DE0B_4DE1_9C33_F8FA51DC6A62__INCLUDED_)
