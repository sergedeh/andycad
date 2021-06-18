// CadAutoCamera.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "CadAutoCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCamera

IMPLEMENT_DYNCREATE(CCadAutoCamera, CCmdTarget)

CCadAutoCamera::CCadAutoCamera()
{
	EnableAutomation();
}

CCadAutoCamera::~CCadAutoCamera()
{
}


void CCadAutoCamera::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoCamera, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoCamera, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoCamera)
	DISP_PROPERTY_EX(CCadAutoCamera, "fPlane", GetFPlane, SetFPlane, VT_R4)
	DISP_PROPERTY_EX(CCadAutoCamera, "nPlane", GetNPlane, SetNPlane, VT_R4)
	DISP_PROPERTY_EX(CCadAutoCamera, "FOV", GetFOV, SetFOV, VT_R4)
	DISP_PROPERTY_EX(CCadAutoCamera, "View", GetView, SetView, VT_I2)
	DISP_PROPERTY_EX(CCadAutoCamera, "Perspective", GetPerspective, SetPerspective, VT_I2)
	DISP_FUNCTION(CCadAutoCamera, "Zoom", Zoom, VT_EMPTY, VTS_R4)
	DISP_FUNCTION(CCadAutoCamera, "Rotate", Rotate, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoCamera, "LooktAt", LooktAt, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoCamera, "Init", Init, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CCadAutoCamera, "Translate", Translate, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoCamera, "Swivel", Swivel, VT_EMPTY, VTS_R4 VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoCamera to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {14A4B89B-0C9A-43D5-A875-CCBF6E652716}
static const IID IID_ICadAutoVector =
{ 0x14a4b89b, 0xc9a, 0x43d5, { 0xa8, 0x75, 0xcc, 0xbf, 0x6e, 0x65, 0x27, 0x16 } };


// {7822402F-3215-4B6C-8B6E-EB9DB14EA2D3}
static const IID IID_ICadAutoCamera =
{ 0x7822402f, 0x3215, 0x4b6c, { 0x8b, 0x6e, 0xeb, 0x9d, 0xb1, 0x4e, 0xa2, 0xd3 } };

BEGIN_INTERFACE_MAP(CCadAutoCamera, CCmdTarget)
	INTERFACE_PART(CCadAutoCamera, IID_ICadAutoCamera, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCamera message handlers

void CCadAutoCamera::Zoom(float u) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->setzoomrat(u);
}

void CCadAutoCamera::Translate(LPDISPATCH v) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr2=v->QueryInterface(IID_ICadAutoVector,(void**) &v);
	if(SUCCEEDED(hr2))
	{
	VARIANT f1;
	COleDispatchDriver d2;
	d2.AttachDispatch(v);
	CVector v2;
	d2.GetProperty(0x4,VT_VARIANT,(void*)&f1);
	v2=*(CVector*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->translatecam(v2);
	}
}

void CCadAutoCamera::Rotate(float angle, short axis) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->rotatecam(axis,angle);
}

void CCadAutoCamera::Swivel(float angle, short axis) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->rotatecam(axis,angle,true);
}

void CCadAutoCamera::LooktAt(LPDISPATCH cam_pos, LPDISPATCH target_pos) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=cam_pos->QueryInterface(IID_ICadAutoVector,(void**) &cam_pos);
	HRESULT hr2=target_pos->QueryInterface(IID_ICadAutoVector,(void**) &target_pos);
/*	if(SUCCEEDED(hr2))
	{
	VARIANT f1;
	COleDispatchDriver d2;
	d2.AttachDispatch(v);
	CVector v2;
	d2.GetProperty(0x4,VT_VARIANT,(void*)&f1);
	v2=*(CVector*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->translatecam(v2);
	}
*/
}

float CCadAutoCamera::GetFPlane() 
{
	// TODO: Add your property handler here

	return 0.0f;
}

void CCadAutoCamera::SetFPlane(float newValue) 
{
	// TODO: Add your property handler here

}

float CCadAutoCamera::GetNPlane() 
{
	// TODO: Add your property handler here

	return 0.0f;
}

void CCadAutoCamera::SetNPlane(float newValue) 
{
	// TODO: Add your property handler here

}

float CCadAutoCamera::GetFOV() 
{
	// TODO: Add your property handler here

	return 0.0f;
}

void CCadAutoCamera::SetFOV(float newValue) 
{
	// TODO: Add your property handler here

}

short CCadAutoCamera::GetView() 
{
	// TODO: Add your property handler here

	return 0;
}

void CCadAutoCamera::SetView(short nNewValue) 
{
	// TODO: Add your property handler here

}

short CCadAutoCamera::GetPerspective() 
{
	// TODO: Add your property handler here

	return 0;
}

void CCadAutoCamera::SetPerspective(short nNewValue) 
{
	// TODO: Add your property handler here

}

void CCadAutoCamera::Init() 
{
	// TODO: Add your dispatch handler code here

}

