#if !defined(AFX_CADAUTOCAMERA_H__B226C895_E0FF_4838_8423_96B9E43A5569__INCLUDED_)
#define AFX_CADAUTOCAMERA_H__B226C895_E0FF_4838_8423_96B9E43A5569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoCamera.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoCamera command target

class CCadAutoCamera : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoCamera)

	CCadAutoCamera();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoCamera)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoCamera();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoCamera)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoCamera)
	afx_msg float GetFPlane();
	afx_msg void SetFPlane(float newValue);
	afx_msg float GetNPlane();
	afx_msg void SetNPlane(float newValue);
	afx_msg float GetFOV();
	afx_msg void SetFOV(float newValue);
	afx_msg short GetView();
	afx_msg void SetView(short nNewValue);
	afx_msg short GetPerspective();
	afx_msg void SetPerspective(short nNewValue);
	afx_msg void Zoom(float u);
	afx_msg void Rotate(float angle, short axis);
	afx_msg void LooktAt(LPDISPATCH cam_pos, LPDISPATCH target_pos);
	afx_msg void Init();
	afx_msg void Translate(LPDISPATCH v);
	afx_msg void Swivel(float angle, short axis);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOCAMERA_H__B226C895_E0FF_4838_8423_96B9E43A5569__INCLUDED_)
