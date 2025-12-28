// cmoveandrotatebar.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "cmoveandrotatebar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cmoveandrotatebar dialog


cmoveandrotatebar::cmoveandrotatebar()
{
	//{{AFX_DATA_INIT(cmoveandrotatebar)
	m_angle = 0.0;
	m_copies = 0;
	m_usecurrentlayer = FALSE;
	//}}AFX_DATA_INIT
}


void cmoveandrotatebar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cmoveandrotatebar)
	DDX_Text(pDX, IDC_angle, m_angle);
	DDX_Text(pDX, IDC_Copies, m_copies);
	DDX_Check(pDX, IDC_USECLAYER, m_usecurrentlayer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cmoveandrotatebar, CDialogBar)
	//{{AFX_MSG_MAP(cmoveandrotatebar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cmoveandrotatebar message handlers
