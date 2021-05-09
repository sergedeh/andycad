// InPlaceFrame.h: interface for the CInPlaceFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPLACEFRAME_H__43B45D1D_9F34_47E6_9B15_3F6FAF6E3F95__INCLUDED_)
#define AFX_INPLACEFRAME_H__43B45D1D_9F34_47E6_9B15_3F6FAF6E3F95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ZoomD.h"	// Added by ClassView
#include "TextD.h"	// Added by ClassView
#include "popbar.h"
#include "Zoombar.h"
#include "splash.h"
#include "infobar.h"
#include "reccolor.h"
#include "colord.h"
#include "ToolBarW.h"
#include "Proppage.h"
#include "NstatusBar.h"

class CInPlaceFrame : public COleDocIPFrameWnd  
{
		DECLARE_DYNCREATE(CInPlaceFrame)
	public:
		CInPlaceFrame();

	// Attributes
	public:

	public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CInPlaceFrame)
		public:
		virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		//}}AFX_VIRTUAL

	// Implementation
	public:
		virtual ~CInPlaceFrame();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:
		CStatusBar  m_wndStatusBar, m_wndTxtBar;
		CToolBar    m_wndToolBar,m_wndToolBar1,m_wndToolBar2,m_wndToolBar3;
		CToolBar	m_cercToolBar,m_tbrotateToolBar,m_tbselectToolBar;
		CZoomBar    m_wndZoomBar;
	//	CLineBar    m_wndlinestylBar;
		CToolBar    m_wndimensionBar,m_wndsnapingBar;
		CDialogBar m_wndMousePosition;
		CInfoBar m_wndMyDialogBar;
		CColorD colorToolBar;
		CTextD text;
		CZoomD zoomwnd;
		CDialogBar m_wndDlgBar;		

		COleDropTarget	m_dropTarget;
		COleResizeBar   m_wndResizeBar;

	// Generated message map functions
	protected:
		//{{AFX_MSG(CInPlaceFrame)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			// NOTE - the ClassWizard will add and remove member functions here.
			//    DO NOT EDIT what you see in these blocks of generated code!
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_INPLACEFRAME_H__43B45D1D_9F34_47E6_9B15_3F6FAF6E3F95__INCLUDED_)
