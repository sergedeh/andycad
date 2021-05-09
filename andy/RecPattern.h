#if !defined(AFX_RECPATTERN_H__5E267CDC_1791_49F0_9E06_9E9FC3A8430E__INCLUDED_)
#define AFX_RECPATTERN_H__5E267CDC_1791_49F0_9E06_9E9FC3A8430E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecPattern.h : header file
//
#include "subject.h"
/////////////////////////////////////////////////////////////////////////////
// CRecPattern window

class CRecPattern : public CButton,public CSubject
{
// Construction
public:
	CRecPattern();

// Attributes
public:
	    CString patsource;
		CRect v;
//		CImagex texture;

// Operations
public:
	CBitmap*  pattern;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecPattern)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setBitmap(CBitmap* s,CString sg);

//    static CBITMAP pat1, pat2;
	static CFile fpat;
	virtual ~CRecPattern();

private:
	bool change;
	// Generated message map functions
protected:
	//{{AFX_MSG(CRecPattern)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECPATTERN_H__5E267CDC_1791_49F0_9E06_9E9FC3A8430E__INCLUDED_)
