// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "cad.h"
//#include "MLinestyle.h"

#include "MainFrm.h"
//#include "Splash.h"
//#include "AddinSettingsDialog1.h"
#include "NewMacroDlg.h"
#include "FileMacroDlg.h"
#include "EditMacroDlg.h"
#include "RunMacroDlg.h"
#include "imagex.h"
//#include "macromanager.h"
#include "caddoc.h"

//#include "ToolBarW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_ITEMS 15
#define PF_MIN_MSG					0
#define PF_MAX_MSG					0xFFFF

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MOUSEPOSITION, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MOUSEPOSITION, OnUpdateControlBarMenu)
	ON_WM_MENUSELECT()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND(ID_DIMVIEW, OnDimview)
	ON_UPDATE_COMMAND_UI(ID_DIMVIEW, OnUpdateDimview)
	ON_COMMAND(ID_INFOBAR_VIEW, OnInfobarView)
	ON_UPDATE_COMMAND_UI(ID_INFOBAR_VIEW, OnUpdateInfobarView)
	ON_COMMAND(ID_COLOR_VIEW, OnColorView)
	ON_UPDATE_COMMAND_UI(ID_COLOR_VIEW, OnUpdateColorView)
	ON_COMMAND(ID_TRANS_VIEW, OnTransView)
	ON_UPDATE_COMMAND_UI(ID_TRANS_VIEW, OnUpdateTransView)
	ON_COMMAND(ID_EDIT_VIEW, OnEditView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_VIEW, OnUpdateEditView)
	ON_COMMAND(ID_VIEW_TOOLBAR_COLORBAR, OnViewToolbarColorbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_COLORBAR, OnUpdateViewToolbarColorbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_DIMENSIONBAR, OnViewToolbarDimensionbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_DIMENSIONBAR, OnUpdateViewToolbarDimensionbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_INFORMATIONBAR, OnViewToolbarInformationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_INFORMATIONBAR, OnUpdateViewToolbarInformationbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_MODIFYINGBAR, OnViewToolbarModifyingbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_MODIFYINGBAR, OnUpdateViewToolbarModifyingbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_STANDARDBAR, OnViewToolbarStandardbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_STANDARDBAR, OnUpdateViewToolbarStandardbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_TRANSFORMATIONBAR, OnViewToolbarTransformationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_TRANSFORMATIONBAR, OnUpdateViewToolbarTransformationbar)
	ON_COMMAND(ID_VIEW_TOOLBAR_ZOOMBAR, OnViewToolbarZoombar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_ZOOMBAR, OnUpdateViewToolbarZoombar)
	ON_COMMAND(ID_VIEW_TOOLBAR_DRAWINGBAR, OnViewToolbarDrawingbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_DRAWINGBAR, OnUpdateViewToolbarDrawingbar)
	ON_COMMAND(ID_HELP_TIPOFTHEDAY, OnHelpTipoftheday)
	ON_COMMAND(ID_VIEW_TOOLBAR_SHOWTOOLBARS, OnViewToolbarShowtoolbars)
	ON_COMMAND(ID_VIEW_TOOLBAR_HIDETOOLBARS, OnViewToolbarHidetoolbars)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_HIDETOOLBARS, OnUpdateViewToolbarHidetoolbars)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_COMMAND(ID_HELP_REGISTRATION, OnHelpRegistration)
	ON_COMMAND(ID_VIEW_TOOLBAR_SHOWSNAP, OnViewToolbarShowsnap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_SHOWSNAP, OnUpdateViewToolbarShowsnap)
	ON_COMMAND(ID_VIEW_TOOLBAR_SHOWLAY, OnViewToolbarShowlay)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_SHOWLAY, OnUpdateViewToolbarShowlay)
	ON_COMMAND(ID_VIEW_TOOLBAR_SHOWLIBBAR, OnViewToolbarShowlibbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_SHOWLIBBAR, OnUpdateViewToolbarShowlibbar)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_LIBT1, OnBegindragLibt1)
	ON_COMMAND(ID_EDIT_LAYER, OnEditLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LAYER, OnUpdateEditLayer)
	ON_COMMAND(ID_LIBRARY, OnLibrary)
	ON_UPDATE_COMMAND_UI(ID_LIBRARY, OnUpdateLibrary)
	ON_COMMAND(ID_VIEW_TOOLBAR_TEXTBAR, OnViewToolbarTextbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_TEXTBAR, OnUpdateViewToolbarTextbar)
	ON_COMMAND(ID_TOOLS_TOOLBARS_PATTERNTEXTUREBAR, OnToolsToolbarsPatterntexturebar)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TOOLBARS_PATTERNTEXTUREBAR, OnUpdateToolsToolbarsPatterntexturebar)
	ON_COMMAND(ID_TOOLS_TOOLBARS_CREATESURFACEBAR, OnToolsToolbarsCreatesurfacebar)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TOOLBARS_CREATESURFACEBAR, OnUpdateToolsToolbarsCreatesurfacebar)
	ON_COMMAND(ID_TOOLS_TOOLBARS_VIEWBAR, OnToolsToolbarsViewbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TOOLBARS_VIEWBAR, OnUpdateToolsToolbarsViewbar)
	ON_COMMAND(ID_TOOLS_TOOLBARS_SMOOTHINGLIGHTBAR, OnToolsToolbarsSmoothinglightbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TOOLBARS_SMOOTHINGLIGHTBAR, OnUpdateToolsToolbarsSmoothinglightbar)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_NOTIFY(TBN_DROPDOWN,IDR_TOOLBAR1,OnSubMenu)
	ON_COMMAND(ID_VIEW_TOOLBAR_SHOWCMDBAR, OnViewToolbarShowcmdbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_SHOWCMDBAR, OnUpdateViewToolbarShowcmdbar)
	
//	ON_COMMAND_RANGE(PF_ADDIN_CMD_MIN_MSG_ID, PF_ADDIN_CMD_MAX_MSG_ID, OnAddinMenuItems)
//	ON_UPDATE_COMMAND_UI_RANGE(PF_ADDIN_CMD_MIN_MSG_ID, PF_ADDIN_CMD_MAX_MSG_ID, OnUpdateAddinMenuItems)

	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, PF_MIN_MSG, PF_MAX_MSG, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, PF_MIN_MSG, PF_MAX_MSG, OnToolTipText)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// CG: The following block was inserted by 'Status Bar' component.
	{
		m_nStatusPane1Width = -1;
		m_bMenuSelect = FALSE;
	}

//	 m_pSheet = NULL;
	 menudrw=false;
	 menustd=false;
	 menuedit=false;
	 menustat=false;
	 menucol=false;
	 menuzoom=false;
	 menuinfo=false;
	 menutrans=false;
	 menudim=false;
	 menulib=false;
	 menusnp=false;
	 menulay=false;
     menucerc=false;
	 menultb=false;
	 menupat=false;
     menutext=false;
	 menusurf=false;
     menucam=false;
     menulay=false;
     menulib=false;

	
    return;

	
}

