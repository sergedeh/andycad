// AddinSettingsDialog.cpp : implementation file
//

#include "Stdafx.h"
#include "CAD.h"
#include "AddinSettingsDialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddinSettingsDialog dialog


CAddinSettingsDialog::CAddinSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddinSettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddinSettingsDialog)
	//}}AFX_DATA_INIT
}


void CAddinSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddinSettingsDialog)
	DDX_Control(pDX, IDC_LIST_ADDIN, m_ListAddin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddinSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(CAddinSettingsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddinSettingsDialog message handlers

BOOL CAddinSettingsDialog::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
	

	for(int i=0;i < CCadApp::m_AddinManager.GetAddinCount();i++)
	{
		int index=m_ListAddin.AddString(CCadApp::m_AddinManager.GetAddinInfo(i).m_strAddinName);
		m_ListAddin.SetCheck(index,CCadApp::m_AddinManager.GetAddinInfo(i).m_bLoadAddin); 
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddinSettingsDialog::OnOK() 
{
	for(int i=0;i<m_ListAddin.GetCount();i++)
	{
		CString strAddinText="";
		m_ListAddin.GetText(i,strAddinText); 
		CCadApp::m_AddinManager.SetAddinVisible(strAddinText,m_ListAddin.GetCheck(i));
	}
	CDialog::OnOK();
}
