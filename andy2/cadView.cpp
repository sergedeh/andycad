// cadView.cpp : implementation of the CCadView class
//

#include "stdafx.h"
#include "cad.h"

#include <afxinet.h>
#include <afx.h>
#include <stdio.h>

#include "cadView.h"
#include "cadDoc.h"
#include "mainfrm.h"
#include "customwidth.h"
#include "objedit.h"
//#include "pgrid.h"
#include "Cpapersize.h"
#include "numcopy.h"
#include "arrayangle.h"
//#include "customsheet.h"
#include "paperpag.h"
#include "gridpag.h"
//#include "newtext.h"
#include "RecArray.h"
#include "ChamfD.h"
#include "TransDlg.h"
#include "observer.h"
#include "thickd.h"
#include "smoothd.h"
#include "lightd.h"
#include "cameradlg.h"
#include "dlgcap.h"
#include "textdi.h"
#include "SnapGridDlg.h"
#include "SnapObjectDlg.h"
#include "PolarTrackDlg.h"
#include "SnapDlg.h"

#include "register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HINT_DELCHAR_AFTER 100
#define HINT_DELCHAR_BEFORE 101
#define HINT_DELETE_SELECTION 102
#define HINT_PASTE 103
#define HINT_SELECTION 104
#define HINT_UNSELECTION 105
#define HINT_INPUT 106


/////////////////////////////////////////////////////////////////////////////
// CCadView

IMPLEMENT_DYNCREATE(CCadView, CScrollView)

BEGIN_MESSAGE_MAP(CCadView, CScrollView)
	//{{AFX_MSG_MAP(CCadView)
	ON_COMMAND(ID_LINE, OnLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CERCLE, OnCercle)
	ON_COMMAND(ID_RECTANGLE, OnRectangle)
	ON_WM_SIZE()
	ON_COMMAND(ID_TBSELECT, OnTbselect)
	ON_COMMAND(ID_TBROTATE, OnTbrotate)
	ON_COMMAND(ID_TBMIRROR, OnTbmirror)
	ON_COMMAND(ID_Taddnode, OnTaddnode)
	ON_COMMAND(ID_Tdeletenode, OnTdeletenode)
	ON_COMMAND(ID_Tclosecurve, OnTclosecurve)
	ON_COMMAND(ID_Text, OnText)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EFFECT_ZOOMIN, OnEffectZoomin)
	ON_COMMAND(ID_RECTANGLEFREE, OnRectanglefree)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_COMMAND(ID_COPYLINE, OnCopyline)
	ON_COMMAND(ID_ANGCOPY, OnAngcopy)
	ON_COMMAND(ID_COPYRAL, OnCopyral)
	ON_COMMAND(ID_COPYBYCENTER, OnCopybycenter)
	ON_COMMAND(ID_ALIGNBYLINE, OnAlignbyline)
	ON_COMMAND(ID_2CERCLE, On2cercle)
	ON_COMMAND(ID_3CERCLE, On3cercle)
	ON_COMMAND(ID_POLYB, OnPolyb)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_SQLINE, OnSqline)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ARC, OnArc)
	ON_COMMAND(ID_3ARCCLOSE, On3arcclose)
	ON_COMMAND(ID_3ARCOPEN, On3arcopen)
	ON_COMMAND(ID_BPERCENT, OnBpercent)
	ON_COMMAND(ID_FITPAGE, OnFitpage)
	ON_COMMAND(ID_NPAGE, OnNpage)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_GROUP, OnGroup)
	ON_COMMAND(ID_GROUPUP, OnGroupup)
	ON_COMMAND(ID_DIML, OnDiml)
	ON_COMMAND(ID_DimA, OnDimA)
	ON_COMMAND(ID_DIMHO, OnDimho)
	ON_COMMAND(ID_DIMVERT, OnDimvert)
	ON_COMMAND(ID_DIM1FREE, OnDim1free)
	ON_COMMAND(ID_DIMCDIA, OnDimcdia)
	ON_COMMAND(ID_INTERSETPT, OnIntersetpt)
	ON_COMMAND(ID_SNAPCTR, OnSnapctr)
	ON_COMMAND(ID_SNAPMIDPOINT, OnSnapmidpoint)
	ON_COMMAND(ID_SNAPNEAR, OnSnapnear)
	ON_COMMAND(ID_SNAPOFF, OnSnapoff)
	ON_COMMAND(ID_SNAPPEN, OnSnappen)
	ON_COMMAND(ID_SNAPQUAD, OnSnapquad)
	ON_COMMAND(ID_SNAPTAN, OnSnaptan)
	ON_COMMAND(ID_TOOLS_SNAP, OnSnap)
	ON_COMMAND(ID_SNAPENDPOINT, OnSnapendpoint)
	ON_WM_CHAR()
	ON_COMMAND(ID_DIALOG_FONT, OnDialogFont)
	ON_COMMAND(ID_SENDTOFRONT, OnSendtofront)
	ON_COMMAND(ID_SENDTOBACKGRD, OnSendtobackgrd)
	ON_COMMAND(ID_SENDFORWARD, OnSendforward)
	ON_COMMAND(ID_ECLIPSE, OnEclipse)
	ON_COMMAND(ID_SENDBACKWARD, OnSendbackward)
	ON_COMMAND(ID_SLIDE, OnSlide)
	ON_COMMAND(ID_PERP, OnPerp)
	ON_COMMAND(ID_TOOLS_PAPER, OnToolsPaper)
	ON_COMMAND(ID_FLIH, OnFlih)
	ON_COMMAND(ID_FILPVERT, OnFilpvert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_GROUP, OnUpdateGroup)
	ON_UPDATE_COMMAND_UI(ID_GROUPUP, OnUpdateGroupup)
	ON_UPDATE_COMMAND_UI(ID_SENDBACKWARD, OnUpdateSendbackward)
	ON_UPDATE_COMMAND_UI(ID_SENDFORWARD, OnUpdateSendforward)
	ON_UPDATE_COMMAND_UI(ID_SENDTOBACKGRD, OnUpdateSendtobackgrd)
	ON_UPDATE_COMMAND_UI(ID_SENDTOFRONT, OnUpdateSendtofront)
	ON_UPDATE_COMMAND_UI(ID_SLIDE, OnUpdateSlide)
	ON_UPDATE_COMMAND_UI(ID_DIMHO, OnUpdateDimho)
	ON_UPDATE_COMMAND_UI(ID_DIML, OnUpdateDiml)
	ON_UPDATE_COMMAND_UI(ID_DIMRAD, OnUpdateDimrad)
	ON_UPDATE_COMMAND_UI(ID_DIMTXT, OnUpdateDimtxt)
	ON_UPDATE_COMMAND_UI(ID_DIMVERT, OnUpdateDimvert)
	ON_UPDATE_COMMAND_UI(ID_DIMCDIA, OnUpdateDimcdia)
	ON_UPDATE_COMMAND_UI(ID_DimA, OnUpdateDimA)
	ON_COMMAND(ID_RECARRAYCOPY, OnRecarraycopy)
	ON_COMMAND(ID_MIRRORNOCOPY, OnMirrornocopy)
	ON_UPDATE_COMMAND_UI(ID_DIM1FREE, OnUpdateDim1free)
	ON_UPDATE_COMMAND_UI(ID_TBSELECT, OnUpdateTbselect)
	ON_UPDATE_COMMAND_UI(ID_Text, OnUpdateText)
	ON_UPDATE_COMMAND_UI(ID_TGLINE, OnUpdateTgline)
	ON_UPDATE_COMMAND_UI(ID_TBMIRROR, OnUpdateTbmirror)
	ON_UPDATE_COMMAND_UI(ID_SQLINE, OnUpdateSqline)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLEFREE, OnUpdateRectanglefree)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_2CERCLE, OnUpdate2cercle)
	ON_UPDATE_COMMAND_UI(ID_3ARCCLOSE, OnUpdate3arcclose)
	ON_UPDATE_COMMAND_UI(ID_3ARCOPEN, OnUpdate3arcopen)
	ON_UPDATE_COMMAND_UI(ID_3CERCLE, OnUpdate3cercle)
	ON_UPDATE_COMMAND_UI(ID_CERCLE, OnUpdateCercle)
	ON_UPDATE_COMMAND_UI(ID_COPYRAL, OnUpdateCopyral)
	ON_UPDATE_COMMAND_UI(ID_ECLIPSE, OnUpdateEclipse)
	ON_UPDATE_COMMAND_UI(ID_PERP, OnUpdatePerp)
	ON_UPDATE_COMMAND_UI(ID_Taddnode, OnUpdateTaddnode)
	ON_UPDATE_COMMAND_UI(ID_TBROTATE, OnUpdateTbrotate)
	ON_UPDATE_COMMAND_UI(ID_Tdeletenode, OnUpdateTdeletenode)
	ON_UPDATE_COMMAND_UI(ID_Tclosecurve, OnUpdateTclosecurve)
	ON_UPDATE_COMMAND_UI(ID_POLYB, OnUpdatePolyb)
	ON_UPDATE_COMMAND_UI(ID_ARC, OnUpdateArc)
	ON_UPDATE_COMMAND_UI(ID_MIRRORNOCOPY, OnUpdateMirrornocopy)
	ON_UPDATE_COMMAND_UI(ID_ANGCOPY, OnUpdateAngcopy)
	ON_UPDATE_COMMAND_UI(ID_COPYBYCENTER, OnUpdateCopybycenter)
	ON_UPDATE_COMMAND_UI(ID_FILPVERT, OnUpdateFilpvert)
	ON_UPDATE_COMMAND_UI(ID_FLIH, OnUpdateFlih)
	ON_UPDATE_COMMAND_UI(ID_RECARRAYCOPY, OnUpdateRecarraycopy)
	ON_UPDATE_COMMAND_UI(ID_COPYLINE, OnUpdateCopyline)
	ON_COMMAND(ID_PAGE_SETUP, OnPageSetup)
	ON_COMMAND(ID__DASH, OnDash)
	ON_COMMAND(ID__DOT, OnDot)
	ON_COMMAND(ID__DOUBLEDOT, OnDoubledot)
	ON_COMMAND(ID__LINEWIDTH_CUSTOM, OnLinewidthCustom)
	ON_COMMAND(ID__LINEWIDTH_NORMAL, OnLinewidthNormal)
	ON_COMMAND(ID__LINEWIDTH_THICK, OnLinewidthThick)
	ON_COMMAND(ID__LINEWIDTH_THIN, OnLinewidthThin)
	ON_COMMAND(ID_EEE_SOLID, OnEeeSolid)
	ON_COMMAND(ID_BL, OnBl)
	ON_COMMAND(ID_TOOL_CUSTOM, OnToolCustom)
	ON_COMMAND(ID_TOOL_OPTION, OnToolOption)
	ON_COMMAND(ID_EFFECT_ZOOMOUT, OnEffectZoomout)
	ON_COMMAND(ID_DASH_DOT, OnDashDot)
	ON_COMMAND(ID_DASHDOTDOT, OnDashdotdot)
	ON_COMMAND(ID_TOOLS_LCOLOR, OnToolsLcolor)
	ON_UPDATE_COMMAND_UI(ID_SNAPCTR, OnUpdateSnapctr)
	ON_UPDATE_COMMAND_UI(ID_SNAPENDPOINT, OnUpdateSnapendpoint)
	ON_UPDATE_COMMAND_UI(ID_SNAPMIDPOINT, OnUpdateSnapmidpoint)
	ON_UPDATE_COMMAND_UI(ID_SNAPNEAR, OnUpdateSnapnear)
	ON_UPDATE_COMMAND_UI(ID_SNAPOFF, OnUpdateSnapoff)
	ON_UPDATE_COMMAND_UI(ID_SNAPPEN, OnUpdateSnappen)
	ON_UPDATE_COMMAND_UI(ID_SNAPQUAD, OnUpdateSnapquad)
	ON_UPDATE_COMMAND_UI(ID_SNAPTAN, OnUpdateSnaptan)
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_CHAMFER, OnChamfer)
	ON_UPDATE_COMMAND_UI(ID_CHAMFER, OnUpdateChamfer)
	ON_COMMAND(ID_FILLET, OnFillet)
	ON_UPDATE_COMMAND_UI(ID_FILLET, OnUpdateFillet)
	ON_COMMAND(ID_DIMLV, OnDimlv)
	ON_UPDATE_COMMAND_UI(ID_DIMLV, OnUpdateDimlv)
	ON_COMMAND(ID_DIMLH, OnDimlh)
	ON_UPDATE_COMMAND_UI(ID_DIMLH, OnUpdateDimlh)
	ON_COMMAND(ID_COPYLINENOCOPY, OnCopylinenocopy)
	ON_UPDATE_COMMAND_UI(ID_COPYLINENOCOPY, OnUpdateCopylinenocopy)
	ON_COMMAND(ID_OFFSET, OnOffset)
	ON_UPDATE_COMMAND_UI(ID_OFFSET, OnUpdateOffset)
	ON_COMMAND(ID_TRIM, OnTrim)
	ON_UPDATE_COMMAND_UI(ID_TRIM, OnUpdateTrim)
	ON_COMMAND(ID_EDIT_ALAYER, OnEditAlayer)
	ON_COMMAND(ID_IMAGE, OnImage)
	ON_UPDATE_COMMAND_UI(ID_IMAGE, OnUpdateImage)
	ON_COMMAND(ID_EDIT_DEL, OnEditDel)
	ON_COMMAND(ID_HELP_REGISTRATION, OnHelpRegistration)
	ON_COMMAND(ID_HELP_WWWANDYCADCOM, OnHelpWwwandycadcom)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_TBLIB, OnTblib)
	ON_WM_TIMER()
	ON_COMMAND(ID_SNAPON, OnSnapon)
	ON_UPDATE_COMMAND_UI(ID_SNAPON, OnUpdateSnapon)
	ON_COMMAND(ID_CAMPAD, OnCampad)
	ON_UPDATE_COMMAND_UI(ID_CAMPAD, OnUpdateCampad)
	ON_COMMAND(ID_CAMROT, OnCamrot)
	ON_UPDATE_COMMAND_UI(ID_CAMROT, OnUpdateCamrot)
	ON_COMMAND(ID_Surfa, OnSurfa)
	ON_UPDATE_COMMAND_UI(ID_Surfa, OnUpdateSurfa)
	ON_COMMAND(ID_TDEGP, OnTdegp)
	ON_UPDATE_COMMAND_UI(ID_TDEGP, OnUpdateTdegp)
	ON_COMMAND(ID_surfrev, Onsurfrev)
	ON_UPDATE_COMMAND_UI(ID_surfrev, OnUpdatesurfrev)
	ON_COMMAND(ID_surfext, Onsurfext)
	ON_UPDATE_COMMAND_UI(ID_surfext, OnUpdatesurfext)
	ON_COMMAND(ID_surfcoon, Onsurfcoon)
	ON_UPDATE_COMMAND_UI(ID_surfcoon, OnUpdatesurfcoon)
	ON_COMMAND(ID_VOL, OnVol)
	ON_UPDATE_COMMAND_UI(ID_VOL, OnUpdateVol)
	ON_COMMAND(ID_BUTTON40142, OnButton40142)
	ON_COMMAND(ID_PTSELECT, OnPtselect)
	ON_UPDATE_COMMAND_UI(ID_PTSELECT, OnUpdatePtselect)
	ON_COMMAND(ID_FREECAMERA, OnFreecamera)
	ON_UPDATE_COMMAND_UI(ID_FREECAMERA, OnUpdateFreecamera)
	ON_COMMAND(ID_FRONTVIEW, OnFrontview)
	ON_UPDATE_COMMAND_UI(ID_FRONTVIEW, OnUpdateFrontview)
	ON_COMMAND(ID_BACKVIEW, OnBackview)
	ON_UPDATE_COMMAND_UI(ID_BACKVIEW, OnUpdateBackview)
	ON_COMMAND(ID_LEFTVIEW, OnLeftview)
	ON_UPDATE_COMMAND_UI(ID_LEFTVIEW, OnUpdateLeftview)
	ON_COMMAND(ID_NORTHEAST, OnNortheast)
	ON_UPDATE_COMMAND_UI(ID_NORTHEAST, OnUpdateNortheast)
	ON_COMMAND(ID_NORTHWESTVIEW, OnNorthwestview)
	ON_UPDATE_COMMAND_UI(ID_NORTHWESTVIEW, OnUpdateNorthwestview)
	ON_COMMAND(ID_RIGHTVIEW, OnRightview)
	ON_UPDATE_COMMAND_UI(ID_RIGHTVIEW, OnUpdateRightview)
	ON_COMMAND(ID_SHAPE2DWIRED, OnShape2dwired)
	ON_UPDATE_COMMAND_UI(ID_SHAPE2DWIRED, OnUpdateShape2dwired)
	ON_COMMAND(ID_SHAPE3DWIRE, OnShape3dwire)
	ON_UPDATE_COMMAND_UI(ID_SHAPE3DWIRE, OnUpdateShape3dwire)
	ON_COMMAND(ID_SHAPEFLAT, OnShapeflat)
	ON_UPDATE_COMMAND_UI(ID_SHAPEFLAT, OnUpdateShapeflat)
	ON_COMMAND(ID_SHAPEFLATEDGEON, OnShapeflatedgeon)
	ON_UPDATE_COMMAND_UI(ID_SHAPEFLATEDGEON, OnUpdateShapeflatedgeon)
	ON_COMMAND(ID_SHAPEGOURAND, OnShapegourand)
	ON_UPDATE_COMMAND_UI(ID_SHAPEGOURAND, OnUpdateShapegourand)
	ON_COMMAND(ID_SHAPEGOURANDEDGEON, OnShapegourandedgeon)
	ON_UPDATE_COMMAND_UI(ID_SHAPEGOURANDEDGEON, OnUpdateShapegourandedgeon)
	ON_COMMAND(ID_SOLIDBOX, OnSolidbox)
	ON_UPDATE_COMMAND_UI(ID_SOLIDBOX, OnUpdateSolidbox)
	ON_COMMAND(ID_SOLIDCONE, OnSolidcone)
	ON_UPDATE_COMMAND_UI(ID_SOLIDCONE, OnUpdateSolidcone)
	ON_COMMAND(ID_SOLIDCYLINDER, OnSolidcylinder)
	ON_UPDATE_COMMAND_UI(ID_SOLIDCYLINDER, OnUpdateSolidcylinder)
	ON_COMMAND(ID_SOLIDRORUS, OnSolidrorus)
	ON_UPDATE_COMMAND_UI(ID_SOLIDRORUS, OnUpdateSolidrorus)
	ON_COMMAND(ID_SOLIDSHPERE, OnSolidshpere)
	ON_UPDATE_COMMAND_UI(ID_SOLIDSHPERE, OnUpdateSolidshpere)
	ON_COMMAND(ID_SOLIDWEDGE, OnSolidwedge)
	ON_UPDATE_COMMAND_UI(ID_SOLIDWEDGE, OnUpdateSolidwedge)
	ON_COMMAND(ID_SOUTHEASTVIEW, OnSoutheastview)
	ON_UPDATE_COMMAND_UI(ID_SOUTHEASTVIEW, OnUpdateSoutheastview)
	ON_COMMAND(ID_SOUTHWESTVIEW, OnSouthwestview)
	ON_UPDATE_COMMAND_UI(ID_SOUTHWESTVIEW, OnUpdateSouthwestview)
	ON_COMMAND(ID_SURAFCE2DSOLID, OnSurafce2dsolid)
	ON_UPDATE_COMMAND_UI(ID_SURAFCE2DSOLID, OnUpdateSurafce2dsolid)
	ON_COMMAND(ID_SURFACE3D, OnSurface3d)
	ON_UPDATE_COMMAND_UI(ID_SURFACE3D, OnUpdateSurface3d)
	ON_COMMAND(ID_SURFACE3DMESH, OnSurface3dmesh)
	ON_UPDATE_COMMAND_UI(ID_SURFACE3DMESH, OnUpdateSurface3dmesh)
	ON_COMMAND(ID_SURFACEBOX, OnSurfacebox)
	ON_UPDATE_COMMAND_UI(ID_SURFACEBOX, OnUpdateSurfacebox)
	ON_COMMAND(ID_SURFACECONE, OnSurfacecone)
	ON_UPDATE_COMMAND_UI(ID_SURFACECONE, OnUpdateSurfacecone)
	ON_COMMAND(ID_SURFACEDISH, OnSurfacedish)
	ON_UPDATE_COMMAND_UI(ID_SURFACEDISH, OnUpdateSurfacedish)
	ON_COMMAND(ID_SURFACEDOME, OnSurfacedome)
	ON_UPDATE_COMMAND_UI(ID_SURFACEDOME, OnUpdateSurfacedome)
	ON_COMMAND(ID_SURFACEEDGE, OnSurfaceedge)
	ON_UPDATE_COMMAND_UI(ID_SURFACEEDGE, OnUpdateSurfaceedge)
	ON_COMMAND(ID_SURFACEREVOLVED, OnSurfacerevolved)
	ON_UPDATE_COMMAND_UI(ID_SURFACEREVOLVED, OnUpdateSurfacerevolved)
	ON_COMMAND(ID_SURFACERULED, OnSurfaceruled)
	ON_UPDATE_COMMAND_UI(ID_SURFACERULED, OnUpdateSurfaceruled)
	ON_COMMAND(ID_SURFACESPHERE, OnSurfacesphere)
	ON_UPDATE_COMMAND_UI(ID_SURFACESPHERE, OnUpdateSurfacesphere)
	ON_COMMAND(ID_SURFACESPYRAMID, OnSurfacespyramid)
	ON_UPDATE_COMMAND_UI(ID_SURFACESPYRAMID, OnUpdateSurfacespyramid)
	ON_COMMAND(ID_SURFACETABULATED, OnSurfacetabulated)
	ON_UPDATE_COMMAND_UI(ID_SURFACETABULATED, OnUpdateSurfacetabulated)
	ON_COMMAND(ID_SURFACETORUS, OnSurfacetorus)
	ON_UPDATE_COMMAND_UI(ID_SURFACETORUS, OnUpdateSurfacetorus)
	ON_COMMAND(ID_SURFACEWEDGE, OnSurfacewedge)
	ON_UPDATE_COMMAND_UI(ID_SURFACEWEDGE, OnUpdateSurfacewedge)
	ON_COMMAND(ID_BOTTOMVIEW, OnBottomview)
	ON_UPDATE_COMMAND_UI(ID_BOTTOMVIEW, OnUpdateBottomview)
	ON_COMMAND(ID_CAMERAROTATION, OnCamerarotation)
	ON_UPDATE_COMMAND_UI(ID_CAMERAROTATION, OnUpdateCamerarotation)
	ON_COMMAND(ID_BUCKETFILL, OnBucketfill)
	ON_UPDATE_COMMAND_UI(ID_BUCKETFILL, OnUpdateBucketfill)
	ON_COMMAND(ID_TOPVIEW, OnTopview)
	ON_UPDATE_COMMAND_UI(ID_TOPVIEW, OnUpdateTopview)
	ON_COMMAND(ID_TRANSPARENCY, OnTransparency)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENCY, OnUpdateTransparency)
	ON_COMMAND(ID_TOOLS_GRID, OnToolsGrid)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_GRID, OnUpdateToolsGrid)
	ON_COMMAND(ID_RENDER, OnRender)
	ON_UPDATE_COMMAND_UI(ID_RENDER, OnUpdateRender)
	ON_COMMAND(ID_RENDERPREFER, OnRenderprefer)
	ON_UPDATE_COMMAND_UI(ID_RENDERPREFER, OnUpdateRenderprefer)
	ON_COMMAND(ID_LIGHT, OnLight)
	ON_UPDATE_COMMAND_UI(ID_LIGHT, OnUpdateLight)
	ON_COMMAND(ID_FOG, OnFog)
	ON_UPDATE_COMMAND_UI(ID_FOG, OnUpdateFog)
	ON_UPDATE_COMMAND_UI(ID_HELP_WWWANDYCADCOM, OnUpdateHelpWwwandycadcom)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_HELP_FINDER, OnUpdateHelpFinder)
	ON_COMMAND(ID_DRAW_ARCSTARTCENTEREND, OnDrawArcstartcenterend)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ARCSTARTCENTEREND, OnUpdateDrawArcstartcenterend)
	ON_COMMAND(ID_SNAPFRONT, OnSnapfront)
	ON_UPDATE_COMMAND_UI(ID_SNAPFRONT, OnUpdateSnapfront)
	ON_COMMAND(ID_SNAPLEFT, OnSnapleft)
	ON_UPDATE_COMMAND_UI(ID_SNAPLEFT, OnUpdateSnapleft)
	ON_COMMAND(ID_SNAPTOP, OnSnaptop)
	ON_UPDATE_COMMAND_UI(ID_SNAPTOP, OnUpdateSnaptop)
	ON_COMMAND(ID_TRANSFORM_FFD_2X2X2, OnTransform2Ffd)
	ON_COMMAND(ID_TRANSFORM_FFD_3X3X3, OnTransform3Ffd)
	ON_COMMAND(ID_TRANSFORM_FFD_4X4X4, OnTransform4Ffd)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_FFD_2X2X2, OnUpdateTransform2Ffd)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_FFD_3X3X3, OnUpdateTransform3Ffd)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_FFD_4X4X4, OnUpdateTransform4Ffd)
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_BOX, OnDrawBox)
	ON_COMMAND(ID_EDIT_SMOOTH, OnEditSmooth)
	ON_COMMAND(ID_EDIT_LIGHT, OnEditLight)
	ON_COMMAND(ID_EDIT_CAMERA, OnEditCamera)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CAMERA, OnUpdateEditCamera)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DEL, OnUpdateEditDel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LIGHT, OnUpdateEditLight)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SMOOTH, OnUpdateEditSmooth)
	ON_UPDATE_COMMAND_UI(ID_EEE_SOLID, OnUpdateEeeSolid)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_ZOOMIN, OnUpdateEffectZoomin)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_ZOOMOUT, OnUpdateEffectZoomout)
	ON_COMMAND(ID_MODIFY_FLOODFILL, OnModifyFloodfill)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_FLOODFILL, OnUpdateModifyFloodfill)
	ON_COMMAND(ID_GEOMETRY, OnGeometry)
	ON_UPDATE_COMMAND_UI(ID_GEOMETRY, OnUpdateGeometry)
	ON_COMMAND(ID_TBSCALE, OnTbscale)
	ON_UPDATE_COMMAND_UI(ID_TBSCALE, OnUpdateTbscale)
	ON_COMMAND(ID_MODIFY_SURFACECAP, OnModifySurfacecap)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_SURFACECAP, OnUpdateModifySurfacecap)
	ON_COMMAND(ID_suftext2, Onsuftext2)
	ON_UPDATE_COMMAND_UI(ID_suftext2, OnUpdatesuftext2)
	ON_COMMAND(ID_surfext3, Onsurfext3)
	ON_COMMAND(ID_MODIFY_JOIN, OnModifyJoin)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_JOIN, OnUpdateModifyJoin)
	ON_COMMAND(ID_CAMSWIV, OnCamswiv)
	ON_UPDATE_COMMAND_UI(ID_CAMSWIV, OnUpdateCamswiv)
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES, OnUpdateProperties)
	ON_COMMAND(ID_VIEW_PAN_DOWN, OnViewPanDown)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAN_DOWN, OnUpdateViewPanDown)
	ON_COMMAND(ID_VIEW_PAN_LEFT, OnViewPanLeft)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAN_LEFT, OnUpdateViewPanLeft)
	ON_COMMAND(ID_VIEW_PAN_RIGHT, OnViewPanRight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAN_RIGHT, OnUpdateViewPanRight)
	ON_COMMAND(ID_VIEW_PAN_UP, OnViewPanUp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAN_UP, OnUpdateViewPanUp)
	ON_COMMAND(ID_DRAW_SOLID_SPHERE, OnDrawSolidSphere)
	ON_COMMAND(ID_DRAW_PLANE, OnDrawPlane)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_DIMRAD, OnDimrad)
	ON_COMMAND(ID_Tbreakcurve, OnTbreakcurve)
	ON_UPDATE_COMMAND_UI(ID_Tbreakcurve, OnUpdateTbreakcurve)
	ON_COMMAND(ID_DIMENSION_LEADER, OnLeader)
	ON_COMMAND(ID_DRAW_MULTILINE, OnMultLine)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_MODIFY_POINTCONSTRAINT, OnModifyPointconstraint)
	ON_COMMAND(ID_MODIFY_VECTORCONSTRAINT, OnModifyVectorconstraint)
	ON_COMMAND(ID_MODIFY_CONSTRAINTSEGMENTS_VERTICAL, OnModifyVerticalconstraint)
	ON_COMMAND(ID_MODIFY_CONSTRAINTLINES_HORIZONTAL, OnModifyHorizontalconstraint)
	ON_COMMAND(ID_MODIFY_CONSTRAINTLINES_PARALLEL, OnModifyParallelconstraint)
	ON_COMMAND(ID_MODIFY_CONSTRAINTLINES_PERPENDICULAR, OnModifyPerpendicularconstraint)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
	// contigous toolbar commands
