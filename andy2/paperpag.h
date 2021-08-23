#if !defined(AFX_PAPERPAG_H__1060D346_3542_4478_89BF_AA337C53D9F4__INCLUDED_)
#define AFX_PAPERPAG_H__1060D346_3542_4478_89BF_AA337C53D9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaperPag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaperPag dialog

class CPaperPag : public CPropertyPage
{
	DECLARE_DYNCREATE(CPaperPag)

// Construction
public:
	CPaperPag();
	~CPaperPag();

// Dialog Data
	//{{AFX_DATA(CPaperPag)
	enum { IDD = IDD_DIALOGPAPERSET };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPaperPag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPaperPag)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPERPAG_H__1060D346_3542_4478_89BF_AA337C53D9F4__INCLUDED_)
