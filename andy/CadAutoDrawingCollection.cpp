// CadAutoDrawingCollection.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CadAutoDrawingCollection.h"
#include "CadAutoShape.h"
#include "caddoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawingCollection

IMPLEMENT_DYNCREATE(CCadAutoDrawingCollection, CCmdTarget)

CCadAutoDrawingCollection::CCadAutoDrawingCollection()
{
	EnableAutomation();
}

CCadAutoDrawingCollection::~CCadAutoDrawingCollection()
{
}


void CCadAutoDrawingCollection::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoDrawingCollection, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoDrawingCollection)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoDrawingCollection, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoDrawingCollection)
	DISP_PROPERTY_EX(CCadAutoDrawingCollection, "Count", GetCount, SetCount, VT_I2)
	DISP_FUNCTION(CCadAutoDrawingCollection, "Item", Item, VT_DISPATCH, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoDrawingCollection to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {4AA11FC0-F053-40D0-AD60-2B0B2DD3F342}
static const IID IID_ICadAutoDrawingCollection =
{ 0x4aa11fc0, 0xf053, 0x40d0, { 0xad, 0x60, 0x2b, 0xb, 0x2d, 0xd3, 0xf3, 0x42 } };

BEGIN_INTERFACE_MAP(CCadAutoDrawingCollection, CCmdTarget)
	INTERFACE_PART(CCadAutoDrawingCollection, IID_ICadAutoDrawingCollection, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawingCollection message handlers

LPDISPATCH CCadAutoDrawingCollection::Item(short i) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    CFigure* f=pDoc->m_objects->getFigure(i);
	CCAdAutoShape* shape=new CCAdAutoShape;
	VARIANT fv;
	VariantInit(&fv);
	fv.byref=f;
	fv.vt=VT_BYREF;
	COleDispatchDriver d;
	d.AttachDispatch(shape->GetIDispatch(TRUE));
	d.SetProperty(0x1,VT_VARIANT,&fv);//InvokeHelper(*/shape->SetFigure(&fv);
	return shape->GetIDispatch(TRUE);
}

short CCadAutoDrawingCollection::GetCount() 
{
	// TODO: Add your property handler here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    short f=pDoc->m_objects->getFigures();

	return f;
}

void CCadAutoDrawingCollection::SetCount(short nNewValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}
