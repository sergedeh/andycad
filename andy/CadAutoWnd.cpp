// CadAutoWnd.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "cadview.h"
#include "CadAutoWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoWnd

IMPLEMENT_DYNCREATE(CCadAutoWnd, CCmdTarget)

CCadAutoWnd::CCadAutoWnd()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CCadAutoWnd::~CCadAutoWnd()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CCadAutoWnd::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoWnd, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoWnd, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoWnd)
	DISP_PROPERTY_EX(CCadAutoWnd, "Visible", GetVisible, SetVisible, VT_BOOL)
	DISP_PROPERTY_EX(CCadAutoWnd, "camera", GetCamera, SetCamera, VT_DISPATCH)
	DISP_FUNCTION(CCadAutoWnd, "Refresh", Refresh, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoWnd to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {6CE928A1-E790-4E91-AFCC-0E22993746F0}
static const IID IID_ICadAutoWnd =
{ 0x6ce928a1, 0xe790, 0x4e91, { 0xaf, 0xcc, 0xe, 0x22, 0x99, 0x37, 0x46, 0xf0 } };

BEGIN_INTERFACE_MAP(CCadAutoWnd, CCmdTarget)
	INTERFACE_PART(CCadAutoWnd, IID_ICadAutoWnd, Dispatch)
END_INTERFACE_MAP()

// {343F6C50-8F61-4375-9B4A-A4D80BD3E3CE}
IMPLEMENT_OLECREATE(CCadAutoWnd, "AndyCAD.Window", 0x343f6c50, 0x8f61, 0x4375, 0x9b, 0x4a, 0xa4, 0xd8, 0xb, 0xd3, 0xe3, 0xce)

/////////////////////////////////////////////////////////////////////////////
// CCadAutoWnd message handlers

BOOL CCadAutoWnd::GetVisible() 
{
	// TODO: Add your property handler here
	return AfxGetMainWnd ()->IsWindowVisible ();
}

void CCadAutoWnd::SetVisible(BOOL bNewValue) 
{
	// TODO: Add your property handler here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	if(!pView->getInit())
		pView->OnInitialUpdate();
	AfxGetMainWnd()->ShowWindow (bNewValue ? SW_SHOWMAXIMIZED : SW_HIDE);
 
}

void CCadAutoWnd::Refresh() 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->UpdateAllViews (NULL);
}

LPDISPATCH CCadAutoWnd::GetCamera() 
{
	// TODO: Add your property handler here
	auto_cam=new CCadAutoCamera;
	return auto_cam->GetIDispatch(TRUE);
}

void CCadAutoWnd::SetCamera(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}