CMainFrame::~CMainFrame()
{
//	delete m_pSheet;
	for(int i=0;i<m_pAddinToolbarArray.GetSize();i++ )
	{
		delete m_pAddinToolbarArray[i];
	}

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	CRect rcClientNow,rcClientFirst;
	GetClientRect(rcClientFirst);
	it_ptbegin=ptbegin.begin();
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	{
	 

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD|WS_CAPTION | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY|CCS_ADJUSTABLE| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_MAINFRAME) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	// Create the macro combo box
	if (!m_wndMacro.Create(CBS_DROPDOWNLIST | WS_CHILD | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_SORT,CRect(0,0,200,120),this,AFX_IDW_TOOLBAR + 1))
	{
		TRACE0("Failed to create combobox\n");
		return -1;      // fail to create
	}

/*	m_wndToolBar.SetButtonText (0, _T ("New"));
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
*/
	m_wndToolBar.SetBarStyle( m_wndToolBar.GetBarStyle()| CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC);

	if (!m_wndToolBar1.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_VISIBLE|WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY |CCS_ADJUSTABLE   | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TOOLBAR1) ||
		!m_wndToolBar1.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	}
	

	m_wndToolBar1.SetBarStyle( m_wndToolBar1.GetBarStyle()| CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC);

    if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndZoomBar.CreateEx(this,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndZoomBar.LoadToolBar(IDR_ZOOMBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (!m_wndtransfill.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP|CCS_ADJUSTABLE|  CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TRANSFILL) ||
		!m_wndtransfill.LoadToolBar(IDR_TRANSFILL))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	
		 
	/*if (!m_wndrender.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY|CCS_ADJUSTABLE| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_RENDER) ||
		!m_wndrender.LoadToolBar(IDR_RENDER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_prop.Create(this,IDD_DBPROPERTY,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) 
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}*/


	if (!m_wndimensionBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_TOP|
		CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_DIMENSION)||
   	!m_wndimensionBar.LoadToolBar(IDR_DIMENSION))
	{
		TRACE0("Failed to create dialogBar\n");
		return -1;      // fail to create
	}

	if (!m_wndsnapingBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_BOTTOM| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_LINESTYLE) ||
		!m_wndsnapingBar.LoadToolBar(IDR_SNAPPING))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndsnapoptionsBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_BOTTOM| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SNAPOPTIONS) ||
		!m_wndsnapoptionsBar.LoadToolBar(IDR_SNAPOPTIONS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
/*	if(!m_wndlinestyleBar.Create(this,IDD_LINESTYLE,CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY,IDD_LINESTYLE))
		{
			TRACE0("Failed to create toolbar\n");
			return -1;
		}*/
	

	/*
	if(!m_linestyle.Create(IDD_LDIALOG,NULL))
	{
			TRACE0("Failed to create toolbar\n");
			return -1;
	}*/

//	(m_wndToolBar1.GetToolBarCtrl()).SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);	
//	(m_wndlinestyleBar.GetToolBarCtrl()).SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);

	UINT idcercle=m_wndToolBar1.CommandToIndex(ID_CERCLE);
//	UINT st=m_wndToolBar1.GetButtonStyle(idcercle);
//	st|=TBSTYLE_DROPDOWN;
//	m_wndToolBar1.SetButtonStyle(idcercle,st);

//	idcercle=m_wndToolBar1.CommandToIndex(ID_TBSELECT);
//	st=m_wndToolBar1.GetButtonStyle(idcercle);
//	st|=TBSTYLE_DROPDOWN;
//	m_wndToolBar1.SetButtonStyle(idcercle,st);

//	idcercle=m_wndToolBar1.CommandToIndex(ID_TBROTATE);
//	st=m_wndToolBar1.GetButtonStyle(idcercle);
//	st|=TBSTYLE_DROPDOWN;
//	m_wndToolBar1.SetButtonStyle(idcercle,st);

	idcercle=m_wndToolBar1.CommandToIndex(ID_Text);
//	st=m_wndToolBar1.GetButtonStyle(idcercle);
//	st|=TBSTYLE_DROPDOWN;
//	m_wndToolBar1.SetButtonStyle(idcercle,st);

/*	idcercle=m_wndLinestyleBar.CommandToIndex(ID_LINESYTLE);
	st=m_wndLinestyleBar.GetButtonStyle(idcercle);
	st|=TBSTYLE_LIST   ;
	m_wndLinestyleBar.SetButtonStyle(idcercle,st);
*/
	
	if (!m_cercToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_CER) ||
		!m_cercToolBar.LoadToolBar(IDR_CER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_tbselectToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_EDIT) ||
		!m_tbselectToolBar.LoadToolBar(IDR_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_tbrotateToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TRAN) ||
		!m_tbrotateToolBar.LoadToolBar(IDR_TRAN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndsurface.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP|CCS_ADJUSTABLE|  CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SURFACE) ||
		!m_wndsurface.LoadToolBar(IDR_SURFACE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    /*
	if (!m_wndshape.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CCS_ADJUSTABLE| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SHAPE) ||
		!m_wndshape.LoadToolBar(IDR_SHAPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

	/*if (!m_wnddefinedshape.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP|CCS_ADJUSTABLE|  CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SOLID) ||
		!m_wnddefinedshape.LoadToolBar(IDR_SOLID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

	if (!m_wndcamera.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP|CCS_ADJUSTABLE|  CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_CAMERA) ||
		!m_wndcamera.LoadToolBar(IDR_CAMERA))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}



	if (!text.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|WS_CAPTION |CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_TOP| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TEXT) ||
		!text.LoadToolBar(IDR_TEXT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

 
/*	if (!m_wndsnapingBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD |
		WS_VISIBLE|CBRS_GRIPPER|CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_RIGHT| CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SNAPPING) ||
		!m_wndsnapingBar.LoadToolBar(IDR_SNAPPING))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!colorToolBar.Create(this,IDD_DIALOGBAR, CBRS_BOTTOM|
		CBRS_GRIPPER | CBRS_FLYBY ,IDD_DIALOGBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
/*	if (!laybar.Create(this, IDD_LAYDIA,
		CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY,
		IDD_LAYDIA))
	{
		TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
		return -1;		// fail to create
	}
*/
	if (!m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER|CBRS_HIDE_INPLACE,
			CG_ID_VIEW_MYDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}

	if (!comd_dlg.Create(this, IDD_DIALOGBAR_PARSE,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER|CBRS_HIDE_INPLACE| CBRS_SIZE_DYNAMIC,
			IDD_DIALOGBAR_PARSE))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}
	
		if (!m_wndlibdia.Create(this, IDD_LIB,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER,
			DLIB_ID))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}

		if (!m_wndlaydia.Create(this, IDD_LAYDIA,
			CBRS_RIGHT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER,
			DLAY_ID))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}

	    if (!patternBar.Create(this, IDD_DIALOGPATTERN,
			CBRS_BOTTOM|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER,
			IDD_DIALOGPATTERN))
		{
			TRACE0("Failed to create dialog bar\n");
			return -1;		// fail to create
		}

	/*	if (!m_wndmandrbar.Create(this, IDD_MOVEANDROTATE_DIALOGBAR,
			CBRS_BOTTOM|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER,
			IDD_MOVEANDROTATE_DIALOGBAR))
		{
			TRACE0("Failed to create dialog bar\n");
			return -1;		// fail to create
		}
*/
		text.ShowWindow(SW_HIDE);
//	    m_cercToolBar.ShowWindow(SW_HIDE);
//	    m_tbselectToolBar.ShowWindow(SW_HIDE);
//	    m_tbrotateToolBar.ShowWindow(SW_HIDE);
		
//		EnableDocking(CBRS_ALIGN_ANY);
		
		m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		comd_dlg.EnableDocking(CBRS_ALIGN_RIGHT);
		
	   

		m_wndlibdia.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		m_wndlaydia.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		patternBar.EnableDocking(CBRS_ALIGN_ANY);
//		m_wndmandrbar.EnableDocking(CBRS_ALIGN_ANY);
		
		//m_wndrender.EnableDocking(CBRS_ALIGN_ANY);
	    m_wndtransfill.EnableDocking(CBRS_ALIGN_ANY);
	    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
        m_wndsnapingBar.EnableDocking(CBRS_ALIGN_ANY);
		m_wndsnapoptionsBar.EnableDocking(CBRS_ALIGN_ANY);
	    m_tbrotateToolBar.EnableDocking(CBRS_ALIGN_ANY);
	    m_tbselectToolBar.EnableDocking(CBRS_ALIGN_ANY);
	    m_cercToolBar.EnableDocking(CBRS_ALIGN_ANY);
	    text.EnableDocking(CBRS_ALIGN_ANY);
	    m_wndToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	    m_wndimensionBar.EnableDocking(CBRS_ALIGN_ANY);
        //m_wndshape.EnableDocking(CBRS_ALIGN_ANY);
	    m_wndsurface.EnableDocking(CBRS_ALIGN_ANY);
        m_wndcamera.EnableDocking(CBRS_ALIGN_ANY);
	    //m_wnddefinedshape.EnableDocking(CBRS_ALIGN_ANY);

	    m_wndZoomBar.EnableDocking(CBRS_ALIGN_ANY);

        colorToolBar.EnableDocking(CBRS_ALIGN_BOTTOM|CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);

	EnableDocking(CBRS_ALIGN_ANY);
   // DockControlBar(&m_wndrender);
