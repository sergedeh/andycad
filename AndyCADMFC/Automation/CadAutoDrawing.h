#if !defined(AFX_CADAUTODRAWING_H__93A4D608_4E1C_44A5_94D2_040CF2D17643__INCLUDED_)
#define AFX_CADAUTODRAWING_H__93A4D608_4E1C_44A5_94D2_040CF2D17643__INCLUDED_

#include "CadAutoDrawingCollection.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CadAutoDrawing.h : header file
//


class CCadAutoCanvas;
/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawing command target

class CCadAutoDrawing : public CCmdTarget
{
	DECLARE_DYNCREATE(CCadAutoDrawing)
	CCadAutoDrawing();           // protected constructor used by dynamic creation

	friend CCadAutoCanvas;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadAutoDrawing)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCadAutoDrawing();

	// Generated message map functions
	//{{AFX_MSG(CCadAutoDrawing)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCadAutoDrawing)
	afx_msg LPDISPATCH GetDrawingCollection();
	afx_msg void SetDrawingCollection(LPDISPATCH newValue);
	afx_msg void AddLine(float left, float top, float right, float bottom);
	afx_msg void AddRectangle(float left, float top, float right, float bottom);
	afx_msg void AddLinev(LPDISPATCH p1, LPDISPATCH p2);
	afx_msg void AddRectanglev(LPDISPATCH p1, LPDISPATCH p2);
	afx_msg void AddCircle(LPDISPATCH center, float radius);
	afx_msg void AddCirclev(LPDISPATCH center, LPDISPATCH rvec);
	afx_msg void AddSpline(LPDISPATCH ponts);
	afx_msg void AddPolyLine(LPDISPATCH points);
	afx_msg void AddCircle3(LPDISPATCH p1, LPDISPATCH p2, LPDISPATCH p3);
	afx_msg void AddArc(LPDISPATCH center, float radius);
	afx_msg void AddArc2(LPDISPATCH p1, LPDISPATCH p2);
	afx_msg void AddArc3(LPDISPATCH p1, LPDISPATCH p2, LPDISPATCH p3);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CCadAutoDrawingCollection m_coll;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADAUTODRAWING_H__93A4D608_4E1C_44A5_94D2_040CF2D17643__INCLUDED_)
