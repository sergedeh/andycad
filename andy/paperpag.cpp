// PaperPag.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "PaperPag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaperPag property page

IMPLEMENT_DYNCREATE(CPaperPag, CPropertyPage)

CPaperPag::CPaperPag() : CPropertyPage(CPaperPag::IDD)
{
	//{{AFX_DATA_INIT(CPaperPag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPaperPag::~CPaperPag()
{
}

void CPaperPag::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaperPag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaperPag, CPropertyPage)
	//{{AFX_MSG_MAP(CPaperPag)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaperPag message handlers
