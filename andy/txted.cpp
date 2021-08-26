// TxtED.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "TxtED.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxtED

CTxtED::CTxtED()
{
}

CTxtED::~CTxtED()
{
}


BEGIN_MESSAGE_MAP(CTxtED, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTxtED)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTxtED message handlers

BOOL CTxtED::PreCreateWindow(CREATESTRUCT& cs) 
{
		if(!AfxInitRichEdit())
			return FALSE;
		if(cs.cy<0)
			cs.cy=-cs.cy;
//		if(cs.y<0)
//			cs.y=-cs.y;
	//	cs.cx=cs.cy=400;
		cs.style|=WS_CLIPSIBLINGS;
	
	return CRichEditCtrl::PreCreateWindow(cs);
}


int CTxtED::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
