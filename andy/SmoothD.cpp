// SmoothD.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "SmoothD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmoothD dialog


CSmoothD::CSmoothD(CWnd* pParent /*=NULL*/)
	: CDialog(CSmoothD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmoothD)
	m_us = -1;
	m_vs = -1;
	m_ws = -1;
	//}}AFX_DATA_INIT
}


void CSmoothD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmoothD)
	DDX_Text(pDX, IDC_EDITUS, m_us);
	DDX_Text(pDX, IDC_EDITVS, m_vs);
	DDX_Text(pDX, IDC_EDITWS, m_ws);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmoothD, CDialog)
	//{{AFX_MSG_MAP(CSmoothD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmoothD message handlers

BOOL CSmoothD::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

BOOL CSmoothD::OnInitDialog()
{
	CDialog::OnInitDialog();	// CG: This was added by the ToolTips component.
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		m_tooltip.AddTool(GetDlgItem(IDC_EDITUS), "Increase or Decrease the number of segment");
		m_tooltip.AddTool(GetDlgItem(IDC_EDITVS), "Increase or Decrease smoothness");
		m_tooltip.AddTool(GetDlgItem(IDC_EDITWS), "Increase or Decrease depth");
		//m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}
	return TRUE;	// CG: This was added by the ToolTips component.
}

