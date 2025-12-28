// CadAutoTransform.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "CadAutoTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadAutoTransform

IMPLEMENT_DYNCREATE(CCadAutoTransform, CCmdTarget)

CCadAutoTransform::CCadAutoTransform()
{
	EnableAutomation();
}

CCadAutoTransform::~CCadAutoTransform()
{
}


void CCadAutoTransform::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoTransform, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoTransform)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoTransform, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoTransform)
	DISP_FUNCTION(CCadAutoTransform, "Rotate", Rotate, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoTransform, "Scale", Scale, VT_EMPTY, VTS_R4 VTS_I2)
	DISP_FUNCTION(CCadAutoTransform, "AngCopy", AngCopy, VT_EMPTY, VTS_R4 VTS_I2 VTS_I2 VTS_R4)
	DISP_FUNCTION(CCadAutoTransform, "PolarCopy", PolarCopy, VT_EMPTY, VTS_R4 VTS_I2 VTS_I2 VTS_R4)
	DISP_FUNCTION(CCadAutoTransform, "ArrayCopy", ArrayCopy, VT_EMPTY, VTS_I2 VTS_R4 VTS_I2 VTS_R4 VTS_I2 VTS_R4)
	DISP_FUNCTION(CCadAutoTransform, "Flip", Flip, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CCadAutoTransform, "Mirror", Mirror, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoTransform, "Mirror2", Mirror2, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoTransform, "Copy", Copy, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoTransform, "Copy2", Copy2, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoTransform, "Scale2", Scale2, VT_EMPTY, VTS_R4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoTransform to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.
// {14A4B89B-0C9A-43D5-A875-CCBF6E652716}
static const IID IID_ICadAutoVector =
{ 0x14a4b89b, 0xc9a, 0x43d5, { 0xa8, 0x75, 0xcc, 0xbf, 0x6e, 0x65, 0x27, 0x16 } };

static const IID IID_ICAdAutoShape =
{ 0xc38283a1, 0x8aae, 0x4cda, { 0x9b, 0x74, 0x88, 0xbe, 0x60, 0x30, 0x1d, 0x93 } };


// {EB970C20-A88E-4440-BA4B-A2F7476B3079}
static const IID IID_ICadAutoTransform =
{ 0xeb970c20, 0xa88e, 0x4440, { 0xba, 0x4b, 0xa2, 0xf7, 0x47, 0x6b, 0x30, 0x79 } };

BEGIN_INTERFACE_MAP(CCadAutoTransform, CCmdTarget)
	INTERFACE_PART(CCadAutoTransform, IID_ICadAutoTransform, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoTransform message handlers

void CCadAutoTransform::Rotate(float u, short axis) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument();
    pDoc->m_objects->rotate(u,axis);

}

void CCadAutoTransform::Scale(float u, short axis) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->scale(u,axis);

}

void CCadAutoTransform::AngCopy(float u, short nb, short level, float dst) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->copyRSparam(NULL,u,nb,level,dst,false);

}

void CCadAutoTransform::PolarCopy(float u, short nb, short level, float dst) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->copyRSparam(NULL,u,nb,level,dst,true);

}

void CCadAutoTransform::ArrayCopy(short rows, float r_space, short column, float c_space, short level, float l_spacing) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->pastearray(NULL,true,rows,column,r_space,c_space,level,l_spacing);
}

void CCadAutoTransform::Flip(short dir) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->flip(dir);
}

void CCadAutoTransform::Mirror(LPDISPATCH figure) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=figure->QueryInterface(IID_ICAdAutoShape,(void**) &figure);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(figure);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->mirror(f,false);
	}
}

void CCadAutoTransform::Mirror2(LPDISPATCH figure) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=figure->QueryInterface(IID_ICAdAutoShape,(void**) &figure);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(figure);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->mirror(f,true);
	}
}

void CCadAutoTransform::Copy(LPDISPATCH figure) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=figure->QueryInterface(IID_ICAdAutoShape,(void**) &figure);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(figure);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->copy(f,false);
	}
}

void CCadAutoTransform::Copy2(LPDISPATCH figure) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=figure->QueryInterface(IID_ICAdAutoShape,(void**) &figure);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(figure);
	VARIANT f1;
	d1.GetProperty(0x1, VT_VARIANT, (void*)&f1);
	CFigure* f=(CFigure*)f1.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->copy(f,true);
	}

}

void CCadAutoTransform::Scale2(float u) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->copy2(u);

}
