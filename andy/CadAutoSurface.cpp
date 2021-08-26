// CadAutoSurface.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "CadAutoSurface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoSurface

IMPLEMENT_DYNCREATE(CCadAutoSurface, CCmdTarget)

CCadAutoSurface::CCadAutoSurface()
{
	EnableAutomation();
}

CCadAutoSurface::~CCadAutoSurface()
{
}


void CCadAutoSurface::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoSurface, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoSurface)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoSurface, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoSurface)
	DISP_FUNCTION(CCadAutoSurface, "Loft", Loft, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoSurface, "Extrude", Extrude, VT_EMPTY, VTS_R4 VTS_I2 VTS_R4)
	DISP_FUNCTION(CCadAutoSurface, "Extrude2", Extrude2, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoSurface, "gCylinder", gCylinder, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoSurface, "Revolve", Revolve, VT_EMPTY, VTS_R4 VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoSurface to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {164D0D08-3145-4901-BE22-84C48469A330}
static const IID IID_ICadAutoSurface =
{ 0x164d0d08, 0x3145, 0x4901, { 0xbe, 0x22, 0x84, 0xc4, 0x84, 0x69, 0xa3, 0x30 } };

BEGIN_INTERFACE_MAP(CCadAutoSurface, CCmdTarget)
	INTERFACE_PART(CCadAutoSurface, IID_ICadAutoSurface, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoSurface message handlers

void CCadAutoSurface::Loft(float thick, short cap) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->surface2("loft",thick,cap);
}

void CCadAutoSurface::Extrude(float thick, short cap, float extr) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->surface2("extrus",thick,cap,extr);

}

void CCadAutoSurface::Extrude2(float thick, short cap) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->surface2("extrus2",thick,cap);

}

void CCadAutoSurface::gCylinder(float thick, short cap) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->surface2("gextrusion",thick,cap);

}

void CCadAutoSurface::Revolve(float thick, short cap) 
{
	// TODO: Add your dispatch handler code here

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->surface2("simplerevol",thick,cap);
}
