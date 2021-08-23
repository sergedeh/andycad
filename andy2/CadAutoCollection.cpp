// CadAutoCollection.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CadAutoCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCollection

IMPLEMENT_DYNCREATE(CCadAutoCollection, CCmdTarget)

CCadAutoCollection::CCadAutoCollection()
{
	EnableAutomation();
}

CCadAutoCollection::~CCadAutoCollection()
{
}


void CCadAutoCollection::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoCollection, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoCollection)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoCollection, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoCollection)
	DISP_PROPERTY_EX(CCadAutoCollection, "Count", GetCount, SetCount, VT_I2)
	DISP_PROPERTY_EX(CCadAutoCollection, "begin", GetBegin, SetBegin, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadAutoCollection, "end", GetEnd, SetEnd, VT_DISPATCH)
	DISP_FUNCTION(CCadAutoCollection, "Add", Add, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoCollection, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CCadAutoCollection, "Item", Item, VT_DISPATCH, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoCollection to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {016DF3A9-1221-4263-8F09-890A79F35F56}
static const IID IID_ICadAutoCollection =
{ 0x16df3a9, 0x1221, 0x4263, { 0x8f, 0x9, 0x89, 0xa, 0x79, 0xf3, 0x5f, 0x56 } };

BEGIN_INTERFACE_MAP(CCadAutoCollection, CCmdTarget)
	INTERFACE_PART(CCadAutoCollection, IID_ICadAutoCollection, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoCollection message handlers

void CCadAutoCollection::Add(LPDISPATCH item) 
{
	// TODO: Add your dispatch handler code here
	v.push_back(item);
}


short CCadAutoCollection::GetCount() 
{
	// TODO: Add your property handler here

	return v.size();
}

void CCadAutoCollection::SetCount(short nNewValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

void CCadAutoCollection::Clear() 
{
	// TODO: Add your dispatch handler code here
	v.clear();
}

LPDISPATCH* CCadAutoCollection::GetBegin() 
{
	// TODO: Add your property handler here

	return &*v.begin();
}

void CCadAutoCollection::SetBegin(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();

}

LPDISPATCH* CCadAutoCollection::GetEnd() 
{
	// TODO: Add your property handler here

	return &*v.end();
}

void CCadAutoCollection::SetEnd(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}


LPDISPATCH CCadAutoCollection::Item(short index) 
{
	// TODO: Add your dispatch handler code here
	if(index<v.size())
		return v[index];
	else
		return NULL;
}
