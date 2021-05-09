#if !defined(AFX_TEXTDI_H__67719261_B248_4581_AA20_F7401BEE6466__INCLUDED_)
#define AFX_TEXTDI_H__67719261_B248_4581_AA20_F7401BEE6466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDi dialog

class CTextDi : public CDialog
{
// Construction
public:
	void settext(CString s);
	CTextDi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextDi)
	enum { IDD = IDD_DIALOG_TEXT };
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool pnew;
	// Generated message map functions
	//{{AFX_MSG(CTextDi)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDI_H__67719261_B248_4581_AA20_F7401BEE6466__INCLUDED_)
