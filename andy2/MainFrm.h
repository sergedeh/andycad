// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BED856F1_6AA0_4D3C_8999_1535C65F6E5C__INCLUDED_)
#define AFX_MAINFRM_H__BED856F1_6AA0_4D3C_8999_1535C65F6E5C__INCLUDED_

#include "ParseDlg.h"	// Added by ClassView
#include "Subwnd.h"	// Added by ClassView
//#include "NStatusBar.h"	// Added by ClassView
#include "Ruler1.h"	// Added by ClassView
#include "reccolor.h"
#include "colord.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<vector>
#include "ZoomD.h"	// Added by ClassView
#include "TextD.h"	// Added by ClassView
#include "pattern.h"
#include "Zoombar.h"
#include "splash.h"
#include "infobar.h"
#include "layerd.h"
#include "pattern.h"
#include "subject.h"
#include "cmoveandrotatebar.h"
//#include "Proppage.h"
//+
//#include "NstatusBar.h"
//#include "CLineSty.h"
//#include "LayBar.h"	// Added by ClassView
//#include "Linebar.h"
#include "Libdialog.h"	// Added by ClassView

#define TOOL_BAR				"Tool Bar"

#import "ScriptObject.tlb" no_namespace named_guids

using namespace std;


class CMainFrame : public CFrameWnd
{
	
public: // create from serialization only
	//void LoadMacro(const CString& strMacroName, CString& strMacroText);
	void RunMacro(LPCTSTR strText);
	BOOL RemoveCommands(UINT iCommand);
	bool PFMergeAccelerator(HACCEL& hDestination, HACCEL hToMerge);
	BOOL LoadAditionalAccelerators();
	CMainFrame();
	BOOL GetToolText(HWND toolHandle, UINT nID, CString& strTipText, CString& strMessage );
	//BOOL LoadAllAddinCommands();
	CMenu* FindMenu(CMenu *pMenu, CString strMenuString);
	BOOL AddAccelerator(UINT iCommandID, CString strAccel);
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CColorD colorToolBar;
	CPattern patternBar;
	CInfoBar m_wndMyDialogBar;
	CLibdialog m_wndlibdia;
	CLayerD m_wndlaydia;
//	cmoveandrotatebar m_wndmandrbar;

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitObjects();
	void setInterestObject(CSubject* s);
	int m_nDatePaneNo;
	int m_nTimePaneNo;
	CWnd m_button;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar, m_wndTxtBar;
	CToolBar    m_wndToolBar,m_wndToolBar1,m_wndToolBar2,m_wndToolBar3;
	CToolBar	m_cercToolBar,m_tbrotateToolBar,m_tbselectToolBar;
	CZoomBar    m_wndZoomBar;
//	CLineBar    m_wndlinestylBar;
	CToolBar    m_wndimensionBar,m_wndsnapingBar,m_wndsnapoptionsBar;
	CToolBar    m_wndsurface, m_wndshape, m_wnddefinedshape, m_wndcamera;
	CDialogBar m_wndMousePosition;
	CToolBar    m_wndtransfill,m_wndrender;
	CArray<ACCEL,ACCEL> m_AcceleratorArray;
	CArray<CToolBar*,CToolBar*> m_pAddinToolbarArray;
	
	CTextD text;
	CZoomD zoomwnd;
	CDialogBar m_wndDlgBar;



	CMenu pmenu;
//	CPropPage* m_pSheet;
	
   

	
	void GetClientR( LPRECT lpRect ) ;
	CRect initrec;
	vector<CPoint> ptbegin;
	vector<CPoint>::iterator it_ptbegin;

	int m_nViewWidth;   // Workspace width in pixels
    int m_nViewHeight;  // Workspace height in pixels
    int m_nHScrollPos;  // Horizontal scroll position
    int m_nVScrollPos;  // Vertical scroll position
    int m_nHPageSize;   // Horizontal page size
    int m_nVPageSize;   // Vertical page size


// Generated message map functions
protected:
	CParseDlg comd_dlg;
	
