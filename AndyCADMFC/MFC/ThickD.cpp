// ThickD.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "ThickD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThickD dialog


CThickD::CThickD(CWnd* pParent /*=NULL*/)
	: CDialog(CThickD::IDD, pParent)
{
	ext=false;
	//{{AFX_DATA_INIT(CThickD)
	m_thickness = 0.0f;
	m_cbot = FALSE;
	m_ctop = FALSE;
	m_ext = 0.0f;
	//}}AFX_DATA_INIT
}


void CThickD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThickD)
	DDX_Control(pDX, IDC_EDIT_EXT, m_cext);
	DDX_Control(pDX, IDC_STATIC_EXT, m_sext);
	DDX_Text(pDX, IDC_EDITTHICK, m_thickness);
	DDX_Check(pDX, IDC_CHECKCAPBOT, m_cbot);
	DDX_Check(pDX, IDC_CHECKCAPTOP, m_ctop);
	DDX_Text(pDX, IDC_EDIT_EXT, m_ext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThickD, CDialog)
	//{{AFX_MSG_MAP(CThickD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThickD message handlers

BOOL CThickD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(ext)
	{
		m_cext.ShowWindow(SW_SHOW);
		m_sext.ShowWindow(SW_SHOW);

	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
