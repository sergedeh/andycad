#if !defined(AFX_CAMERADLG_H__817CC97A_5696_42AC_8AF5_A4D56A8CB956__INCLUDED_)
#define AFX_CAMERADLG_H__817CC97A_5696_42AC_8AF5_A4D56A8CB956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraDlg.h : header file
//
#include "subject.h"
#include "observer.h"
/////////////////////////////////////////////////////////////////////////////
// CCameraDlg dialog

class CCameraDlg : public CDialog,public CSubject,public CObserver
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SendNotify(CString s,void *param[]);
	void updateviewpara();
	void updatepara();
	bool pv;
	CCameraDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCameraDlg)
	enum { IDD = IDD_DIALOGCAMERA };
	CSliderCtrl	m_cfov;
	float	m_xp;
	float	m_xt;
	float	m_yp;
	float	m_yt;
	float	m_zp;
	float	m_zt;
	float	m_fp;
	float	m_np;
	CString	m_sfov;
	int		m_fov;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CCameraDlg)
	afx_msg void OnChangeEditxp();
	afx_msg void OnChangeEdityp();
	afx_msg void OnChangeEditzp();
	afx_msg void OnChangeEditxt();
	afx_msg void OnChangeEdityt();
	afx_msg void OnChangeEditzt();
	afx_msg void OnChangeEditfplane();
	afx_msg void OnChangeEditnplane();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void sendNotify();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERADLG_H__817CC97A_5696_42AC_8AF5_A4D56A8CB956__INCLUDED_)
