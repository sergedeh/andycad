#if !defined(AFX_GRIDPAG_H__2C4E41B8_2A38_4A36_B4A9_52F5B60D6EF0__INCLUDED_)
#define AFX_GRIDPAG_H__2C4E41B8_2A38_4A36_B4A9_52F5B60D6EF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridPag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridPag dialog

class CGridPag : public CPropertyPage
{
	DECLARE_DYNCREATE(CGridPag)

// Construction
public:
	CGridPag();
	~CGridPag();

// Dialog Data
	//{{AFX_DATA(CGridPag)
	enum { IDD = IDD_GRID };
	CButton	m_sgrid;
	int		m_gridvert;
	int		m_gridho;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGridPag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGridPag)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDPAG_H__2C4E41B8_2A38_4A36_B4A9_52F5B60D6EF0__INCLUDED_)
