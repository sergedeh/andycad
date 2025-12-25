#if !defined(AFX_LINEAGAIN_H__32995A73_890C_41C8_A9BD_58858836257E__INCLUDED_)
#define AFX_LINEAGAIN_H__32995A73_890C_41C8_A9BD_58858836257E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineAgain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineAgain dialog

class CLineAgain : public CDialogBar
{
// Construction
public:
	CComboBoxEx m_comboex;
	CLineAgain();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineAgain)
	enum { IDD = IDD_DIALOGLI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineAgain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineAgain)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEAGAIN_H__32995A73_890C_41C8_A9BD_58858836257E__INCLUDED_)