//	DockControlBar(&m_wndmandrbar);
	CRect v,v1;
	m_wndToolBar.GetWindowRect(&v);
	DockControlBar(&m_wndToolBar);//,UINT(0),CRect(0,0,v1.Width(),v.Height()));
	m_wndToolBar1.GetWindowRect(&v1);

	DockControlBar(&m_wndToolBar1);//,UINT(0),CRect(v1.Width()+20,0,v1.Width(),v1.Height()));
	m_cercToolBar.GetWindowRect(&v);
//	v1-=v.TopLeft()+CPoint(v.Width(),0);
//	m_cercToolBar.MoveWindow(v1);
	DockControlBar(&m_cercToolBar);//,UINT(0),CRect(650,0,v.Width(),v.Height()));
	DockControlBar(&m_tbselectToolBar);
	DockControlBar(&m_tbrotateToolBar);
	DockControlBar(&m_wndMyDialogBar);
	DockControlBar(&m_wndtransfill);
	DockControlBar(&m_wndcamera);
	DockControlBar(&m_wndsurface);	
	DockControlBar(&m_wndsnapoptionsBar);
	DockControlBar(&m_wndimensionBar);
	DockControlBar(&m_wndsnapingBar);
	DockControlBar(&colorToolBar);
	DockControlBar(&comd_dlg);
//		pView->setDrawObservers(&m_wndMyDialogBar); 	
	
//	DockControlBar(&laybar);

	DockControlBar(&m_wndZoomBar);
//	m_wndToolBar.GetWindowRect(&v);
//	DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP,CRect(0,0,v.Width(),v.Height()));


//	m_wndToolBar1.GetWindowRect(&v1);


//	DockControlBar(&m_wndToolBar1,AFX_IDW_DOCKBAR_TOP,CRect(v.Width()+2,0,v.Width()+v1.Width(),v.Height()));
	DockControlBar(&text);
    DockControlBar(&m_wndlibdia);
	DockControlBar(&m_wndlaydia);
	DockControlBar(&patternBar);

    m_wndlaydia.ShowWindow(SW_HIDE);
    m_wndlibdia.ShowWindow(SW_HIDE);
    m_wndsnapoptionsBar.ShowWindow(SW_HIDE);
    comd_dlg.ShowWindow(SW_HIDE);
    m_wndcamera.ShowWindow(SW_HIDE);
    m_wndsurface.ShowWindow(SW_HIDE);
   // m_wndlibdia.ShowWindow(SW_HIDE);

	LoadBarState(_T("AnddyCAD"));

	{
		int nOrigSize = sizeof(indicators) / sizeof(UINT);

		UINT* pIndicators = new UINT[nOrigSize + 2];
		memcpy(pIndicators, indicators, sizeof(indicators));

		// Call the Status Bar Component's status bar creation function
		if (!InitStatusBar(pIndicators, nOrigSize, 60))
		{
			TRACE0("Failed to initialize Status Bar\n");
			return -1;
		}
		delete[] pIndicators;
	}
		// Finally, create the scripting object...
/*	if ( FAILED(m_pScriptObject.CreateInstance(CLSID_ScriptObject)) ) {
		// Unable to create the scripting object...
		DWORD d=GetLastError();
		AfxMessageBox("Unable to create the scripting object",MB_OK|MB_ICONERROR);
	//	return -1;
	} // if
*/
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
		strPath += "start";
		strPath += '\\';
	} // if

	SetCurrentDirectory(strPath);

/*    if(CCadApp::m_AddinManager.LoadAddinDefaultSettings())
    {
        if(CCadApp::m_AddinManager.GetLoadAllAddinStatus())
        {
            if(CCadApp::m_AddinManager.LoadAllAddins()) 
				LoadAllAddinCommands();
        }
    }*/
	SetCurrentDirectory(CString(szCurrentDir));

	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	//cs.style|=WS_CLIPCHILDREN;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/*void CMainFrame::OnAddinAddinsettings() 
{
//	CAddinSettingsDialog AddinSettingsDialog;
//	if(AddinSettingsDialog.DoModal()==IDOK)
	{

	}
	
}*/


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : PFMergeAccelerator
	Description	      : 
	Return Type	      : bool CMainFrame:: 
	Warning           : 
  Argument          : HACCEL& hDestination
  Argument          : HACCEL hToMerge
------------------------------------------------------------------------------------------------------------*/

bool CMainFrame:: PFMergeAccelerator(HACCEL& hDestination, HACCEL hToMerge)
{
	// this function merges the hToMerge accelerator table with that of hDestination
	ASSERT(hToMerge) ;

	int		original_count = 0 ;
	int		add_count ;
	if (hDestination != NULL)
	{
		// we have an existing table
		original_count = CopyAcceleratorTable(hDestination, NULL, 0) ;
 	}
	add_count = CopyAcceleratorTable(hToMerge, NULL, 0) ;
	if (add_count > 0)
	{
		ACCEL	*pElements = new ACCEL[original_count + add_count] ;
		// copy in the existing data if it exists
		if (hDestination != NULL)
			CopyAcceleratorTable(hDestination, pElements, original_count) ;
		// now add in the merge accelerator
		CopyAcceleratorTable(hToMerge, &pElements[original_count], add_count) ;
		HACCEL hNew = CreateAcceleratorTable(pElements, original_count + add_count) ;
		DestroyAcceleratorTable(hDestination) ;			// because it gets replaced
		hDestination = hNew ;
		delete []pElements ;
		return true ;
	}
	return false ;
}


BOOL CMainFrame::LoadAditionalAccelerators()
{
	if(m_AcceleratorArray.GetSize()>0)
	{
		ACCEL* pAccelArray= new ACCEL[m_AcceleratorArray.GetSize()]; 
		for(int i=0;i<m_AcceleratorArray.GetSize();i++)
		{
			pAccelArray[i]=m_AcceleratorArray[i];
		}
		HACCEL AcclAppend=CreateAcceleratorTable(pAccelArray,m_AcceleratorArray.GetSize());
		PFMergeAccelerator(m_hAccelTable,AcclAppend);
		delete [] pAccelArray;
	}
	return TRUE;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	

}

void CMainFrame::GetClientR( LPRECT lpRect ) 
{
	CRect rect;

	CFrameWnd::GetClientRect(lpRect);
	if(m_wndToolBar.IsWindowVisible())
	{
		m_wndToolBar.GetClientRect(rect);
		lpRect->bottom-=rect.Height();
	}
	if(m_wndToolBar1.IsWindowVisible())
	{
		m_wndToolBar1.GetClientRect(rect);
		lpRect->bottom-=rect.Height();
	}
	if(m_wndStatusBar.IsWindowVisible())
	{
		m_wndStatusBar.GetClientRect(rect);
		lpRect->bottom-=rect.Height();
	}
}