//	ON_COMMAND_RANGE(ID_RECTANGLE,ID_SQLINE,OnButtons)
//	ON_UPDATE_COMMAND_UI_RANGE(ID_RECTANGLE,ID_SQLINE,OnUpdateButtons)
	ON_COMMAND_RANGE(ID_SNAPON,ID_SNAPOFF,OnSnapButtons)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SNAPON,ID_SNAPOFF,OnUpdateSnapButtons)
//	ON_COMMAND_RANGE(ID_DIMHO,ID_DIMTXT,OnDimButtons)
//	ON_UPDATE_COMMAND_UI_RANGE(ID_DIMHO,ID_DIMTXT,OnUpdateDimButtons)
	//Paragraph alignment	
	ON_COMMAND(ID_BUTTONLEFT, OnParaLeft)
	ON_COMMAND(ID_BUTTONRIGHT, OnParaRight)
	ON_COMMAND(ID_BUTTONCENTER, OnParaCenter)
	ON_COMMAND(ID_BUTTONJUST, OnParaJustify)
	ON_UPDATE_COMMAND_UI(ID_BUTTONLEFT, OnUpdateParaLeft)
	ON_UPDATE_COMMAND_UI(ID_BUTTONRIGHT, OnUpdateParaRight)
	ON_UPDATE_COMMAND_UI(ID_BUTTONCENTER, OnUpdateParaCenter)
	ON_UPDATE_COMMAND_UI(ID_BUTTONJUST, OnUpdateParaJustify)
	ON_COMMAND(ID_MODIFY_CLIPSHAPE, OnModifyClip)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadView construction/destruction
CCadView* pv;
CLightD lightdlg;
CCameraDlg camdlg;

CCadView::CCadView()
{
	strcurrPath=_T("");
	hmdc=NULL;
	zoomrat=1;
	inter.SetRectEmpty();
	centx=0;
	centy=0;
	siv=new SCROLLINFO;
	sih=new SCROLLINFO;
	zoom=false;
	isPrint=false;

	fPrevLine = FALSE;
	pen.CreatePen(PS_SOLID,1,RGB(12,12,250));
	selT=false;
	m_bpastenow =false;
	m_currentbtn;
	selectedview =front;
	selectedplane=pfront;
	m_bBtnSelected;
	m_Dimselected;
	m_snapon=false;
	m_grouped = false;
	pageset=false;
	snap_menu=false;
	m_mode.map_mode=MM_LOMETRIC;
	m_mode.str="inch";
	m_mode.delta=1;
	m_mode.aprec=0;
	m_mode.lprec=0;
	m_mode.pu=1;
	m_mode.wu=1;
	m_mode.unit=1;

	m_mode.Sg=CSize(850,-1100);
	m_mode.orient=false;
	change=true;
	bmp=new CBitmap;
	isSaving=false;
	initOK=false;
	bmpchange=false;
 
	
}

CCadView::~CCadView()
{
	delete hmdc;
	delete siv;
	delete sih;
	delete bmp;

}

BOOL CCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_OWNDC|CS_VREDRAW,0,(HBRUSH)LTGRAY_BRUSH,0);
	cs.style|=CS_OWNDC; 
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCadView drawing

void CCadView::OnDrawP(CDC*pDC)
{
	BITMAP bm;
	bmp->GetBitmap(&bm);
	
	DWORD d=bm.bmWidth*bm.bmHeight*4;
	BYTE* bits=new BYTE[d];
	memset(bits,0,d);
	BITMAPINFO bitinfo1;
	
	BITMAPINFOHEADER bitinfo;

	bitinfo.biSize=sizeof(BITMAPINFOHEADER);
	bitinfo.biWidth=bm.bmWidth;
	bitinfo.biHeight=bm.bmHeight;
	bitinfo.biPlanes = 1;
	bitinfo.biBitCount = 32;
	bitinfo.biCompression = BI_RGB;
    bitinfo.biXPelsPerMeter = 0;
    bitinfo.biYPelsPerMeter = 0;
    bitinfo.biClrUsed       = 0;
    bitinfo.biClrImportant  = 0;

	bitinfo1.bmiHeader=bitinfo;

	GetDIBits(pDC->GetSafeHdc(),(HBITMAP)bmp->GetSafeHandle(),0,-bm.bmHeight,NULL,&bitinfo1,DIB_RGB_COLORS);
	int o=GetDIBits(pDC->GetSafeHdc(),(HBITMAP)bmp->GetSafeHandle(),0,bm.bmHeight,(LPVOID)bits,&bitinfo1,DIB_RGB_COLORS);
	int v=GetLastError();

//	DrawDibBegin(hdd, pDC->GetSafeHdc(), bm.bmWidth, bm.bmHeight, &bitinfo1.bmiHeader, bm.bmWidth,bm.bmHeight, NULL); 
//	bool l=DrawDibDraw(hdd,pDC->GetSafeHdc(),0,0,bm.bmWidth,bm.bmHeight,&bitinfo1.bmiHeader,bits,0,0,bm.bmWidth,bm.bmHeight,DDF_SAME_DRAW|DDF_SAME_HDC);
	delete []bits;
}

void CCadView::OnDraw(CDC*pDC)
{
	pv=this;
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

//	pDC->SelectPalette(&mg->colorToolBar.palette,FALSE);
//	pDC->RealizePalette();

	CCadDoc* pDoc = GetDocument();

	if(!pDC->IsPrinting())
	{
//	pDC->SetViewportOrg(CPoint(0,0));
//	pDC->SetWindowOrg(CPoint(0,0));
	OnPrepareDC(pDC);
	if(hmdc==NULL)
	{
		hmdc=new CDC;
		hmdc->CreateCompatibleDC(pDC);
	}
	
	
	CRect wcr;
	GetClientRect(&wcr);
	pDC->DPtoLP(&wcr);
	
//	CRect R(CPoint(0,0),CSize(CSize(GetTotalSize().cx,-GetTotalSize().cy)));//=pDoc->m_objects->getgrid(CSize(GetTotalSize().cx,-GetTotalSize().cy));		
	
	CRect bn;
	wcr.NormalizeRect();
//	R.NormalizeRect();
//	bn.UnionRect(&wcr,&R);
	bn=wcr;


	if(change)
	{
	oldbmp=hmdc->SelectObject(bmp);
	}
	OnPrepareDC(hmdc);	
//	hmdc->SetMapMode(pDC->GetMapMode());
//	hmdc->SetViewportOrg(CPoint(0,0));
//	hmdc->SetWindowOrg(CPoint(0,0));
	CRect p(0,0,bn.Size().cx,-bn.Size().cy);
	
	if(change)
	{
		if(!isSaving)
		{
		HBRUSH br=(HBRUSH)SelectObject(hmdc->GetSafeHdc(),GetStockObject(WHITE_BRUSH));
		HPEN pe=(HPEN)SelectObject(hmdc->GetSafeHdc(),GetStockObject(WHITE_PEN));
	//	hmdc->Rectangle(p);
		SelectObject(hmdc->GetSafeHdc(),br);
		SelectObject(hmdc->GetSafeHdc(),pe);
		p=pDoc->m_objects->grid(hmdc,hmdc,p.Size());//m_mode.Sg);		
		change=false;
		}else
		{
/*		CRect rall=pDoc->m_objects->getAllBox();		
		bmp2->Detach();
		CSize rss=rall.Size();
		bmp2->CreateCompatibleBitmap(pDC,rss.cx,-rss.cy);//uz.cx+10,-(uz.cy+10));
		oldbmp=hmdc->SelectObject(bmp);

		pDoc->m_objects->drawforbmp(hmdc);		
*/
		}
	if(p!=CRect(0,0,0,0)||bmpchange)
		pDC->BitBlt(0,0,bn.Size().cx,-bn.Size().cy,hmdc,0,0,SRCCOPY);
	bmpchange=false;
	BITMAP nb;
	int j=bmp->GetBitmap(&nb);//GetObject(jj,sizeof(BITMAP),NULL);
	}
	ReleaseDC(hmdc);
	ReleaseDC(pDC);

	}
	else
	{
// Use the printable region of the printer to determine  
// the margins.
	isPrint=true;
	int iXOrigin = GetDeviceCaps(pDC->GetSafeHdc(), PHYSICALOFFSETX);
	int iYOrigin = GetDeviceCaps(pDC->GetSafeHdc(), PHYSICALOFFSETY); 
	// Obtain info about printer resolution
	int xSize = /*pDC->GetDeviceCaps(PHYSICALWIDTH);//*/GetDeviceCaps(pDC->GetSafeHdc(), HORZRES);
	int ySize = GetDeviceCaps(pDC->GetSafeHdc(), VERTRES);
	xSize=pDC->GetDeviceCaps(PHYSICALWIDTH);
	ySize=pDC->GetDeviceCaps(PHYSICALHEIGHT);
	xRes  = (double)GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSX)/72;
	yRes  = (double)GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY)/72;
	CSize p1=pDC->GetViewportExt();
	CSize p2=pDC->GetWindowExt();
    
	OnPrepareDC(pDC);
	p1=pDC->GetViewportExt();
	p2=pDC->GetWindowExt();
