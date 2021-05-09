#if !defined(AFX_ARRAYANGLE_H__8B3CDFDE_2B95_4BC2_A715_17AD669FDF3C__INCLUDED_)
#define AFX_ARRAYANGLE_H__8B3CDFDE_2B95_4BC2_A715_17AD669FDF3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArrayAngle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArrayAngle dialog

class CArrayAngle : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CArrayAngle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArrayAngle)
	enum { IDD = IDD_ARRAYCOPY };
	long	m_anglrot;
	int		m_nbcopy;
	float	m_dlevel;
	int		m_nblevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArrayAngle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CArrayAngle)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARRAYANGLE_H__8B3CDFDE_2B95_4BC2_A715_17AD669FDF3C__INCLUDED_)
