// CadAutoDrawing.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "caddoc.h"
#include "CadAutoDrawing.h"
#include "CadAutoVector.h"
#include "CadAutoCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////
//	[ uuid(14A4B89B-0C9A-43D5-A875-CCBF6E652716) ]
//	dispinterface ICadAutoVector
static const IID IID_ICadAutoVector =
{ 0x14a4b89b, 0xc9a, 0x43d5, { 0xa8, 0x75, 0xcc, 0xbf, 0x6e, 0x65, 0x27, 0x16 } };

//016DF3A9-1221-4263-8F09-890A79F35F56
static const IID IID_ICadAutoCollection =
{ 0x16df3a9, 0x1221, 0x4263, { 0x8f, 0x9, 0x89, 0xa, 0x79, 0xf3, 0x5f, 0x56 } };

/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawing

IMPLEMENT_DYNCREATE(CCadAutoDrawing, CCmdTarget)

CCadAutoDrawing::CCadAutoDrawing()
{
	EnableAutomation();
}

CCadAutoDrawing::~CCadAutoDrawing()
{
}


void CCadAutoDrawing::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCadAutoDrawing, CCmdTarget)
	//{{AFX_MSG_MAP(CCadAutoDrawing)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCadAutoDrawing, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCadAutoDrawing)
	DISP_PROPERTY_EX(CCadAutoDrawing, "DrawingCollection", GetDrawingCollection, SetDrawingCollection, VT_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddLine", AddLine, VT_EMPTY, VTS_R4 VTS_R4 VTS_R4 VTS_R4)
	DISP_FUNCTION(CCadAutoDrawing, "AddRectangle", AddRectangle, VT_EMPTY, VTS_R4 VTS_R4 VTS_R4 VTS_R4)
	DISP_FUNCTION(CCadAutoDrawing, "AddLinev", AddLinev, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddRectanglev", AddRectanglev, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddCircle", AddCircle, VT_EMPTY, VTS_DISPATCH VTS_R4)
	DISP_FUNCTION(CCadAutoDrawing, "AddCirclev", AddCirclev, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddSpline", AddSpline, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddPolyLine", AddPolyLine, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddCircle3", AddCircle3, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddArc", AddArc, VT_EMPTY, VTS_DISPATCH VTS_R4)
	DISP_FUNCTION(CCadAutoDrawing, "AddArc2", AddArc2, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH)
	DISP_FUNCTION(CCadAutoDrawing, "AddArc3", AddArc3, VT_EMPTY, VTS_DISPATCH VTS_DISPATCH VTS_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICadAutoDrawing to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {980538BD-C145-4413-B2D2-B314017871A1}
static const IID IID_ICadAutoDrawing =
{ 0x980538bd, 0xc145, 0x4413, { 0xb2, 0xd2, 0xb3, 0x14, 0x1, 0x78, 0x71, 0xa1 } };

BEGIN_INTERFACE_MAP(CCadAutoDrawing, CCmdTarget)
	INTERFACE_PART(CCadAutoDrawing, IID_ICadAutoDrawing, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadAutoDrawing message handlers

void CCadAutoDrawing::AddLine(float left, float top, float right, float bottom) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument();
    pDoc->m_objects->AddLine(left,top,right,bottom);
}

void CCadAutoDrawing::AddRectangle(float left, float top, float right, float bottom) 
{
	// TODO: Add your dispatch handler code here
    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddRectangle(left,top,right,bottom);

}

void CCadAutoDrawing::AddLinev(LPDISPATCH p1, LPDISPATCH p2) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=p1->QueryInterface(IID_ICadAutoVector,(void**) &p1);
	HRESULT hr2=p2->QueryInterface(IID_ICadAutoVector,(void**) &p2);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	vector<CVector> vs;

	COleDispatchDriver d1;
	d1.AttachDispatch(p1);
	float f1,f2,f3;
	d1.GetProperty(0x1, VT_R4, (void*)&f1);
	d1.GetProperty(0x2, VT_R4, (void*)&f2);
	d1.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v1(f1,f2,f3);
	vs.push_back(v1);

	COleDispatchDriver d2;
	d2.AttachDispatch(p2);
	d2.GetProperty(0x1, VT_R4, (void*)&f1);
	d2.GetProperty(0x2, VT_R4, (void*)&f2);
	d2.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v2(f1,f2,f3);
	vs.push_back(v2);

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddLine(vs);
//  pDoc->m_objects->AddRectangle(((CCadAutoVector*)(CCmdTarget*)p1)->getV(),((CCadAutoVector*)(CCmdTarget*)p2)->getV());
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}
}