//	p2.cx-=1;
//	p2.cy-=1;
//	pDoc->m_objects->setPrintPage(CRect(CPoint(0,0),p2),m_mode.delta);
		if(papersize.fit)
		{
			pDoc->m_objects->setPrintPage(CRect(CPoint(0,0),p2),1);
			m_mode.delta=pDoc->m_objects->getFitPrintRatio();
			pDoc->m_objects->setPrintPage(CRect(CPoint(0,0),p2),m_mode.delta);
			m_mode.pu=10;
			m_mode.wu=10*m_mode.delta;
		}

	xRes=(double)p1.cx/p2.cx;
	yRes=(double)p1.cy/p2.cy;
//	p1=pDC->GetWindowOrg();
//	CSize sz(m_mode.Sg.cx,-m_mode.Sg.cy),sz1;

//	if(bmp->GetSafeHandle!=NULL)
//	{
//		bmp->DeleteObject();
//	}
	CRect wcr;
	GetClientRect(&wcr);
	pDC->DPtoLP(&wcr);
	wcr.NormalizeRect();
//	CSize sz(wcr.Size().cx,wcr.Size().cy);
//	pDoc->m_objects->setpixel0(sz.cx,sz.cy);


	CPoint p00=pDoc->m_objects->PreparePrint();
	CRect g(p00,m_mode.Sg);
	int top2=g.top;
	g.top=g.bottom;
	g.bottom=top2;
	g.NormalizeRect();
	CRect r=pDoc->m_objects->getPrintPage();
//	CRect t2=pDoc->m_objects->getBox();
//	r.UnionRect(r,t2);
	CRect r2=r;
	int top1=r.top;
	r.top=r.bottom;
	r.bottom=top1;
	CRect rd=r;
	pDC->LPtoDP(&rd);
	rd.NormalizeRect();
	CSize rs=p1;//r.Size();
	CSize rs1=rd.Size();
	CSize gs=g.Size();
	CSize uz=CSize(p2.cx,-p2.cy);
	bmp->Detach();
	CSize rss=rs+uz;
	bmp->CreateCompatibleBitmap(pDC,xSize,ySize);//rss.cx,-rss.cy);//uz.cx+10,-(uz.cy+10));


	CDC* phmdc=new CDC;
	phmdc->CreateCompatibleDC(pDC);
	oldbmp=phmdc->SelectObject(bmp);
	OnPrepareDC(phmdc);

	CRect p=pDoc->m_objects->getPage();
	int top=p.top;
	p.top=p.bottom;
	p.bottom=top;
	CSize ps=p.Size();
	CRect pd=p;
	pDC->LPtoDP(&pd);
	CSize ps1=pd.Size();

	phmdc->SelectObject(GetStockObject(WHITE_BRUSH));
	r.NormalizeRect();
	CSize cc(xSize,ySize);
	phmdc->DPtoLP(&cc);
	phmdc->Rectangle(CRect(p00,CSize(cc.cx,-cc.cy)));
//	pDoc->m_objects->drawforbmp(phmdc);		
//	phmdc->SetWindowOrg(CPoint(p00.x,p00.y));
//	pDC->SetWindowOrg(CPoint(p00.x,p00.y));
//	int o=phmdc->SetMapMode(MM_TEXT);
	pDoc->m_objects->drawforbmp(phmdc);	
//	phmdc->SetMapMode(o);
	
//	phmdc->SetWindowOrg(CPoint(0,0));
//	pDoc->m_objects->drawforbmp(pDC);		
	DWORD d= ::GetLastError();
	pDoc->m_objects->endPrint();
	
//	pDC->LPtoDP(&rs);
	pDC->LPtoDP(&gs);
//	pDC->LPtoDP(&p00);
//	pDC->BitBlt(0,0,rss.cx,rss.cy,phmdc,0,0,SRCCOPY);
	pDC->StretchBlt(0,0,/*rss.cx,rss.cy*/cc.cx,-cc.cy,phmdc,p00.x,p00.y,/*rss.cx,rss.cy*/cc.cx,-cc.cy,SRCCOPY);
//	pDC->StretchBlt(0,0,xSize,-ySize,phmdc,0,0,rs.cx,rs.cy,SRCCOPY);
//	pDC->StretchBlt(0,0,wcr.Width(),-wcr.Height(),phmdc,0,0,wcr.Width(),-wcr.Height(),SRCCOPY);
	phmdc->SelectObject(oldbmp);
	delete phmdc;
	isPrint=false;
//    ::StretchDIBits(pDC->GetSafeHdc(),0,0,bm.bmWidth,bm.bmHeight,0,0,bm.bmWidth,bm.bmHeight,bits,&bitinfo1,DIB_RGB_COLORS,SRCCOPY);


	
	}
	change=false;
}
CBitmap* CCadView::getBitmap() 
{
	return bmp;
}
CRect CCadView::getClientRect()
{
	CRect wcr;
	GetWindowRect(&wcr);
	return wcr;
}
CDC* CCadView::getHdc()
{
	CDC* hdc;
	OnPrepareDC(hdc);
	return hdc;

}
/////////////////////////////////////////////////////////////////////////////
// CCadView printing

void CCadView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_objects->setPrintPage(pInfo->m_rectDraw,m_mode.delta);
//	pDoc->m_objects->setPrintPage(((CPreviewDC*)pDC)->m_sizeTopLeft+((CPreviewDC*)pDC)->m_sizeVpExt,m_mode.delta);
	pInfo->m_nNumPreviewPages=1;
	CScrollView::OnPrint(pDC, pInfo);
	
}

BOOL CCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing

}

void CCadView::OnEndPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

//	pDoc->m_objects->setCenter(pg);
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCadView diagnostics

