// CAdAutoShape.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "CAdAutoShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAdAutoShape

IMPLEMENT_DYNCREATE(CCAdAutoShape, CCmdTarget)

CCAdAutoShape::CCAdAutoShape()
{
	EnableAutomation();
}

CCAdAutoShape::~CCAdAutoShape()
{
}


void CCAdAutoShape::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCAdAutoShape, CCmdTarget)
	//{{AFX_MSG_MAP(CCAdAutoShape)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCAdAutoShape, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCAdAutoShape)
	DISP_PROPERTY_EX(CCAdAutoShape, "figure", GetFigure, SetFigure, VT_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICAdAutoShape to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C38283A1-8AAE-4CDA-9B74-88BE60301D93}
static const IID IID_ICAdAutoShape =
{ 0xc38283a1, 0x8aae, 0x4cda, { 0x9b, 0x74, 0x88, 0xbe, 0x60, 0x30, 0x1d, 0x93 } };

BEGIN_INTERFACE_MAP(CCAdAutoShape, CCmdTarget)
	INTERFACE_PART(CCAdAutoShape, IID_ICAdAutoShape, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAdAutoShape message handlers

VARIANT CCAdAutoShape::GetFigure() 
{

	// TODO: Add your property handler here
	VARIANT  result;
	VariantInit(&result);
	result.byref=shape;
	result.vt=VT_BYREF;

	return result;
}

void CCAdAutoShape::SetFigure(const VARIANT FAR* newValue) 
{
	// TODO: Add your property handler here
	shape=(CFigure*)newValue->byref;
}
