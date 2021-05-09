#if !defined(AFX_SNAPGRIDDLG2_H__9C90CE98_B4BB_4C11_8CE4_D6486294BCFA__INCLUDED_)
#define AFX_SNAPGRIDDLG2_H__9C90CE98_B4BB_4C11_8CE4_D6486294BCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnapGridDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg2 dialog

class CSnapGridDlg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSnapGridDlg2)

// Construction
public:
	CSnapGridDlg2();
	~CSnapGridDlg2();

// Dialog Data
	//{{AFX_DATA(CSnapGridDlg2)
	enum { IDD = IDD_ZOOM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSnapGridDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSnapGridDlg2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAPGRIDDLG2_H__9C90CE98_B4BB_4C11_8CE4_D6486294BCFA__INCLUDED_)
