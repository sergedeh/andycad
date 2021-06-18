// TransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "TransDlg.h"
#include "cadview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog


CTransDlg::CTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransDlg)
	m_value = 0;
	m_slidev = 0;
	//}}AFX_DATA_INIT
}


void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransDlg)
	DDX_Control(pDX, IDC_TEDIT, m_edit);
	DDX_Control(pDX, IDC_TSLIDER, m_slidec);
	DDX_Text(pDX, IDC_TEDIT, m_value);
	DDV_MinMaxInt(pDX, m_value, 0, 100);
	DDX_Slider(pDX, IDC_TSLIDER, m_slidev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransDlg, CDialog)
	//{{AFX_MSG_MAP(CTransDlg)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransDlg message handlers

BOOL CTransDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	// TODO: Add extra initialization here
	int min,max;
	m_slidec.SetRange(0,100,TRUE);
	m_slidev=100;
	m_value=100;
	UpdateData(FALSE);

	//	m_value.GetPos,
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		 m_tooltip.AddTool(GetDlgItem(IDC_TSLIDER), "Use the Slider to increase or decrease the opacity of the selected");
	     m_tooltip.AddTool(GetDlgItem(IDC_TEDIT), "Enter a value (Range 0-100");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	m_slidev=m_slidec.GetPos();
	float tr=(float)m_slidev/100;
	void* param[1];
	param[0]=&tr;
	m_value=m_slidev;
	UpdateData(FALSE);
	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Transparency",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CTransDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}
