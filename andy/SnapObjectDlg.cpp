// SnapObject.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "SnapObjectDlg.h"
#include "IntP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapObject dialog


CSnapObjectDlg::CSnapObjectDlg()
	: CPropertyPage(CSnapObjectDlg::IDD)
{
	//{{AFX_DATA_INIT(CSnapDlgObject)
	m_appint = FALSE;
	m_center = FALSE;
	m_endpoint = FALSE;
	m_exten = FALSE;
	m_inter = FALSE;
	m_midpoint = FALSE;
	m_nearest = FALSE;
	m_para = FALSE;
	m_perp = FALSE;
	m_snapon = FALSE;
	m_tangent = FALSE;
	m_trackingon = FALSE;
	//}}AFX_DATA_INIT
}


void CSnapObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapObjectDlg)
	DDX_Check(pDX, IDC_CHECKAPPINT, m_appint);
	DDX_Check(pDX, IDC_CHECKCENTER, m_center);
	DDX_Check(pDX, IDC_CHECKENDPOINT, m_endpoint);
	DDX_Check(pDX, IDC_CHECKEXTEN, m_exten);
	DDX_Check(pDX, IDC_CHECKINTER, m_inter);
	DDX_Check(pDX, IDC_CHECKMIDPOINT, m_midpoint);
	DDX_Check(pDX, IDC_CHECKNEAREST, m_nearest);
	DDX_Check(pDX, IDC_CHECKPARA, m_para);
	DDX_Check(pDX, IDC_CHECKPERP, m_perp);
	DDX_Check(pDX, IDC_CHECKSNAPON, m_snapon);
	DDX_Check(pDX, IDC_CHECKTANGENT, m_tangent);
	DDX_Check(pDX, IDC_CHECKTRACKINGON, m_trackingon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapObjectDlg, CDialog)
	//{{AFX_MSG_MAP(CSnapObject)
	ON_BN_CLICKED(IDC_BUTTONSELECTALL, OnButtonselectall)
	ON_BN_CLICKED(IDC_BUTTONCANCELALL, OnButtoncancelall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapObject message handlers

void CSnapObjectDlg::OnButtonselectall() 
{
	// TODO: Add your control notification handler code here
	m_appint = TRUE;
	m_center = TRUE;
	m_endpoint = TRUE;
	m_exten = TRUE;
	m_inter = TRUE;
	m_midpoint = TRUE;
	m_nearest = TRUE;
	m_para = TRUE;
	m_perp = TRUE;
	m_snapon = TRUE;
	m_tangent = TRUE;
	m_trackingon = TRUE;
	UpdateData();
	
}

void CSnapObjectDlg::OnButtoncancelall() 
{
	// TODO: Add your control notification handler code here
	m_appint = FALSE;
	m_center = FALSE;
	m_endpoint = FALSE;
	m_exten = FALSE;
	m_inter = FALSE;
	m_midpoint = FALSE;
	m_nearest = FALSE;
	m_para = FALSE;
	m_perp = FALSE;
	m_snapon = FALSE;
	m_tangent = FALSE;
	m_trackingon = FALSE;
	UpdateData();
	
}

void CSnapObjectDlg::getValue(vector<CProperty*>& val)
{
	
	val.push_back(new CIntP("appint",m_appint));
	val.push_back(new CIntP("center",m_center));
	val.push_back(new CIntP("endpoint",m_endpoint));
	val.push_back(new CIntP("exten",m_exten));
	val.push_back(new CIntP("inter",m_inter));
	val.push_back(new CIntP("midpoint",m_midpoint));
	val.push_back(new CIntP("nearest",m_nearest));
	val.push_back(new CIntP("para",m_para));
	val.push_back(new CIntP("perp",m_perp));
	val.push_back(new CIntP("snapon",m_snapon));
	val.push_back(new CIntP("tangent",m_tangent));
	val.push_back(new CIntP("trackingon",m_trackingon));
}
