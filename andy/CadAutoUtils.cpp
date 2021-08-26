// CadAutoUtils.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CadAutoUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoUtils

IMPLEMENT_DYNCREATE(CCadAutoUtils, CCmdTarget)

CCadAutoUtils::CCadAutoUtils()
{
	EnableAutomation();
}

CCadAutoUtils::~CCadAutoUtils()
{
}


void CCadAutoUtils::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoUtils, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoUtils)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoUtils, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoUtils)
	DISP_PROPERTY_EX(CCadAutoUtils, "Vector", GetVector, SetVector, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoUtils, "Collection", GetCollection, SetCollection, VT_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoUtils to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {6C92039F-CB9A-42DB-B245-B1808E87FCA2}
static const IID IID_ICadAutoUtils =
{ 0x6c92039f, 0xcb9a, 0x42db, { 0xb2, 0x45, 0xb1, 0x80, 0x8e, 0x87, 0xfc, 0xa2 } };

BEGIN_INTERFACE_MAP(CCadAutoUtils, CCmdTarget)
	INTERFACE_PART(CCadAutoUtils, IID_ICadAutoUtils, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoUtils message handlers

LPDISPATCH CCadAutoUtils::GetVector() 
{
	// TODO: Add your property handler here
//	::CoCreateInstance(__uuidof(CCadAutoVector),NULL,CLSCTX_INPROC_SERVER,NULL);
	auto_vector=new CCadAutoVector;
	return auto_vector->GetIDispatch(TRUE);
}

void CCadAutoUtils::SetVector(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

LPDISPATCH CCadAutoUtils::GetCollection() 
{
	// TODO: Add your property handler here
	auto_coll=new CCadAutoCollection;
	return auto_coll->GetIDispatch(TRUE);
}

void CCadAutoUtils::SetCollection(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

