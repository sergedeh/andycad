// CLineSty.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CLineSty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCLineSty dialog


CCLineSty::CCLineSty(CWnd* pParent /*=NULL*/)
	: CDialog(CCLineSty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCLineSty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCLineSty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCLineSty)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCLineSty, CDialog)
	//{{AFX_MSG_MAP(CCLineSty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCLineSty message handlers

BOOL CCLineSty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
/*	
	m_list.Create (IDB_LSTYLE, 16, 1, RGB (255, 0, 255));
	m_combo.SetImageList (&m_list);

	for (int i=0; i<5; i++) 
	{
    CString string;
    string.Format (_T ("Item %d"), i);

    COMBOBOXEXITEM cbei;
    cbei.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE |CBEIF_TEXT;
    cbei.iItem = i;
    cbei.pszText = (LPTSTR) (LPCTSTR) string;
    cbei.iImage = 0;
    cbei.iSelectedImage = 0;

    m_combo.InsertItem (&cbei);
	}

*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


