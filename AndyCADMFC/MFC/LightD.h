#if !defined(AFX_LIGHTD_H__5073EBC2_FFD2_4B2D_838E_059BD86980C2__INCLUDED_)
#define AFX_LIGHTD_H__5073EBC2_FFD2_4B2D_838E_059BD86980C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightD.h : header file
//
#include "subject.h"
/////////////////////////////////////////////////////////////////////////////
// CLightD dialog

class CLightD : public CDialog,public CSubject
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void updatepara();
	CLightD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightD)
	enum { IDD = IDD_DIALOGLIGHT };
	CStatic	m_dl;
	CSliderCtrl	m_drslider;
	CSliderCtrl	m_dgslider;
	CSliderCtrl	m_dbslider;
	CSliderCtrl	m_srslider;
	CSliderCtrl	m_sgslider;
	CSliderCtrl	m_arslider;
	CSliderCtrl	m_agslider;
	CSliderCtrl	m_abslider;
	CStatic	m_sl;
	CStatic	m_al;
	float	m_y;
	float	m_x;
	float	m_z;
	int		m_ab;
	int		m_ag;
	int		m_ar;
	int		m_sg;
	int		m_sr;
	CString	m_sab;
	CString	m_sag;
	CString	m_sar;
	CString	m_ssb;
	CString	m_ssg;
	CString	m_ssr;
	int		m_db;
	int		m_dg;
	int		m_dr;
	CString	m_sdr;
	CString	m_sdg;
	CString	m_sdb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(CLightD)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeEditLx();
	afx_msg void OnChangeEditLy();
	afx_msg void OnChangeEditLz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTD_H__5073EBC2_FFD2_4B2D_838E_059BD86980C2__INCLUDED_)
