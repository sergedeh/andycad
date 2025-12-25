#if !defined(AFX_POPBAR_H__4F0BE637_5A3B_47DD_965C_90F2A3668B78__INCLUDED_)
#define AFX_POPBAR_H__4F0BE637_5A3B_47DD_965C_90F2A3668B78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPopBar window

class CPopBar : public CToolBar
{
// Construction
public:
	CPopBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void create();
	virtual ~CPopBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPopBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPBAR_H__4F0BE637_5A3B_47DD_965C_90F2A3668B78__INCLUDED_)
