#if !defined(AFX_CADAUTOTRANSFORM_H__4E586428_8C76_4F2B_8D1C_B473DAB9315A__INCLUDED_)
#define AFX_CADAUTOTRANSFORM_H__4E586428_8C76_4F2B_8D1C_B473DAB9315A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoTransform.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoTransform command target

class CCadAutoTransform : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoTransform)

	CCadAutoTransform();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoTransform)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoTransform();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoTransform)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoTransform)
	afx_msg void Rotate(float u, short axis);
	afx_msg void Scale(float u, short axis);
	afx_msg void AngCopy(float u, short nb, short level, float dst);
	afx_msg void PolarCopy(float u, short nb, short level, float dst);
	afx_msg void ArrayCopy(short rows, float r_space, short column, float c_space, short level, float l_spacing);
	afx_msg void Flip(short dir);
	afx_msg void Mirror(LPDISPATCH figure);
	afx_msg void Mirror2(LPDISPATCH figure);
	afx_msg void Copy(LPDISPATCH figure);
	afx_msg void Copy2(LPDISPATCH figure);
	afx_msg void Scale2(float u);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOTRANSFORM_H__4E586428_8C76_4F2B_8D1C_B473DAB9315A__INCLUDED_)
