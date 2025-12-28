#if !defined(AFX_POLARTRACKDLG_H__548E8666_A7EE_4072_ADFD_83DF885AC9BE__INCLUDED_)
#define AFX_POLARTRACKDLG_H__548E8666_A7EE_4072_ADFD_83DF885AC9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolarTrackDlg.h : header file
//
#include "property.h"
/////////////////////////////////////////////////////////////////////////////
// CPolarTrackDlg dialog

class CPolarTrackDlg : public CPropertyPage, public CProperty
{
// Construction
public:
	CPolarTrackDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPolarTrackDlg)
	enum { IDD = IDD_PROPPAGE_POLARTRACK };
	BOOL	m_addangle;
	BOOL	m_polartrackon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolarTrackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPolarTrackDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLARTRACKDLG_H__548E8666_A7EE_4072_ADFD_83DF885AC9BE__INCLUDED_)
