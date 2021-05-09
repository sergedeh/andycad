#if !defined(AFX_CADAUTODRAWINGCOLLECTION_H__739A239F_73CB_4B27_8116_3DE380231095__INCLUDED_)
#define AFX_CADAUTODRAWINGCOLLECTION_H__739A239F_73CB_4B27_8116_3DE380231095__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoDrawingCollection.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawingCollection command target

class CCadAutoDrawingCollection : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoDrawingCollection)

	CCadAutoDrawingCollection();           // protected constructor used by dynamic creation
	friend class CCAdAutoShape;
	friend class CCadAutoDrawing;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoDrawingCollection)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoDrawingCollection();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoDrawingCollection)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoDrawingCollection)
	afx_msg short GetCount();
	afx_msg void SetCount(short nNewValue);
	afx_msg LPDISPATCH Item(short i);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTODRAWINGCOLLECTION_H__739A239F_73CB_4B27_8116_3DE380231095__INCLUDED_)
