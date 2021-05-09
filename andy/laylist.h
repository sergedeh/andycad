#if !defined(AFX_LAYLIST_H__EA8A6D0D_3022_44A1_B41A_9DE60E48DE7A__INCLUDED_)
#define AFX_LAYLIST_H__EA8A6D0D_3022_44A1_B41A_9DE60E48DE7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayList window

class CLayList : public CListCtrl
{
// Construction
public:
	CLayList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLayList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLayList)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYLIST_H__EA8A6D0D_3022_44A1_B41A_9DE60E48DE7A__INCLUDED_)
