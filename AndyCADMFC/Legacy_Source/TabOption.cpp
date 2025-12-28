// TabOption.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "TabOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabOption

CTabOption::CTabOption()
{
}

CTabOption::~CTabOption()
{
}


BEGIN_MESSAGE_MAP(CTabOption, CTabCtrl)
	//{{AFX_MSG_MAP(CTabOption)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabOption message handlers

int CTabOption::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}
