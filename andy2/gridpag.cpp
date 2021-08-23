// GridPag.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "GridPag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridPag property page

IMPLEMENT_DYNCREATE(CGridPag, CPropertyPage)

CGridPag::CGridPag() : CPropertyPage(CGridPag::IDD)
{
	//{{AFX_DATA_INIT(CGridPag)
	m_gridvert = 0;
	m_gridho = 0;
	//}}AFX_DATA_INIT
}

CGridPag::~CGridPag()
{
}

void CGridPag::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridPag)
	DDX_Control(pDX, IDC_CHECK1, m_sgrid);
	DDX_Text(pDX, IDC_EDIT1, m_gridvert);
	DDV_MinMaxInt(pDX, m_gridvert, 1, 2147483647);
	DDX_Text(pDX, IDC_EDIT2, m_gridho);
	DDV_MinMaxInt(pDX, m_gridho, 1, 10000000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridPag, CPropertyPage)
	//{{AFX_MSG_MAP(CGridPag)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridPag message handlers