void CMainFrame::OnSubMenu( NMHDR * pNotifyStruct, LRESULT * result )
{
	NMTOOLBAR* notif=(NMTOOLBAR*)pNotifyStruct;
	switch(notif->iItem)
	{
	case(ID_CERCLE):
		{
		CRect rec;
		m_wndToolBar1.GetItemRect(m_wndToolBar1.CommandToIndex(ID_CERCLE),rec);
		ClientToScreen(rec);
		CPoint v;
		v.x=rec.left;
		v.y=rec.bottom;
	
		m_cercToolBar.LoadToolBar(IDR_CER);

		m_cercToolBar.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_cercToolBar);

		m_cercToolBar.ShowWindow(SW_SHOWNORMAL);

		FloatControlBar(&m_cercToolBar,v,CBRS_ALIGN_ANY);

			break;
		}
	case(ID_TBSELECT):
		{
		CRect rec;
		m_wndToolBar1.GetItemRect(m_wndToolBar1.CommandToIndex(ID_TBSELECT),rec);
		ClientToScreen(rec);
		CPoint v;
	//	rec = rec+50;
		v.x=rec.left;
		v.y=rec.bottom;
	
		m_tbselectToolBar.LoadToolBar(IDR_EDIT);

		m_tbselectToolBar.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_tbselectToolBar);

		m_tbselectToolBar.ShowWindow(SW_SHOWNORMAL);

		FloatControlBar(&m_tbselectToolBar,v,CBRS_ALIGN_ANY);
		break;
		}
	case(ID_TBROTATE):
		{
		CRect rec;
		m_wndToolBar1.GetItemRect(m_wndToolBar1.CommandToIndex(ID_TBROTATE),rec);
		ClientToScreen(rec);
		CPoint v;
		v.x=rec.left;
		v.y=rec.bottom;
	
		m_tbrotateToolBar.LoadToolBar(IDR_TRAN);

		m_tbrotateToolBar.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_tbrotateToolBar);

		m_tbrotateToolBar.ShowWindow(SW_SHOWNORMAL);

		FloatControlBar(&m_tbrotateToolBar,v,CBRS_ALIGN_ANY);
		break;
		}

		case(ID_Text):
		{
		CRect rec;
		text.GetItemRect(text.CommandToIndex(ID_Text),rec);
		ClientToScreen(rec);
		CPoint v;
		//rec=rec-20;
		v.x=rec.left;
		v.y=rec.bottom;
	
		text.LoadToolBar(IDR_TEXT);

		text.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&text);

		text.ShowWindow(SW_SHOWNORMAL);

		FloatControlBar(&text,v,CBRS_ALIGN_ANY);
	
		}

	}
}




void CMainFrame::OnInitMenu(CMenu* pMenu)
{
   CFrameWnd::OnInitMenu(pMenu);
  
	// CG: This block added by 'Tip of the Day' component.
	{
		// TODO: This code adds the "Tip of the Day" menu item
		// on the fly.  It may be removed after adding the menu
		// item to all applicable menu items using the resource
		// editor.

		// Add Tip of the Day menu item on the fly!
		static CMenu* pSubMenu = NULL;

		CString strHelp; strHelp.LoadString(CG_IDS_TIPOFTHEDAYHELP);
		CString strMenu;
		int nMenuCount = pMenu->GetMenuItemCount();
		BOOL bFound = FALSE;
		for (int i=0; i < nMenuCount; i++) 
		{
			pMenu->GetMenuString(i, strMenu, MF_BYPOSITION);
			if (strMenu == strHelp)
			{ 
				pSubMenu = pMenu->GetSubMenu(i);
				bFound = TRUE;
				ASSERT(pSubMenu != NULL);
			}
		}

		CString strTipMenu;
		strTipMenu.LoadString(CG_IDS_TIPOFTHEDAYMENU);
		if (!bFound)
		{
			// Help menu is not available. Please add it!
			if (pSubMenu == NULL) 
			{
				// The same pop-up menu is shared between mainfrm and frame 
				// with the doc.
				static CMenu popUpMenu;
				pSubMenu = &popUpMenu;
				pSubMenu->CreatePopupMenu();
				pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION, 
					CG_IDS_TIPOFTHEDAY, strTipMenu);
			} 
			pMenu->AppendMenu(MF_STRING|MF_BYPOSITION|MF_ENABLED|MF_POPUP, 
				(UINT)pSubMenu->m_hMenu, strHelp);
			DrawMenuBar();
		} 
		else
		{      
			// Check to see if the Tip of the Day menu has already been added.
			pSubMenu->GetMenuString(0, strMenu, MF_BYPOSITION);

			if (strMenu != strTipMenu) 
			{
				// Tip of the Day submenu has not been added to the 
				// first position, so add it.
				pSubMenu->InsertMenu(0, MF_BYPOSITION);  // Separator
				pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION, 
					CG_IDS_TIPOFTHEDAY, strTipMenu);
			}
		}
	}

}


void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
  	CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
  
	// CG: The following block was inserted by 'Status Bar' component.
	{
		// Restore first pane of the statusbar?
		if (nFlags == 0xFFFF && hSysMenu == 0 && m_nStatusPane1Width != -1)
		{
			m_bMenuSelect = FALSE;
			m_wndStatusBar.SetPaneInfo(0, 
				m_nStatusPane1ID, m_nStatusPane1Style, m_nStatusPane1Width);
			m_nStatusPane1Width = -1;   // Set it to illegal value
		}
		else 
		{
			m_bMenuSelect = TRUE;
		}
	}

}

 void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
 {
   	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
   
 	// CG: The following block was inserted by 'Status Bar' component.
 	{
 		// store width of first pane and its style
 		if (m_nStatusPane1Width == -1 && m_bMenuSelect)
 		{
 			m_wndStatusBar.GetPaneInfo(0, m_nStatusPane1ID, 
 				m_nStatusPane1Style, m_nStatusPane1Width);
 			m_wndStatusBar.SetPaneInfo(0, m_nStatusPane1ID, 
 				SBPS_NOBORDERS|SBPS_STRETCH, 16384);
 		}
 	}
 
 }

void CMainFrame::OnUpdateDate(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strDate = time.Format(_T("%A, %B %d, %y "));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strDate);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current date
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nDatePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nDatePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strDate);
	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%X"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strTime);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current time
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nTimePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nTimePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strTime);
	pCmdUI->Enable(TRUE);

}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Create an index for the DATE pane
	m_nDatePaneNo = nSize++;
	pIndicators[m_nDatePaneNo] = ID_INDICATOR_DATE;
	// Create an index for the TIME pane
	m_nTimePaneNo = nSize++;
	nSeconds = 1;
	pIndicators[m_nTimePaneNo] = ID_INDICATOR_TIME;

	// TODO: Select an appropriate time interval for updating
	// the status bar when idling.
	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);

}

void CMainFrame::OnClose() 
{
	SaveBarState(_T("AnddyCAD"));
//	CCadApp::m_AddinManager.UnloadAllAddins();  
	CFrameWnd::OnClose();
}



void CMainFrame::OnCustomize() 
{
	m_wndToolBar.GetToolBarCtrl().Customize();
}

void CMainFrame::OnDimview() 
{
	menudim=(!menudim); 
	ShowControlBar(&m_wndimensionBar,menudim,true);
}

void CMainFrame::OnUpdateDimview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menudim);
}

void CMainFrame::OnInfobarView() 
{
	menuinfo=(!menuinfo);
	ShowControlBar(&m_wndMyDialogBar,menuinfo,true);
}

void CMainFrame::OnUpdateInfobarView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menuinfo);	
}

void CMainFrame::OnColorView() 
{
	menucol=(!menucol);
	ShowControlBar(&colorToolBar,menucol,true);
}

void CMainFrame::OnUpdateColorView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menucol);	
}

void CMainFrame::OnTransView() 
{
	menutrans=(!menutrans);
	ShowControlBar(&m_tbrotateToolBar,menutrans,true);
}

void CMainFrame::OnUpdateTransView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menutrans);		
}

void CMainFrame::OnEditView() 
{
	menuedit=(!menuedit);
	ShowControlBar(&m_tbselectToolBar,menuedit,true);
}

void CMainFrame::OnUpdateEditView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menuedit);		
}

void CMainFrame::OnViewToolbarColorbar() 
{
		menucol=(!menucol);
	ShowControlBar(&colorToolBar,menucol,true);
	
}

void CMainFrame::OnUpdateViewToolbarColorbar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menucol);	
	
}

void CMainFrame::OnViewToolbarDimensionbar() 
{
	menudim=(!menudim); 
	ShowControlBar(&m_wndimensionBar,menudim,true);
	
}

