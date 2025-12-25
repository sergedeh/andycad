/// IpFrame.cpp : implementation of the CInPlaceFrame class
//

#include "stdafx.h"
#include "Cad.h"

#include "InPlaceFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleDocIPFrameWnd)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleDocIPFrameWnd)
	//{{AFX_MSG_MAP(CInPlaceFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame construction/destruction

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleDocIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar implements in-place resizing.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}

	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Remove this if you use pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Set owner to this window, so messages are delivered to correct app
	m_wndToolBar.SetOwner(this);

	// Create toolbar on client's frame window
/*	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}*/

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable


	CRect rcClientNow,rcClientFirst;
	GetClientRect(rcClientFirst);

	{
	 
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY|CCS_ADJUSTABLE| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_MAINFRAME) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetButtonText (0, _T ("New"));
	m_wndToolBar.SetButtonText (1, _T ("Open"));
	m_wndToolBar.SetButtonText (2, _T ("Save"));

	m_wndToolBar.SetButtonText (4, _T ("Cut"));
	m_wndToolBar.SetButtonText (5, _T ("Copy"));
	m_wndToolBar.SetButtonText (6, _T ("Paste"));


	m_wndToolBar.SetButtonText (8, _T ("Undo"));
	m_wndToolBar.SetButtonText (9, _T ("Redo"));
	m_wndToolBar.SetButtonText (10, _T ("Delete"));

	m_wndToolBar.SetButtonText (12, _T ("Preview"));
	m_wndToolBar.SetButtonText (13, _T ("Print"));


	m_wndToolBar.SetSizes (CSize (48, 42), CSize (40, 19));

	m_wndToolBar.SetBarStyle( m_wndToolBar.GetBarStyle()| CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC);


	m_wndToolBar1.SetOwner(this);
	if (!m_wndToolBar1.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_VISIBLE|WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY |CCS_ADJUSTABLE   | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TOOLBAR1) ||
		!m_wndToolBar1.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	}
	m_wndToolBar1.SetBarStyle( m_wndToolBar1.GetBarStyle()| CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC);

	m_wndStatusBar.SetOwner(this);
	if (!m_wndStatusBar.Create(pWndFrame) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	

	m_wndZoomBar.SetOwner(this);
	if (!m_wndZoomBar.CreateEx(pWndFrame,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndZoomBar.LoadToolBar(IDR_ZOOMBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	m_wndimensionBar.SetOwner(this);
	if (!m_wndimensionBar.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_LEFT|
		CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_DIMENSION)||
   	!m_wndimensionBar.LoadToolBar(IDR_DIMENSION))
	{
		TRACE0("Failed to create dialogBar\n");
		return -1;      // fail to create
	}

	m_wndsnapingBar.SetOwner(this);
	if (!m_wndsnapingBar.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_LEFT| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_LINESTYLE) ||
		!m_wndsnapingBar.LoadToolBar(IDR_SNAPPING))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	

	(m_wndToolBar1.GetToolBarCtrl()).SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);	

	UINT idcercle=m_wndToolBar1.CommandToIndex(158);
	UINT st=m_wndToolBar1.GetButtonStyle(idcercle);
	st|=TBSTYLE_DROPDOWN;
	m_wndToolBar1.SetButtonStyle(idcercle,st);

	idcercle=m_wndToolBar1.CommandToIndex(ID_TBSELECT);
	st=m_wndToolBar1.GetButtonStyle(idcercle);
	st|=TBSTYLE_DROPDOWN;
	m_wndToolBar1.SetButtonStyle(idcercle,st);

	idcercle=m_wndToolBar1.CommandToIndex(ID_TBROTATE);
	st=m_wndToolBar1.GetButtonStyle(idcercle);
	st|=TBSTYLE_DROPDOWN;
	m_wndToolBar1.SetButtonStyle(idcercle,st);

	idcercle=m_wndToolBar1.CommandToIndex(ID_Text);
	st=m_wndToolBar1.GetButtonStyle(idcercle);
	st|=TBSTYLE_DROPDOWN;
	m_wndToolBar1.SetButtonStyle(idcercle,st);

	
	m_cercToolBar.SetOwner(this);
	if (!m_cercToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_CER) ||
		!m_cercToolBar.LoadToolBar(IDR_CER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	m_tbselectToolBar.SetOwner(this);
	if (!m_tbselectToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_EDIT) ||
		!m_tbselectToolBar.LoadToolBar(IDR_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_tbrotateToolBar.SetOwner(this);
	if (!m_tbrotateToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TRAN) ||
		!m_tbrotateToolBar.LoadToolBar(IDR_TRAN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	text.SetOwner(this);
	if (!text.CreateEx(pWndFrame, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TEXT) ||
		!m_cercToolBar.LoadToolBar(IDR_TEXT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	colorToolBar.SetOwner(this);
	if (!colorToolBar.Create(pWndFrame,IDD_DIALOGBAR3, CBRS_BOTTOM|
		CBRS_GRIPPER | CBRS_FLYBY ,IDD_DIALOGBAR3))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndsnapingBar.EnableDocking(CBRS_ALIGN_ANY);
	m_tbrotateToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_tbselectToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_cercToolBar.EnableDocking(CBRS_ALIGN_ANY);
	text.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	m_wndimensionBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndZoomBar.EnableDocking(CBRS_ALIGN_ANY);
	colorToolBar.EnableDocking(CBRS_ALIGN_BOTTOM|CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	



	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndimensionBar);
	pWndFrame->DockControlBar(&m_wndsnapingBar);
	pWndFrame->DockControlBar(&colorToolBar);
	pWndFrame->DockControlBar(&m_wndZoomBar);
	
	CRect v,v1;
	m_wndToolBar.GetWindowRect(&v);
	pWndFrame->DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP,CRect(0,0,v.Width(),v.Height()));
	m_wndToolBar1.GetWindowRect(&v1);
	pWndFrame->DockControlBar(&m_wndToolBar1);
	pWndFrame->DockControlBar(&m_cercToolBar);
	pWndFrame->DockControlBar(&m_tbselectToolBar);
	pWndFrame->DockControlBar(&m_tbrotateToolBar);
	pWndFrame->DockControlBar(&text);
	
	text.ShowWindow(SW_HIDE);
	m_cercToolBar.ShowWindow(SW_HIDE);
	m_tbselectToolBar.ShowWindow(SW_HIDE);
	m_tbrotateToolBar.ShowWindow(SW_HIDE);

	

	m_wndMyDialogBar.SetOwner(this);
	if (!m_wndMyDialogBar.Create(pWndFrame, CG_IDD_MYDIALOGBAR,
		CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER|CBRS_HIDE_INPLACE,
		CG_ID_VIEW_MYDIALOGBAR))
	{
		TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
		return -1;		// fail to create
	}

	m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndMyDialogBar);
	//	LoadBarState(_T("AnddyCAD"));


	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDocIPFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame diagnostics

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleDocIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleDocIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame commands