	void OnInitMenu(CMenu* pMenu);
	void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	void FillMacroBox();

	
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnCustomize();
	afx_msg void OnDimview();
	afx_msg void OnUpdateDimview(CCmdUI* pCmdUI);
	afx_msg void OnInfobarView();
	afx_msg void OnUpdateInfobarView(CCmdUI* pCmdUI);
	afx_msg void OnColorView();
	afx_msg void OnUpdateColorView(CCmdUI* pCmdUI);
	afx_msg void OnTransView();
	afx_msg void OnUpdateTransView(CCmdUI* pCmdUI);
	afx_msg void OnEditView();
	afx_msg void OnUpdateEditView(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarColorbar();
	afx_msg void OnUpdateViewToolbarColorbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarDimensionbar();
	afx_msg void OnUpdateViewToolbarDimensionbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarInformationbar();
	afx_msg void OnUpdateViewToolbarInformationbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarModifyingbar();
	afx_msg void OnUpdateViewToolbarModifyingbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarStandardbar();
	afx_msg void OnUpdateViewToolbarStandardbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarTransformationbar();
	afx_msg void OnUpdateViewToolbarTransformationbar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarZoombar();
	afx_msg void OnUpdateViewToolbarZoombar(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarDrawingbar();
	afx_msg void OnUpdateViewToolbarDrawingbar(CCmdUI* pCmdUI);
	afx_msg void OnHelpTipoftheday();
	afx_msg void OnViewToolbarShowtoolbars();
	afx_msg void OnViewToolbarHidetoolbars();
	afx_msg void OnUpdateViewToolbarHidetoolbars(CCmdUI* pCmdUI);
	afx_msg void OnHelpFinder();
	afx_msg void OnHelpRegistration();
	afx_msg void OnViewToolbarShowsnap();
	afx_msg void OnUpdateViewToolbarShowsnap(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarShowlay();
	afx_msg void OnUpdateViewToolbarShowlay(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarShowlibbar();
	afx_msg void OnUpdateViewToolbarShowlibbar(CCmdUI* pCmdUI);
	afx_msg void OnBegindragLibt1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditLayer();
	afx_msg void OnUpdateEditLayer(CCmdUI* pCmdUI);
	afx_msg void OnLibrary();
	afx_msg void OnUpdateLibrary(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarTextbar();
	afx_msg void OnUpdateViewToolbarTextbar(CCmdUI* pCmdUI);
	afx_msg void OnToolsToolbarsPatterntexturebar();
	afx_msg void OnUpdateToolsToolbarsPatterntexturebar(CCmdUI* pCmdUI);
	afx_msg void OnToolsToolbarsCreatesurfacebar();
	afx_msg void OnUpdateToolsToolbarsCreatesurfacebar(CCmdUI* pCmdUI);
	afx_msg void OnToolsToolbarsViewbar();
	afx_msg void OnUpdateToolsToolbarsViewbar(CCmdUI* pCmdUI);
	afx_msg void OnToolsToolbarsSmoothinglightbar();
	afx_msg void OnUpdateToolsToolbarsSmoothinglightbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnSubMenu( NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnAddinMenuItems(UINT iCommandID);
	afx_msg void OnUpdateAddinMenuItems(CCmdUI* pCmdUI);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewToolbarShowcmdbar();
	afx_msg void OnUpdateViewToolbarShowcmdbar(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
private:
	bool menuinfo;
	bool menucol;
	bool menutrans;
	bool menuedit;
	bool menuzoom;
	bool menudrw;
	bool menutext;
	bool menustd;
	bool menuhide;
	bool menushow;
	bool menustat;
	bool menusnp;
	bool menulay;
	bool menupat;
	bool menucerc;
	bool menucmd;
//	CLayBar laybar;
	UINT m_nStatusPane1ID;
	UINT m_nStatusPane1Style;
	INT  m_nStatusPane1Width;
	BOOL m_bMenuSelect;
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
//	CRuler m_vruler;
//	CRuler m_hruler;
	CPoint whvar;
//	CNStatusBar m_prop;//,m_nstatusbar1,m_nstatusbar2,m_scrb;
//	CRuler m_ruler;
//	CSubWnd m_subwnd;
	bool menudim,menulib;
	bool menucam,menusurf; 
	bool menultb;
 	CComboBox   m_wndMacro;
	IScriptObjectPtr m_pScriptObject;
	CImageList m_ImageList;

//	IAppObjectPtr	m_pAppObject;


};	

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BED856F1_6AA0_4D3C_8999_1535C65F6E5C__INCLUDED_)
