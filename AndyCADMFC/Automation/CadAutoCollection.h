#if !defined(AFX_CADAUTOCOLLECTION_H__0D8573F6_2543_40D3_A453_E9874221860F__INCLUDED_)
#define AFX_CADAUTOCOLLECTION_H__0D8573F6_2543_40D3_A453_E9874221860F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoCollection.h : header file
//
#include<vector>
using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CCadAutoCollection command target

class CCadAutoCollection : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoCollection)

	CCadAutoCollection();           // protected constructor used by dynamic creation
	friend class CCadAutoUtils;
	friend class CCadAutoDrawing;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoCollection)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoCollection();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoCollection)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoCollection)
	afx_msg short GetCount();
	afx_msg void SetCount(short nNewValue);
	afx_msg LPDISPATCH* GetBegin();
	afx_msg void SetBegin(LPDISPATCH newValue);
	afx_msg LPDISPATCH* GetEnd();
	afx_msg void SetEnd(LPDISPATCH newValue);
	afx_msg void Add(LPDISPATCH item);
	afx_msg void Clear();
	afx_msg LPDISPATCH Item(short index);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	vector<LPDISPATCH> v;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOCOLLECTION_H__0D8573F6_2543_40D3_A453_E9874221860F__INCLUDED_)
