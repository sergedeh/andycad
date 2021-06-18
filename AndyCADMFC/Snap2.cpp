// Snap2.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "Snap2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnap2

IMPLEMENT_DYNAMIC(CSnap2, CPropertySheet)

CSnap2::CSnap2(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSnap2::CSnap2(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CSnap2::~CSnap2()
{
}


BEGIN_MESSAGE_MAP(CSnap2, CPropertySheet)
	//{{AFX_MSG_MAP(CSnap2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnap2 message handlers
