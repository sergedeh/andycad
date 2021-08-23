#if !defined(AFX_FILENAMEEDIT_H__F9B433F7_6FFA_11D2_B203_00C04FBEDB8F__INCLUDED_)
#define AFX_FILENAMEEDIT_H__F9B433F7_6FFA_11D2_B203_00C04FBEDB8F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FilenameEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit window

class CFilenameEdit : public CEdit
{
// Construction
public:
	CFilenameEdit();

// Attributes
public:

// Operations
public:
	BOOL IsValidFileChar( UINT nChar );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilenameEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilenameEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFilenameEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMEEDIT_H__F9B433F7_6FFA_11D2_B203_00C04FBEDB8F__INCLUDED_)
