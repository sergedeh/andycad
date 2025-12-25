#if !defined(AFX_CADAUTOVECTOR_H__90B7D139_4A84_44AE_A1E2_02385883050A__INCLUDED_)
#define AFX_CADAUTOVECTOR_H__90B7D139_4A84_44AE_A1E2_02385883050A__INCLUDED_

#include "CVector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoVector.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoVector command target

class CCadAutoVector : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoVector)

	CCadAutoVector();           // protected constructor used by dynamic creation
	friend class CCadAutoUtils;
// Attributes
public:

// Operations
public:
	CVector getV();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoVector)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoVector();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoVector)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoVector)
	afx_msg float GetX();
	afx_msg void SetX(float newValue);
	afx_msg float GetY();
	afx_msg void SetY(float newValue);
	afx_msg float GetZ();
	afx_msg void SetZ(float newValue);
	afx_msg VARIANT GetV();
	afx_msg void SetV(const VARIANT FAR& newValue);
	afx_msg void Init(float x, float y, float z=0);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CVector v;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOVECTOR_H__90B7D139_4A84_44AE_A1E2_02385883050A__INCLUDED_)
