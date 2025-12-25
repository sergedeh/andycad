#if !defined(AFX_PGRID_H__27AEB73C_4BD6_4132_884A_7D3C53999D38__INCLUDED_)
#define AFX_PGRID_H__27AEB73C_4BD6_4132_884A_7D3C53999D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGrid dialog

class CPGrid : public CDialog
{
// Construction
public:
	CPGrid(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPGrid)
	enum { IDD = IDD_GRID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGrid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPGrid)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGRID_H__27AEB73C_4BD6_4132_884A_7D3C53999D38__INCLUDED_)
