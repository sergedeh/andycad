#if !defined(AFX_CADAUTOEDIT_H__030C24BB_5C83_4F53_93DA_F04A6C5FE4AB__INCLUDED_)
#define AFX_CADAUTOEDIT_H__030C24BB_5C83_4F53_93DA_F04A6C5FE4AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoEdit.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoEdit command target

class CCadAutoEdit : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoEdit)

	CCadAutoEdit();           // protected constructor used by dynamic creation
	friend class CCadAutoCanvas;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoEdit)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoEdit();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoEdit)
	afx_msg void Select(LPDISPATCH object);
	afx_msg void Group(LPDISPATCH object1, LPDISPATCH object2);
	afx_msg void SelectNode(LPDISPATCH object, short i);
	afx_msg void Close(LPDISPATCH object);
	afx_msg void Move(LPDISPATCH object, LPDISPATCH v);
	afx_msg void MoveNode(LPDISPATCH object, short node, LPDISPATCH v);
	afx_msg void Chamfer(LPDISPATCH f1, float u1, LPDISPATCH f2, float u2, float length);
	afx_msg void Fillet(LPDISPATCH f1, float u1, LPDISPATCH f2, float u2, float l);
	afx_msg BOOL Trim(LPDISPATCH obj_to_trim, LPDISPATCH obj_trim, LPDISPATCH point);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOEDIT_H__030C24BB_5C83_4F53_93DA_F04A6C5FE4AB__INCLUDED_)
