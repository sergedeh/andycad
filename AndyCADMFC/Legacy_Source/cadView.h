// cadView.h : interface of the CCadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CADVIEW_H__C49EB8A6_277B_40AA_8989_C8B9656FE71D__INCLUDED_)
#define AFX_CADVIEW_H__C49EB8A6_277B_40AA_8989_C8B9656FE71D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<vector>
//#include "Ruler1.h"	// Added by ClassView
//#include "SubWnd.h"	// Added by ClassView
#include "mouse.h"
#include "CPapersize.h"
#include "CVector.h"
#include "CSubject.h"
#include "Snap.h"	// Added by ClassView

//#include "Ctext.h"
//#include "LineProp.h"

using namespace std;

class CCadDoc;
class CFigure;
class CMainFrame;
class CCadView : public CScrollView,public CSubject,public CObserver 
{
protected: // create from serialization only
	CCadView();
	CPoint ptsPrevEnd;      // previous endpoint 
	BOOL fPrevLine;
	HCURSOR m_hCur;
	UINT TMF;
//	CCText m_edlg;
	DECLARE_DYNCREATE(CCadView)
	

//grace`
/*int m_nSelIndexBgn;
int m_nSelIndexEnd;
CString m_szText;
int m_nCaretIndex;*/
// Attributes
public:
	CCadDoc* GetDocument();
	CBitmap* getBitmap(); 
	void OnChangeColor(COLORREF lc,COLORREF bc);
	CBitmap* bmp;
	CBitmap *oldbmp;
	CString strcurrPath;
//	HDRAWDIB hdd;

