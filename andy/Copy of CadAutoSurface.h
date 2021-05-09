#if !defined(AFX_CADAUTOSURFACE_H__3D78A313_3CF6_40C2_8D01_4463D78232F0__INCLUDED_)
#define AFX_CADAUTOSURFACE_H__3D78A313_3CF6_40C2_8D01_4463D78232F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoSurface.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoSurface command target

class CCadAutoSurface : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoSurface)

	CCadAutoSurface();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoSurface)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoSurface();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoSurface)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoSurface)
	afx_msg void Loft(float thick, short cap);
	afx_msg void Extrude(float thick, short cap, float extr);
	afx_msg void Extrude2(float thick, short cap);
	afx_msg void gCylinder(float thick, short cap);
	afx_msg void Revolve(float thick, short cap);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOSURFACE_H__3D78A313_3CF6_40C2_8D01_4463D78232F0__INCLUDED_)
