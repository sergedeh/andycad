// ToolBarW.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "ToolBarW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarW

CToolBarW::CToolBarW()
{
}

CToolBarW::~CToolBarW()
{
}


BEGIN_MESSAGE_MAP(CToolBarW, CToolBar)
	//{{AFX_MSG_MAP(CToolBarW)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarW message handlers

void CToolBarW::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CToolBar::OnClose();
}

void CToolBarW::OnDestroy() 
{
	CToolBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}


