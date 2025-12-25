#if !defined(AFX_CADAUTOUTILS_H__8DA77CB0_A8A8_4B90_80A4_7C8028D8E3B9__INCLUDED_)
#define AFX_CADAUTOUTILS_H__8DA77CB0_A8A8_4B90_80A4_7C8028D8E3B9__INCLUDED_

#include "CadAutoVector.h"	// Added by ClassView
#include "CadAutoCollection.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoUtils.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoUtils command target

class CCadAutoUtils : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoUtils)

	CCadAutoUtils();           // protected constructor used by dynamic creation
	friend class CCadDoc;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoUtils)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoUtils();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoUtils)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoUtils)
	afx_msg LPDISPATCH GetVector();
	afx_msg void SetVector(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetCollection();
	afx_msg void SetCollection(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CCadAutoCollection* auto_coll;
	CCadAutoVector* auto_vector;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOUTILS_H__8DA77CB0_A8A8_4B90_80A4_7C8028D8E3B9__INCLUDED_)
