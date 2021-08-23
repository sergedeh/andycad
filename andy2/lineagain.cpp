// LineAgain.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "LineAgain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineAgain dialog


CLineAgain::CLineAgain()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CLineAgain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLineAgain::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineAgain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineAgain, CDialogBar)
	//{{AFX_MSG_MAP(CLineAgain)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineAgain message handlers
