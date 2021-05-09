// SnapGridDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "SnapGridDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg2 property page

IMPLEMENT_DYNCREATE(CSnapGridDlg2, CPropertyPage)

CSnapGridDlg2::CSnapGridDlg2() : CPropertyPage(CSnapGridDlg2::IDD)
{
	//{{AFX_DATA_INIT(CSnapGridDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSnapGridDlg2::~CSnapGridDlg2()
{
}

void CSnapGridDlg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapGridDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapGridDlg2, CPropertyPage)
	//{{AFX_MSG_MAP(CSnapGridDlg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg2 message handlers
