#if !defined(AFX_TEXT_H__8783310F_65AB_435E_A656_7C423B1100E2__INCLUDED_)
#define AFX_TEXT_H__8783310F_65AB_435E_A656_7C423B1100E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Text.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Text view

class Text : public CEditView
{
protected:
	Text();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Text)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Text)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Text();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(Text)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextEditor window

class CTextEditor : public CRichEditCtrl
{
// Construction
public:
	CTextEditor();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextEditor)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextEditor();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextEditor)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXT_H__8783310F_65AB_435E_A656_7C423B1100E2__INCLUDED_)
