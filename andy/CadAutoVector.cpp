// CadAutoVector.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "CadAutoVector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoVector

IMPLEMENT_DYNCREATE(CCadAutoVector, CCmdTarget)

CCadAutoVector::CCadAutoVector()
{
	EnableAutomation();
}

CCadAutoVector::~CCadAutoVector()
{
}


void CCadAutoVector::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoVector, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoVector)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoVector, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoVector)
	DISP_PROPERTY_EX(CCadAutoVector, "x", GetX, SetX, VT_R4)
	DISP_PROPERTY_EX(CCadAutoVector, "y", GetY, SetY, VT_R4)
	DISP_PROPERTY_EX(CCadAutoVector, "z", GetZ, SetZ, VT_R4)
	DISP_PROPERTY_EX(CCadAutoVector, "v", GetV, SetV, VT_VARIANT)
	DISP_FUNCTION(CCadAutoVector, "Init", Init, VT_EMPTY, VTS_R4 VTS_R4 VTS_R4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoVector to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {14A4B89B-0C9A-43D5-A875-CCBF6E652716}
static const IID IID_ICadAutoVector =
{ 0x14a4b89b, 0xc9a, 0x43d5, { 0xa8, 0x75, 0xcc, 0xbf, 0x6e, 0x65, 0x27, 0x16 } };

BEGIN_INTERFACE_MAP(CCadAutoVector, CCmdTarget)
	INTERFACE_PART(CCadAutoVector, IID_ICadAutoVector, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoVector message handlers

float CCadAutoVector::GetX() 
{
	// TODO: Add your property handler here

	return v.x;
}

void CCadAutoVector::SetX(float newValue) 
{
	// TODO: Add your property handler here
	v.x=newValue;
}

float CCadAutoVector::GetY() 
{
	// TODO: Add your property handler here

	return v.y;
}

void CCadAutoVector::SetY(float newValue) 
{
	// TODO: Add your property handler here
	v.y=newValue;
}

float CCadAutoVector::GetZ() 
{
	// TODO: Add your property handler here
	return v.z;
}

void CCadAutoVector::SetZ(float newValue) 
{
	// TODO: Add your property handler here
	v.z=newValue;
}

void CCadAutoVector::Init(float x, float y, float z) 
{
	// TODO: Add your dispatch handler code here
	v=CVector(x,y,z);
}

CVector CCadAutoVector::getV()
{
	return v;
}

VARIANT CCadAutoVector::GetV() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	// TODO: Add your property handler here

	vaResult.byref=&v;
	vaResult.vt=VT_BYREF;

	return vaResult;
}

void CCadAutoVector::SetV(const VARIANT FAR& newValue) 
{
	// TODO: Add your property handler here

}