void CMainFrame::OnUpdateViewToolbarDimensionbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menudim);
	
}

void CMainFrame::OnViewToolbarInformationbar() 
{
	menuinfo=(!menuinfo);
	ShowControlBar(&m_wndMyDialogBar,menuinfo,false);
}

void CMainFrame::OnUpdateViewToolbarInformationbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menuinfo);	
}

void CMainFrame::OnViewToolbarModifyingbar() 
{
	menuedit=(!menuedit);
	ShowControlBar(&m_tbselectToolBar,menuedit,true);
	
}

void CMainFrame::OnUpdateViewToolbarModifyingbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menuedit);	
}

void CMainFrame::OnViewToolbarStandardbar() 
{
		menustd=(!menustd);
	ShowControlBar(&m_wndToolBar,menustd,true);
	
}

void CMainFrame::OnUpdateViewToolbarStandardbar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menustd);
	
}

void CMainFrame::OnViewToolbarTextbar() 
{
		menutext=(!menutext);
	ShowControlBar(&text,menutext,true);
	
}

void CMainFrame::OnUpdateViewToolbarTextbar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menutext);
	
}

void CMainFrame::OnViewToolbarTransformationbar() 
{
	menutrans=(!menutrans);
	ShowControlBar(&m_tbrotateToolBar,menutrans,true);
}


void CMainFrame::OnUpdateViewToolbarTransformationbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menutrans);
	
}

void CMainFrame::OnViewToolbarZoombar() 
{
		menuzoom=(!menuzoom);
	ShowControlBar(&m_wndZoomBar,menuzoom,true);
	
}

void CMainFrame::OnUpdateViewToolbarZoombar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menuzoom);
	
}

void CMainFrame::OnViewToolbarDrawingbar() 
{
	menudrw=(!menudrw);
	ShowControlBar(&m_wndToolBar1,menudrw,true);
	
}

void CMainFrame::OnUpdateViewToolbarDrawingbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menudrw);
	
}

void CMainFrame::OnHelpTipoftheday() 
{
	CTipDlg dlg;
	dlg.DoModal();	
}

void CMainFrame::OnViewToolbarShowtoolbars() 
{	
	if(menushow=(!menushow))
	{
		menudrw=(!menudrw);
		ShowControlBar(&m_wndToolBar1,menudrw,true);
		menuzoom=(!menuzoom);
		ShowControlBar(&m_wndZoomBar,menuzoom,false);
		menutrans=(!menutrans);
		ShowControlBar(&m_tbrotateToolBar,menutrans,false);
		menustd=(!menustd);
		ShowControlBar(&m_wndToolBar,menustd,true);
		menuedit=(!menuedit);
		ShowControlBar(&m_tbselectToolBar,menuedit,false);
		menuinfo=(!menuinfo);
		ShowControlBar(&m_wndMyDialogBar,menuinfo,false);
		menudim=(!menudim); 
		ShowControlBar(&m_wndimensionBar,menudim,false);
		menucol=(!menucol);
		ShowControlBar(&colorToolBar,menucol,false);
		menuinfo=(!menuinfo);
		ShowControlBar(&m_wndMyDialogBar,menuinfo,false);
		menustat=(!menustat);
		ShowControlBar(&m_wndStatusBar,menustat,false);

		menusnp=(!menusnp);
		ShowControlBar(&m_wndsnapingBar,menusnp,false);

		menultb=(!menultb);
		ShowControlBar(&m_wndtransfill,menultb,false);
		menupat=(!menupat);
		ShowControlBar(&patternBar,menupat,false);

		menutext=(!menutext);
		ShowControlBar(&text,menutext,false);
		
		menusurf=(!menusurf);
		ShowControlBar(&m_wndsurface,menusurf,false);

		menucam=(!menucam);
		ShowControlBar(&m_wndcamera,menucam,false);

		menulay=(!menulay);
		ShowControlBar(&m_wndlaydia,menulay,false);

		menulib=(!menulib);
		ShowControlBar(&m_wndlibdia,menulib,false);
     
		menucerc=(!menucerc);
		ShowControlBar(&m_cercToolBar,menucerc,false);

		
		}
	

}

/*void CMainFrame::OnUpdateViewToolbarShowtoolbars(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menushow);
	
}
*/
void CMainFrame::OnViewToolbarHidetoolbars() 
{
	if(menuhide=(!menuhide))
	{
		menudrw=(!menudrw);
		ShowControlBar(&m_wndToolBar1,menudrw,true);
		menuzoom=(!menuzoom);
		ShowControlBar(&m_wndZoomBar,menuzoom,true);
		menutrans=(!menutrans);
		ShowControlBar(&m_tbrotateToolBar,menutrans,true);
		menustd=(!menustd);
		ShowControlBar(&m_wndToolBar,menustd,true);
		menuedit=(!menuedit);
		ShowControlBar(&m_tbselectToolBar,menuedit,true);
		menuinfo=(!menuinfo);
		ShowControlBar(&m_wndMyDialogBar,menuinfo,true);
		menudim=(!menudim); 
		ShowControlBar(&m_wndimensionBar,menudim,true);
		menucol=(!menucol);
		ShowControlBar(&colorToolBar,menucol,true);
		menultb=(!menultb);
		ShowControlBar(&m_wndtransfill,menultb,true);
		menupat=(!menupat);
		ShowControlBar(&patternBar,menupat,true);
		menustat=(!menustat);
		ShowControlBar(&m_wndStatusBar,menustat,true);


		menutext=(!menutext);
		ShowControlBar(&text,menutext,true);
		
			menusnp=(!menusnp);
		ShowControlBar(&m_wndsnapingBar,menusnp,true);

		menusurf=(!menusurf);
		ShowControlBar(&m_wndsurface,menusurf,true);

		menucam=(!menucam);
		ShowControlBar(&m_wndcamera,menucam,true);

		menulay=(!menulay);
		ShowControlBar(&m_wndlaydia,menulay,true);

		menulib=(!menulib);
		ShowControlBar(&m_wndlibdia,menulib,true);
	}
	
	
}

void CMainFrame::OnUpdateViewToolbarHidetoolbars(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menuhide);
}
void CMainFrame::OnHelpFinder() 
{
//	::HtmlHelp(NULL,
//		"cad.chm",
//		HH_DISPLAY_TOPIC,0);
}

void CMainFrame::OnHelpRegistration() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewToolbarShowsnap() 
{
	menusnp=(!menusnp);
	ShowControlBar(&m_wndsnapingBar,menusnp,true);
}

void CMainFrame::OnUpdateViewToolbarShowsnap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menusnp);
}

void CMainFrame::OnViewToolbarShowlay() 
{
	if(m_wndlaydia.IsWindowVisible())
		{
			menulay=true;
		}
	menulay=(!menulay);
	ShowControlBar(&m_wndlaydia,menulay,true);
	
}

void CMainFrame::OnUpdateViewToolbarShowlay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(menulay);

}
void CMainFrame::OnViewToolbarShowlibbar() 
{
		if(m_wndlibdia.IsWindowVisible())
		{
			menulib=true;
		}
		menulib=(!menulib);
		ShowControlBar(&m_wndlibdia,menulib,false);
}

void CMainFrame::OnUpdateViewToolbarShowlibbar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menulib);
}

void CMainFrame::OnViewToolbarShowcmdbar() 
{
		if(comd_dlg.IsWindowVisible())
		{
			menucmd=true;
		}
		menucmd=(!menucmd);
		ShowControlBar(&comd_dlg,menucmd,false);
}

void CMainFrame::OnUpdateViewToolbarShowcmdbar(CCmdUI* pCmdUI) 
{
		pCmdUI->SetCheck(menucmd);
}

void CMainFrame::setInterestObject(CSubject* s)
{
	CCadView *pView = (CCadView *)GetActiveView();
	pView->RegisterInterest(&m_wndMyDialogBar);
	s->RegisterInterest(&m_wndMyDialogBar);
	pView->RegisterInterest(&comd_dlg);
	s->RegisterInterest(&comd_dlg);
}

BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if(wParam==IDC_LIBT1)
	{
		m_wndlibdia.m_libtree = (CTreeCtrl*)m_wndlibdia.GetDlgItem(IDC_LIBT1);
		if(!m_wndlibdia.m_libtree->GetImageList(TVSIL_NORMAL))
		{
		m_wndlibdia.m_libtree->SetImageList(&m_wndlibdia.libimlist,TVSIL_NORMAL);
		}
	
		LPNMHDR lpnmh = (LPNMHDR) lParam;
		if(lpnmh->code==TVN_BEGINDRAG)
		{
 		HTREEITEM it=((NM_TREEVIEW *)lParam)->itemNew.hItem;//m_wndlibdia.m_libtree->GetSelectedItem();
			if(!m_wndlibdia.m_libtree->ItemHasChildren(it))
 			{
				HTREEITEM pit=m_wndlibdia.m_libtree->GetParentItem(it);
 				
 				CFrameWnd *pFrame = 
 						 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
 
 				// Get the active view attached to the active MDI child
 				// window.
 				CCadView *pView = (CCadView *) pFrame->GetActiveView();
 			
				CRect rc;
				m_wndlibdia.m_libtree->GetItemRect(it,rc,0);
				CPoint pl=rc.CenterPoint();
				m_wndlibdia.m_libtree->MapWindowPoints(pView,&pl,1);
 				pView->draglib(m_wndlibdia.m_libtree->GetItemText(pit),m_wndlibdia.m_libtree->GetItemText(it),pl);

//				pView->SetCapture();
				m_wndlibdia.drag=true;
 			}
		}
	}
	
	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CMainFrame::OnBegindragLibt1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void CMainFrame::OnEditLayer() 
{
    if(m_wndlaydia.IsWindowVisible())
		{
			menulay=true;
		}
	menulay=(!menulay);
	ShowControlBar(&m_wndlaydia,menulay,true);
	
}

void CMainFrame::OnUpdateEditLayer(CCmdUI* pCmdUI) 
{
  	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(menulay);	
}

void CMainFrame::OnLibrary() 
{
       if(m_wndlibdia.IsWindowVisible())
		{
			menulib=true;
		}
		menulib=(!menulib);
		ShowControlBar(&m_wndlibdia,menulib,false);
		// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateLibrary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(menulib);	
}


void CMainFrame::OnToolsToolbarsPatterntexturebar() 
{
	    if(patternBar.IsWindowVisible())
		{
			menupat=true;
		}
		menupat=(!menupat);
		ShowControlBar(&patternBar,menupat,false);
		// TODO: Add your command handler code here

	
}

void CMainFrame::OnUpdateToolsToolbarsPatterntexturebar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(menupat);	
}

void CMainFrame::OnToolsToolbarsCreatesurfacebar() 
{

	    if(m_wndsurface.IsWindowVisible())
		{
			menusurf=true;
		}
		menusurf=(!menusurf);
		ShowControlBar(&m_wndsurface,menusurf,false);
		// TODO: Add your command handler code here

	
}

void CMainFrame::OnUpdateToolsToolbarsCreatesurfacebar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(menusurf);
}

void CMainFrame::OnToolsToolbarsViewbar() 
{
	// TODO: Add your command handler code here
    if(m_wndcamera.IsWindowVisible())
		{
			menucam=true;
		}
		menucam=(!menucam);
		ShowControlBar(&m_wndcamera,menucam,false);
	
	
}

void CMainFrame::OnUpdateToolsToolbarsViewbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(menucam);

}

void CMainFrame::OnToolsToolbarsSmoothinglightbar() 
{
	// TODO: Add your command handler code here
       if(m_wndtransfill.IsWindowVisible())
		{
			menultb=true;
		}
		menultb=(!menultb);
		ShowControlBar(&m_wndtransfill,menultb,false);
		
}

void CMainFrame::OnUpdateToolsToolbarsSmoothinglightbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(menultb);	
}

/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CMainFrame::OnAddinMenuItems
	Description	      : Here we can invoke all the functionss of all addins
	Return Type	      : void 
	Warning           : 
  Argument          : UINT nID
------------------------------------------------------------------------------------------------------------*/

void CMainFrame::OnAddinMenuItems(UINT nID)
{
//	CCadApp::m_AddinManager.InvokeAddinMenuItem(nID);

}


/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CMainFrame::OnUpdateAddinMenuItems
	Description	      : Here we can enable/disable all the menus and toolbars
						of all addins depending on the business logic
	Return Type	      : void 
	Warning           : 
  Argument          : CCmdUI* pCmdUI
------------------------------------------------------------------------------------------------------------*/

void CMainFrame::OnUpdateAddinMenuItems(CCmdUI* pCmdUI)
{
//	const CAddinInfo& AddinInfo=CCadApp::m_AddinManager.GetAddinInformation(pCmdUI->m_nID);
//	pCmdUI->Enable(AddinInfo.m_bLoadAddin); 
	
}

/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CMainFrame::OnToolTipText
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
  Argument          : UINT nID
  Argument          : NMHDR* pNMHDR
  Argument          : LRESULT* pResult
------------------------------------------------------------------------------------------------------------*/

BOOL CMainFrame::OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult)
{

	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

	CString strTipText;
	CString strMessage;
	if ( GetToolText(pNMHDR->hwndFrom,  pNMHDR->idFrom, strTipText, strMessage ) )
	{
		//----------------------------------------------------------------
		// We got a text string so lets give it to Windows to display
		// as our custom tool tip.
		//----------------------------------------------------------------
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		else
		_mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		else
		lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));


		//-----------------------------------------------------------------
		// This sets the status bar message to our custom message string.
		//-----------------------------------------------------------------
#endif
		
		SetMessageText( strMessage );
		return TRUE;
	}

	//----------------------------------------------------------------
	// We DID NOT get our own string so pass this notification on to
	// to the base class for processing.
	//----------------------------------------------------------------

	return CFrameWnd::OnToolTipText( nID, pNMHDR, pResult );
}

// Replace this routine with whatever is specific to your needs.
// Obviously, you will want to switch on nID.
//--------------------------------------------------------------------------------------------------

BOOL CMainFrame::GetToolText(HWND toolHandle, UINT nID, CString& strTipText, CString& strMessage )
{
/*	if((nID >=PF_ADDIN_CMD_MIN_MSG_ID) && (nID<=PF_ADDIN_CMD_MAX_MSG_ID))
	{
		strTipText=CCadApp::m_AddinManager.GetAddinCommadInfo(nID).m_strToolTip;
		strMessage=CCadApp::m_AddinManager.GetAddinCommadInfo(nID).m_strHelpString;
		return TRUE;
	}
	else
	{
		return FALSE;
	}*/
	return FALSE;
	
}

