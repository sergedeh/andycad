// PGrid.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "PGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGrid dialog


CPGrid::CPGrid(CWnd* pParent /*=NULL*/)
	: CDialog(CPGrid::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPGrid)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGrid)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGrid, CDialog)
	//{{AFX_MSG_MAP(CPGrid)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGrid message handlers
