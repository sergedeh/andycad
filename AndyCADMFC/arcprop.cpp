// ArcProp.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "ArcProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArcProp dialog


CArcProp::CArcProp(CWnd* pParent /*=NULL*/)
	: CDialog(CArcProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArcProp)
	m_arcRadius = 0.0;
	m_swaprad = FALSE;
	//}}AFX_DATA_INIT
}


void CArcProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArcProp)
	DDX_Text(pDX, IDC_EDIT1, m_arcRadius);
	DDX_Check(pDX, IDC_CHECK1, m_swaprad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArcProp, CDialog)
	//{{AFX_MSG_MAP(CArcProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArcProp message handlers