	//grace
	/*void RedrawCaret();
    void CreateNewCaret(BOOL);*/


// Operations
public:
	void OnDrawP(CDC*pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL IsSelected(const CObject* pDocItem) const;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDC* getHdc();
	CRect getClientRect();
	void SendNotify(CString s, void *param[]);
	CBitmap* getRegion(CRect r);
	void Close(CFigure* f);
	void Select(CFigure* f,bool full=false);
	bool getInit();
	void OnChangeTexture(CString s);
	void update();
	void Unfill();
	CPoint getpos();
	void draglib(CString&  f, CString& l,CPoint point);
	void OnPageSetup2(float paper_width,float paper_height); 
	void libupdate();
	void import(int fileindex,CStdioFile &file);
	void import(int fileindex,CFile &file);
	void Save(int fileindex,CStdioFile &file);
	void Save(int fileindex, CFile &file);
	void Open(int fileindex,CFile &file);
	BOOL m_bpastenow;
	UINT m_Dimselected;
	UINT m_grouped;
	UINT m_snapon;
	UINT m_currentbtn;
	UINT  m_undo;
	bool change;
	bool bmpchange;
	double xRes,yRes;
	bool isPrint;
//	CRuler m_hruler,m_vruler;
	
	virtual ~CCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	BOOL m_bGrid;
	COLORREF m_gridColor;
	BOOL m_bActive; // is the view active?
protected:
	UINT  m_bBtnSelected;

// Generated message map functions
protected:
	BOOL KeyScroll(UINT nChar);
	//{{AFX_MSG(CCadView)
	afx_msg void OnLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCercle();
	afx_msg void OnRectangle();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTbselect();
	afx_msg void OnTbrotate();
	afx_msg void OnTbmirror();
	afx_msg void OnTaddnode();
	afx_msg void OnTdeletenode();
	afx_msg void OnTclosecurve();
	afx_msg void OnText();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEffectZoomin();
	afx_msg void OnRectanglefree();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCopyline();
	afx_msg void OnAngcopy();
	afx_msg void OnCopyral();
	afx_msg void OnCopybycenter();
	afx_msg void OnAlignbyline();
	afx_msg void On2cercle();
	afx_msg void On3cercle();
	afx_msg void OnPolyb();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSqline();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnArc();
	afx_msg void On3arcclose();
	afx_msg void On3arcopen();
	afx_msg void OnBpercent();
	afx_msg void OnFitpage();
	afx_msg void OnNpage();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnGroup();
	afx_msg void OnGroupup();
	afx_msg void OnDiml();
	afx_msg void OnDimA();
	afx_msg void OnDimho();
	afx_msg void OnDimvert();
	afx_msg void OnDim1free();
	afx_msg void OnDimcdia();
	afx_msg void OnIntersetpt();
	afx_msg void OnSnapctr();
	afx_msg void OnSnapmidpoint();
	afx_msg void OnSnapnear();
	afx_msg void OnSnapoff();
	afx_msg void OnSnappen();
	afx_msg void OnSnapquad();
	afx_msg void OnSnaptan();
	afx_msg void OnSnap();
	afx_msg void OnSnapendpoint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDialogFont();
	afx_msg void OnSendtofront();
	afx_msg void OnSendtobackgrd();
	afx_msg void OnSendforward();
	afx_msg void OnEclipse();
	afx_msg void OnSendbackward();
	afx_msg void OnSlide();
	afx_msg void OnPerp();
	afx_msg void OnToolsPaper();
	afx_msg void OnFlih();
	afx_msg void OnFilpvert();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroupup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendbackward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendforward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendtobackgrd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendtofront(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSlide(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimho(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDiml(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimrad(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimtxt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimvert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimcdia(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDimA(CCmdUI* pCmdUI);
	afx_msg void OnRecarraycopy();
	afx_msg void OnMirrornocopy();
	afx_msg void OnUpdateDim1free(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTbselect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTgline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTbmirror(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSqline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectanglefree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2cercle(CCmdUI* pCmdUI);
	afx_msg void OnUpdate3arcclose(CCmdUI* pCmdUI);
	afx_msg void OnUpdate3arcopen(CCmdUI* pCmdUI);
	afx_msg void OnUpdate3cercle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCercle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopyral(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEclipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePerp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTaddnode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTbrotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTdeletenode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTclosecurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePolyb(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMirrornocopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAngcopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopybycenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilpvert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlih(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecarraycopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopyline(CCmdUI* pCmdUI);
	afx_msg void OnPageSetup();
	afx_msg void OnDash();
	afx_msg void OnDot();
	afx_msg void OnDoubledot();
	afx_msg void OnLinewidthCustom();
	afx_msg void OnLinewidthNormal();
	afx_msg void OnLinewidthThick();
	afx_msg void OnLinewidthThin();
	afx_msg void OnEeeSolid();
	afx_msg void OnBl();
	afx_msg void OnToolCustom();
	afx_msg void OnToolOption();
	afx_msg void OnEffectZoomout();
	afx_msg void OnDashDot();
	afx_msg void OnDashdotdot();
	afx_msg void OnToolsLcolor();
	afx_msg void OnUpdateSnapctr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnapendpoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnapmidpoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnapnear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnapoff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnappen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnapquad(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnaptan(CCmdUI* pCmdUI);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnChamfer();
	afx_msg void OnUpdateChamfer(CCmdUI* pCmdUI);
	afx_msg void OnFillet();
	afx_msg void OnUpdateFillet(CCmdUI* pCmdUI);
	afx_msg void OnDimlv();
	afx_msg void OnUpdateDimlv(CCmdUI* pCmdUI);
	afx_msg void OnDimlh();
	afx_msg void OnUpdateDimlh(CCmdUI* pCmdUI);
	afx_msg void OnCopylinenocopy();
	afx_msg void OnUpdateCopylinenocopy(CCmdUI* pCmdUI);
	afx_msg void OnOffset();
	afx_msg void OnUpdateOffset(CCmdUI* pCmdUI);
	afx_msg void OnTrim();
	afx_msg void OnUpdateTrim(CCmdUI* pCmdUI);
	afx_msg void OnEditAlayer();
	afx_msg void OnImage();
	afx_msg void OnUpdateImage(CCmdUI* pCmdUI);
	afx_msg void OnEditDel();
	afx_msg void OnHelpRegistration();
	afx_msg void OnHelpWwwandycadcom();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnTblib();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSnapon();
	afx_msg void OnUpdateSnapon(CCmdUI* pCmdUI);
	afx_msg void OnCampad();
	afx_msg void OnUpdateCampad(CCmdUI* pCmdUI);
	afx_msg void OnCamrot();
	afx_msg void OnUpdateCamrot(CCmdUI* pCmdUI);
	afx_msg void OnSurfa();
	afx_msg void OnUpdateSurfa(CCmdUI* pCmdUI);
	afx_msg void OnTdegp();
	afx_msg void OnUpdateTdegp(CCmdUI* pCmdUI);
	afx_msg void Onsurfrev();
	afx_msg void OnUpdatesurfrev(CCmdUI* pCmdUI);
	afx_msg void Onsurfext();
	afx_msg void OnUpdatesurfext(CCmdUI* pCmdUI);
	afx_msg void Onsurfcoon();
	afx_msg void OnUpdatesurfcoon(CCmdUI* pCmdUI);
	afx_msg void OnVol();
	afx_msg void OnUpdateVol(CCmdUI* pCmdUI);
	afx_msg void OnButton40142();
	afx_msg void OnPtselect();
	afx_msg void OnUpdatePtselect(CCmdUI* pCmdUI);
	afx_msg void OnFreecamera();
	afx_msg void OnUpdateFreecamera(CCmdUI* pCmdUI);
	afx_msg void OnFrontview();
	afx_msg void OnUpdateFrontview(CCmdUI* pCmdUI);
	afx_msg void OnBackview();
	afx_msg void OnUpdateBackview(CCmdUI* pCmdUI);
	afx_msg void OnLeftview();
	afx_msg void OnUpdateLeftview(CCmdUI* pCmdUI);
	afx_msg void OnNortheast();
	afx_msg void OnUpdateNortheast(CCmdUI* pCmdUI);
	afx_msg void OnNorthwestview();
	afx_msg void OnUpdateNorthwestview(CCmdUI* pCmdUI);
	afx_msg void OnRightview();
	afx_msg void OnUpdateRightview(CCmdUI* pCmdUI);
	afx_msg void OnShape2dwired();
	afx_msg void OnUpdateShape2dwired(CCmdUI* pCmdUI);
	afx_msg void OnShape3dwire();
	afx_msg void OnUpdateShape3dwire(CCmdUI* pCmdUI);
	afx_msg void OnShapeflat();
	afx_msg void OnUpdateShapeflat(CCmdUI* pCmdUI);
	afx_msg void OnShapeflatedgeon();
	afx_msg void OnUpdateShapeflatedgeon(CCmdUI* pCmdUI);
	afx_msg void OnShapegourand();
	afx_msg void OnUpdateShapegourand(CCmdUI* pCmdUI);
	afx_msg void OnShapegourandedgeon();
	afx_msg void OnUpdateShapegourandedgeon(CCmdUI* pCmdUI);
	afx_msg void OnSolidbox();
	afx_msg void OnUpdateSolidbox(CCmdUI* pCmdUI);
	afx_msg void OnSolidcone();
	afx_msg void OnUpdateSolidcone(CCmdUI* pCmdUI);
	afx_msg void OnSolidcylinder();
	afx_msg void OnUpdateSolidcylinder(CCmdUI* pCmdUI);
	afx_msg void OnSolidrorus();
	afx_msg void OnUpdateSolidrorus(CCmdUI* pCmdUI);
	afx_msg void OnSolidshpere();
	afx_msg void OnUpdateSolidshpere(CCmdUI* pCmdUI);
	afx_msg void OnSolidwedge();
	afx_msg void OnUpdateSolidwedge(CCmdUI* pCmdUI);
	afx_msg void OnSoutheastview();
	afx_msg void OnUpdateSoutheastview(CCmdUI* pCmdUI);
	afx_msg void OnSouthwestview();
	afx_msg void OnUpdateSouthwestview(CCmdUI* pCmdUI);
	afx_msg void OnSurafce2dsolid();
	afx_msg void OnUpdateSurafce2dsolid(CCmdUI* pCmdUI);
	afx_msg void OnSurface3d();
	afx_msg void OnUpdateSurface3d(CCmdUI* pCmdUI);
	afx_msg void OnSurface3dmesh();
	afx_msg void OnUpdateSurface3dmesh(CCmdUI* pCmdUI);
	afx_msg void OnSurfacebox();
	afx_msg void OnUpdateSurfacebox(CCmdUI* pCmdUI);
	afx_msg void OnSurfacecone();
	afx_msg void OnUpdateSurfacecone(CCmdUI* pCmdUI);
	afx_msg void OnSurfacedish();
	afx_msg void OnUpdateSurfacedish(CCmdUI* pCmdUI);
	afx_msg void OnSurfacedome();
	afx_msg void OnUpdateSurfacedome(CCmdUI* pCmdUI);
	afx_msg void OnSurfaceedge();
	afx_msg void OnUpdateSurfaceedge(CCmdUI* pCmdUI);
	afx_msg void OnSurfacerevolved();
	afx_msg void OnUpdateSurfacerevolved(CCmdUI* pCmdUI);
	afx_msg void OnSurfaceruled();
	afx_msg void OnUpdateSurfaceruled(CCmdUI* pCmdUI);
	afx_msg void OnSurfacesphere();
	afx_msg void OnUpdateSurfacesphere(CCmdUI* pCmdUI);
	afx_msg void OnSurfacespyramid();
	afx_msg void OnUpdateSurfacespyramid(CCmdUI* pCmdUI);
	afx_msg void OnSurfacetabulated();
	afx_msg void OnUpdateSurfacetabulated(CCmdUI* pCmdUI);
	afx_msg void OnSurfacetorus();
	afx_msg void OnUpdateSurfacetorus(CCmdUI* pCmdUI);
	afx_msg void OnSurfacewedge();
	afx_msg void OnUpdateSurfacewedge(CCmdUI* pCmdUI);
	afx_msg void OnBottomview();
	afx_msg void OnUpdateBottomview(CCmdUI* pCmdUI);
	afx_msg void OnCamerarotation();
	afx_msg void OnUpdateCamerarotation(CCmdUI* pCmdUI);
	afx_msg void OnBucketfill();
	afx_msg void OnUpdateBucketfill(CCmdUI* pCmdUI);
	afx_msg void OnTopview();
	afx_msg void OnUpdateTopview(CCmdUI* pCmdUI);
	afx_msg void OnTransparency();
	afx_msg void OnUpdateTransparency(CCmdUI* pCmdUI);
	afx_msg void OnToolsGrid();
	afx_msg void OnUpdateToolsGrid(CCmdUI* pCmdUI);
	afx_msg void OnRender();
	afx_msg void OnUpdateRender(CCmdUI* pCmdUI);
	afx_msg void OnRenderprefer();
	afx_msg void OnUpdateRenderprefer(CCmdUI* pCmdUI);
	afx_msg void OnLight();
	afx_msg void OnUpdateLight(CCmdUI* pCmdUI);
	afx_msg void OnFog();
	afx_msg void OnUpdateFog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpWwwandycadcom(CCmdUI* pCmdUI);
	afx_msg void OnHelpFinder();
	afx_msg void OnUpdateHelpFinder(CCmdUI* pCmdUI);
	afx_msg void OnDrawArcstartcenterend();
	afx_msg void OnUpdateDrawArcstartcenterend(CCmdUI* pCmdUI);
	afx_msg void OnSnapfront();
	afx_msg void OnUpdateSnapfront(CCmdUI* pCmdUI);
	afx_msg void OnSnapleft();
	afx_msg void OnUpdateSnapleft(CCmdUI* pCmdUI);
	afx_msg void OnSnaptop();
	afx_msg void OnUpdateSnaptop(CCmdUI* pCmdUI);
	afx_msg void OnTransform2Ffd();
	afx_msg void OnTransform3Ffd();
	afx_msg void OnTransform4Ffd();
	afx_msg void OnUpdateTransform2Ffd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransform3Ffd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransform4Ffd(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawBox();
	afx_msg void OnEditSmooth();
	afx_msg void OnEditLight();
	afx_msg void OnEditCamera();
	afx_msg void OnUpdateEditCamera(CCmdUI* pCmdUI);
	afx_msg void OnEditClear();
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSmooth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEeeSolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectZoomout(CCmdUI* pCmdUI);
	afx_msg void OnModifyFloodfill();
	afx_msg void OnUpdateModifyFloodfill(CCmdUI* pCmdUI);
	afx_msg void OnGeometry();
	afx_msg void OnUpdateGeometry(CCmdUI* pCmdUI);
	afx_msg void OnTbscale();
	afx_msg void OnUpdateTbscale(CCmdUI* pCmdUI);
	afx_msg void OnModifySurfacecap();
	afx_msg void OnUpdateModifySurfacecap(CCmdUI* pCmdUI);
	afx_msg void Onsuftext2();
	afx_msg void OnUpdatesuftext2(CCmdUI* pCmdUI);
	afx_msg void Onsurfext3();
	afx_msg void OnModifyJoin();
	afx_msg void OnUpdateModifyJoin(CCmdUI* pCmdUI);
	afx_msg void OnCamswiv();
	afx_msg void OnUpdateCamswiv(CCmdUI* pCmdUI);
	afx_msg void OnProperties();
	afx_msg void OnUpdateProperties(CCmdUI* pCmdUI);
	afx_msg void OnViewPanDown();
	afx_msg void OnUpdateViewPanDown(CCmdUI* pCmdUI);
	afx_msg void OnViewPanLeft();
	afx_msg void OnUpdateViewPanLeft(CCmdUI* pCmdUI);
	afx_msg void OnViewPanRight();
	afx_msg void OnUpdateViewPanRight(CCmdUI* pCmdUI);
	afx_msg void OnViewPanUp();
	afx_msg void OnUpdateViewPanUp(CCmdUI* pCmdUI);
	afx_msg void OnDrawSolidSphere();
	afx_msg void OnDrawPlane();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDimrad();
	afx_msg void OnTbreakcurve();
	afx_msg void OnUpdateTbreakcurve(CCmdUI* pCmdUI);
	afx_msg void OnLeader();
	afx_msg void OnMultLine();
	afx_msg void OnModifyPointconstraint();
	afx_msg void OnModifyVectorconstraint();
	afx_msg void OnModifyHorizontalconstraint();
	afx_msg void OnModifyVerticalconstraint();
	afx_msg void OnModifyParallelconstraint();
	afx_msg void OnModifyPerpendicularconstraint();
	//}}AFX_MSG
	afx_msg void OnParaLeft();
	afx_msg void OnParaCenter();
	afx_msg void OnParaJustify();
	afx_msg void OnParaRight();
	afx_msg void OnUpdateParaRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaCenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaJustify(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateButtons(CCmdUI *pCmdUI);
//	afx_msg void OnDimButtons(UINT);
//	afx_msg void OnUpdateDimButtons(CCmdUI *pCmdUI);
	afx_msg void OnSnapButtons(UINT);
	afx_msg void OnUpdateSnapButtons(CCmdUI *pCmdUI);
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnFilePrintSetup();
	afx_msg void OnModifyClip();
	DECLARE_MESSAGE_MAP()
private:
	bool initOK;
	CSnap snap;
	LPVOID obmap[3];
	CDC* hmdc,*hdc;
	CPoint pos;
	bool pageset;
	bool selT;
	CSize currentPosdev;
	CSize currentPos;
	CSize maxscrollPos;
	CSize minscrollPos;
	CRect bn;
	SCROLLINFO *siv;
	SCROLLINFO *sih;
	CPoint pg;

//	CNStatusBar m_nstatusbar,m_nstatusbar1,m_nstatusbar2,m_scrb;
	int centy;
	int centx;
	CSize pagerec,screenrec;
	bool zoom;
	CRect inter,scr;
	double zoomrat;
	CSize zrec;
	bool isSaving;
//	CSubWnd m_wndsub;
	enum {Circle,Line,Rectangle,Rectanglefree,FreeLine,select,rotate,scale,\
		text,paraLeft,paraCenter,paraRight,paraJustify,alignbyline,circle2,circle3,\
		polyline,polybezier,sqline,arc,arc2,arc3,arc32,freecirc,paste,undo,redo,Dim1,DimL,\
		DimA,DimH,DimV,DimF,DimR,DimD,DimT,DimLH,DimLV,ellipse,perpline,tangline,not,\
		copyrec,copyang,copyanglin,copybycenter,copyline,copylinenocopy,fliph,flipv,\
		mirrornocopy,slide,mirror,notm,offset,chamf,filt,trim,C2L,image, campad,camsw,camrot,\
		spoint,fill,box,camset,sphere,plane,leader,multline,extend,clip,init} menu;
	enum {addnode,deletenode,breakcurve,closecurve,group,ungroup,sendbgr,sendfront,sendforward,sendbackward,\
		vectorconstraint,pointconstraint,nothing} submenu;
	enum {copy,cut,null} menu_edit;
	bool snap_menu;
	enum {zoomin,zoomout} zmode;
	enum {vectorconstraint_item,horizontal,vertical,perpendicular,parallel,collinear,\
		equal,angular} vectorconstraint_mode;
	enum {pointconstraint_item,coincident,fix,size_linear,aligned} pointconstraint_mode;
	enum {symmetric,concentric,size_radius,size_diameter} figureconstraint_mode;

	//enum {copyrec,copyang,copyanglin,copybycenter,copyline,fliph,flipv,mirrornocopy,slide,mirror,notm} menu_tran;
//	CCercle circle;
//	CRectangle rectangle;
	CMouse mouse;
	CPen pen;
	CBrush brush;
	CCPaperSize papersize;
	struct SCA
	{
		UINT map_mode;
		CString str;
		int unit,lprec,aprec; 
		float delta,wu,pu;
		CSize Sg;
		bool orient;
	}m_mode;
	
	protected:
		enum {front,back,top,bottom,left,right,ne,nw,sw,se} selectedview;
		enum {pfront,ptop,pleft} selectedplane;
		
};

#ifndef _DEBUG  // debug version in cadView.cpp
inline CCadDoc* CCadView::GetDocument()
   { return (CCadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADVIEW_H__C49EB8A6_277B_40AA_8989_C8B9656FE71D__INCLUDED_)