#ifdef _DEBUG
void CCadView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCadView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCadDoc* CCadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCadDoc)));
	return (CCadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCadView message handlers

void CCadView::OnCercle() 
{
	menu=Circle;

	CString input,output;
	input="circle";
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDoc->m_parser->execute(input,output,NULL);

	void* pp[2];
	pp[0]=&input;
	pp[1]=&output;

//	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
//	{
//	(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
//	}
	
}
void CCadView::OnLine() 
{
	menu=Line;	
	CString input,output;
	input="line";
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDoc->m_parser->execute(input,output,NULL);

	void* pp[2];
	pp[0]=&input;
	pp[1]=&output;

//	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
//	{
//	(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
//	}

	
}

void CCadView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pos = point;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	OnPrepareDC(hdc);

    hdc->DPtoLP (&pos);
	CSize p1=hdc->GetViewportExt();

//	CCadApp::m_AddinManager.SendStatus("Hello");
	bool CTRL=false;
	if (nFlags==9) 
	{
		CTRL=true;
	}
		
	bool RH=false;
	if (nFlags==(UINT)MK_RBUTTON)
	{
		RH=true;
	}
	mouse.setMove(false);
	mouse.setLBdown(true);
	mouse.setPrevPos(pos);


	bool b=false;
			float u1,u2,u3;
			CString input,output;
			input="Command: ";
			pDoc->m_objects->getPoint(pos,u1,u2,u3,hdc);
 
            // Convert the cursor coordinates into a POINTS 
            // structure, which defines the beginning point of the 
            // line drawn during a WM_MOUSEMOVE message. 
			if ((menu==Line)||(menu==Circle)||(menu==Rectangle)||(menu==polybezier))
			{			
//			pDoc->m_objects->Create(hdc,"Line",pos);
			input.Format("<%f,%f,%f>",u1,u2,u3);
//			pDoc->m_parser->execute(input,output,NULL);
			void* pp[2];
			pp[0]=&input;
			pp[1]=&output;

			for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
			{
//			(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
			}
			b=true;
			} 
			if (menu==camset)
			{
				CVector v;
				v=pDoc->m_objects->getobject(hdc,pos);
				if(!camdlg.pv)
				{
				camdlg.m_xp=v.x;
				camdlg.m_yp=v.y;
				camdlg.m_zp=v.z;
				}else
				{
				camdlg.m_xt=v.x;
				camdlg.m_yt=v.y;
				camdlg.m_zt=v.z;
				}
				camdlg.updateviewpara();
			b=true;
			} else
			if (menu==box)
			{
/*				CPoint p1;
				CVector v1(0,0);
				CVector v2(0,-100);
				hdc->MoveTo(v1);
				p1=v2;
				hdc->LineTo(p1);
 				hdc->LPtoDP(&p1);
		        ClientToScreen(&p1); 

				::SetCursorPos(p1.x,p1.y);
*/	
			pDoc->m_objects->Create(hdc,CString("Box"),pos);
			b=true;
			} else
			if (menu==image)
			{			
			pDoc->m_objects->Create(hdc, CString("Image"),pos);
			b=true;
			} else
			if (menu==DimH)
			{			
			pDoc->m_objects->Create(hdc, CString("DimH"),pos);
			b=true;
			} else
			if (menu==leader)
			{			
			pDoc->m_objects->Create(hdc, CString("leader"),pos);
			b=true;
			} else
			if (menu==multline)
			{			
			pDoc->m_objects->Create(hdc, CString("multline"),pos);
			b=true;
			} else
			if (menu==DimV)
			{			
			pDoc->m_objects->Create(hdc, CString("DimV"),pos);
			b=true;
			} else
			if (menu==DimF)
			{			
			pDoc->m_objects->Create(hdc, CString("DimF"),pos);
			b=true;
			} else
			if (menu==DimL)
			{			
			pDoc->m_objects->Create(hdc, CString("DimL"),pos);
			b=true;
			} else
			if (menu==DimLH)
			{			
			pDoc->m_objects->Create(hdc, CString("DimLH"),pos);
			b=true;
			} else
			if (menu==DimLV)
			{			
			pDoc->m_objects->Create(hdc, CString("DimLV"),pos);
			b=true;
			} else
			if (menu==DimA)
			{			
			pDoc->m_objects->Create(hdc, CString("DimA"),pos);
			b=true;
			} else
			if (menu==chamf)
			{			
			pDoc->m_objects->Create(hdc, CString("Chamfer"),pos);
			change=true;
			Invalidate();
			} else
			if (menu==filt)
			{			
			pDoc->m_objects->Create(hdc, CString("Fillet"),pos);
			change=true;
			Invalidate();
			} else
			if (menu==C2L)
			{			
			pDoc->m_objects->Create(hdc, CString("2CLine"),pos);
			b=true;
			} else
			if (menu==sqline)
			{			
			pDoc->m_objects->Create(hdc, CString("QLine"),pos);
			b=true;
			
			} else
			if (menu==Line)
			{			
			pDoc->m_objects->Create(hdc, CString("Line"),pos);
			b=true;
			
			} else
			if (menu==perpline)
			{			
			pDoc->m_objects->Create(hdc, CString("QPLine"),pos);
			b=true;
			} else
			if (menu==tangline)
			{			
			pDoc->m_objects->Create(hdc, CString("QTLine"),pos);
			b=true;
			} else
			if (menu==polybezier)
			{			
			pDoc->m_objects->Create(hdc, CString("Bezier"),pos);
			b=true;
			
			} else
            if (menu==Circle)
			{			
			pDoc->m_objects->Create(hdc, CString("Circle"),pos);
			b=true;
			} else
			if ((menu==Rectangle)||(menu==Rectanglefree))
			{			
			pDoc->m_objects->Create(hdc, CString("Rectangle"),pos);//rectangle.setPtsBegin(point);
			b=true;
			} else
			if (menu==circle2)
			{
				pDoc->m_objects->Create(hdc, CString("2DotCircle"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==circle3)
			{
				pDoc->m_objects->Create(hdc, CString("3DotCircle"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==ellipse)
			{
				pDoc->m_objects->Create(hdc, CString("Ellipse"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==arc)
			{
				pDoc->m_objects->Create(hdc, CString("Arc"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==arc2)
			{
				pDoc->m_objects->Create(hdc, CString("2DotArc"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==arc3)
			{
				pDoc->m_objects->Create(hdc, CString("3DotArc"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==arc32)
			{
				pDoc->m_objects->Create(hdc, CString("3DotArc2"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==box)
			{
				pDoc->m_objects->Create(hdc, CString("Box"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==sphere)
			{
				pDoc->m_objects->Create(hdc, CString("Sphere"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			if (menu==plane)
			{
				pDoc->m_objects->Create(hdc, CString("Plane"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==text)
			{
				pDoc->m_objects->Create(hdc, CString("Text"),pos);//rectangle.setPtsBegin(point);
			b=true;
			}
			else
			if (menu==slide)
			{ 
				pDoc->m_objects->slide(hdc,pos);
				menu=select;
			b=true;
				
			}else 
			if (menu==DimD)
			{
				pDoc->m_objects->Create(hdc, CString("DimD"),pos);;
		//		menu=select;
				Invalidate();
			b=true;
				
			}else 
			if (menu==DimR)
			{
				pDoc->m_objects->Create(hdc, CString("DimR"),pos);;
		//		menu=select;
				change=true;
				Invalidate();
			b=true;
				
			}else 
			if (menu==select)
			{
				
				bool sel;
				
				if (submenu==closecurve)
				{
					selT=pDoc->m_objects->closecurve(pos,hdc);
				}else 
				{
				sel=pDoc->m_objects->select(false,CTRL,pos,hdc);
				b=false;
				if (sel==true)
				{
					pDoc->m_objects->displayselect(hdc);
				Invalidate();
//					pDoc->m_objects->forundo(hdc);
				b=true;
				
				}else
				{
					pDoc->m_objects->Create(hdc,"select",pos);//rectangle.setPtsBegin(point);
					b=true;
				}
				}
			}
			else 
			if(menu==spoint)
				{

				if (submenu==addnode)	
					{
				    selT=pDoc->m_objects->addnode(pos,hdc);
				
					} else
				if (submenu==deletenode)
				{
					selT=pDoc->m_objects->deletenode(pos,hdc);
				} else
				if (submenu==breakcurve)
				{
					if(pDoc->m_objects->breakcurve(pos))
						submenu=nothing;
				} else
				if (submenu==pointconstraint)
				{
					if(pDoc->m_objects->pointconstraint(pos))
						submenu=nothing;
				} else
				if (submenu==vectorconstraint)
				{
					if(vectorconstraint_mode==vectorconstraint_item)
					{
						if(pDoc->m_objects->vectorconstraint(pos))
							submenu=nothing;
					}else
					if(vectorconstraint_mode==horizontal)
					{
						if(pDoc->m_objects->vectorconstraint(pos,0))
							submenu=nothing;
					}else
					if(vectorconstraint_mode==vertical)
					{
						if(pDoc->m_objects->vectorconstraint(pos,1))
							submenu=nothing;
					}else
					if(vectorconstraint_mode==perpendicular)
					{
						if(pDoc->m_objects->vectorconstraint(pos,2))
							submenu=nothing;
					}else
					if(vectorconstraint_mode==parallel)
					{
						if(pDoc->m_objects->vectorconstraint(pos,3))
							submenu=nothing;
					}else
					if(vectorconstraint_mode==collinear)
					{
						if(pDoc->m_objects->vectorconstraint(pos,4))
							submenu=nothing;
					}

				} else
				{
				int sens=0;
				if(nFlags==(UINT)(MK_CONTROL|MK_LBUTTON))
				{
					sens=1;
				}else
				if(nFlags==(UINT)(MK_SHIFT|MK_LBUTTON))
				{
					sens=2;
				}

					
				bool sel=pDoc->m_objects->select(true,sens,pos,hdc);
				b=false;
				if (sel==true)
				{
					pDoc->m_objects->displayselect(hdc);
//					pDoc->m_objects->forundo(hdc);
				b=true;
				
				}else
				{
					pDoc->m_objects->Create(hdc,"select",pos);//rectangle.setPtsBegin(point);
					b=true;
				}
				}
				}
			else
			if (menu==mirror)
			{	
		       selT=pDoc->m_objects->mirrorselect(hdc,pos,false);
			   change=true;
			   Invalidate();
			b=true;
			}
			else
			if (menu==mirrornocopy)
			{	
		       selT=pDoc->m_objects->mirrorselect(hdc,pos,true);
			   change=true;
			   Invalidate();
				menu=select;
			}
			else
			if (menu==copyline)
			{	
		       selT=pDoc->m_objects->copyl(hdc,pos,false); 
			   change=true;
			   Invalidate();
			b=true;
			}
			else
			if (menu==copylinenocopy)
			{	
		       selT=pDoc->m_objects->copyl(hdc,pos,true);
			   change=true;
			   Invalidate();
				menu=select;
			}
			else
			if (menu==copyrec)
			{	
		       selT=pDoc->m_objects->copyl(hdc,pos,false); 
			   change=true;
			   menu=select;
			   Invalidate();
			b=true;
			}
		else
		if (menu==rotate)
		{
  
//			if(!mouse.getMove())
//			{
//				pDoc->m_objects->selectRotateCenter(hdc,mouse.getPrevPos(),mouse.getPostPos());
//			}
		}
/*		else
		if (menu==copyang)
		{
  
//			if(!mouse.getMove())
//			{
//				pDoc->m_objects->copyRS(hdc,pos,false);
//				menu=select;
//			}
			b=true;
		}
		else
		if (menu==copyanglin)
		{
  
//			if(!mouse.getMove())
//			{
//				pDoc->m_objects->copyRS(hdc,pos,true);
//				menu=select;
//			}
			b=true;
		}*/
		else
		if (menu==copybycenter)
		{
  
//			if(!mouse.getMove())
//			{
				pDoc->m_objects->copybyCenter(hdc,pos);
			   change=true;
			   menu=select;
			   Invalidate();
//			}
			b=true;
		}
		else
		if (menu==trim)
		{
			bool b;
			if(GetKeyState(VK_CONTROL) & 0x8000)
				b=true;
			else
				b=false;
			pDoc->m_objects->Trim(hdc,pos,b);
		} else
		if(menu==paste)
		{
			pDoc->m_objects->paste(hdc,pos);
			b=true;
		
		}
		else
		if(menu==extend)
		{
			pDoc->m_objects->extend(pos);
			b=true;
		
		}
		else
		if(menu==clip)
		{
			pDoc->m_objects->clip(pos);
			pDoc->m_objects->cleardraw(hdc);
			b=true;
		
		}
		else
		if(menu==fill)
		{
			pDoc->m_objects->fill(hdc,pos);
			b=true;
		}
		if(selT) b=true;
		pDoc->m_objects->forundo(this,hdc);
		
//	 hdc->BitBlt(bn.left,bn.top,bn.Width(),bn.Height(),hmdc,bn.left,bn.top,SRCCOPY);
	 ReleaseDC(hdc);
	 change=true;
 
	CScrollView::OnLButtonDown(nFlags, point);
}



void CCadView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
     //fPrevLine = TRUE; // previous line flag	
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pos = point;
    CDC *hdc=GetDC();
    
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

 

	OnPrepareDC(hdc);

	mouse.setMove(true);

	bool b=false;
	
	CRect wcr;
	GetClientRect(&wcr);
	hdc->DPtoLP(&wcr);
	CRect R(CPoint(0,0),CSize(CSize(GetTotalSize().cx,-GetTotalSize().cy)));//=pDoc->m_objects->getgrid(CSize(GetTotalSize().cx,-GetTotalSize().cy));		
	CRect bn;
	wcr.NormalizeRect();
	R.NormalizeRect();
	bn.UnionRect(&wcr,&R);
	CPoint pl2=pos;
	hdc->DPtoLP (&pos);
	CPoint pl=pos;
	hdc->LPtoDP(&pl);
	//hmdc->SelectObject(&pen);
	CVector vpos=pos,vpos1=pos;
	pDoc->m_objects->fsnap(vpos,hdc);
//	pDoc->m_objects->drawmouse(hdc,vpos);
	if(vpos.y<=0)
	{
		int omg=0;
	}
	pDoc->m_objects->getBinfo(vpos);
	static int ic=0;
//	if(ic>4)
	{
	ic=0;
//	CVector vb=CPoint(378,-50);
//	vpos.x=-184;  //pos(378,-50)
//	vpos.y=-171;
	CPoint p1=vpos,p2;
	p2=p1;
	CVector v2=p1;
	hdc->LPtoDP(&p1);
	hdc->DPtoLP(&p1);
	hdc->LPtoDP(&p2);
	hdc->DPtoLP(&p2);
	hdc->LPtoDP(&p2);
    ClientToScreen(&p2); 
	float ix=p1.x-pos.x;
	float iy=p1.y-pos.y;
	if((p1!=pos)&&(ix*ix+iy*iy!=1))
	{
	::SetCursorPos(p2.x,p2.y);
	ReleaseDC(hdc);
	return;
	}
	else
	{
	}
	}
	ic++;
	switch(menu)
	{
/*	case Line:
		{
			CString input=pDoc->m_parser->getInput();
			input.MakeLower();
			if (input.Find("next point")!=-1)
			{
				//mouse.setMove(true);
//				mouse.setPostPos(pos);
	
                 fPrevLine = pDoc->m_objects->add("Line",fPrevLine,hdc, vpos); 
            
			}
		b=true;
		break;	
		}*/
	case box:
		{
			if (mouse.getLBdownStatus())
			{
	DWORD tick=GetTickCount();
	static DWORD prevtick=0;
	if(tick-prevtick>0)
	{
	prevtick=tick;

				//mouse.setMove(true);
			//	mouse.setPostPos(pos);
	
                 fPrevLine = pDoc->m_objects->add("Box",fPrevLine,hdc, vpos); 
				change=true;
				OnDraw(hdc);
	}            
			}
		b=true;
		break;	
		}
	case image:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(vpos);
                fPrevLine = pDoc->m_objects->add("Image",fPrevLine,hdc, vpos); 
			}
		b=true;
			break;
		}
	case DimA:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimA",fPrevLine,hdc, vpos);
			}
		b=true;
			break;
		}
	case DimV:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimV",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimF:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimF",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimR:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimR",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}

	case DimD:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimD",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimH:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimH",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case leader:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("leader",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case multline:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("multline",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimL:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("DimL",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimLH:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
	
                 fPrevLine = pDoc->m_objects->add("DimLH",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case DimLV:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
	
                 fPrevLine = pDoc->m_objects->add("DimLV",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case sqline:
	case perpline:
	case tangline:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("QLine",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case Line:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
                fPrevLine = pDoc->m_objects->add("Line",fPrevLine,hdc, pos);
			}
		b=true;
			break;
		}
	case polybezier:
		{
			if (mouse.getLBdownStatus())
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
				
                 fPrevLine = pDoc->m_objects->add("Bezier",fPrevLine,hdc, pos); b=true;
			}else
			{
				//mouse.setMove(true);
				mouse.setPostPos(pos);
				
                 fPrevLine = pDoc->m_objects->add("BezierFree",fPrevLine,hdc, pos); b=true;

			}
		b=true;
			break;
		}
	case Circle:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
	
				fPrevLine = pDoc->m_objects->add("Circle",fPrevLine,hdc, pos);
				}
   		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case circle2:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
	
				fPrevLine = pDoc->m_objects->add("2DotCircle",fPrevLine,hdc, pos); 
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case circle3:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
	
				fPrevLine = pDoc->m_objects->add("3DotCircle",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case ellipse:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
	
				fPrevLine = pDoc->m_objects->add("Ellipse",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case arc:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
	
				fPrevLine = pDoc->m_objects->add("Arc",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case arc2:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine = pDoc->m_objects->add("2DotArc",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case arc3:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine = pDoc->m_objects->add("3DotArc",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case arc32:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine = pDoc->m_objects->add("3DotArc2",fPrevLine,hdc, pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case Rectangle:
	case Rectanglefree:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine=pDoc->m_objects->add("Rectangle",fPrevLine,hdc,pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case plane:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine=pDoc->m_objects->add("Plane",fPrevLine,hdc,pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case text:
		{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				fPrevLine=pDoc->m_objects->add("Text",fPrevLine,hdc,pos);
			}
		b=true;
			ptsPrevEnd=pos;
			break;
		}
	case select:
	case spoint:
		{
			if (mouse.getLBdownStatus())
			{
				bool sel;
            // When moving the mouse, the user must hold down 
            // the left mouse button to draw lines. 
				mouse.setPostPos(pos);
				if(mouse.getPrevPos()!=mouse.getPostPos())
				{

					selT=pDoc->m_objects->translate(this,hdc,mouse.getPrevPos(),mouse.getPostPos(),0);
					change=true;
					if (!selT)
					{
						fPrevLine=pDoc->m_objects->add("select",fPrevLine,hdc,pos);
					}
				}
		b=true;
			} 
			break;
		}
	case campad:
		{
			if (mouse.getLBdownStatus())
			{
				bool sel;
            // When moving the mouse, the user must hold down 
            // the left mouse button to draw lines. 
				mouse.setPostPos(pos);
				if(mouse.getPrevPos()!=mouse.getPostPos())
				{

				int sens=-1;
				if(nFlags==(UINT)(MK_CONTROL|MK_LBUTTON))
				{
					sens=1;
				}else if(nFlags==(UINT)(MK_LBUTTON))
				{
					sens=0;
				}
				else
				if(nFlags==(UINT)(MK_SHIFT|MK_LBUTTON))
				{
					sens=2;
				}
					selT=pDoc->m_objects->translatecam(sens,mouse.getPrevPos(),mouse.getPostPos());
					selT=true;
					Invalidate();
				}
		b=true;
			} 
			break;
		}
	case rotate:
	{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				if(mouse.getPrevPos()!=mouse.getPostPos())
				{
				int sens=0;
				if(nFlags==(UINT)(MK_CONTROL|MK_LBUTTON))
				{
					sens=1;
				}else
				if(nFlags==(UINT)(MK_SHIFT|MK_LBUTTON))
				{
					sens=2;
				}
				pDoc->m_objects->rotate(hdc,sens,mouse.getPrevPos(),mouse.getPostPos());
				selT=true;
				//Invalidate();
				}
		b=true;
			}
			break;
	}
	case scale:
	{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				if(mouse.getPrevPos()!=mouse.getPostPos())
				{
				int sens=0;
				if(nFlags==(UINT)(MK_CONTROL|MK_LBUTTON))
				{
					sens=1;
				}else
				if(nFlags==(UINT)(MK_SHIFT|MK_LBUTTON))
				{
					sens=2;
				}
				pDoc->m_objects->scale(hdc,sens,mouse.getPrevPos(),mouse.getPostPos());
				selT=true;
				//Invalidate();
					}					
		b=true;
			}
			break;
	}
		case camrot:
			{
			if (mouse.getLBdownStatus())
			{
				mouse.setPostPos(pos);
				if(mouse.getPrevPos()!=mouse.getPostPos())
				{
				int sens=33;
				if(nFlags==(UINT)(MK_CONTROL|MK_LBUTTON))
				{
					sens=32;
				}else
				if(nFlags==(UINT)(MK_SHIFT|MK_LBUTTON))
				{
					sens=31;
				}
				
				pDoc->m_objects->rotatecam(sens,mouse.getPrevPos(),mouse.getPostPos());
				Invalidate();
				selT=true;
				}
		b=true;
			}
			break;
	}
	}

//	CVector v=pos;
//	if(snap_menu)
//	{
//	DWORD tick=GetTickCount();
//	static DWORD prevtick=0;
//	if(!pDoc->m_objects->fsnap(v,hdc))
//		v.w=-2;
//	snap.display(v,hdc);
/*	if(pDoc->m_objects->fsnap(v,hdc))
	{
		snap.display(v,hdc);
	}
	else
	{
		v.w=-2;
		snap.display(v,hdc);
	}*/
//	}
	void* pp[2];
//	CVector p=pDoc->m_objects->getMouse(pos);
	pp[0]=&vpos;
	pp[1]=hdc;
	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
	(*it)->SendNotify("mouse",pp);//mg->m_wndMyDialogBar.setmouse(p);
	}
	
	ReleaseDC(hdc);
	CScrollView::OnMouseMove(nFlags,point);
}

	


void CCadView::OnLButtonUp(UINT nFlags, CPoint point) 
{

			// The user has finished drawing the line. Reset the 
            // previous line flag, release the mouse cursor, and 
            // release the mouse capture. 
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pos = point;
    CDC *hdc=GetDC();

	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

//	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
//	hdc->RealizePalette();
	
	OnPrepareDC(hdc);
	hdc->SetViewportOrg(CPoint(0,0));
	hdc->SetWindowOrg(CPoint(0,0));

/*	CDC *hmdc=new CDC;
	hmdc->CreateCompatibleDC(hdc);
	hmdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hmdc->RealizePalette();
*/
//	CRect wcr;
//
//	GetClientRect(&wcr);


	bool b=false;


		hdc->DPtoLP (&pos);
	//	hmdc->SelectObject(&pen);
		pDoc->m_objects->mouseon=false;

		switch(menu)//if ((menu==Line)|(menu==Circle)|(menu==Rectangle)|menu==select|menu==rotate)
			{
			case Line:
				pDoc->m_objects->finaladd(hdc,"Line",pos,"");
			b=true;
				break;
			case box:
				pDoc->m_objects->finaladd(hdc,"Box",pos,"");
			b=true;
				break;
			case plane:
				pDoc->m_objects->finaladd(hdc,"Plane",pos,"");
			b=true;
				break;
			case image:
				pDoc->m_objects->finaladd(hdc,"Image",pos,"");
			b=true;
				break;
			case DimR:
				{
				pDoc->m_objects->finaladd(hdc,"DimR",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimD:
				{
				pDoc->m_objects->finaladd(hdc,"DimD",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimH:
				{
				pDoc->m_objects->finaladd(hdc,"DimH",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case leader:
				{
				pDoc->m_objects->finaladd(hdc,"leader",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case multline:
				{
				pDoc->m_objects->finaladd(hdc,"multline",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimV:
				{
				pDoc->m_objects->finaladd(hdc,"DimV",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimF:
				{
				pDoc->m_objects->finaladd(hdc,"DimF",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimL:
				{
				pDoc->m_objects->finaladd(hdc,"DimL",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimLH:
				{
				pDoc->m_objects->finaladd(hdc,"DimLH",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimLV:
				{
				pDoc->m_objects->finaladd(hdc,"DimLV",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case DimA:
				{
				pDoc->m_objects->finaladd(hdc,"DimA",pos,"");
				change=true;
				Invalidate();
			b=true;
				break;
				}
			case chamf:
				{
				bool ot=pDoc->m_objects->finDimA();
				if (ot)
				{
				}
//				selT=ot;
				break;
				}
			case filt:
				{
				bool ot=pDoc->m_objects->finDimA();
				if (ot)
				{
				}
//				selT=ot;
				break;
				}
			case C2L:
				{
				bool ot=pDoc->m_objects->finDimA();
				if (ot)
				{
				}
			b=true;
				break;
				}
			case sqline:
				pDoc->m_objects->finaladd(hdc,"QLine",pos,"");
			b=true;
				break;
			case perpline:
				pDoc->m_objects->finaladd(hdc,"QLine",pos,"");
			b=true;
				break;
			case tangline:
				pDoc->m_objects->finaladd(hdc,"QLine",pos,"");
			b=true;
				break;
			case polybezier:
				pDoc->m_objects->finaladd(hdc,"Bezier",pos,"");
			b=true;
				break;
			case Circle:
				pDoc->m_objects->finaladd(hdc,"Circle",pos,"");
			b=true;
				break;
			case circle2:
				{
				pDoc->m_objects->finaladd(hdc,"2DotCircle",pos,"");
			b=true;
				break;
				}
			case circle3:
				{
				pDoc->m_objects->finaladd(hdc,"3DotCircle",pos,"");
			b=true;
				break;
				}
			case ellipse:
				{
				pDoc->m_objects->finaladd(hdc,"Ellipse",pos,"");
			b=true;
				break;
				}
			case arc:
				pDoc->m_objects->finaladd(hdc,"Arc",pos,"");
			b=true;
				break;
			case arc2:
				pDoc->m_objects->finaladd(hdc,"2DotArc",pos,"");
			b=true;
				break;
			case arc3:
				pDoc->m_objects->finaladd(hdc,"3DotArc",pos,"");
			b=true;
				break;
			case arc32:
				pDoc->m_objects->finaladd(hdc,"3DotArc2",pos,"");
			b=true;
				break;
			case Rectangle:
				pDoc->m_objects->finaladd(hdc,"Rectangle",pos,"stricte");
			b=true;
				break;
			case select:
				{
				pDoc->m_objects->finaladd(hdc,"select",pos,"");				
			b=true;
				break;
				}
			case spoint:
				{
				pDoc->m_objects->finaladd(hdc,"spoint",pos,"");

			b=true;
				break;
				}
			case Rectanglefree:
				pDoc->m_objects->finaladd(hdc,"Rectangle",pos,"free");
			b=true;
				break;
			case text:
				{
				CTextDi dlg11;
		//		if(dlg11.DoModal()==IDOK)
				{
				
				pDoc->m_objects->finaladd(hdc,"Text",pos,dlg11.m_text);
				menu=select;
				}
			//	CNewText dlg;
			//	pDoc->m_objects->GetTextrec(this,hdc);
			//	dlg.rec=rec;
				//	CRect rrec;
				//GetWindowRect(rrec);
			b=true;
				
				break;
				}
			case rotate:
			case scale:
				pDoc->m_objects->SelectRotState(false);
			b=true;
				break;


			}

		if(selT)
		{
			change=true;
//			pDoc->m_objects->forundo(this,hdc);
			selT=false;
		}
		change=true;
			
			mouse.setLBdown(false); 
			fPrevLine = FALSE;
//			submenu=nothing;
//			menu_edit=null;
            ClipCursor(NULL); 
            ReleaseCapture();

	Invalidate(TRUE);
//	pDoc->m_objects->drawmouse(hdc,pos);
	 ReleaseDC(hdc);
	CScrollView::OnLButtonUp(nFlags, point);
}



void CCadView::OnRectangle() 
{
	menu=Rectangle;	
	CString input,output;
	input="rect";
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDoc->m_parser->execute(input,output,NULL);

	void* pp[2];
	pp[0]=&input;
	pp[1]=&output;

//	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
//	{
//	(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
//	}
	
}



void CCadView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	
	CRect wcr;
	GetClientRect(&wcr);
	CDC* pDC=GetDC();
	OnPrepareDC(pDC);
	int map;
	CSize s;
	pDC->DPtoLP(&wcr);
	
	change=true;
	wcr.NormalizeRect();

	CSize sz(wcr.Size().cx,wcr.Size().cy);
	pDoc->m_objects->setpixel0(sz.cx,sz.cy);
	pDC->LPtoDP(&sz);
	if(bmp->GetSafeHandle()!=NULL)
	{
		bmp->DeleteObject();
	}
	bmp->CreateCompatibleBitmap(pDC,sz.cx,sz.cy);

}

void CCadView::OnTbselect() 
{
	int prevmenu=menu;
	menu=select;
	submenu=nothing;
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setBmode(hdc);
	ReleaseDC(hdc);
//	if(prevmenu==polybezier||prevmenu==textselect)
	{
//	change=true;
//	Invalidate();
	}	
}

void CCadView::OnTbrotate() 
{
	menu=rotate;
		
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();


	OnPrepareDC(hdc);

	pDoc->m_objects->selectRotateCenter(hdc,mouse.getPrevPos(),mouse.getPostPos());
	ReleaseDC(hdc);
}

void CCadView::OnTbmirror() 
{
	// TODO: Add your command handler code here
	menu=mirror;
}

void CCadView::OnTaddnode() 
{
	submenu=addnode;
}

void CCadView::OnTdeletenode() 
{
	submenu=deletenode;	
}

void CCadView::OnTbreakcurve() 
{
	submenu=breakcurve;	
}

void CCadView::OnTclosecurve() 
{
	submenu=closecurve;	
}

void CCadView::OnText() 
{
	menu=text;
/*	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();
	
	OnPrepareDC(hdc);
	CPoint p;
	p=pDoc->m_objects->movecurskb(hdc,"nil");
		CreateSolidCaret(1,15);
	SetCaretPos(p);
	ShowCaret();
	ReleaseDC(hdc);

	/*
	CNewText dlg;
	dlg.DoModal();*/
	
	


}

/*
void CCadView::OnDimButtons(UINT uID)
{

	m_Dimselected = uID;

}
void CCadView::OnUpdateDimButtons(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(pCmdUI->m_nID==m_Dimselected);
}
*/


void CCadView::OnSnapButtons(UINT uID)

{
	m_snapon = uID;
}

void CCadView::OnUpdateSnapButtons(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(pCmdUI->m_nID==m_snapon);
}



void CCadView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	m_bpastenow = TRUE;
	menu_edit=copy;

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_objects->copy();
}

void CCadView::OnEditCut() 
{
m_bpastenow = TRUE;

    CDC *hdc=GetDC();
	
	OnPrepareDC(hdc);

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_objects->cut(hdc);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnEditPaste() 
{
	menu=paste;
}

DWORD WINAPI DrawSp(LPVOID l)
{
  CCadView* t=(CCadView*) l;
  DWORD init=GetTickCount(),last;
  while(true)
  {
  last=GetTickCount()-init;
	  if(last>5)
	  {
	  t->change=true;
	  CDC* hdc=t->GetDC();

 	  t->OnDrawP(hdc);
	  init=GetTickCount();
	  t->ReleaseDC(hdc);
	  }
  }
 return NULL;
}

void CCadView::OnInitialUpdate() 
 {

	SetTimer(TMF,180000,(TIMERPROC)NULL);
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CWnd* d2=::AfxGetMainWnd();
	CFrameWnd *d3=d2->GetTopLevelFrame();
	CMainFrame* mg=	STATIC_DOWNCAST(CMainFrame, d3);
	mg->InitObjects();
	mg->setInterestObject(pDoc->m_objects);
	pDoc->m_parser->RegisterInterest(this);
	
//	mg->m_wndMyDialogBar.setparam(this,pDoc->m_objects);
 

	CDC *hdc=GetDC();
	hdc->SetMapMode(m_mode.map_mode);
 	zoomrat=1;
	CRect wcr;

	GetClientRect(&wcr);

	
	
//    SetScrollSizes(m_mode.map_mode, CSize (m_mode.Sg.cx,-m_mode.Sg.cy));
    CSize zs(m_mode.Sg.cx,-m_mode.Sg.cy);
	
	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	ASSERT_VALID(pDoc);
	OnPrepareDC(hdc);
	ShowWindow(SW_SHOWMAXIMIZED);

	pDoc->m_objects->setWnd(this);
	pDoc->m_objects->Initlib(mg->m_wndlibdia);//.m_libtree);//GetDlgItem(IDC_LIBT1));//l.m_libtree);
	CFileFind finder;
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if(strcurrPath==_T(""))
	{
		strcurrPath=strPath;
	}else
	{
		SetCurrentDirectory(strcurrPath);
	}
	bool bWorking=finder.FindFile("Library/*.dxf");
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CStdioFile file(finder.GetFilePath(),CFile::modeRead);
	CString output;
	pDoc->m_parserdxf->executeFile(hdc,file,output,true);
	pDoc->m_objects->InitlibDxf(mg->m_wndlibdia,file);	
	}
	bWorking=finder.FindFile("Library/*.aff");
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CStdioFile file(finder.GetFilePath(),CFile::modeRead);
	CString output;
	pDoc->m_objects->InitlibAff(mg->m_wndlibdia,file);	
	}
	pDoc->m_objects->initlayer(mg->m_wndlaydia.m_liblist);

	pDoc->m_objects->setgeneralInterest(&lightdlg);
	pDoc->m_objects->setcamInterest(&camdlg);
	if(lightdlg.m_hWnd==NULL)
	{
	lightdlg.Create(IDD_DIALOGLIGHT,AfxGetMainWnd());
	camdlg.Create(IDD_DIALOGCAMERA,AfxGetMainWnd());
	pDoc->m_objects->RegisterInterest(&camdlg);
	}
	

	hdc->DPtoLP(&wcr);
	wcr.NormalizeRect();
	CRect r(CPoint(0,0),m_mode.Sg);
	r.NormalizeRect();
	r.UnionRect(&r,&wcr);
	CSize z=wcr.Size();
	pDoc->m_objects->setpixel(z.cx,z.cy);

	pDoc->m_objects->setPage(m_mode.Sg);

	CRect page=pDoc->m_objects->getPage();

	CRect t;
	t.UnionRect(wcr,page);	

	SetScrollSizes (m_mode.map_mode, t.Size());

	SetScrollPos(SB_VERT,GetScrollLimit(SB_VERT)/2);
	SetScrollPos(SB_HORZ,GetScrollLimit(SB_HORZ)/2);

	ReleaseDC(hdc);
	change=true;

    CScrollView::OnInitialUpdate ();

	pv=this;
	initOK=true;
	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
	(*it)->SendNotify("ViewInit",NULL);//mg->m_wndMyDialogBar.setmouse(p);
	}
	
 }

void CCadView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	
/*	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	

	/// partie pour permettre de centrer les dessin lors du rendu
	CRect scr1;												
															
	GetClientRect(&scr1);

	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);*/

	OnPrepareDC(hdc);

	if(menu!=init)
	{
		if(nChar==(UINT)(VK_RETURN))
		{
			if(menu==text){
				pDoc->m_objects->entertxt(hdc);
			}else
			{
				CString input,output;
				input="end command";
				CCadDoc* pDoc = GetDocument();
				ASSERT_VALID(pDoc);
				pDoc->m_parser->execute(input,output,NULL);
				output="";
				void* pp[2];
				pp[0]=&input;
				pp[1]=&output;

				for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
				{
				(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
				}
				menu=init;
			}
		}else
		if(nChar==(UINT)(VK_ESCAPE))
		{

			for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
			{
			(*it)->SendNotify("CancelCommand",NULL);//mg->m_wndMyDialogBar.setmouse(p);
			}
		}
	}
	BOOL processed;
		if(menu==campad)
		{
				int sens=-1;
				if(nChar==(UINT)(VK_LEFT))
				{
					sens=00;
				}else
				if(nChar==(UINT)(VK_RIGHT))
				{
					sens=01;
				}else
				if(nChar==(UINT)(VK_UP))
				{
					sens=10;
				}else
				if(nChar==(UINT)(VK_DOWN))
				{
					sens=11;
				}else
				if(nChar==(UINT)(VK_PRIOR))
				{
					sens=20;
				}else
				if(nChar==(UINT)(VK_NEXT))
				{
					sens=21;
				}
				if(sens!=-1)
				{
				pDoc->m_objects->translatecam(sens,mouse.getPrevPos(),mouse.getPrevPos());
				selT=true;
				Invalidate();
				}
			}else
		if(menu==camrot)
		{
				int sens=-1;
				if(nChar==(UINT)(VK_LEFT))
				{
					sens=00;
				}else
				if(nChar==(UINT)(VK_RIGHT))
				{
					sens=01;
				}else
				if(nChar==(UINT)(VK_UP))
				{
					sens=10;
				}else
				if(nChar==(UINT)(VK_DOWN))
				{
					sens=11;
				}else
				if(nChar==(UINT)(VK_PRIOR))
				{
					sens=20;
				}else
				if(nChar==(UINT)(VK_NEXT))
				{
					sens=21;
				}
				if(sens!=-1)
				{
				pDoc->m_objects->rotatecam(sens,mouse.getPrevPos(),mouse.getPostPos());
				selT=true;
				Invalidate();
				}
			}
		else
		if(menu==camsw)
		{
				int sens=-1;
				if(nChar==(UINT)(VK_LEFT))
				{
					sens=00;
				}else
				if(nChar==(UINT)(VK_RIGHT))
				{
					sens=01;
				}else
				if(nChar==(UINT)(VK_UP))
				{
					sens=10;
				}else
				if(nChar==(UINT)(VK_DOWN))
				{
					sens=11;
				}else
				if(nChar==(UINT)(VK_PRIOR))
				{
					sens=20;
				}else
				if(nChar==(UINT)(VK_NEXT))
				{
					sens=21;
				}
				if(sens!=-1)
				{
				pDoc->m_objects->rotatecam(sens,mouse.getPrevPos(),mouse.getPostPos(),true);
				selT=true;
				Invalidate();
				}
			}else
		if(menu==select)
		{
				int sens=0;
				if(nChar==(UINT)(VK_LEFT))
				{
					sens=01;
				}else
				if(nChar==(UINT)(VK_RIGHT))
				{
					sens=02;
				}else
				if(nChar==(UINT)(VK_UP))
				{
					sens=11;
				}else
				if(nChar==(UINT)(VK_DOWN))
				{
					sens=12;
				}else
				if(nChar==(UINT)(VK_PRIOR))
				{
					sens=21;
				}else
				if(nChar==(UINT)(VK_NEXT))
				{
					sens=22;
				}
				if(sens!=0)
				pDoc->m_objects->translate(this,hdc,mouse.getPrevPos(),mouse.getPostPos(),sens);
				selT=true;
				Invalidate();
			}
	ReleaseDC(hdc);
    change=true;
//	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CCadView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	
/*	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	

	/// partie pour permettre de centrer les dessin lors du rendu
	CRect scr1;												
															
	GetClientRect(&scr1);

	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);
*/
	OnPrepareDC(hdc);


	BOOL processed;
	if(menu==text)
	{
		if(nChar==VK_SHIFT)
		{
				pDoc->m_objects->movecurskb(hdc,"selStop");
 //               change=true;
//				Invalidate();
		}
	}
	else 
	if(menu==select)
	{
	change=true;
//	Invalidate(TRUE);
	}
	ReleaseDC(hdc);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



BOOL CCadView::KeyScroll(UINT nChar)
{
	switch(nChar)
	{
	case VK_UP:
		OnVScroll(SB_LINEUP,0,NULL);
		break;
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN,0,NULL);
		break;
	case VK_LEFT:
		OnHScroll(SB_LINELEFT,0,NULL);
		break;
	case VK_RIGHT:
		OnHScroll(SB_LINERIGHT,0,NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP,0,NULL);
		break;
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN,0,NULL);
		break;
	default:
		return FALSE;
	}
    change=false;

	return true;
}


void CCadView::OnEffectZoomin() 
{
	//menu=zoomin;

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	zoomrat=pDoc->m_objects->getzoomrat();
	zoomrat=zoomrat*0.5;

	pDoc->m_objects->setzoomrat(zoomrat);
	CRect page=pDoc->m_objects->getPage();

	GetClientRect(&scr);
	page.NormalizeRect();
	CRect t;
	t.UnionRect(scr,page);	
	change=true;
	Invalidate();
	SetScrollSizes (m_mode.map_mode, t.Size());
 	ReleaseDC(pDC);
}



void CCadView::OnRectanglefree() 
{
	menu=Rectanglefree;

}



BOOL CCadView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	dwStyle|=WS_HSCROLL|WS_VSCROLL;

	BOOL result= CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	pagerec.cx=1200;
	pagerec.cy=1500;

	screenrec.cx=3000;
	screenrec.cy=3000;

	currentPos.cx=0;
	currentPos.cy=0;
	minscrollPos.cx=-screenrec.cx/2;
	minscrollPos.cy=-screenrec.cy/2;

	maxscrollPos.cx=screenrec.cx/2;
	maxscrollPos.cy=screenrec.cy/2;

	
	siv->cbSize=sizeof(siv);
	siv->fMask=SIF_ALL;
	siv->nMin=-screenrec.cy/2;
	siv->nMax=screenrec.cy/2;
	siv->nPage=pagerec.cy;
	siv->nPos=currentPos.cy;
 	zrec.cx=800;
 	zrec.cy=500;
 
 	CSize nono=zrec;
 
     
	zrec.cx=200;
 	zrec.cy=200;
 
	SetScrollInfo(SB_VERT,siv);


	sih->cbSize=sizeof(sih);
	sih->fMask=SIF_ALL;
	sih->nMin=-screenrec.cx/2;
	sih->nMax=+screenrec.cx/2;
	sih->nPage=pagerec.cx;
	sih->nPos=currentPos.cx;

	SetScrollInfo(SB_HORZ,sih);
	SetTimer (1, 60000, NULL);

	return result;

}

void CCadView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	int sens=-1,s=0;

	switch(nSBCode)
	{
	case SB_LINEUP:
			sens=10;
			s=1;
		break;
	case SB_LINEDOWN:
			sens=11;
			s=-1;
		break;
	case SB_PAGEUP:
			sens=10;
			s=2;
		break;
	case SB_PAGEDOWN:
			sens=11;
			s=-2;
		break;
	}
	int c=GetScrollLimit(SB_VERT);
	int cp=GetScrollPos(SB_VERT);
//	if((cp>0)&&(cp<c))
//	{
	if(sens!=-1)
	{
	pDoc->m_objects->translatecam(sens,mouse.getPrevPos(),mouse.getPrevPos());
	change=true;
	Invalidate(FALSE);
	}
//	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

}

void CCadView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	int sens=-1;

	switch(nSBCode)
	{
	case SB_LINELEFT:
			sens=00;
		break;
	case SB_LINERIGHT:
			sens=01;
		break;
	case SB_PAGELEFT:
			sens=00;
		break;
	case SB_PAGERIGHT:
			sens=01;
		break;
	}
	int c=GetScrollLimit(SB_HORZ);
	int cp=GetScrollPos(SB_HORZ);
//	if((cp>0)&&(cp<c))
//	{
	if(sens!=-1)
	{
	pDoc->m_objects->translatecam(sens,mouse.getPrevPos(),mouse.getPrevPos());
	change=true;
	Invalidate();
	}
//	}
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

}



void CCadView::OnCopyline() 
{
	menu=copyline;

}

void CCadView::OnAngcopy() 
{
	menu=copyang;
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	CArrayAngle Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->copyRSparam(hdc,Adlg.m_anglrot,Adlg.m_nbcopy,Adlg.m_nblevel,Adlg.m_dlevel,false);
	menu=select;
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnCopyral() 
{
	menu=copyanglin;
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	CArrayAngle Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->copyRSparam(hdc,Adlg.m_anglrot,Adlg.m_nbcopy,Adlg.m_nblevel,Adlg.m_dlevel,true);
	menu=select;
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnCopybycenter() 
{
	menu=copybycenter;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	CNumCopy offdlg;
	if(offdlg.DoModal()==IDOK)
	{
		pDoc->m_objects->Offset(offdlg.m_offset);
	}
	menu=select;

}

void CCadView::OnAlignbyline() 
{
	menu=alignbyline;	
}

void CCadView::On2cercle() 
{
	menu=circle2;
}

void CCadView::On3cercle() 
{
	menu=circle3;
	
}



void CCadView::OnPolyb() 
{
	menu=polybezier;
	CString input,output;
	input="spline";
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDoc->m_parser->execute(input,output,NULL);

	void* pp[2];
	pp[0]=&input;
	pp[1]=&output;

//	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
//	{
//	(*it)->SendNotify("View",pp);//mg->m_wndMyDialogBar.setmouse(p);
//	}
	
}

void CCadView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *hdc=GetDC();
	OnPrepareDC(hdc);

    hdc->DPtoLP (&point);
		if (menu==select)
		{				
		pDoc->m_objects->editobj(point);
		}

/*	if(pDoc->m_objects->getselect())
	{
		pDoc->m_objects->editobj(hdc);
	    change=true;
		Invalidate(TRUE);

/*		COBJEdit edt;
		edt.setobj(pDoc->m_objects->getobif());
		if(edt.DoModal()==IDOK)
		{
			pDoc->m_objects->setobjinfo(edt.m_auth,edt.m_descr,\
										edt.m_name,edt.m_cost);

		}*/
//	}

	ReleaseDC(hdc);
	CView::OnLButtonDblClk(nFlags, point);
}

void CCadView::OnSqline() 
{
	// TODO: Add your command handler code here
	menu=sqline;
}

void CCadView::OnRButtonDown(UINT nFlags, CPoint pos) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPoint point = pos;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

/*	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();
*/	OnPrepareDC(hdc);

    hdc->DPtoLP (&point);

	bool tr=false;
/*	if(menu==DimA)
	{
	//	tr=pDoc->m_objects->straightDimA(true);
	//	Invalidate();
	}
	else
	{*/
		switch (menu)
		{
		
		case select:
			{
				
				CMenu menu;
				CMenu *ptrMenu;
				menu.LoadMenu(IDR_MENU_POPUP);
				ptrMenu=menu.GetSubMenu(0);
				ClientToScreen(&pos);
				ptrMenu->TrackPopupMenu
				(
				TPM_LEFTALIGN|TPM_RIGHTBUTTON,
				pos.x,
				pos.y,
				this,
				NULL
				);
			
				break;
		}
		case rotate:
			{
				CMenu menu;
				CMenu *ptrMenu;	
				menu.LoadMenu(IDR_MENU_ROTATE);
				ptrMenu=menu.GetSubMenu(0);
				ClientToScreen(&pos);
				ptrMenu->TrackPopupMenu
				(
					TPM_LEFTALIGN|TPM_RIGHTBUTTON,
					pos.x,
					pos.y,
					this,
				NULL
				);
				break;
			}
		default:
			{
				CMenu menu;
				CMenu *ptrMenu;
				menu.LoadMenu(IDR_MENUDRW);
				ptrMenu=menu.GetSubMenu(0);
				ClientToScreen(&pos);
				ptrMenu->TrackPopupMenu
				(
				TPM_LEFTALIGN|TPM_RIGHTBUTTON,
				pos.x,
				pos.y,
				this,
				NULL
				);
			}


	//	}
}
	ReleaseDC(hdc);
	CView::OnRButtonDown(nFlags, pos);
}

void CCadView::OnArc() 
{
	menu=arc;	
}

void CCadView::On3arcclose() 
{
	menu=arc3;	
}

void CCadView::On3arcopen() 
{
	menu=arc2;// TODO: Add your command handler code here
	
}

//DEL void CCadView::OnFreecirc() 
//DEL {
//DEL 	menu=freecirc;	
//DEL }





void CCadView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
 {
	if(menu==text)
	{
		CCadDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

	    CDC *hdc=GetDC();
	
/*		hdc->SetMapMode(MM_ISOTROPIC);
		hdc->SetWindowExt(100,100);
		hdc->SetViewportExt(100*zoomrat,100*zoomrat);
		hdc->SetWindowOrg(0,0);
	
		CRect scr1;;

		GetClientRect(&scr1);

		currentPosdev=currentPos;
		hdc->LPtoDP(&currentPosdev);

		hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);*/
		OnPrepareDC(hdc);
		//hdc->SelectObject(&pen);

	switch(nChar)
	{
	    case 0x08:
			{
				HideCaret();
				CPoint p=pDoc->m_objects->deletebk(hdc);
				p.y-=10;
				SetCaretPos(p);
				ShowCaret();
				Invalidate();
            break; 
			}
 
         case 0x0A: 
			 {           
              // Process a linefeed. 
              break; 
			 }
          case 0x1B: 
			  {                  
				HideCaret();
				pDoc->m_objects->inittext();
				menu=select;
               break; 
			  }
          case 0x09: 
			  {          
               // Process a tab. 
               break; 
			  }
          case 0x0D: 
			  {          
				HideCaret();
				CPoint p=pDoc->m_objects->entertxt(hdc);
				p.y-=10;
				SetCaretPos(p);
				ShowCaret();
				Invalidate();
               break; 
			  }
          default: 
			  {
				HideCaret();
				CPoint p=pDoc->m_objects->drawtext(hdc,nChar);
		//	    change=true;
				Invalidate(TRUE);
				p.y-=10;
				SetCaretPos(p);
				ShowCaret();
               break;
			  }
	}
	ReleaseDC(hdc);
//    change=true;
//	Invalidate();
	}
	
 	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}





/*void CCadView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bEnable=TRUE;
	if(bEnable=FALSE);
	pCmdUI->Enable(bEnable);
}

*/

BOOL CCadView::IsSelected(const CObject* pDocItem) const
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::IsSelected(pDocItem);
}

/*
void CCadView::OnAlignright() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnAlleft() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnAlcent() 
{
	// TODO: Add your command handler code here
	
}
*/
//DEL void CCadView::OnLbuttonColor() 
//DEL {
//DEL 	CCadDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL //	CColorD colD;
//DEL 	CDC *hdc=GetDC();
//DEL 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
//DEL 
//DEL 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
//DEL 	hdc->RealizePalette();
//DEL 
//DEL 	hdc->SetMapMode(MM_ISOTROPIC);
//DEL 	hdc->SetWindowExt(100,100);
//DEL 	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
//DEL 	CRect scr1;												
//DEL 															
//DEL 	GetClientRect(&scr1);
//DEL 	
//DEL 	currentPosdev=currentPos;
//DEL 	hdc->LPtoDP(&currentPosdev);
//DEL 
//DEL 	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
//DEL 	
//DEL 	hdc->SetWindowOrg(0,0);
//DEL 
//DEL 	OnPrepareDC(hdc);
//DEL 
//DEL 
//DEL 
//DEL //	CRecColor rec;
//DEL 	CRect v(0,0,0,0);
//DEL //	rec.CreateEx(WS_EX_CLIENTEDGE,_T("BUTTON"),NULL,
//DEL //			WS_CHILD,v,this,44500,NULL);
//DEL 
//DEL //	pDoc->m_objects->setLcolor(hdc,rec.ccolor,rec.bcolor);
//DEL 	
//DEL 	ReleaseDC(hdc);
//DEL //	delete rec;
//DEL 
//DEL 
//DEL }



void CCadView::OnBpercent() 
{
	// TODO: Add your command handler code here

	
}

/*void CCadView::OnBzoomminus() 
{
	// TODO: Add your command handler code here

}

void CCadView::OnBzoomplus() 
{
	// TODO: Add your command handler code here
	

}*/
void CCadView::OnParaLeft()
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	bool c=pDoc->m_objects->setpara("left");
	if(c)
	{
	    change=true;
		Invalidate();
	}
	ReleaseDC(pDC);

}
void CCadView::OnParaCenter()
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	bool c=pDoc->m_objects->setpara("center");
	if(c)
	{
	    change=true;
		Invalidate();
	}
	ReleaseDC(pDC);
}
void CCadView::OnParaJustify()
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	bool c=pDoc->m_objects->setpara("justify");
	if(c)
	{
	    change=true;
		Invalidate();
	}
	ReleaseDC(pDC);
}
void CCadView::OnParaRight()
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	bool c=pDoc->m_objects->setpara("right");
	if(c)
	{
	    change=true;
		Invalidate();
	}
	ReleaseDC(pDC);
}
void CCadView::OnUpdateParaRight(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(menu==paraRight);	
}
void CCadView::OnUpdateParaLeft(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(menu==paraLeft);	
}
void CCadView::OnUpdateParaCenter(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(menu==paraCenter);	
}
void CCadView::OnUpdateParaJustify(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(menu==paraJustify);	
}

void CCadView::OnFitpage() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
//	OnPrepareDC(pDC);
	zoom= false;
	zmode = zoomin;
	zoomrat=1/zoomrat;
	pDoc->m_objects->setfitzoom(zoomrat);
//	pDoc->m_objects->setPage(m_mode.Sg);
	CRect page=pDoc->m_objects->getPage();

	GetClientRect(&scr);
	
	page.NormalizeRect();
	scr.NormalizeRect();
	CRect t;
	t.UnionRect(scr,page);	
    change=true;
	SetScrollSizes (m_mode.map_mode, t.Size());
	SetScrollPos(SB_VERT,GetScrollLimit(SB_VERT)/2);
	SetScrollPos(SB_HORZ,GetScrollLimit(SB_HORZ)/2);
	Invalidate();
	ReleaseDC(pDC);

}

void CCadView::OnNpage() 
{
	// TODO: Add your command handler code here

	
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
//	OnPrepareDC(pDC);
	zoom= false;
	zmode = zoomin;
	zoomrat=1/zoomrat;
	pDoc->m_objects->setinitzoom();
//	pDoc->m_objects->setPage(m_mode.Sg);
	CRect page=pDoc->m_objects->getPage();

	GetClientRect(&scr);
	
	page.NormalizeRect();
	scr.NormalizeRect();
	CRect t;
	t.UnionRect(scr,page);	
    change=true;
	SetScrollSizes (m_mode.map_mode, t.Size());
	SetScrollPos(SB_VERT,GetScrollLimit(SB_VERT)/2);
	SetScrollPos(SB_HORZ,GetScrollLimit(SB_HORZ)/2);
	Invalidate();
	ReleaseDC(pDC);
}



/*void CCadView::OnPAtTERN() 
{
	CPattern  plg;
	plg.DoModal();


}*/

BOOL CCadView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return 1;//CScrollView::OnEraseBkgnd(pDC);
}

void CCadView::OnEditUndo() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
//	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

//	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
//	hdc->RealizePalette();

//	OnPrepareDC(hdc);
	string input;
	pDoc->m_objects->undo(input);
	if(input.empty()) return;
 	pDoc->m_parser->execute(CString(input.c_str()),CString(""),NULL);
	change=true;
	Invalidate();

}

void CCadView::OnEditRedo() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	string input;
	pDoc->m_objects->redo(NULL,input);
	if(input.empty()) return;
 	pDoc->m_parser->execute(CString(input.c_str()),CString(""),NULL);
	change=true;
	Invalidate();
	
}

void CCadView::OnGroup() 
{
	m_grouped= true;
	submenu=group;

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();


	OnPrepareDC(hdc);

	pDoc->m_objects->group(hdc);
	ReleaseDC(hdc);
    change=true;
	Invalidate();
	submenu=nothing;

	
}

void CCadView::OnGroupup() 
{
	submenu=ungroup;
	//	m_grouped=false;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

	pDoc->m_objects->ungroup(hdc);
	ReleaseDC(hdc);
    change=true;
	Invalidate();
	submenu=nothing;
	
}

/*void CCadView::OnLinesytle() 
{
	// TODO: Add your command handler code here
	
}
*/
void CCadView::OnDiml() 
{
	menu=DimL;	
	//	m_Dimselected=ID_DIML;
}
void CCadView::OnLeader() 
{
	menu=leader;	
	//	m_Dimselected=ID_DIML;
}
void CCadView::OnMultLine() 
{
	menu=multline;	
	//	m_Dimselected=ID_DIML;
}

void CCadView::OnDimA() 
{
	menu=DimA;
	//m_Dimselected=ID_DimA;
	
}

void CCadView::OnDimho() 
{
	menu = DimH;
	//m_Dimselected=ID_DIMHO;
}

void CCadView::OnDimvert() 
{
	menu=DimV;
	//m_Dimselected=ID_DIMVERT;
}

void CCadView::OnDim1free() 
{
	menu=DimF;
	//m_Dimselected=ID_DIM1FREE;
}

void CCadView::OnDimrad() 
{
	// TODO: Add your command handler code here
	//m_Dimselected=ID_DIMRAD;
	menu=DimR;
}

void CCadView::OnDimcdia() 
{
	// TODO: Add your command handler code here
	//m_Dimselected=ID_DIMCDIA;
	menu=DimD;
}

/*void CCadView::OnDimtxt() 
{
	//m_Dimselected=ID_DIMTXT;
	menu=DimT;
}
*/
void CCadView::OnIntersetpt() 
{
	// TODO: Add your command handler code here
	
}
void CCadView::OnSnap() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *hdc=GetDC();
	OnPrepareDC(hdc);
	CSnapGridDlg griddlg;
	CSnapObjectDlg objectdlg;
	CPolarTrackDlg polartrack;
	CSnapDlg snapdlg("Snap and grid settings");
	snapdlg.AddPage(&griddlg);
	snapdlg.AddPage(&objectdlg);
	snapdlg.AddPage(&polartrack);
	vector<CProperty*> v;
	v.push_back(&griddlg);
	v.push_back(&objectdlg);
	v.push_back(&polartrack);
	pDoc->m_objects->getsnap(v);
	if(snapdlg.DoModal()==IDOK)
	{
	vector<CProperty*> v;
	v.push_back(&griddlg);
	v.push_back(&objectdlg);
	v.push_back(&polartrack);

	pDoc->m_objects->setsnap(v,hdc);
	change=true;
	Invalidate(TRUE);
	}
}

void CCadView::OnSnapctr() 
{
	//snap_menu=snapc;	
}

void CCadView::OnSnapmidpoint() 
{
	//snap_menu=snapmi;	
}

void CCadView::OnSnapnear() 
{
	//snap_menu=snapnear;	
}

void CCadView::OnSnapoff() 
{
//	snap_menu=snapoff;	
}

void CCadView::OnSnapon() 
{
//	CToolBar snp;
/*    if(!snap_menu) 
		SetTimer(2, 50, NULL);
	else
		KillTimer(2);
*/	snap_menu=!snap_menu;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_objects->setsnap(snap_menu);
	if(!snap_menu)
	{
		CVector v;
		v.w=-2;
	    CDC *hdc=GetDC();
		OnPrepareDC(hdc);
		snap.display(v,hdc);
		ReleaseDC(hdc);
	}
//	RegisterInterest(&snappy);
//	snappy.setDraw(pDoc->m_objects);
}

void CCadView::OnSnappen() 
{
//	snap_menu=snapp;	
}

void CCadView::OnSnapquad() 
{
//	snap_menu=snapq;	
}

void CCadView::OnSnaptan() 
{
//	snap_menu=snapt;	
}
void CCadView::OnSnapendpoint() 
{
//	snap_menu=snapp;
	
}



void CCadView::OnDialogFont() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();


	OnPrepareDC(hdc);


	CFontDialog dlg;
	LOGFONT lf;
	COLORREF ccl;
	TEXTMETRIC tm;
	CHARFORMAT cf;
	//CClientDC dc(NULL);
	CFont *ptrFtOld;
	dlg.m_cf.Flags|=CF_EFFECTS|CF_INITTOLOGFONTSTRUCT;
	pDoc->m_objects->getfont(cf);
	dlg.FillInLogFont(cf);
	if(dlg.DoModal() == IDOK)	
	{
		dlg.GetCurrentFont(&lf);
		ccl=dlg.GetColor();
		dlg.GetCharFormat(cf);
//		HideCaret();
		CPoint p=pDoc->m_objects->setFont(hdc,lf,ccl,cf);
//		CreateSolidCaret(1,15);
//		SetCaretPos(p);
//		ShowCaret();
		if(p.x==0)
		{
			change=true;
			Invalidate();
		}
	}

	ReleaseDC(hdc);
}

void CCadView::OnSendtofront() 
{
//	menu=flipv;	
	submenu=sendfront;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->pos("front");
    change=true;
	Invalidate();	// TODO: Add your command handler code here
	
}

void CCadView::OnSendtobackgrd() 
{
//	menu=flipv;
	submenu=sendbgr;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->pos("back");
    change=true;
	Invalidate();	// TODO: Add your command handler code here
	
}

void CCadView::OnChangeColor(COLORREF lc,COLORREF bc) 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *hdc=GetDC();
	

	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();
	OnPrepareDC(hdc);

	pDoc->m_objects->setLcolor(hdc,lc,bc);
    change=true;

	Invalidate(TRUE);	// TODO: Add your command handler code here
	ReleaseDC(hdc);
	
}




void CCadView::OnSendforward() 
{
//	menu=flipv;	
	submenu=sendforward;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->pos("front1");
    change=true;
	Invalidate();	// TODO: Add your command handler code here
	
}

void CCadView::OnSendbackward() 
{
//	menu=flipv;	
	submenu=sendbackward;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->pos("back1");
    change=true;
	Invalidate();	// TODO: Add your command handler code here
	
}


void CCadView::OnEclipse() 
{
	// TODO: Add your command handler code here
	menu=ellipse;
}

void CCadView::OnSlide() 
{
	menu=slide;	
}

void CCadView::OnPerp() 
{
	menu=perpline;
}

//DEL void CCadView::OnTgline() 
//DEL {
//DEL 	menu=tangline;	
//DEL }

void CCadView::OnToolsGrid() 
{
//	CPGrid dlg;
//	dlg.DoModal();
	
	CPen dot;
	dot.CreatePen(PS_DOT,1,RGB(12,12,250));
	CPen* pOldyPen2=hmdc->SelectObject(&dot);

	int i=0;
	
	int step=50;
	for(i=inter.top;i<inter.bottom;i+=step)
	{
		hmdc->MoveTo(inter.left,i);
		hmdc->LineTo(inter.right,i);
	}
	for(i=inter.left;i<inter.right;i+=step)
	{
		hmdc->MoveTo(i,inter.top);
		hmdc->LineTo(i,inter.bottom);

	}
	
}

void CCadView::OnToolsPaper() 
{
/*	CCPaperSize pdlg;
	pdlg.DoModal();	*/

}

void CCadView::OnFlih() 
{
	menu =fliph;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_objects->flip(false);
	menu=select;
    change=true;
	Invalidate();
}

void CCadView::OnFilpvert() 
{
	menu=flipv;
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	pDoc->m_objects->flip(true);
	menu=select;
    change=true;
	Invalidate();

}



//update button function for coppy paste undo redo.

/*void CCadView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}*/

void CCadView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
//	m_bpastenow = TRUE;
	
}

void CCadView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bpastenow);
}


//update button function for  undo redo.

void CCadView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->
}

void CCadView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


//update button function for group and ungrp.

void CCadView::OnUpdateGroup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu==group);
}

void CCadView::OnUpdateGroupup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_grouped);
	pCmdUI->SetRadio(submenu==ungroup);
}



//update button function for arannging buttons

void CCadView::OnUpdateSendbackward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu==sendbackward);
}

void CCadView::OnUpdateSendforward(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(submenu==sendforward);
	
}

void CCadView::OnUpdateSendtobackgrd(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(submenu==sendbgr);
	
}

void CCadView::OnUpdateSendtofront(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(submenu==sendfront);
	
}


//update button function for slide button

void CCadView::OnUpdateSlide(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== slide);
	
}



//update button function grid
/*void CCadView::OnUpdateToolsGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}*/

void CCadView::OnUpdateDimho(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimH);
	
}

void CCadView::OnUpdateDiml(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==DimL);
}

void CCadView::OnUpdateDimrad(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimR);
	
}

void CCadView::OnUpdateDimtxt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimT);
	
}

void CCadView::OnUpdateDimvert(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== DimV);
	
}

void CCadView::OnUpdateDimcdia(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu == DimD);
	
}

void CCadView::OnUpdateDimA(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimA);
	
}

void CCadView::OnRecarraycopy() 
{
	// TODO: Add your command handler code here
	menu=copyrec;

	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

	CRecArray Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->pastearray(hdc,false,Adlg.m_rnb,Adlg.m_cnb,Adlg.m_dx,Adlg.m_dy,Adlg.m_nblevel,Adlg.m_lspacing);
	menu=select;
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnMirrornocopy() 
{
	// TODO: Add your command handler code here
	menu=mirrornocopy;
}

void CCadView::OnUpdateDim1free(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimF);
	
}

void CCadView::OnUpdateTbselect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==select);
	
}

void CCadView::OnUpdateText(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==text);
	
}

