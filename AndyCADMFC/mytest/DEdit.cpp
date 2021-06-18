// DEdit.cpp : implementation file
//

#include "stdafx.h"
#include "mytest.h"
#include "DEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDEdit

CDEdit::CDEdit()
{
}

CDEdit::~CDEdit()
{
}


BEGIN_MESSAGE_MAP(CDEdit, CEdit)
	//{{AFX_MSG_MAP(CDEdit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDEdit message handlers

int CDEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
