// SnapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "SnapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapDlg dialog
IMPLEMENT_DYNAMIC(CSnapDlg, CPropertySheet)


CSnapDlg::CSnapDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSnapDlg::CSnapDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CSnapDlg::~CSnapDlg()
{
}



BEGIN_MESSAGE_MAP(CSnapDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CSnapDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapDlg message handlers
