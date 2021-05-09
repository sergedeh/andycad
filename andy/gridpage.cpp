// GridPage.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "GridPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridPage

IMPLEMENT_DYNAMIC(CGridPage, CPropertySheet)

CGridPage::CGridPage(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CGridPage::CGridPage(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CGridPage::~CGridPage()
{
}


BEGIN_MESSAGE_MAP(CGridPage, CPropertySheet)
	//{{AFX_MSG_MAP(CGridPage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridPage message handlers
