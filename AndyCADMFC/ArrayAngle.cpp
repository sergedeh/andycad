// ArrayAngle.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "ArrayAngle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArrayAngle dialog


CArrayAngle::CArrayAngle(CWnd* pParent /*=NULL*/)
	: CDialog(CArrayAngle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArrayAngle)
	m_anglrot = 0;
	m_nbcopy = 0;
	m_dlevel = 1.0f;
	m_nblevel = 1;
	//}}AFX_DATA_INIT
}


void CArrayAngle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArrayAngle)
	DDX_Text(pDX, IDC_ANGLEROT, m_anglrot);
	DDX_Text(pDX, IDC_NBCOPY, m_nbcopy);
	DDV_MinMaxInt(pDX, m_nbcopy, 1, 1000);
	DDX_Text(pDX, IDC_DLEVEL, m_dlevel);
	DDV_MinMaxFloat(pDX, m_dlevel, 1.f, 1000.f);
	DDX_Text(pDX, IDC_NBLEVEL, m_nblevel);
	DDV_MinMaxInt(pDX, m_nblevel, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArrayAngle, CDialog)
	//{{AFX_MSG_MAP(CArrayAngle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArrayAngle message handlers


BOOL CArrayAngle::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

BOOL CArrayAngle::OnInitDialog()
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