void CCadView::OnUpdateTbrotate(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==rotate);
}
	
void CCadView::OnUpdateTgline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==tangline);
	
}

void CCadView::OnUpdateTbmirror(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== mirror);
	
}

void CCadView::OnUpdateSqline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==sqline);//pCmdUI->m_nID == m_currentbtn);
	
}

void CCadView::OnUpdateRectangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==Rectangle);//pCmdUI->m_nID == m_currentbtn);
	
}

void CCadView::OnUpdateRectanglefree(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==Rectanglefree);
	
}

void CCadView::OnUpdateLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==Line);	
}

void CCadView::OnUpdate2cercle(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==circle2);
	
}

void CCadView::OnUpdate3arcclose(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==arc3);
	
}

void CCadView::OnUpdate3arcopen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==arc2);	
}



void CCadView::OnUpdate3cercle(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==circle3);
	
}

void CCadView::OnUpdateCercle(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==Circle);
	
}

void CCadView::OnUpdateCopyral(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==copyanglin);
	
}

void CCadView::OnUpdateEclipse(CCmdUI* pCmdUI) 
{
		pCmdUI->SetRadio(menu==ellipse);
	
}

void CCadView::OnUpdatePerp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== perpline);
	
}

void CCadView::OnUpdateTaddnode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu== addnode);
}

