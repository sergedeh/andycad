// CustomSheet.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "CustomSheet.h"
#include "paperpag.h"
#include "gridpag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomSheet

IMPLEMENT_DYNAMIC(CCustomSheet, CPropertySheet)

CCustomSheet::CCustomSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_custgrid);
	AddPage(&m_custpaper);
}

CCustomSheet::CCustomSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CCustomSheet::~CCustomSheet()
{
}


BEGIN_MESSAGE_MAP(CCustomSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCustomSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomSheet message handlers