/*BOOL CMainFrame::LoadAllAddinCommands()
{

	UINT iCommandID= WM_USER+1000;

	int iAddinCount=CCadApp::m_AddinManager.GetAddinCount();
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);

	for(int i=0;i<iAddinCount;i++)
	{
		//Get the Addin info
		CAddinInfo AddinInfo=CCadApp::m_AddinManager.GetAddinInfo(i);
		CToolBar* pAddinToolbar= new CToolBar();
		pAddinToolbar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP 
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

		//Get the toolbar count
		int iToolbarButtonCount=AddinInfo.m_lToolbarButtonCount; 
		//Create an integer array for storing the toolbar Button Commands
		int *piTollbarCommandsID= new int[iToolbarButtonCount];
		
		//Get the main menu
		CMenu* pMainMenu =GetMenu();
		CMenu *pCraetedMenu=pMainMenu;
		int iMenuCount=pMainMenu->GetMenuItemCount();
		if (pMainMenu != NULL && iMenuCount > 0)
		{
			pCraetedMenu=pMainMenu;
			//Create all the leaf menus
			for(int j=0;j<AddinInfo.m_AddinCommadInfoArray.GetSize();j++)
			{
				iMenuCount=pMainMenu->GetMenuItemCount();
				CStringArray MenuArray;
				MenuArray.Copy(AddinInfo.m_AddinCommadInfoArray[j].m_MenuStringsArray);
				//Iterate through all MenuArray to see the given menu and submenu is there
				//Check the menu is already there and is in index 0

				CMenu *pSubMenu=FindMenu(pMainMenu,MenuArray[0]);
				CMenu *pMainSubMenu=NULL; 
				//If the menu is not there create a submenu and appened this menu
				if(!pSubMenu)
				{
					
					//Insert this menu to the main menu
					pMainMenu->InsertMenu(iMenuCount-1,MF_BYPOSITION | MF_POPUP,(UINT)CreatePopupMenu(),MenuArray[0]);
					pSubMenu=FindMenu(pMainMenu,MenuArray[0]);
										
									
				}
				//
				pMainSubMenu=pSubMenu;
				for(int k=1;k < MenuArray.GetSize();k++)
				{
					pSubMenu=FindMenu(pMainSubMenu,MenuArray[k]);
					if(!pSubMenu)
					{
						//Insert this menu to the main menu
						if(pMainSubMenu->InsertMenu(pMainSubMenu->GetMenuItemCount()-1,MF_BYPOSITION | MF_POPUP,(UINT)CreatePopupMenu(),MenuArray[k]))
						{
							pSubMenu=FindMenu(pMainSubMenu,MenuArray[k]);
						}
						
										
					}
					if(pSubMenu)
					{
						pMainSubMenu=pSubMenu;
					}
					
				}
				//Check if separator is there
				if(AddinInfo.m_AddinCommadInfoArray[j].m_iSeparator >0)
				{
					pMainSubMenu->AppendMenu(MF_SEPARATOR,0,"");
					
				}
				//Append the leaf menu with a command ID
				CString strLeafMenu=AddinInfo.m_AddinCommadInfoArray[j].m_strMenuString;
				
				//Append the shortcut key if any
				if(AddinInfo.m_AddinCommadInfoArray[j].m_strShortCutKey!="")
				{
					strLeafMenu+="\t";
					strLeafMenu+=AddinInfo.m_AddinCommadInfoArray[j].m_strShortCutKey;
					
				}
				pMainSubMenu->AppendMenu(MF_STRING,iCommandID,strLeafMenu);
				//Add the accel key too
				if(AddinInfo.m_AddinCommadInfoArray[j].m_strShortCutKey!="")
				{
					AddAccelerator(iCommandID,AddinInfo.m_AddinCommadInfoArray[j].m_strShortCutKey);
				}
				//Set the Command ID of the menu too
				AddinInfo.m_AddinCommadInfoArray[j].m_iCommandID=iCommandID;
				CCadApp::m_AddinManager.SetAddinInfo(i,AddinInfo);
				if(AddinInfo.m_AddinCommadInfoArray[j].m_iToolbarIndex!=-1)
				{
					piTollbarCommandsID[AddinInfo.m_AddinCommadInfoArray[j].m_iToolbarIndex]=iCommandID;
					iCommandID++;//Increment the command ID So that the command is unique
					
				}
				
			}
		
		}

		//: Get the Main Menu name
		//: If the main menu name is there iterate through the sub menu nmes
		//: Else create the main menu
		//: If the sub menu is not there create the sub menu with popup enabled
		//: Create the leaf menu
		//: Set the command ID for the menu

		HBITMAP AddinBitMap;
		if(AddinInfo.m_type)
		{
			AddinBitMap=LoadBitmap((HINSTANCE)AddinInfo.m_lInstanceHandle,MAKEINTRESOURCE(AddinInfo.m_lToobarRes));
			pAddinToolbar->LoadToolBar(IDR_TOOLBAR1);
			pAddinToolbar->SetButtons((const unsigned int *)piTollbarCommandsID,iToolbarButtonCount); 
			pAddinToolbar->SetBitmap(AddinBitMap);
		}
		else
		{
			pAddinToolbar->LoadToolBar(IDR_TOOLBAR1);
			pAddinToolbar->SetButtons((const unsigned int *)piTollbarCommandsID,iToolbarButtonCount); 
			
			  m_ImageList.Create(22,
				  19,
				  FALSE,   // list does not include masks
				  iToolbarButtonCount,
				  0 );   // list will not grow


			int iCount=0;
			if ( strPath[strPath.GetLength()-1] != '\\' ) {
				// The directory doesn't end with a backslash,
				// so we add one now.
				strPath += '\\';
				strPath += AddinInfo.m_strAddinName;
				strPath += '\\';
			} // if

			CString strFile = strPath + "*.bmp";
			WIN32_FIND_DATA wfd;
			HBITMAP hBitmap;
			SetCurrentDirectory(strPath);
			HANDLE hSearchHandle = FindFirstFile(strFile,&wfd);
			if ( hSearchHandle != INVALID_HANDLE_VALUE ) {
				// Pull first filename
				hBitmap = (HBITMAP)LoadImage(NULL, wfd.cFileName, IMAGE_BITMAP, 22, 19, 
				LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE); 
				CBitmap pattern;
				CBitmap* p=pattern.FromHandle(hBitmap);
				m_ImageList.Add(p,RGB(255,255,255));
				iCount++;

				while ( FindNextFile(hSearchHandle,&wfd) ) {
					// While we have more files...
				hBitmap = (HBITMAP)LoadImage(NULL, wfd.cFileName, IMAGE_BITMAP, 22, 19, 
				LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE); 
				p=pattern.FromHandle(hBitmap);
				m_ImageList.Add(p,RGB(255,255,255));

				if(iCount>iToolbarButtonCount) break;
				iCount++;
				} // while

				// Close our search handle
				FindClose(hSearchHandle);
				CMacroManager mac;
				mac.LoadandRunScript(strPath);

			} // if
			  
			 (pAddinToolbar->GetToolBarCtrl()).SetImageList(&m_ImageList);
		      strPath=CString(szCurrentDir);
		}

		pAddinToolbar->EnableDocking(CBRS_ALIGN_ANY);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(pAddinToolbar);
		m_pAddinToolbarArray.Add(pAddinToolbar); 
		delete [] piTollbarCommandsID;

	}

	return TRUE;

}
*/
CMenu* CMainFrame::FindMenu(CMenu *pMenu, CString strMenuString)
{
	int iMenuCount=pMenu->GetMenuItemCount(); 
	CMenu* pSubMenu=NULL;
	for(int iMenuIndex=0;iMenuIndex<iMenuCount;iMenuIndex++)
	{
		CString strSubMenuString;
		int iPos=pMenu->GetMenuString(iMenuIndex,strSubMenuString,MF_BYPOSITION);
		if(strSubMenuString==strMenuString)
		{
			pSubMenu=pMenu->GetSubMenu(iMenuIndex); 
			return pSubMenu;
		}
	}
	return pSubMenu;
}

/*-------------------------------------------- Function Header ---------------------------------------------*
	Function Name	  : CMainFrame::AddAccelerator
	Description	      : 
	Return Type	      : BOOL 
	Warning           : 
  Argument          : UINT iCommandID
  Argument          : CString strAccel
------------------------------------------------------------------------------------------------------------*/

BOOL CMainFrame::AddAccelerator(UINT iCommandID, CString strAccel)
{
		
	CString strBeforePlus="";
	CString strAfterPlus="";
	CString strShortcut=strAccel;
	for(int i=0;i<strShortcut.GetLength();i++)
	{
		if(strShortcut[i]=='+')
		{
			strBeforePlus=strAfterPlus;
			strAfterPlus="";
		}
		else
		{
			strAfterPlus+=strShortcut[i];
		}
	}
	//Process the Virtual key First
	ACCEL Accel;

	if(strBeforePlus=="Ctrl")
	{
		Accel.fVirt=FCONTROL|FVIRTKEY;
	}
	else if(strBeforePlus=="Alt")
	{
		Accel.fVirt=FALT|FVIRTKEY;		
	}
	else if(strBeforePlus=="Shift")
	{
		Accel.fVirt=FSHIFT|FVIRTKEY;	
	}
	if(strAfterPlus.GetLength()>0)
	{
		Accel.key=strAfterPlus.GetAt(0);
	}
	Accel.cmd=iCommandID;
	m_AcceleratorArray.Add(Accel);

	return TRUE;

}