void CCadAutoDrawing::AddRectanglev(LPDISPATCH p1, LPDISPATCH p2) 
{
	// TODO: Add your dispatch handler code here

}

void CCadAutoDrawing::AddCircle(LPDISPATCH center, float radius) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=center->QueryInterface(IID_ICadAutoVector,(void**) &center);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(center);
	float f1,f2,f3;
	VARIANT result;
	CVector v;
	d1.GetProperty(0x4,VT_VARIANT,(void*)&result);
	v=*(CVector*)result.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddCircle(v,radius);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddCirclev(LPDISPATCH center, LPDISPATCH rvec) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=center->QueryInterface(IID_ICadAutoVector,(void**) &center);
	HRESULT hr2=rvec->QueryInterface(IID_ICadAutoVector,(void**) &rvec);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(center);
	VARIANT result;
	CVector v1;
	d1.GetProperty(0x4,VT_VARIANT,(void*)&result);
	v1=*(CVector*)result.byref;

	COleDispatchDriver d2;
	d2.AttachDispatch(rvec);
	CVector v2;
	d2.GetProperty(0x4,VT_VARIANT,(void*)&result);
	v2=*(CVector*)result.byref;

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddCircle(v1,v2);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddSpline(LPDISPATCH ponts) 
{
	// TODO: Add your dispatch handler code here
	// TODO: Add your dispatch handler code here
	HRESULT hr1=ponts->QueryInterface(IID_ICadAutoCollection,(void**) &ponts);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(ponts);
	short f0;
	float f1,f2,f3;

	static BYTE parms[] =VTS_DISPATCH;
	static BYTE parms1[] =VTS_I2;
	d1.GetProperty(0x1, VT_I2, (void*)&f0);
	if(!f0) return;
	vector<CVector> vs;
	for(int i=0; i<f0;i++)
	{
		LPDISPATCH v;
		d1.InvokeHelper(0x6,DISPATCH_METHOD, VT_DISPATCH, (void*)&v,parms1,i);
		
		COleDispatchDriver d2;
		d2.AttachDispatch(v);
		d2.GetProperty(0x1, VT_R4, (void*)&f1);
		d2.GetProperty(0x2, VT_R4, (void*)&f2);
		d2.GetProperty(0x3, VT_R4, (void*)&f3);
		CVector v2(f1,f2,f3);
		vs.push_back(v2);
	}


    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddSpline(vs);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddPolyLine(LPDISPATCH points) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=points->QueryInterface(IID_ICadAutoCollection,(void**) &points);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(points);
	short f0;
	float f1,f2,f3;

	static BYTE parms[] =VTS_DISPATCH;
	static BYTE parms1[] =VTS_I2;
	d1.GetProperty(0x1, VT_I2, (void*)&f0);
	if(!f0) return;
	vector<CVector> vs;
	for(int i=0; i<f0;i++)
	{
		LPDISPATCH v;
		d1.InvokeHelper(0x6,DISPATCH_METHOD, VT_DISPATCH, (void*)&v,parms1,i);
		
		COleDispatchDriver d2;
		d2.AttachDispatch(v);
		d2.GetProperty(0x1, VT_R4, (void*)&f1);
		d2.GetProperty(0x2, VT_R4, (void*)&f2);
		d2.GetProperty(0x3, VT_R4, (void*)&f3);
		CVector v2(f1,f2,f3);
		vs.push_back(v2);
	}


    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddLine(vs);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddCircle3(LPDISPATCH p1, LPDISPATCH p2, LPDISPATCH p3) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=p1->QueryInterface(IID_ICadAutoVector,(void**) &p1);
	HRESULT hr2=p2->QueryInterface(IID_ICadAutoVector,(void**) &p2);
	HRESULT hr3=p3->QueryInterface(IID_ICadAutoVector,(void**) &p3);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2)&&SUCCEEDED(hr3))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(p1);
	float f1,f2,f3;
	d1.GetProperty(0x1, VT_R4, (void*)&f1);
	d1.GetProperty(0x2, VT_R4, (void*)&f2);
	d1.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v1(f1,f2,f3);

	COleDispatchDriver d2;
	d2.AttachDispatch(p2);
	d2.GetProperty(0x1, VT_R4, (void*)&f1);
	d2.GetProperty(0x2, VT_R4, (void*)&f2);
	d2.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v2(f1,f2,f3);

	COleDispatchDriver d3;
	d3.AttachDispatch(p3);
	d3.GetProperty(0x1, VT_R4, (void*)&f1);
	d3.GetProperty(0x2, VT_R4, (void*)&f2);
	d3.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v3(f1,f2,f3);

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddCircle(v1,v2,v3);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddArc(LPDISPATCH center, float radius) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=center->QueryInterface(IID_ICadAutoVector,(void**) &center);
	if(SUCCEEDED(hr1))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(center);
	float f1,f2,f3;
	d1.GetProperty(0x1, VT_R4, (void*)&f1);
	d1.GetProperty(0x2, VT_R4, (void*)&f2);
	d1.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v1(f1,f2,f3);

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
//    pDoc->m_objects->AddArc(v1,radius);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddArc2(LPDISPATCH p1, LPDISPATCH p2) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=p1->QueryInterface(IID_ICadAutoVector,(void**) &p1);
	HRESULT hr2=p2->QueryInterface(IID_ICadAutoVector,(void**) &p2);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(p1);
	float f1,f2,f3;
	d1.GetProperty(0x1, VT_R4, (void*)&f1);
	d1.GetProperty(0x2, VT_R4, (void*)&f2);
	d1.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v1(f1,f2,f3);

	COleDispatchDriver d2;
	d2.AttachDispatch(p2);
	d2.GetProperty(0x1, VT_R4, (void*)&f1);
	d2.GetProperty(0x2, VT_R4, (void*)&f2);
	d2.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v2(f1,f2,f3);

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddArc(v1,v2);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

