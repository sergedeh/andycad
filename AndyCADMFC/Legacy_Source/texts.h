#if !defined(AFX_TEXTS_H__DB9FE93E_BE0B_4421_972D_00BC34AF63B1__INCLUDED_)
#define AFX_TEXTS_H__DB9FE93E_BE0B_4421_972D_00BC34AF63B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Texts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTexts window

class CTexts : public CRichEditCtrl
{
// Construction
public:
	CTexts();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTexts)
	//}}AFX_VIRTUAL

// Implementation
public:
	int DrawText();
	virtual ~CTexts();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTexts)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTS_H__DB9FE93E_BE0B_4421_972D_00BC34AF63B1__INCLUDED_)