void CCadView::OnUpdateTbreakcurve(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu==breakcurve); 
}



void CCadView::OnUpdateTdeletenode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu== deletenode);
}



void CCadView::OnUpdateTclosecurve(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(submenu==closecurve );
}

void CCadView::OnUpdatePolyb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetRadio(menu== polybezier);
}


void CCadView::OnUpdateArc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==arc);
}

void CCadView::OnUpdateMirrornocopy(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== mirrornocopy);
	
}

void CCadView::OnUpdateAngcopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu== copyang);
}



void CCadView::OnUpdateCopybycenter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== copybycenter);
	
}

void CCadView::OnUpdateFilpvert(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== flipv);
	
}

void CCadView::OnUpdateFlih(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== fliph);
	
}

void CCadView::OnUpdateRecarraycopy(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu== copyrec);	
}

void CCadView::OnUpdateCopyline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu== copyline);
}
void CCadView::OnPageSetup2(float paper_width,float paper_height) 
{
		CSize t(paper_width,paper_height);
		SetScrollSizes (m_mode.map_mode, t);

		SetScrollPos(SB_VERT,GetScrollLimit(SB_VERT)/2);
		SetScrollPos(SB_HORZ,GetScrollLimit(SB_HORZ)/2);

		change=true;
		Invalidate();

}
void CCadView::OnPageSetup() 
{
	CDC* hdc=GetDC();
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	OnPrepareDC(hdc);
	papersize.setdata(m_mode.unit,m_mode.wu,m_mode.pu,m_mode.lprec,m_mode.aprec);
	int le_type,le_stype,le_prec;
	pDoc->m_objects->getdimL(le_type,le_stype,le_prec);
	papersize.setdata2(le_type,le_stype,le_prec);
	pDoc->m_objects->getdimA(le_type,le_prec);
	papersize.setdata3(le_type,le_prec);
	papersize.setdata4(pDoc->m_objects->fittopage);
	if(papersize.DoModal()==IDOK)
	{
		m_mode.unit=papersize.getUnit();//getUnit(m_mode.map_mode);
		m_mode.delta=papersize.m_ewu/papersize.m_epu;
		m_mode.wu=papersize.m_ewu;
		m_mode.pu=papersize.m_epu;
		if(m_mode.unit)
			m_mode.map_mode=MM_LOMETRIC;
		else
			m_mode.map_mode=MM_LOENGLISH;

		
		GetClientRect(&scr);
		hdc->DPtoLP(&scr);
		scr.NormalizeRect();
		CSize z=scr.Size();
//		pDoc->m_objects->setpixel(z.cx,z.cy);
//		pDoc->m_objects->setPage(m_mode.Sg);
		pDoc->m_objects->setdimL(papersize.length_type,papersize.length_subtype,papersize.length_prec);
		pDoc->m_objects->setdimA(papersize.angle_type,papersize.angle_prec);

		CRect page=pDoc->m_objects->getPage();
		pDoc->m_objects->fitToPage(papersize.fit);
		if(papersize.fit)
		{
			m_mode.delta=pDoc->m_objects->getFitPrintRatio();
			m_mode.pu=10;
			m_mode.wu=10*m_mode.delta;
		}
		
		page.NormalizeRect();
		scr.NormalizeRect();
		CRect t;
		t.UnionRect(scr,page);	
		SetScrollSizes (m_mode.map_mode, t.Size());

		SetScrollPos(SB_VERT,GetScrollLimit(SB_VERT)/2);
		SetScrollPos(SB_HORZ,GetScrollLimit(SB_HORZ)/2);

		change=true;
		Invalidate();

		ReleaseDC(hdc);
	}
}

void CCadView::OnDash() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinestyle(PS_DASH);
	change=true;
	Invalidate();
	
}

void CCadView::OnDot() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinestyle(PS_DOT);
	change=true;
	Invalidate();
	
}
void CCadView::OnDashDot() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

//	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinestyle(PS_DASHDOT);
	change=true;
	Invalidate();
}

void CCadView::OnDashdotdot() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinestyle(PS_DASHDOTDOT);
	change=true;
	Invalidate();
}
void CCadView::OnEeeSolid() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
//	hdc->RealizePalette();

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinestyle(PS_SOLID);
	change=true;
	Invalidate();
}

void CCadView::OnBl() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnDoubledot() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnLinewidthCustom() 
{
	CCustomWidth dlg;

	if(dlg.DoModal()==IDOK)
	{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
/*	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);
*/
	pDoc->m_objects->setlinewidth(dlg.m_cwidth);
	change=true;
	Invalidate();

	}
	
}