void CCadAutoDrawing::AddArc3(LPDISPATCH p1, LPDISPATCH p2, LPDISPATCH p3) 
{
	// TODO: Add your dispatch handler code here
	HRESULT hr1=p1->QueryInterface(IID_ICadAutoVector,(void**) &p1);
	HRESULT hr2=p2->QueryInterface(IID_ICadAutoVector,(void**) &p2);
	HRESULT hr3=p3->QueryInterface(IID_ICadAutoVector,(void**) &p3);
	if(SUCCEEDED(hr1)&&SUCCEEDED(hr2)&&SUCCEEDED(hr3))
	{
	COleDispatchDriver d1;
	d1.AttachDispatch(p1);
	float f1,f2,f3;
	d1.GetProperty(0x1, VT_R4, (void*)&f1);
	d1.GetProperty(0x2, VT_R4, (void*)&f2);
	d1.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v1(f1,f2,f3);

	COleDispatchDriver d2;
	d2.AttachDispatch(p2);
	d2.GetProperty(0x1, VT_R4, (void*)&f1);
	d2.GetProperty(0x2, VT_R4, (void*)&f2);
	d2.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v2(f1,f2,f3);

	COleDispatchDriver d3;
	d3.AttachDispatch(p3);
	d3.GetProperty(0x1, VT_R4, (void*)&f1);
	d3.GetProperty(0x2, VT_R4, (void*)&f2);
	d3.GetProperty(0x3, VT_R4, (void*)&f3);
	CVector v3(f1,f2,f3);

    CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
    CCadDoc* pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
    pDoc->m_objects->AddArc(v1,v2,v3);
	}
	else
	{
		::AfxMessageBox("Problem getting the vector Object");
	}

}

LPDISPATCH CCadAutoDrawing::GetDrawingCollection() 
{
	// TODO: Add your property handler here

	return m_coll.GetIDispatch(TRUE);
}

void CCadAutoDrawing::SetDrawingCollection(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}
