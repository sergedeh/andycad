// PaperPage.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "PaperPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaperPage

IMPLEMENT_DYNAMIC(CPaperPage, CPropertySheet)

CPaperPage::CPaperPage(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPaperPage::CPaperPage(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPaperPage::~CPaperPage()
{
}


BEGIN_MESSAGE_MAP(CPaperPage, CPropertySheet)
	//{{AFX_MSG_MAP(CPaperPage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaperPage message handlers
