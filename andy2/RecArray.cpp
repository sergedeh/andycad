// RecArray.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "RecArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecArray dialog


CRecArray::CRecArray(CWnd* pParent /*=NULL*/)
	: CDialog(CRecArray::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecArray)
	m_cnb = 1;
	m_rnb = 1;
	m_dx = 0;
	m_dy = 0;
	m_lspacing = 0.0f;
	m_nblevel = 1;
	//}}AFX_DATA_INIT
}


void CRecArray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecArray)
	DDX_Text(pDX, IDC_CNB, m_cnb);
	DDX_Text(pDX, IDC_RNB, m_rnb);
	DDX_Text(pDX, IDC_DX, m_dx);
	DDX_Text(pDX, IDC_DY, m_dy);
	DDX_Text(pDX, IDC_LSP, m_lspacing);
	DDX_Text(pDX, IDC_NBL, m_nblevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecArray, CDialog)
	//{{AFX_MSG_MAP(CRecArray)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecArray message handlers

BOOL CRecArray::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

BOOL CRecArray::OnInitDialog()
{
	CDialog::OnInitDialog();	// CG: This was added by the ToolTips component.
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}
	return TRUE;	// CG: This was added by the ToolTips component.
}
