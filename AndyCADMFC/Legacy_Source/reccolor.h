#if !defined(AFX_RECCOLOR_H__22131377_DB92_4BF5_8FDF_082EB3DA9914__INCLUDED_)
#define AFX_RECCOLOR_H__22131377_DB92_4BF5_8FDF_082EB3DA9914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecColor window

class CRecColor : public CButton//,public CSubject
{
// Construction
public:
	CRecColor();

// Attributes
public:
	COLORREF color;
	CRect v;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecColor)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	static COLORREF ccolor,bcolor;
	virtual ~CRecColor();

	// Generated message map functions
protected:
		CPalette palette;

	//{{AFX_MSG(CRecColor)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	bool change;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECCOLOR_H__22131377_DB92_4BF5_8FDF_082EB3DA9914__INCLUDED_)
