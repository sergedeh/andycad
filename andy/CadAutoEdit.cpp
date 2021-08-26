// CadAutoEdit.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CadAutoEdit.h"
#include "caddoc.h"
#include "Cadview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoEdit

IMPLEMENT_DYNCREATE(CCadAutoEdit, CCmdTarget)

CCadAutoEdit::CCadAutoEdit()
{
	EnableAutomation();
}

CCadAutoEdit::~CCadAutoEdit()
{
}


void CCadAutoEdit::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoEdit, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoEdit, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoEdit)
	DISP_FUNCTION(CCadAutoEdit, "Select", Select, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoEdit, "Group", Group, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoEdit, "SelectNode", SelectNode, VT_EMPTY, VTS_DISPATCH VTS_I2)
	DISP_FUNCTION(CCadAutoEdit, "Close", Close, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoEdit, "Move", Move, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoEdit, "MoveNode", MoveNode, VT_EMPTY, VTS_DISPATCH VTS_I2 VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoEdit, "Chamfer", Chamfer, VT_EMPTY, VTS_DISPATCH VTS_R4 VTS_DISPATCH VTS_R4 VTS_R4)
	DISP_FUNCTION(CCadAutoEdit, "Fillet", Fillet, VT_EMPTY, VTS_DISPATCH VTS_R4 VTS_DISPATCH VTS_R4 VTS_R4)
	DISP_FUNCTION(CCadAutoEdit, "Trim", Trim, VT_BOOL, VTS_DISPATCH VTS_DISPATCH VTS_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoEdit to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {14A4B89B-0C9A-43D5-A875-CCBF6E652716}
static const IID IID_ICadAutoVector =
{ 0x14a4b89b, 0xc9a, 0x43d5, { 0xa8, 0x75, 0xcc, 0xbf, 0x6e, 0x65, 0x27, 0x16 } };

static const IID IID_ICAdAutoShape =
{ 0xc38283a1, 0x8aae, 0x4cda, { 0x9b, 0x74, 0x88, 0xbe, 0x60, 0x30, 0x1d, 0x93 } };

// {0F6000FC-1C78-4F7F-9A12-94B592ADEA01}
static const IID IID_ICadAutoEdit =
{ 0xf6000fc, 0x1c78, 0x4f7f, { 0x9a, 0x12, 0x94, 0xb5, 0x92, 0xad, 0xea, 0x1 } };

BEGIN_INTERFACE_MAP(CCadAutoEdit, CCmdTarget)
	INTERFACE_PART(CCadAutoEdit, IID_ICadAutoEdit, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoEdit message handlers

void CCadAutoEdit::Select(LPDISPATCH object) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object->QueryInterface(IID_ICAdAutoShape,(void**) &object);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->Select(f);
	}
	else
	{
		::AfxMessageBox("The object to be selected should be a shape");
	}

}

void CCadAutoEdit::SelectNode(LPDISPATCH object, short i) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object->QueryInterface(IID_ICAdAutoShape,(void**) &object);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->Select(f,false);
	}
	else
	{
		::AfxMessageBox("The object to be selected should be a shape");
	}

}

void CCadAutoEdit::Group(LPDISPATCH object1, LPDISPATCH object2) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object1->QueryInterface(IID_ICAdAutoShape,(void**) &object1);
	HRESULT hr2=object2->QueryInterface(IID_ICAdAutoShape,(void**) &object2);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object1);
	VARIANT f11;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f11);
	CFigure* f01=(CFigure*)f11.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(object2);
	VARIANT f21;
	d2.GetProperty(0x1, VT_VARIANT, (void*)&f21);
	CFigure* f02=(CFigure*)f21.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->Group(f01,f02);
	}
	else
	{
		::AfxMessageBox("Bad parameters");
	}

}




void CCadAutoEdit::Close(LPDISPATCH object) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object->QueryInterface(IID_ICAdAutoShape,(void**) &object);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->Close(f);
	}
	else
	{
		::AfxMessageBox("Bad parameters to Move");
	}

}


void CCadAutoEdit::Move(LPDISPATCH object, LPDISPATCH v) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object->QueryInterface(IID_ICAdAutoShape,(void**) &object);
	HRESULT hr2=v->QueryInterface(IID_ICadAutoVector,(void**) &v);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(v);
	CVector v2;
	d2.GetProperty(0x4,VT_VARIANT,(void*)&f1);
	v2=*(CVector*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->Move(f,v2);
	}
	else
	{
		::AfxMessageBox("Bad parameters to Move");
	}

}


void CCadAutoEdit::MoveNode(LPDISPATCH object, short node, LPDISPATCH v) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=object->QueryInterface(IID_ICAdAutoShape,(void**) &object);
	HRESULT hr2=v->QueryInterface(IID_ICadAutoVector,(void**) &v);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(object);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(v);
	CVector v2;
	d2.GetProperty(0x4,VT_VARIANT,(void*)&f1);
	v2=*(CVector*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->Move(f,node,v2);
	}
	else
	{
		::AfxMessageBox("Bad parameters to Move");
	}

}

void CCadAutoEdit::Chamfer(LPDISPATCH f1, float u1, LPDISPATCH f2, float u2, float length) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=f1->QueryInterface(IID_ICAdAutoShape,(void**) &f1);
	HRESULT hr2=f2->QueryInterface(IID_ICAdAutoShape,(void**) &f2);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(f1);
	VARIANT f11;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f11);
	CFigure* f01=(CFigure*)f11.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(f2);
	VARIANT f21;
	d2.GetProperty(0x1, VT_VARIANT, (void*)&f21);
	CFigure* f02=(CFigure*)f21.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->Chamfer(f01,u1,f02,u2,length);
	}
	else
	{
		::AfxMessageBox("Bad parameters");
	}

}

void CCadAutoEdit::Fillet(LPDISPATCH f1, float u1, LPDISPATCH f2, float u2, float l) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=f1->QueryInterface(IID_ICAdAutoShape,(void**) &f1);
	HRESULT hr2=f2->QueryInterface(IID_ICAdAutoShape,(void**) &f2);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(f1);
	VARIANT f11;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f11);
	CFigure* f01=(CFigure*)f11.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(f2);
	VARIANT f21;
	d2.GetProperty(0x1, VT_VARIANT, (void*)&f21);
	CFigure* f02=(CFigure*)f21.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->Fillet(f01,u1,f02,u2,l);
	}
	else
	{
		::AfxMessageBox("Bad parameters");
	}

}

BOOL CCadAutoEdit::Trim(LPDISPATCH obj_to_trim, LPDISPATCH obj_trim, LPDISPATCH point) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=obj_to_trim->QueryInterface(IID_ICAdAutoShape,(void**) &obj_to_trim);
	HRESULT hr2=obj_trim->QueryInterface(IID_ICAdAutoShape,(void**) &obj_trim);
	HRESULT hr3=point->QueryInterface(IID_ICadAutoVector,(void**) &point);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2)&&SUCCEEDED(hr3))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(obj_to_trim);
	VARIANT f11;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f11);
	CFigure* f01=(CFigure*)f11.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(obj_trim);
	VARIANT f21;
	d2.GetProperty(0x1, VT_VARIANT, (void*)&f21);
	CFigure* f02=(CFigure*)f21.byref;

	COleDispatchDriver d3;
	d3.AttachDispatch(point);
	CVector v2;
	d3.GetProperty(0x4,VT_VARIANT,(void*)&f11);
	v2=*(CVector*)f11.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
//    pDoc->m_objects->Trim(f01,f02,v2);
	}
	else
	{
		::AfxMessageBox("Bad parameters");
	}

	return TRUE;
}
