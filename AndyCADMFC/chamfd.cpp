// ChamfD.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "ChamfD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChamfD dialog


CChamfD::CChamfD(CWnd* pParent /*=NULL*/)
	: CDialog(CChamfD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChamfD)
	m_chlgth = 0;
	//}}AFX_DATA_INIT
}


void CChamfD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChamfD)
	DDX_Text(pDX, IDC_CHLGTH, m_chlgth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChamfD, CDialog)
	//{{AFX_MSG_MAP(CChamfD)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChamfD message handlers
