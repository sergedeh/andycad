// ProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressBar

CProgressBar::CProgressBar()
{
}

CProgressBar::~CProgressBar()
{
}


BEGIN_MESSAGE_MAP(CProgressBar, CProgressCtrl)
	//{{AFX_MSG_MAP(CProgressBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressBar message handlers

int CProgressBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CProgressCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