void CCadView::OnLinewidthNormal() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	pDoc->m_objects->setlinewidth(1);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnLinewidthThick() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	pDoc->m_objects->setlinewidth(3);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnLinewidthThin() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	OnPrepareDC(hdc);

	pDoc->m_objects->setlinewidth(0.5);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}



void CCadView::OnToolCustom() 
{
	// TODO: Add your command handler code here
	CPropertySheet dlgPropertySheet(AFX_IDS_APP_TITLE);
	CGridPag  m_custgrid;
	CPaperPag m_custpaper;

	dlgPropertySheet.AddPage(&m_custgrid);
	dlgPropertySheet.AddPage(&m_custpaper);

	if (dlgPropertySheet.DoModal() == IDOK)
	{
		GetDocument()->SetModifiedFlag();
		GetDocument()->UpdateAllViews(NULL);
	}	
}

void CCadView::OnToolOption() 
{
	// TODO: Add your command handler code here
	
}


void CCadView::OnEffectZoomout() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	change=true;
	zoomrat=pDoc->m_objects->getzoomrat();
 	zoomrat=zoomrat*1.5;

	pDoc->m_objects->setzoomrat(zoomrat);
	CRect page=pDoc->m_objects->getPage();

	GetClientRect(&scr);
	
	page.NormalizeRect();
	scr.NormalizeRect();
	CRect t;
	t.UnionRect(scr,page);	
	Invalidate();
	SetScrollSizes (m_mode.map_mode, t.Size());
	ReleaseDC(pDC);
}


void CCadView::OnToolsLcolor() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSnapctr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetRadio(snap_menu == snapc);	
}

void CCadView::OnUpdateSnapendpoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(snap_menu == snapbb);
}

/*void CCadView::OnUpdateSnapon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(snap_menu);
	{/*
		pCmdUI->Enable(snap_menu==snapp);
		pCmdUI->Enable(snap_menu==snapq);
		pCmdUI->Enable(snap_menu==snapmi);
		pCmdUI->Enable(snap_menu==snapb);
		pCmdUI->Enable(snap_menu==snapt);
		pCmdUI->Enable(snap_menu==snapnear);
		pCmdUI->Enable(snap_menu==snapc);
		
	}

}*/
void CCadView::OnUpdateSnapmidpoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetRadio(snap_menu == snapmi);
}

void CCadView::OnUpdateSnapnear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(snap_menu == snapnear);
}

void CCadView::OnUpdateSnapoff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->SetRadio(snap_menu == snapoff);
}

void CCadView::OnUpdateSnappen(CCmdUI* pCmdUI) 
{
//	pCmdUI->SetRadio(snap_menu == snapp);
	
}

void CCadView::OnUpdateSnapquad(CCmdUI* pCmdUI) 
{
//		pCmdUI->SetRadio(snap_menu == snapq);
}

void CCadView::OnUpdateSnaptan(CCmdUI* pCmdUI) 
{
//		pCmdUI->SetRadio(snap_menu == snapt);
}

/*
void CCadView::OnGeometry() 

{
		CPropPage m_prop(_T ("Properties"));
	//	m_prop.Create(this);
		m_prop.DoModal();
	//	m_prop.ShowWindow(SW_SHOW);
	//	CLineProp ldlg;
	//	ldlg.DoModal();
		
		switch (select)
		case line:
			CLineProp ldlg;
			ldlg.DoModal();
			break;
		case spline:
			CSplineProp sdlg;
			sdlg.DoModal();
			break;
		case rectangle:
			CLineProp ldlg;
			ldlg.DoModal();
			break;
		case arc:
			CArcProp adlg;
			adlg.DoModal();
			break;

}
*/
/*void CCadView::OnCustomize() 
{
	// TODO: Add your command handler code here
	
}
*/
BOOL CCadView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCadView::OnChamfer() 
{
	menu=chamf;// TODO: Add your command handler code here

		// TODO: Add your command handler code here

	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

	CChamfD Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->setChamfparam(Adlg.m_chlgth);
//	menu=select;
	}
	ReleaseDC(hdc);
}

void CCadView::OnUpdateChamfer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==chamf);	
	
}

void CCadView::OnFillet() 
{
	menu=filt;// TODO: Add your command handler code here

	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

	CChamfD Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->setFiltparam(Adlg.m_chlgth);
//	menu=select;
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateFillet(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==filt);	
	
}

void CCadView::OnDimlv() 
{
	menu=DimLV;	
}

void CCadView::OnUpdateDimlv(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimLV);	
	
}

void CCadView::OnDimlh() 
{
	menu=DimLH;	
}

void CCadView::OnUpdateDimlh(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==DimLH);	
}

void CCadView::OnCopylinenocopy() 
{
	menu=copylinenocopy;
	
}

void CCadView::OnUpdateCopylinenocopy(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==copylinenocopy);		
}

void CCadView::OnOffset() 
{
	// TODO: Add your command handler code here
	menu=offset;

	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

	CRecArray Adlg;
	if(Adlg.DoModal()==IDOK)
	{
	pDoc->m_objects->pastearray(hdc,true,Adlg.m_rnb,Adlg.m_cnb,Adlg.m_dx,Adlg.m_dy,0,0);
	menu=select;
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateOffset(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==offset);		
}

void CCadView::OnTrim() 
{
	menu=trim;	
}

void CCadView::OnUpdateTrim(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==trim);		
}

void CCadView::OnEditAlayer() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CColorD colD;
	CDC *hdc=GetDC();
	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
	hdc->RealizePalette();

	hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	CRect scr1;												
															
	GetClientRect(&scr1);
	
	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);
	
	hdc->SetWindowOrg(0,0);

	OnPrepareDC(hdc);

//	pDoc->m_objects->grid(hdc,);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
}




void CCadView::OnImage() 
{
	menu=image;
	// TODO: Add your command handler code here
}

void CCadView::OnUpdateImage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==image);		
}


//DEL void CCadView::OnFileSaveAs() 
//DEL {
//DEL 	CCadDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL //	CColorD colD;
//DEL 	CDC *hdc=GetDC();
//DEL 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
//DEL 
//DEL 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
//DEL 	hdc->RealizePalette();
//DEL 	OnPrepareDC(hdc);
//DEL 
//DEL 
//DEL 	CFileDialog dllg(FALSE);
//DEL 	dllg.m_ofn.lpstrDefExt="deh";
//DEL 	dllg.m_ofn.lpstrFilter="AndyCad Files(*.deh)\0*.deh\0DIB Files(*.BMP)\0*.BMP\0SVG Files(*.svg)\0*.svg\0";
//DEL 	dllg.m_ofn.nFilterIndex=1;
//DEL 
//DEL 	if(dllg.DoModal()==IDOK)
//DEL 	{
//DEL 
//DEL 		try
//DEL 		{
//DEL 			CFile file(dllg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
//DEL 
//DEL 	
//DEL 			if(dllg.m_ofn.nFilterIndex==1)//(dllg.GetFileExt()=="bmp")
//DEL 			{
//DEL 			pDoc->m_objects->save(hdc,file);
//DEL 			}
//DEL 			else
//DEL 			if(dllg.m_ofn.nFilterIndex==2)//(dllg.GetFileExt()=="svg")
//DEL 			{
//DEL 				dllg.m_ofn.lpstrDefExt="bmp";
//DEL 				pDoc->m_objects->saveBMP(hdc,file);
//DEL      
//DEL 			}
//DEL 			else
//DEL 			if(dllg.m_ofn.nFilterIndex==3)//(dllg.GetFileExt()=="deh")
//DEL 			{
//DEL 				dllg.m_ofn.lpstrDefExt="svg";
//DEL 			}
//DEL 			file.Close();
//DEL 		}		
//DEL 		catch(CFileException * fx)
//DEL 		{
//DEL 			 TCHAR buf[255];
//DEL 			 fx->GetErrorMessage(buf, 255);
//DEL 			 CString strPrompt(buf);
//DEL 			 AfxMessageBox(strPrompt);
//DEL 		}
//DEL 
//DEL 	}
//DEL 
//DEL 
//DEL 	
//DEL }

void CCadView::Save(int fileindex, CStdioFile &file)
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	CColorD colD;
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
 
  	if(fileindex==1)//(dllg.GetFileExt()=="bmp")
 	{
 	pDoc->m_objects->save(hdc,file);
 	}
 	else
 	if(fileindex==4)//(dllg.GetFileExt()=="svg")
 	{
		CString output;
 	pDoc->m_objects->saveDXF(hdc,file);
 	}
 	else
 	if(fileindex==2)//(dllg.GetFileExt()=="svg")
 	{
		change=true;
		isSaving=true;
		OnDraw(hdc);
 		pDoc->m_objects->saveBMP(hmdc,bmp,file);
		isSaving=false;
 	}
 	ReleaseDC(hdc);
}
void CCadView::Save(int fileindex, CFile &file)
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	CColorD colD;
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
 
  	if((fileindex==1)||(fileindex==2)||(fileindex==3))//(dllg.GetFileExt()=="bmp")
 	{
	pDoc->m_objects->version=fileindex-1;
 	pDoc->m_objects->save(hdc,file);
 	}
 	else
 	if((fileindex==5)||(fileindex==6))//(dllg.GetFileExt()=="svg")
 	{
	//	change=true;
	//	isSaving=true;
	//	OnDraw(hdc);
		
		CSize p2=hdc->GetWindowExt();
		pDoc->m_objects->setPrintPage(CRect(CPoint(0,0),p2),1);
		CRect rall1=pDoc->m_objects->getAllBox();
		CSize wh=pDoc->m_objects->setpixel0(rall1.Width(),rall1.Height());
		CPoint p00=pDoc->m_objects->PrepareImage();
		CRect rall=pDoc->m_objects->getAllBox();
		rall.NormalizeRect();
		RECT ra=rall;
		double ytop=ra.top;
		ra.top=ra.bottom;
		ra.bottom=ytop;
//		rall=ra;
		CSize rss1=rall.Size();
//		CPoint p00=rall.TopLeft();
		CPoint p01=p00;
		CBitmap bmp2,bmp3;
		CBitmap* oldbmp2;
		hdc->LPtoDP(rall);
		hdc->LPtoDP(&p01);
		CSize rss=rall.Size();
		CDC hmdc1,hmdc2;
		hmdc1.CreateCompatibleDC(hdc);
		hmdc2.CreateCompatibleDC(hdc);
	 	OnPrepareDC(&hmdc1);
 		OnPrepareDC(&hmdc2);
//		bool rb1=bmp2.CreateCompatibleBitmap(hdc,rss1.cx,rss1.cy);//uz.cx+10,-(uz.cy+10));
		bool rb1=bmp2.CreateCompatibleBitmap(hdc,rss.cx,-rss.cy);//uz.cx+10,-(uz.cy+10));
//		bool rb2=bmp3.CreateCompatibleBitmap(hdc,rss1.cx,rss1.cy);//uz.cx+10,-(uz.cy+10));
		bool rb2=bmp3.CreateCompatibleBitmap(hdc,rss.cx,-rss.cy);//uz.cx+10,-(uz.cy+10));
		oldbmp=hmdc1.SelectObject(&bmp2);
		oldbmp2=hmdc2.SelectObject(&bmp3);
		HBRUSH br=(HBRUSH)SelectObject(hmdc1.GetSafeHdc(),GetStockObject(WHITE_BRUSH));
		CRect t=CRect(CPoint(0,0)/*p00*/,CSize(rss1.cx,-rss1.cy));
		bool b=hmdc1.Rectangle(t);
		hmdc1.LPtoDP(t);
		CRect t2=CRect(CPoint(0,0),CSize(rss1.cx,-rss1.cy));
		HBRUSH br1=(HBRUSH)SelectObject(hmdc2.GetSafeHdc(),GetStockObject(GRAY_BRUSH));
		hmdc2.Rectangle(t2);
		pDoc->m_objects->drawforbmp(&hmdc1);		
//		hmdc2.BitBlt(0,0,rss.cx,rss.cy,&hmdc1,p00.x,p00.y,SRCCOPY);
		hmdc2.StretchBlt(0,0,rss1.cx,-rss1.cy,&hmdc1,0,0,/*p00.x,p00.y,*/rss1.cx,-rss1.cy,SRCCOPY);
		if(fileindex==5)
			pDoc->m_objects->savePNG(&hmdc1,&bmp3,file);
		else
			pDoc->m_objects->saveJPG(&hmdc1,&bmp3,file);

		hmdc1.SelectObject(oldbmp);
		hmdc2.SelectObject(oldbmp2);
		CRect wcr;
		GetClientRect(&wcr);
		CDC* pDC=GetDC();
		OnPrepareDC(pDC);
		int map;
		CSize s;
		pDC->DPtoLP(&wcr);
		
		change=true;
		wcr.NormalizeRect();

		CSize sz(wcr.Size().cx,wcr.Size().cy);
		pDoc->m_objects->setpixel0(sz.cx,sz.cy);
		pDoc->m_objects->endPrint();
	//	isSaving=false;
 	}
 	ReleaseDC(hdc);
}

void CCadView::Open(int fileindex,CFile &file)
{
	change=false;
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	CColorD colD;
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
 
  	if(fileindex==1)//(dllg.GetFileExt()=="bmp")
 	{
 	pDoc->m_objects->open(hdc,file);
	pDoc->m_objects->initlayer(mg->m_wndlaydia.m_liblist);

 	}
 	else
 	if(fileindex==2)//(dllg.GetFileExt()=="svg")
 	{
		;
 	}
 	else
 	if(fileindex==3)//(dllg.GetFileExt()=="deh")
 	{
		;
 	}
	ReleaseDC(hdc);
	change=true;
	Invalidate();
 
}

void CCadView::OnEditDel() 
{
	m_bpastenow = TRUE;

    CDC *hdc=GetDC();
	
	OnPrepareDC(hdc);

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_objects->deleteObject(hdc);
	ReleaseDC(hdc);
    change=true;
	Invalidate();
	
}

void CCadView::import(int fileindex, CStdioFile &file)
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	CColorD colD;
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
 
  	if(fileindex==1)//(dllg.GetFileExt()=="bmp")
 	{
 	pDoc->m_objects->import(hdc,file);
 	}
 	else
 	if(fileindex==2)//(dllg.GetFileExt()=="svg")
 	{
		CString output;
	pDoc->m_parserdxf->executeFile(hdc,file,output);
 	}
 	else
 	if(fileindex==3)//(dllg.GetFileExt()=="deh")
 	{
		;
 	}
	ReleaseDC(hdc);
	change=true;
	Invalidate();

}
void CCadView::import(int fileindex, CFile &file)
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	CColorD colD;
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
 
  	if(fileindex==1)//(dllg.GetFileExt()=="bmp")
 	{
 	pDoc->m_objects->import(hdc,file);
 	}
	ReleaseDC(hdc);
	change=true;
	Invalidate();

}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CCadView::OnCancelEditSrvr()
{
//	GetDocument()->OnDeactivateUI(FALSE);
}

void CCadView::OnHelpRegistration() 
{
	CRegister dlg;
	dlg.DoModal();	
}

void CCadView::OnHelpWwwandycadcom() 
{
	CInternetSession ss;
	CStdioFile* web;
	CString site;
	site="http://andycad.com.ng/help/";
	ShellExecute(0,NULL,site,NULL,NULL,SW_SHOWDEFAULT);
}

/*void CCadView::OnEditClear() 
{
	m_bpastenow = TRUE;

    CDC *hdc=GetDC();
	
////  hdc->SetMapMode(MM_ISOTROPIC);
	hdc->SetWindowExt(100,100);
	hdc->SetViewportExt(100*zoomrat,100*zoomrat);
	hdc->SetWindowOrg(0,0);
	
	CRect scr1;;

	GetClientRect(&scr1);

	currentPosdev=currentPos;
	hdc->LPtoDP(&currentPosdev);

	hdc->SetViewportOrg(scr1.Width()/2-currentPosdev.cx,scr1.Height()/2-currentPosdev.cy);//
	OnPrepareDC(hdc);

	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_objects->cut(hdc);
    change=true;
	Invalidate();
	ReleaseDC(hdc);	
}*/

/*void CCadView::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}*/


void CCadView::OnTblib() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::libupdate()
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->Initlib(mg->m_wndlibdia);//.m_libtree);//GetDlgItem(IDC_LIBT1));//l.m_libtree);
	ReleaseDC(hdc);

}

void CCadView::draglib(CString &f, CString &l,CPoint point)
{
	mouse.setMove(false);
	mouse.setLBdown(true);
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	
	menu=select;
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	hdc->DPtoLP(&point);
	mouse.setPrevPos(point);
	pDoc->m_objects->Insertlib(hdc,f,l,point);
	change=true;
	Invalidate();
	ReleaseDC(hdc);
}





CPoint CCadView::getpos()
{
	return pos;

}

void CCadView::Unfill()
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->unfill(hdc);
	ReleaseDC(hdc);
	change=true;
	Invalidate(TRUE);
}

void CCadView::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==10)
	{
		char result[MAX_PATH],dir[MAX_PATH];

		GetTempPath(MAX_PATH,dir);

		 /* Attempt to find a unique filename: */
		GetTempFileName(dir, // dir. for temp. files 
		"andyc",                // temp. filename prefix 
		0,                    // create unique name 
		result);          // buffer for name 

		CStdioFile filo(result,CFile::modeCreate|CFile::modeReadWrite);

		Save(1,filo);

		CStdioFile file("temp000.aff",CFile::modeCreate | CFile::modeWrite);
		DWORD length=filo.GetLength();
		BYTE* b=new BYTE[length];
		filo.SeekToBegin();
		filo.Read(b,length);
		filo.Close();
		file.Write(b,length);
		file.Remove(result);
		file.Close();
		delete b;

	}
	else
	if(nIDEvent==2)
	{
		CDC *hdc=GetDC();
 		CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 		OnPrepareDC(hdc);
 		snap.clear(hdc);
		ReleaseDC(hdc);

	}
	CScrollView::OnTimer(nIDEvent);
}


void CCadView::OnUpdateSnapon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(snap_menu);
}

void CCadView::update()
{
	change=true;
	Invalidate(TRUE);
}

void CCadView::OnCampad() 
{
	menu=campad;
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateCampad(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnCamrot() 
{
	menu=camrot;
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CVector v0;
	pDoc->m_objects->setCenter(v0);
	ReleaseDC(hdc);
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateCamrot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfa() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
 
	pDoc->m_objects->surface("loft",vthick,vctop,vcbot,hmdc);
	ReleaseDC(hdc);
}

void CCadView::OnUpdateSurfa(CCmdUI* pCmdUI) 
{
 	
}

void CCadView::OnTdegp() 
{
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->degel(hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateTdegp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::Onsurfrev() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
	OnPrepareDC(hdc);

	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
	pDoc->m_objects->surface("simplerevol",vthick,vctop,vcbot,hmdc);
	change=true;
	Invalidate();
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdatesurfrev(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::Onsurfext() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CThickD dthick;
	dthick.ext=true;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
		pDoc->m_objects->surface("extrus",vthick,vctop,vcbot,hdc,dthick.m_ext);
	}
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdatesurfext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::Onsurfcoon() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}

	pDoc->m_objects->surface("gextrusion",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdatesurfcoon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnVol() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->volume(hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateVol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnButton40142() 
{
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("perpective");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnPtselect() 
{
	menu=spoint;
	submenu=nothing;
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setVmode(hdc);
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdatePtselect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(menu==spoint);
	
}
/*
void CCadView::OnFill() 
{
	// TODO: Add your command handler code here
	menu=fill;	
}

void CCadView::OnUpdateFill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==fill);
	
}
*/

void CCadView::OnFreecamera() 
{
	menu=camrot;
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateFreecamera(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==campad);
}

void CCadView::OnFrontview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
   	selectedview=front;


 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("front");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateFrontview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==front);
}

void CCadView::OnBackview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=back;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("back");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateBackview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==back);
}

void CCadView::OnLeftview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=left;

	
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("left");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateLeftview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==left);
}

