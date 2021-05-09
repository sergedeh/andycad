#if !defined(AFX_ZOOMBAR_H__CF5A7094_C818_11D7_BACA_0004CADD4B7C__INCLUDED_)
#define AFX_ZOOMBAR_H__CF5A7094_C818_11D7_BACA_0004CADD4B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*class CZoombar : public CToolBar  
{
public:
};
*/
#endif // !defined(AFX_ZOOMBAR_H__CF5A7094_C818_11D7_BACA_0004CADD4B7C__INCLUDED_)
/////////////////////////////////////////////////////////////////////////////
// CZoomBar window

class CZoomBar : public CToolBar
{
// Construction
public:
	CZoomBar();
	BOOL ShowComboBox();
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZoomBar();

	// Generated message map functions
protected:
		CComboBox m_wndComboZoombar;
	//{{AFX_MSG(CZoomBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
