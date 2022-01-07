// DlgCap.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "DlgCap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCap dialog


CDlgCap::CDlgCap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCap)
	m_cbot = FALSE;
	m_ctop = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgCap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCap)
	DDX_Check(pDX, IDC_CHECK_BOT, m_cbot);
	DDX_Check(pDX, IDC_CHECK_TOP, m_ctop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCap, CDialog)
	//{{AFX_MSG_MAP(CDlgCap)
	ON_BN_CLICKED(IDC_RADIO_GRID, OnRadioGrid)
	ON_BN_CLICKED(IDC_RADIO_POLY, OnRadioPoly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCap message handlers

void CDlgCap::OnRadioGrid() 
{
	// TODO: Add your control notification handler code here
	m_style=true;
}

void CDlgCap::OnRadioPoly() 
{
	// TODO: Add your control notification handler code here
	m_style=false;	
}
