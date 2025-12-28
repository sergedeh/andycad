#if !defined(AFX_LAYBAR_H__A1B9188D_FE17_4876_82B7_FBB7F71699E7__INCLUDED_)
#define AFX_LAYBAR_H__A1B9188D_FE17_4876_82B7_FBB7F71699E7__INCLUDED_

#include "LayList.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayBar dialog

class CLayBar : public CDialogBar
{
// Construction
public:
	CLayBar();   // standard constructor
	virtual ~CLayBar();   // standard constructor


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CLayList list;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYBAR_H__A1B9188D_FE17_4876_82B7_FBB7F71699E7__INCLUDED_)
