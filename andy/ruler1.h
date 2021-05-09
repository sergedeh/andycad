#if !defined(AFX_RULER1_H__BACF47B5_AA22_41F2_8CFD_F78965CA9A57__INCLUDED_)
#define AFX_RULER1_H__BACF47B5_AA22_41F2_8CFD_F78965CA9A57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ruler1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuler window

class CRuler : public CControlBar
{
// Construction
public:
	CRuler();

// Attributes
public:

// Operations
public:
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuler)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CRect rec;
	virtual CRect Create(bool orient,CWnd *pParent);
	virtual ~CRuler();

	// Generated message map functions
protected:
	bool horiz;
	int dir;
	//{{AFX_MSG(CRuler)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	float ratio[2];
	CRect initrec;
	CWnd *pParent;
	CRect rlrec;
	int bigstep;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULER1_H__BACF47B5_AA22_41F2_8CFD_F78965CA9A57__INCLUDED_)
