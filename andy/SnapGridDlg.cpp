// SnapGridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "SnapGridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg dialog


CSnapGridDlg::CSnapGridDlg()
	: CPropertyPage(CSnapGridDlg::IDD)
{
	//{{AFX_DATA_INIT(CSnapGridDlg)
	m_gridon = FALSE;
	m_snapon = TRUE;
	m_angle = 0.0f;
	m_gridxspacing = 20.0f;
	m_gridyspacing = 20.0f;
	m_polardistance = 0.0f;
	m_xbase = 0.0f;
	m_ybase = 0.0f;
	m_snapxspacing = 20.0f;
	m_snapyspacing = 20.0f;
	//}}AFX_DATA_INIT
}


void CSnapGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapGridDlg)
	DDX_Check(pDX, IDC_CHECKGRIDON, m_gridon);
	DDX_Check(pDX, IDC_CHECKSNAPON, m_snapon);
	DDX_Text(pDX, IDC_EDITANGLE, m_angle);
	DDX_Text(pDX, IDC_EDITGRIDXSPACING, m_gridxspacing);
	DDX_Text(pDX, IDC_EDITGRIDYSPACING, m_gridyspacing);
	DDX_Text(pDX, IDC_EDITPOLARDISTANCE, m_polardistance);
	DDX_Text(pDX, IDC_EDITXBASE, m_xbase);
	DDX_Text(pDX, IDC_EDITYBASE, m_ybase);
	DDX_Text(pDX, IDC_EDITXSPACING, m_snapxspacing);
	DDX_Text(pDX, IDC_EDITYSPACING, m_snapyspacing);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapGridDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CSnapGridDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapGridDlg message handlers
