#if !defined(AFX_ZOOMD_H__BD9A2133_C621_4705_AC0B_567A78F88F67__INCLUDED_)
#define AFX_ZOOMD_H__BD9A2133_C621_4705_AC0B_567A78F88F67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomD dialog

class CZoomD : public CToolBar
{
// Construction
public:
	CZoomD();   // standard constructor
	virtual ~CZoomD();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomD)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Onzin();
	CButton zin,zout;
	CStatic perct;

	// Generated message map functions
	//{{AFX_MSG(CZoomD)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMD_H__BD9A2133_C621_4705_AC0B_567A78F88F67__INCLUDED_)
