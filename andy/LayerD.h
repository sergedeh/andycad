#if !defined(AFX_LAYERD_H__584A63E0_B859_11D8_A4A5_DD382ED6C71A__INCLUDED_)
#define AFX_LAYERD_H__584A63E0_B859_11D8_A4A5_DD382ED6C71A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayerD dialog

class CLayerD : public CDialogBar
{
// Construction
public:
	CLayerD();   // standard constructor
	CListCtrl m_liblist;
	CHeaderCtrl hlist;
	CToolBarCtrl hto;
	CComboBoxEx hccb;
	CRect wnd;


// Dialog Data
	//{{AFX_DATA(CLayerD)
	enum { IDD = IDD_LAYDIA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList libimtool,libimlist;

	// Generated message map functions
	//{{AFX_MSG(CLayerD)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERD_H__584A63E0_B859_11D8_A4A5_DD382ED6C71A__INCLUDED_)
