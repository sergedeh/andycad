#if !defined(AFX_CADAUTOCANVAS_H__27352550_B143_45A2_9AD8_7F889C21192A__INCLUDED_)
#define AFX_CADAUTOCANVAS_H__27352550_B143_45A2_9AD8_7F889C21192A__INCLUDED_

#include "CadAutoDrawing.h"	// Added by ClassView
#include "CadAutoEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoCanvas.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCadAutoCanvas command target

class CCadAutoCanvas : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoCanvas)

	CCadAutoCanvas();           // protected constructor used by dynamic creation
	friend class CCadDoc;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoCanvas)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoCanvas();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoCanvas)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoCanvas)
	afx_msg LPDISPATCH GetDrawing();
	afx_msg void SetDrawing(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetEdit();
	afx_msg void SetEdit(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetTransform();
	afx_msg void SetTransform(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetSurface();
	afx_msg void SetSurface(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetShape();
	afx_msg void SetShape(LPDISPATCH newValue);
	afx_msg BOOL Save(LPCTSTR pszPath);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CCadAutoDrawing auto_draw;
	CCadAutoEdit auto_edit;
//	CCadAutoTransform auto_trans;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTOCANVAS_H__27352550_B143_45A2_9AD8_7F889C21192A__INCLUDED_)
