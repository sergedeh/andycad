#if !defined(AFX_LINESTYLE_H__80123D0A_D494_43EF_90EB_EDDBDBCD34FA__INCLUDED_)
#define AFX_LINESTYLE_H__80123D0A_D494_43EF_90EB_EDDBDBCD34FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Linestyle.h : header file
//
#include "LcomboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CLinestyle dialog

class CLinestyle : public CDialogBar
{
// Construction
public:
	CLinestyle();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinestyle)
	enum { IDD = IDD_LINESTYLE };
	CLComboBox	m_combo;
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinestyle)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID );
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap lstyle[7];
	// Generated message map functions
	//{{AFX_MSG(CLinestyle)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINESTYLE_H__80123D0A_D494_43EF_90EB_EDDBDBCD34FA__INCLUDED_)
