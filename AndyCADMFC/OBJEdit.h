#if !defined(AFX_OBJEDIT_H__61190280_BBEA_11D8_A4A5_E8ED6EE0001A__INCLUDED_)
#define AFX_OBJEDIT_H__61190280_BBEA_11D8_A4A5_E8ED6EE0001A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OBJEdit.h : header file
//
#include "vector.h"
/////////////////////////////////////////////////////////////////////////////
// COBJEdit dialog

class COBJEdit : public CDialog
{
// Construction
public:
	void setobj(FINFO oh);
	COBJEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COBJEdit)
	enum { IDD = IDD_OBJEDIT };
	CString	m_auth;
	CString	m_descr;
	CString	m_name;
	double	m_cost;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COBJEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COBJEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJEDIT_H__61190280_BBEA_11D8_A4A5_E8ED6EE0001A__INCLUDED_)
