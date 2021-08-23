// Optionsheet.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "Optionsheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsheet

IMPLEMENT_DYNAMIC(COptionsheet, CPropertySheet)

COptionsheet::COptionsheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

COptionsheet::COptionsheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

COptionsheet::~COptionsheet()
{
}


BEGIN_MESSAGE_MAP(COptionsheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionsheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsheet message handlers