void CCadView::OnNortheast() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=ne;


 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("NE");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateNortheast(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==ne);

}

void CCadView::OnNorthwestview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	selectedview=nw;

	pDoc->m_objects->perpective("NW");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateNorthwestview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==nw);
}

void CCadView::OnRightview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
    
	selectedview=right;
 	
	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("right");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateRightview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedview==right);
}

void CCadView::OnShape2dwired() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShape2dwired(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnShape3dwire() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShape3dwire(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnShapeflat() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShapeflat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnShapeflatedgeon() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShapeflatedgeon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnShapegourand() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShapegourand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnShapegourandedgeon() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateShapegourandedgeon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidbox() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidbox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidcone() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidcone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidcylinder() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidcylinder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidrorus() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidrorus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidshpere() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidshpere(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSolidwedge() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSolidwedge(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSoutheastview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();

	selectedview=se;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("SE");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateSoutheastview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(selectedview==se);
	
}

void CCadView::OnSouthwestview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=sw;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("SW");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateSouthwestview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(selectedview==sw);
	
}

void CCadView::OnSurafce2dsolid() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurafce2dsolid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurface3d() 
{
	// TODO: Add your command handler code here
		CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
 
	pDoc->m_objects->surface("loft",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
//	change=true;
//	Invalidate(TRUE);

}

void CCadView::OnUpdateSurface3d(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurface3dmesh() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurface3dmesh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacebox() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacebox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacecone() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
	pDoc->m_objects->surface("coon",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateSurfacecone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacedish() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacedish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacedome() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacedome(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfaceedge() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfaceedge(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacerevolved() 
{
    CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
 
	pDoc->m_objects->surface("revol",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);

}

void CCadView::OnUpdateSurfacerevolved(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfaceruled() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfaceruled(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacesphere() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacesphere(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacespyramid() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacespyramid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacetabulated() 
{
	// TODO: Add your command handler code here
CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
	pDoc->m_objects->surface("extrus",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
}

void CCadView::OnUpdateSurfacetabulated(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacetorus() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacetorus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnSurfacewedge() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateSurfacewedge(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnBottomview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=bottom;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("bottom");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateBottomview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(selectedview==bottom);
	
}

void CCadView::OnCamerarotation() 
{
	// TODO: Add your command handler code here
	menu=camrot;
}

void CCadView::OnUpdateCamerarotation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   pCmdUI->SetRadio(menu==camrot);	
}

void CCadView::OnBucketfill() 
{
	// TODO: Add your command handler code here
		menu=fill;
	
}

void CCadView::OnUpdateBucketfill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==fill);
}

void CCadView::OnTopview() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 	selectedview=top;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->perpective("top");
	ReleaseDC(hdc);
	change=true;
	Invalidate();
	
}

void CCadView::OnUpdateTopview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(selectedview==top);
}

void CCadView::OnTransparency() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 

	CTransDlg dlg;

	pDoc->m_objects->setInterest(&dlg);
	dlg.setview(this);
	dlg.DoModal();
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateTransparency(CCmdUI* pCmdUI) 
{
//	pCmdUI->SetRadio(menu==fill);
	// TODO: Add your command update UI handler code here
	
}

/*void CCadView::OnToolsGrid() 
{
	// TODO: Add your command handler code here
	
}*/

void CCadView::OnUpdateToolsGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnChangeTexture(CString s)
{
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setTexture(s,hdc);
	change=true;
	Invalidate();
	ReleaseDC(hdc);

}



void CCadView::OnRender() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateRender(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnRenderprefer() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateRenderprefer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnLight() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateLight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnFog() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateFog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateHelpWwwandycadcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(TRUE);
}

void CCadView::OnHelpFinder() 
{

	CInternetSession ss;
	CStdioFile* fp;
	CFile myfile;
    CFileFind findhelp;
	CString ahelp;
	CString helpfname, helpfpath;
	CString myname= "cad.htm";

	CFileFind finder;
	bool bWorking=finder.FindFile("cad.htm");
	
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	}

//    CFile file.Open(finder.GetFilePath(),CFile::modeRead);

		
	
	findhelp.Close();
}

void CCadView::OnUpdateHelpFinder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(FALSE);
}

void CCadView::OnDrawArcstartcenterend() 
{
	// TODO: Add your command handler code here
	menu=arc32;
}

void CCadView::OnUpdateDrawArcstartcenterend(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==arc32);
	
}

void CCadView::OnSnapfront() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	selectedplane=pfront;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setsnapplane("front");
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateSnapfront(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedplane==pfront);
}

void CCadView::OnSnapleft() 
{
	// TODO: Add your command handler code here
	
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	selectedplane=pleft;

 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setsnapplane("left");
	ReleaseDC(hdc);
}

void CCadView::OnUpdateSnapleft(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedplane==pleft);
}

void CCadView::OnSnaptop() 
{
	// TODO: Add your command handler code here
	
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	selectedplane=ptop;
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setsnapplane("top");
	ReleaseDC(hdc);
}

void CCadView::OnUpdateSnaptop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(selectedplane==ptop);
}

void CCadView::OnTransform2Ffd() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setFFD("2x2x2");
	ReleaseDC(hdc);
	
}
void CCadView::OnTransform3Ffd() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setFFD("3x3x3");
	ReleaseDC(hdc);
	
}
void CCadView::OnTransform4Ffd() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	pDoc->m_objects->setFFD("4x4x4");
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateTransform2Ffd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CCadView::OnUpdateTransform3Ffd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CCadView::OnUpdateTransform4Ffd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnRButtonDblClk(nFlags, point);
}

void CCadView::OnDrawBox() 
{
	// TODO: Add your command handler code here
	menu=box;
}

void CCadView::OnEditSmooth() 
{
	// TODO: Add your command handler code here
	CSmoothD sm;
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	if(sm.DoModal()==IDOK)
		pDoc->m_objects->smooth(sm.m_us,sm.m_vs,sm.m_ws);
	ReleaseDC(hdc);
}


void CCadView::OnEditLight() 
{
	// TODO: Add your command handler code here
	
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 


	void** param[3];
	float spec1[3];
	spec1[0]=(lightdlg.m_sr/255);
	spec1[1]=(lightdlg.m_sg/255);

	float amb1[3];
	amb1[0]=(lightdlg.m_ar/255);
	amb1[1]=(lightdlg.m_ag/255);
	amb1[2]=(lightdlg.m_ab/255);

	float diff1[3];
	diff1[0]=(lightdlg.m_dr/255);
	diff1[1]=(lightdlg.m_dg/255);
	diff1[2]=(lightdlg.m_db/255);

	float pos1[3];
	pos1[0]=lightdlg.m_x;
	pos1[1]=lightdlg.m_y;
	pos1[2]=lightdlg.m_z;


	int* spec[3];
	spec[0]=&lightdlg.m_sr;
	spec[1]=&lightdlg.m_sg;

	int *amb[3];
	amb[0]=&lightdlg.m_ar;
	amb[1]=&lightdlg.m_ag;
	amb[2]=&lightdlg.m_ab;

	int *diff[3];
	diff[0]=&lightdlg.m_dr;
	diff[1]=&lightdlg.m_dg;
	diff[2]=&lightdlg.m_db;

	float *pos[3];
	pos[0]=&lightdlg.m_x;
	pos[1]=&lightdlg.m_y;
	pos[2]=&lightdlg.m_z;
	
	
	
	param[0]=(void**)spec;
	param[1]=(void**)amb;
	param[2]=(void**)diff;
	param[3]=(void**)pos;


	pDoc->m_objects->getlightpara(param);
	lightdlg.updatepara();
	lightdlg.setview(this);
	lightdlg.ShowWindow(SW_SHOWNORMAL);
/*	if(lightdlg.DoModal()==IDCANCEL)
	{
		void* param1[3];
		param1[0]=spec1;
		param1[1]=amb1;
		param1[2]=pos1;
		
		pDoc->m_objects->SendNotify("Light",param1);
		change=true;
		Invalidate();

	}*/
	ReleaseDC(hdc);
}

void CCadView::OnEditCamera() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 
	menu=camset;

	void** param[3];
	float pos[3];
	pos[0]=(camdlg.m_xp);
	pos[1]=(camdlg.m_yp);
	pos[2]=(camdlg.m_zp);

	float target[3];
	target[0]=(camdlg.m_xt);
	target[1]=(camdlg.m_yt);
	target[2]=(camdlg.m_zt);

	float plane[2];
	plane[0]=(camdlg.m_fp);
	plane[1]=(camdlg.m_np);

	int fov[1];
	fov[0]=(camdlg.m_fov);

	float* pos1[3];
	pos1[0]=&camdlg.m_xp;
	pos1[1]=&camdlg.m_yp;
	pos1[2]=&camdlg.m_zp;

	float* target1[3];
	target1[0]=&camdlg.m_xt;
	target1[1]=&camdlg.m_yt;
	target1[2]=&camdlg.m_zt;
	
	float* plane1[2];
	plane1[0]=&camdlg.m_fp;
	plane1[1]=&camdlg.m_np;

	int* fov1[1];
	fov1[0]=&camdlg.m_fov;

	param[0]=(void**)pos1;
	param[1]=(void**)target1;
	param[2]=(void**)plane1;
	param[3]=(void**)fov1;


	pDoc->m_objects->getcampara(param);
	camdlg.updatepara();
	camdlg.setview(this);
	camdlg.ShowWindow(SW_SHOWNORMAL);
/*	if(lightdlg.DoModal()==IDCANCEL)
	{
		void* param1[3];
		param1[0]=spec1;
		param1[1]=amb1;
		param1[2]=pos1;
		
		pDoc->m_objects->SendNotify("Light",param1);
		change=true;
		Invalidate();

	}*/
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateEditCamera(CCmdUI* pCmdUI) 
{
	//pCmdUI->SetRadio(menu==fill);
}

void CCadView::OnEditClear() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEditDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEditLight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEditSmooth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEeeSolid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEffectZoomin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnUpdateEffectZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnModifyFloodfill() 
{
	// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateModifyFloodfill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnGeometry() 
{
		CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *hdc=GetDC();
	OnPrepareDC(hdc);

//    hdc->DPtoLP(point);
	if(pDoc->m_objects->getselect())
	{
		COBJEdit edt;
		edt.setobj(pDoc->m_objects->getobif());
		if(edt.DoModal()==IDOK)
		{
			pDoc->m_objects->setobjinfo(edt.m_auth,edt.m_descr,\
										edt.m_name,edt.m_cost);

		}
	}

	ReleaseDC(hdc);

}

void CCadView::OnUpdateGeometry(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnTbscale() 
{
	// TODO: Add your command handler code here
	menu=scale;
}

void CCadView::OnUpdateTbscale(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(menu==scale);
	
}

void CCadView::OnModifySurfacecap() 
{
	// TODO: Add your command handler code here
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *hdc=GetDC();
	OnPrepareDC(hdc);

//    hdc->DPtoLP(point);
	CDlgCap cap;
	if(cap.DoModal()==IDOK)
	{
		pDoc->m_objects->cap(cap.m_cbot,cap.m_ctop,cap.m_style,hdc);
	}
	change=true;
	Invalidate();
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdateModifySurfacecap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::Onsuftext2() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}
	pDoc->m_objects->surface("extrus2",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnUpdatesuftext2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}



void CCadView::Onsurfext3() 
{
	// TODO: Add your command handler code here
 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);
 	CThickD dthick;
	float vthick=0;
	bool vctop=false,vcbot=false;
	if(dthick.DoModal()==IDOK)
	{
		vthick=dthick.m_thickness;
		vctop=dthick.m_ctop;
		vcbot=dthick.m_cbot;
	}

	pDoc->m_objects->surface("gextrusion",vthick,vctop,vcbot,hdc);
	ReleaseDC(hdc);
	
}

void CCadView::OnModifyJoin() 
{
	// TODO: Add your command handler code here
/* 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);

	pDoc->m_objects->join(true,hdc);
	ReleaseDC(hdc);*/
	menu=extend;

	
}
void CCadView::OnModifyClip() 
{
	// TODO: Add your command handler code here
/* 	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	OnPrepareDC(hdc);

	pDoc->m_objects->join(true,hdc);
	ReleaseDC(hdc);*/
	menu=clip;

	
}

void CCadView::OnUpdateModifyJoin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnCamswiv() 
{
	// TODO: Add your command handler code here
menu=camsw;	
}

void CCadView::OnUpdateCamswiv(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnProperties() 
{
	CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

		
	if(pDoc->m_objects->getselect())
	{
 	  COBJEdit edt;
	 // edt.DoModal();
	  edt.setobj(pDoc->m_objects->getobif());
		if(edt.DoModal()==IDOK)
		{
			pDoc->m_objects->setobjinfo(edt.m_auth,edt.m_descr,\
								edt.m_name,edt.m_cost);
	
			}
	}
	
}

void CCadView::OnUpdateProperties(CCmdUI* pCmdUI) 
{
    /*CCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *hdc=GetDC();
	OnPrepareDC(hdc);

	if(pDoc->m_objects->getselect())
	{
		COBJEdit edt;
		edt.setobj(pDoc->m_objects->getobif());
		edt.DoModal();

		if(edt.DoModal()==IDOK)
		{
			pDoc->m_objects->setobjinfo(edt.m_auth,edt.m_descr,\
										edt.m_name,edt.m_cost);

		}
	}
*/
	
}

void CCadView::OnViewPanDown() 
{
menu=select;		
menu=campad;
		// TODO: Add your command handler code here
	
}

void CCadView::OnUpdateViewPanDown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnViewPanLeft() 
{
menu=select;		
menu=campad;
	
}

void CCadView::OnUpdateViewPanLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnViewPanRight() 
{
	// TODO: Add your command handler code here
	menu=select;		
menu=campad;
	
}

void CCadView::OnUpdateViewPanRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCadView::OnViewPanUp() 
{
	// TODO: Add your command handler code here
	menu=select;		
menu=campad;
	
}

void CCadView::OnUpdateViewPanUp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

bool CCadView::getInit()
{
	return initOK;
}

void CCadView::Select(CFigure *f,bool full)
{
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	if(m_nMapMode != NULL)
	OnPrepareDC(hdc);
	pDoc->m_objects->Select(f,hdc,full);
	ReleaseDC(hdc);
}

void CCadView::Close(CFigure *f)
{
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 	CDC *hdc=GetDC();
 	CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 	hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 	hdc->RealizePalette();
 	if(m_nMapMode != NULL)
	OnPrepareDC(hdc);
	pDoc->m_objects->Close(f,hdc);
	ReleaseDC(hdc);

}

void CCadView::OnDrawSolidSphere() 
{
	// TODO: Add your command handler code here
	menu=sphere;
}

void CCadView::OnDrawPlane() 
{
	// TODO: Add your command handler code here
	menu=plane;
}

void CCadView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSize p2=pDC->GetWindowExt();
	CSize p1=pDC->GetViewportExt();

	pDC->SetMapMode(m_mode.map_mode);
	pDC->SetViewportOrg(CPoint(0,0));
	pDC->SetWindowOrg(CPoint(0,0));
	p2=pDC->GetWindowExt();
	p1=pDC->GetViewportExt();
	if(pDC->IsPrinting()&&(pInfo!=NULL))
	{
	CRect g(CPoint(0,0),m_mode.Sg);
	pInfo->m_rectDraw=g;
	pInfo->SetMaxPage(1);
	pInfo->m_nNumPreviewPages=1;
	}
	
//	CScrollView::OnPrepareDC(pDC, pInfo);
}



void CCadView::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);
	change=true;
	CCadDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
//	pDoc->m_objects->mouseon=false;
	Invalidate();
	// TODO: Add your message handler code here
	
}

void CCadView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
//	change=true;
	Invalidate();
	// TODO: Add your message handler code here
	
}

CBitmap* CCadView::getRegion(CRect r)
{
 return NULL;
}


void CCadView::SendNotify(CString s, void *param[])
{
	if(s=="Parser")
	{
		CString input=*(CString*)param[0];
		CString output=*(CString*)param[1];
		output.MakeLower();
		input.MakeLower();
		int i=output.Find("line");
		if(i!=-1)
			menu=Line;
		 i=output.Find("rect");
		if(i!=-1)
			menu=Rectangle;
		 i=output.Find("spline");
		if(i!=-1)
			menu=polybezier;
		 i=output.Find("circle");
		if(i!=-1)
			menu=Circle;
		i=input.Find("command:");
		if(i!=-1)
		{
			menu=select;
			submenu=nothing;
 			CCadDoc* pDoc = GetDocument();
 			ASSERT_VALID(pDoc);
 			CDC *hdc=GetDC();
 			CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
 
 			hdc->SelectPalette(&mg->colorToolBar.palette,FALSE);
 			hdc->RealizePalette();
 			OnPrepareDC(hdc);
 
			pDoc->m_objects->setBmode(hdc);
			ReleaseDC(hdc);
			change=true;
			Invalidate();
		}
	}

}





LRESULT CCadView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CScrollView::WindowProc(message, wParam, lParam);
}
void CCadView::OnFilePrintSetup()
{
	CPrintDialog dlg(TRUE);
	::AfxGetApp()->DoPrintDialog(&dlg);
	DEVMODE* dv;
	dv=	dlg.GetDevMode();

}

void CCadView::OnModifyPointconstraint() 
{
	// TODO: Add your command handler code here
			submenu=pointconstraint;
	pointconstraint_mode=pointconstraint_item;
}
void CCadView::OnModifyVectorconstraint() 
{
	// TODO: Add your command handler code here
			submenu=vectorconstraint;
		vectorconstraint_mode=vectorconstraint_item;
}
void CCadView::OnModifyVerticalconstraint() 
{
	// TODO: Add your command handler code here
			submenu=vectorconstraint;
		vectorconstraint_mode=vertical;
}
void CCadView::OnModifyHorizontalconstraint() 
{
	// TODO: Add your command handler code here
			submenu=vectorconstraint;
		vectorconstraint_mode=horizontal;
}
void CCadView::OnModifyParallelconstraint() 
{
	// TODO: Add your command handler code here
			submenu=vectorconstraint;
		vectorconstraint_mode=parallel;
}
void CCadView::OnModifyPerpendicularconstraint() 
{
	// TODO: Add your command handler code here
			submenu=vectorconstraint;
		vectorconstraint_mode=perpendicular;
}
