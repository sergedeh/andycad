#if !defined(AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_)
#define AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxtED.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxtED window

#include <functional>

class CTxtED : public CRichEditCtrl
{
// Construction
public:
	CTxtED();
	// Called when Escape is pressed in the edit box (cancels the edit).
	std::function<void()> onEscape;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxtED)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTxtED();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTxtED)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// OK button shown under the text edit box; clicking it commits the edit.
class CTextOkButton : public CButton
{
public:
	std::function<void()> onClick;
protected:
	afx_msg void OnClicked();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXTED_H__02C46B2B_DCA3_41C7_B497_B5337370D085__INCLUDED_)