BOOL CMainFrame::RemoveCommands(UINT iCommand)
{
	try
	{
		//Remove the Menu	
		CMenu* pParentMenu=GetMenu();
		for(UINT i=0;i<pParentMenu->GetMenuItemCount();i++)
		{
			CMenu* pSubMenu=pParentMenu->GetSubMenu(i);
			pSubMenu->RemoveMenu(iCommand,MF_BYCOMMAND);

		}
		//Remove the toolbar
		m_wndToolBar.GetToolBarCtrl().SetState(iCommand,TBSTATE_HIDDEN); 

		for(int j=0;j<m_pAddinToolbarArray.GetSize();j++)
		{
			m_pAddinToolbarArray[j]->GetToolBarCtrl().SetState(iCommand,TBSTATE_HIDDEN); 
		}
		//Remove the accelerator associated with that
		
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

/*void CMainFrame::OnToolsMacroNew() 
{
	// TODO: Add your command handler code here
	// Bring up the new macro dialog
	CNewMacroDlg dlgNewMacro;

	if ( dlgNewMacro.DoModal() == IDOK ) {
		// Refill the combo box
		FillMacroBox();

		// Ask if they want to run the macro now
		if ( AfxMessageBox("Run macro now?",MB_YESNO|MB_ICONQUESTION) == IDYES ) {
			// Run the macro
			RunMacro(dlgNewMacro.m_strText);
		} // if
	} // if
}

void CMainFrame::OnToolsMacroEdit() 
{
	// TODO: Add your command handler code here
	// Determine which macro to edit
	CFileMacroDlg dlgFileMacro;

	if ( dlgFileMacro.DoModal() == IDCANCEL ) {
		// User canceled
		return;
	} // if

	// Edit that macro
	CEditMacroDlg dlgEditMacro;
	dlgEditMacro.m_strMacroName = dlgFileMacro.m_strMacroName;
	
	if ( dlgEditMacro.DoModal() == IDOK ) {
		// Ask if they want to run the macro now
		if ( AfxMessageBox("Run macro now?",MB_YESNO|MB_ICONQUESTION) == IDYES ) {
			// Run the macro
			RunMacro(dlgEditMacro.m_strText);
		} // if
	} // if
	
}

void CMainFrame::OnToolsMacroRun() 
{
	// TODO: Add your command handler code here
	// Determine which macro to run
	CRunMacroDlg dlgRunMacro;

	if ( dlgRunMacro.DoModal() == IDOK ) {
		// Run their macro
		RunMacro(dlgRunMacro.m_strText);
	} // if
	
}
void CMainFrame::FillMacroBox() 
{
	// Clear any existing data
	m_wndMacro.ResetContent();

	// Find all files in the current directory with the
	// macro file extension, ".mac".
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	CString strFile = strPath + "*.mac";
	WIN32_FIND_DATA wfd;
	HANDLE hSearchHandle = FindFirstFile(strFile,&wfd);
	if ( hSearchHandle != INVALID_HANDLE_VALUE ) {
		// Pull first filename
		CString strFileTitle(wfd.cFileName);
		strFileTitle = strFileTitle.Left(strFileTitle.Find("."));
		int iItem = m_wndMacro.AddString(strFileTitle);

		while ( FindNextFile(hSearchHandle,&wfd) ) {
			// While we have more files...
			strFileTitle = wfd.cFileName;
			strFileTitle = strFileTitle.Left(strFileTitle.Find("."));
			m_wndMacro.AddString(strFileTitle);
		} // while

		// Close our search handle
		FindClose(hSearchHandle);
	} // if

	// Make sure no macro files are selected...
	m_wndMacro.SetCurSel(-1);
}

void CMainFrame::RunMacro(LPCTSTR strText)
{
	try {
		// The script is passed in, which we convert to a 
		// BSTR, then feed to the parser.
		bstr_t bstrScript(strText);
		bstr_t bstrScript1("");
		if ( FAILED(m_pScriptObject->ParseScript(bstrScript,bstrScript1)) ) {
			// Throw some trash to hit the catch block
			throw "trash";
		} // if

	} // try
	catch (...) {
		// Some error...could be invalid script text, or
		// could be something else.  In any case, it didn't
		// run...
		AfxMessageBox("Error running script",MB_OK|MB_ICONERROR);
	} // catch
}

void CMainFrame::LoadMacro(const CString& strMacroName, CString& strMacroText)
{
	// Rebuild the macro filename
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	ASSERT(strMacroName.GetLength());
	CString strFile;
	strFile = strPath + strMacroName + ".mac";

	// Load the file
	try {
		CFile fileMacro(strFile,CFile::modeRead|CFile::shareDenyWrite);

		// Determine the file's length
		DWORD dwSize = fileMacro.GetLength();

		// Read the file
		fileMacro.Read(strMacroText.GetBuffer(dwSize),dwSize);
		strMacroText.ReleaseBuffer();

		// Close it
		fileMacro.Close();
	} // try
	catch (CFileException* e) {
		// File I/O error
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						e->m_cause,
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("File error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
	} // catch
	catch (...) {
		// Some other error...
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("Error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
	} // catch
}
*/
void CMainFrame::InitObjects()
{
	CCadDoc* p=(CCadDoc*)GetActiveDocument();
	HRESULT hr;

	try {
		hr = m_pScriptObject->AddObject(bstr_t("document"),p->GetIDispatch(TRUE));
//		hr = m_pScriptObject->AddObject(bstr_t("canvas"),p->GetCanvas());
		COleDispatchDriver d,d1,d2;
        LPDISPATCH result,source,in;
		
		d.AttachDispatch(p->GetIDispatch(FALSE));
		in=d;

		d.GetProperty(0x1,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("Window"),result);
	
		d.GetProperty(0x2,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("canvas"),result);
		
		d.GetProperty(0x3,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("utils"),result);

		d.DetachDispatch();

		d.AttachDispatch(in);
		d.GetProperty(0x1,VT_DISPATCH, (void*)&result);
		d.DetachDispatch();
		d.AttachDispatch(result);
		d.GetProperty(0x2,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("camera"),result);
		d.DetachDispatch();

		d.AttachDispatch(in);
		d.GetProperty(0x2,VT_DISPATCH, (void*)&result);
		d.DetachDispatch();
		d.AttachDispatch(result);

		d.GetProperty(0x1,VT_DISPATCH, (void*)&result);
		LPDISPATCH drawing=result;
		hr = m_pScriptObject->AddObject(bstr_t("drawing"),result);
		d.GetProperty(0x2,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("edit"),result);
		d.GetProperty(0x3,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("transform"),result);
		d.GetProperty(0x4,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("surface"),result);
		d.GetProperty(0x5,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("shape"),result);
		d.DetachDispatch();

		d.AttachDispatch(in);
		d.GetProperty(0x3,VT_DISPATCH, (void*)&result);
		d.DetachDispatch();
		d.AttachDispatch(result);

		d.GetProperty(0x1,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("vector"),result);
		d.GetProperty(0x2,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("collection"),result);
		d.DetachDispatch();

		d.AttachDispatch(drawing);
		d.GetProperty(0x1,VT_DISPATCH, (void*)&result);
		hr = m_pScriptObject->AddObject(bstr_t("drawingcollection"),result);
		d.DetachDispatch();

		d.ReleaseDispatch();


	} // try
	catch (...) {
//		AfxMessageBox("Unable to add the text selection object",MB_OK|MB_ICONERROR);
		hr = E_FAIL;
	} // catch

}


BOOL CMainFrame::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::OnChildNotify(message, wParam, lParam, pLResult);
}
