#if !defined(AFX_LIBDIALOG_H__8F776B58_68BA_445F_B8A4_170959C42245__INCLUDED_)
#define AFX_LIBDIALOG_H__8F776B58_68BA_445F_B8A4_170959C42245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Libdialog.h : header file
//
//#include "ctreectrl.h"

/////////////////////////////////////////////////////////////////////////////
// CLibdialog dialog

class CLibdialog : public CDialogBar
{
// Construction
public:
//	CTreeCtrl m_libtree;
	CHeaderCtrl hlist;
	CToolBarCtrl hto;
	bool drag;
	CImageList libimlist,libimtool;
	CRect wnd;

	CLibdialog();   // standard constructor
	virtual ~CLibdialog();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibdialog)
	enum { IDD = IDD_LIB };
	CTreeCtrl*	m_libtree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibdialog)
	public:
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
protected:
	DECLARE_MESSAGE_MAP()
// Implementation
protected:


	CTreeCtrl *m_lib;
	// Generated message map functions
	//{{AFX_MSG(CLibdialog)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBDIALOG_H__8F776B58_68BA_445F_B8A4_170959C42245__INCLUDED_)
