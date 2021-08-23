// CadAutoCanvas.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "CadAutoCanvas.h"
#include "CadAutoShape.h"	// Added by ClassView

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCanvas

IMPLEMENT_DYNCREATE(CCadAutoCanvas, CCmdTarget)

CCadAutoCanvas::CCadAutoCanvas()
{
	EnableAutomation();
}

CCadAutoCanvas::~CCadAutoCanvas()
{
}


void CCadAutoCanvas::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoCanvas, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoCanvas)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoCanvas, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoCanvas)
	DISP_PROPERTY_EX(CCadAutoCanvas, "Drawing", GetDrawing, SetDrawing, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoCanvas, "Edit", GetEdit, SetEdit, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoCanvas, "Transform", GetTransform, SetTransform, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoCanvas, "Surface", GetSurface, SetSurface, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoCanvas, "Shape", GetShape, SetShape, VT_DISPATCH)
	DISP_FUNCTION(CCadAutoCanvas, "Save", Save, VT_BOOL, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoCanvas to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {49302417-D30F-4DA6-B973-8F65E12E9223}
static const IID IID_ICadAutoCanvas =
{ 0x49302417, 0xd30f, 0x4da6, { 0xb9, 0x73, 0x8f, 0x65, 0xe1, 0x2e, 0x92, 0x23 } };

BEGIN_INTERFACE_MAP(CCadAutoCanvas, CCmdTarget)
	INTERFACE_PART(CCadAutoCanvas, IID_ICadAutoCanvas, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCanvas message handlers

BOOL CCadAutoCanvas::Save(LPCTSTR pszPath) 
{
	// TODO: Add your dispatch handler code here

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    return pDoc->OnSaveDocument (pszPath);

}

LPDISPATCH CCadAutoCanvas::GetDrawing() 
{
	// TODO: Add your property handler here
	return auto_draw.GetIDispatch(TRUE);
}

void CCadAutoCanvas::SetDrawing(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

LPDISPATCH CCadAutoCanvas::GetEdit() 
{
	// TODO: Add your property handler here

	return auto_edit.GetIDispatch(TRUE);
}

void CCadAutoCanvas::SetEdit(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();

}

LPDISPATCH CCadAutoCanvas::GetTransform() 
{
	// TODO: Add your property handler here

	return NULL;//auto_trans.GetIDispatch(TRUE);
}

void CCadAutoCanvas::SetTransform(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();

}

LPDISPATCH CCadAutoCanvas::GetSurface() 
{
	// TODO: Add your property handler here

	return NULL;
}

void CCadAutoCanvas::SetSurface(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CCadAutoCanvas::GetShape() 
{
	// TODO: Add your property handler here

	CCAdAutoShape* shape=new CCAdAutoShape;
	return shape->GetIDispatch(TRUE);
}

void CCadAutoCanvas::SetShape(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}
