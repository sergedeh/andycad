#if !defined(AFX_TEXTD_H__7439D9C6_6572_44AD_AB22_4C371326BBF3__INCLUDED_)
#define AFX_TEXTD_H__7439D9C6_6572_44AD_AB22_4C371326BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextD dialog

class CTextD : public CToolBar
{
// Construction
public:
	CTextD();   // standard constructor
	~CTextD();
	CButton let,st1,st2,st3;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextD)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextD)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTD_H__7439D9C6_6572_44AD_AB22_4C371326BBF3__INCLUDED_)
