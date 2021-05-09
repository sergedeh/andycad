// mytestView.h : interface of the CMytestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTESTVIEW_H__8B89BFCA_8351_4324_9857_97DC253AAFAF__INCLUDED_)
#define AFX_MYTESTVIEW_H__8B89BFCA_8351_4324_9857_97DC253AAFAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMytestView : public CView
{
protected: // create from serialization only
	CMytestView();
	DECLARE_DYNCREATE(CMytestView)

// Attributes
public:
	CMytestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMytestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMytestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMytestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mytestView.cpp
inline CMytestDoc* CMytestView::GetDocument()
   { return (CMytestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTESTVIEW_H__8B89BFCA_8351_4324_9857_97DC253AAFAF__INCLUDED_)
