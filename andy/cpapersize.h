//{{AFX_INCLUDES()
#include "mdccombo.h"
#include "OwnCombo.h"
//}}AFX_INCLUDES
#if !defined(AFX_CPAPERSIZE_H__42E9AF1B_A60B_4236_9F9A_45F7F455393F__INCLUDED_)
#define AFX_CPAPERSIZE_H__42E9AF1B_A60B_4236_9F9A_45F7F455393F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CPaperSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCPaperSize dialog

class CCPaperSize : public CDialog
{
// Construction
public:
	CString getorient();
	void setdata(int f, float fw,float fp,int lprec,int aprec);
	void setdata2(int l_type, int l_stype,int prec);
	void setdata3(int a_type, int aprec);
	void setdata4(bool a_fit);
	int getUnit();
	CCPaperSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCPaperSize)
	enum { IDD = IDD_DIALOGPAPERSET };
	CButton	m_cmet;
	CButton	m_cimp;
	CString	m_wunit;
	float	m_ewu;
	float	m_epu;
	//}}AFX_DATA

	int length_type,length_subtype,length_prec,angle_type,angle_prec;
	bool fit;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCPaperSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCPaperSize)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadiometric();
	afx_msg void OnRadioimperial();
	//}}AFX_MSG
	afx_msg void OnLTDrop();
	afx_msg void OnLTDrop2();
	afx_msg void OnLTDropAngle();
	afx_msg void OnLTDropAngle6();
	afx_msg void OnLTDrop3();
	afx_msg void OnFitToPage();
	DECLARE_MESSAGE_MAP()
private:
	int ap,lp,fu;
	int ltype,lstype,lprec,atype,aprec;
	enum{metric,inch} unit;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPAPERSIZE_H__42E9AF1B_A60B_4236_9F9A_45F7F455393F__INCLUDED_)
